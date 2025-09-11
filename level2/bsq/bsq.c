#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

/*
 * This program supports both formats for the first line of the map:
 * - Combined:   9.ox
 * - Spaced:     9 . o x
 * The parser will correctly extract the row count and the three map characters in both cases.
 */

typedef struct s_map {
    int row;
    int col;
    char empty;
    char obst;
    char full;
    char **grid;
} t_map;

// Helper function to check if character is whitespace (excluding newline for first line parsing)
int is_whitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\r' || 
            c == '\v' || c == '\f');
}

// Helper function to check if character is printable
int is_printable(char c) {
    return (c >= 32 && c <= 126);
}

int init_map(t_map *map, FILE *file) {
    if (!file || !map)
        return (0);
    
    char *line = NULL;
    size_t len = 0;
    
    if (getline(&line, &len, file) == -1) {
        free(line);
        return (0);
    }
    
    // Parse: "9.ox" or "9 . o x" format
    char *ptr = line;
    map->row = 0;
    
    // Manual string to integer conversion
    while (*ptr >= '0' && *ptr <= '9') {
        map->row = map->row * 10 + (*ptr - '0');
        ptr++;
    }
    
    if (map->row <= 0) {
        free(line);
        return (0);
    }
    
    // Skip whitespace and parse 3 characters
    while (is_whitespace(*ptr)) ptr++;
    map->empty = *ptr++;
    while (is_whitespace(*ptr)) ptr++;
    map->obst = *ptr++;
    while (is_whitespace(*ptr)) ptr++;
    map->full = *ptr;
    
    free(line);
    
    // Validate: all different, non-null, and printable
    return (map->empty && map->obst && map->full && 
            map->empty != map->obst && map->empty != map->full && map->obst != map->full &&
            is_printable(map->empty) && is_printable(map->obst) && is_printable(map->full));
}

/*
 * Eğer sadece birleşik format (ör: 9.ox) desteklenecekse,
 * init_map fonksiyonu aşağıdaki gibi çok daha basit yazılabilir:
 *
 * int init_map_compact(t_map *map, FILE *file) {
 *     if (!file || !map)
 *         return 0;
 *     char *line = NULL;
 *     size_t len = 0;
 *     if (getline(&line, &len, file) == -1) {
 *         free(line);
 *         return 0;
 *     }
 *     // Satır sayısını oku
 *     int i = 0;
 *     map->row = 0;
 *     while (line[i] >= '0' && line[i] <= '9') {
 *         map->row = map->row * 10 + (line[i] - '0');
 *         i++;
 *     }
 *     // Karakterler
 *     map->empty = line[i++];
 *     map->obst  = line[i++];
 *     map->full  = line[i++];
 *     free(line);
 *     // Karakterlerin farklı ve printable olması kontrolü eklenmeli
 *     return (map->row > 0 && map->empty && map->obst && map->full &&
 *             map->empty != map->obst && map->empty != map->full && map->obst != map->full &&
 *             is_printable(map->empty) && is_printable(map->obst) && is_printable(map->full));
 * }
 */

int read_grid(t_map *map, FILE *file) {
    if (!map || !file)
        return (0);
    
    map->grid = calloc(map->row, sizeof(char *));
    if (!map->grid)
        return (0);
    
    char *line = NULL;
    size_t len = 0;
    int has_empty = 0; // Track if we have at least one empty space
    
    for (int i = 0; i < map->row; i++) {
        ssize_t read = getline(&line, &len, file);
        if (read == -1) {
            free(line);
            return (0);
        }
        
        // Check if line ends with newline (except possibly the last line)
        if (read > 0 && line[read-1] != '\n') {
            free(line);
            return (0);
        }
        
        // Set column count from first row, validate others
        if (i == 0)
            map->col = read - 1;
        else if (read - 1 != map->col) {
            free(line);
            return (0);
        }
        
        // Check minimum size
        if (map->col <= 0) {
            free(line);
            return (0);
        }
        
        // Allocate and copy line (removing newline)
        map->grid[i] = malloc(map->col + 1);
        if (!map->grid[i]) {
            free(line);
            return (0);
        }
        
        // Copy and validate characters in one loop
        for (int j = 0; j < map->col; j++) {
            if (line[j] != map->empty && line[j] != map->obst) {
                free(line);
                return (0);
            }
            if (line[j] == map->empty)
                has_empty = 1;

            map->grid[i][j] = line[j];
        }
        map->grid[i][map->col] = '\0';
    }
    
    free(line);
    
    // Check if we have at least one empty space
    if (!has_empty) {
        return (0);
    }
    
    return (1);
}

void free_map(t_map *map) {
    if (map->grid) {
        for (int i = 0; i < map->row; i++) {
            if (map->grid[i])
                free(map->grid[i]);
        }
        free(map->grid);
        map->grid = NULL;
    }
}

int min3(int a, int b, int c) {
    int result = a;
    if (b < result)
        result = b;
    if (c < result)
        result = c;
    return (result);
}

void find_biggest_square(t_map *map) {
    int max_size = 0;
    int best_top = 0;
    int best_left = 0;
    
    int **dp = calloc(map->row, sizeof(int *));
    for (int i = 0; i < map->row; i++) {
        dp[i] = calloc(map->col, sizeof(int));
    }
    
    // Fill DP table
    for (int i = 0; i < map->row; i++) {
        for (int j = 0; j < map->col; j++) {
            if (map->grid[i][j] == map->empty) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = 1 + min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]);
                }
                
                // Check if this square is better
                // Priority: 1) Larger size 2) Higher position 3) Leftmost position
                int top = i - dp[i][j] + 1;
                int left = j - dp[i][j] + 1;
                
                if (dp[i][j] > max_size ||
                    (dp[i][j] == max_size && top < best_top) ||
                    (dp[i][j] == max_size && top == best_top && left < best_left)) {
                    max_size = dp[i][j];
                    best_top = top;
                    best_left = left;
                }
            }
        }
    }
    
    // If no square found, find first empty cell for 1x1 square
    if (max_size == 0) {
        for (int i = 0; i < map->row && max_size == 0; i++) {
            for (int j = 0; j < map->col; j++) {
                if (map->grid[i][j] == map->empty) {
                    max_size = 1;
                    best_top = i;
                    best_left = j;
                    break;
                }
            }
        }
    }
    
    // Fill the best square
    for (int i = best_top; i < best_top + max_size; i++) {
        for (int j = best_left; j < best_left + max_size; j++) {
            map->grid[i][j] = map->full;
        }
    }
    
    // Free DP table
    for (int i = 0; i < map->row; i++)
        free(dp[i]);
    free(dp);
}

void print_grid(t_map *map) {
    if (!map || !map->grid)
        return;
    
    for (int i = 0; i < map->row; i++) {
        fputs(map->grid[i], stdout);
        fputs("\n", stdout);
    }
}

int main(int ac, char **av) {
    if (ac == 1) {
        t_map map = {0};
        if (!init_map(&map, stdin) || !read_grid(&map, stdin)) {
            fprintf(stderr, "Error: invalid map\n");
            free_map(&map);
            return (1);
        }
        find_biggest_square(&map);
        print_grid(&map);
        free_map(&map);
        return (0);
    } else {
        for (int i = 1; i < ac; i++) {
            t_map map = {0};
            FILE *file = fopen(av[i], "r");
            if (!file) {
                fprintf(stderr, "Error: cannot open file\n");
                continue;
            }
            if (!init_map(&map, file) || !read_grid(&map, file)) {
                fprintf(stderr, "Error: invalid map\n");
                free_map(&map);
                fclose(file);
            } else {
                find_biggest_square(&map);
                print_grid(&map);
                free_map(&map);
                fclose(file);
            }
            if (i < ac - 1)
                fputs("\n", stdout);
        }
        return (0);
    }
}
