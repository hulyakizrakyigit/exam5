// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include <unistd.h>

// typedef struct s_map {
// int row;
// int col;
// char empty;
// char obst;
// char full;
// char **grid;
// } t_map;

// int init_map(t_map *map, FILE *file)
// {
//     if(!file || !map)
//         return 0;
    
//         size_t len = 0;
//         char *line = NULL;
//         ssize_t read;

//         read = getline(&line, &len, file);
//         if (read == -1)
//         {
//             free(line);
//             return 0;
//         }

//         int i = 0;
//         map->row = 0;
//         while (line[i] >= '0' && line[i] <= '9')
//         {
//             map->row = map->row * 10 + (line[i] - '0');
//             i++;
//         }

//         if (i == 0 || map->row <= 0 || read < i + 3)
//         {
//             free(line);
//             return 0;
//         }

//         map->empty = line[i++];
//         map->obst = line[i++];
//         map->full = line[i++];

//         if(!map->empty || !map->obst || !map->full || map->empty == map->obst || map->empty == map->full || map->obst == map->full) {
//             free(line);
//             return 0;
//         }

//     free(line);
//     return 1;
// }

// int read_grid(t_map *map, FILE *file) {
//     if (!map || !file)
//         return 0;
    
//         size_t len = 0;
//         ssize_t read;
//         char *line = NULL;
//         int row = 0;

//         map->grid = calloc(map->row, sizeof(char *));
//         if(!map->grid)
//             return 0;
        
//         while((read = getline(&line, &len, file)) != -1 && row < map->row){
//             if (row == 0)
//                 map->col = read - 1;
//             else if(read - 1 != map->col){
//                 free(line);
//                 return 0;
//             }

//             map->grid[row] = malloc(sizeof(char) * map->col + 1);
//             if(!map->grid[row]){
//                 free(line);
//                 return 0;
//             }

//             for(int col = 0; col < map->col; col++)
//             {
//                 if(line[col] != map->empty && line[col] != map->obst){
//                     free(line);
//                     return 0;
//                 }
//                 map->grid[row][col] = line[col];
//             }
//             map->grid[row][map->col] = '\0';
//             row++; 
//         }
//         free(line);
//         return (row == map->row);
// }
// int min3(int a, int b, int c){
//     int res = a;
//     if (b < res)
//         res = b;
//     if(c < res)
//         res = c;
//     return res;
// }

// void find_biggest_square(t_map *map) {
//     int max_i = 0, max_j = 0, max_size = 0;

//     int **dp = calloc(map->row, sizeof(int *));
//     for (int i = 0; i < map->row; i++)
//         dp[i] = calloc(map->col, sizeof(int));

//     for (int i = 0; i < map->row; i++) {
//         for (int j = 0; j < map->col; j++) {
//             if (map->grid[i][j] == map->empty) {
//                 if (i == 0 || j == 0)
//                     dp[i][j] = 1;
//                 else
//                     dp[i][j] = 1 + min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]);

//                 if (dp[i][j] > max_size) {
//                     max_size = dp[i][j];
//                     max_i = i;
//                     max_j = j;
//                 }
//             } else {
//                 dp[i][j] = 0;
//             }
//         }
//     }

//     // En büyük kareyi doldur
//     for (int i = max_i - max_size + 1; i <= max_i; i++) {
//         for (int j = max_j - max_size + 1; j <= max_j; j++) {
//             map->grid[i][j] = map->full;
//         }
//     }

//     // dp matrisini temizle
//     for (int i = 0; i < map->row; i++)
//         free(dp[i]);
//     free(dp);
// }


// void print_grid(t_map *map){
//     if(!map || !map->grid)
//         return;
//     for(int i = 0; i < map->row; i++)
//         fprintf(stdout, "%s\n", map->grid[i]);
// }

// void free_map(t_map *map){
//     if(map->grid){
//         for(int i = 0; i < map->row; i++)
//             free(map->grid[i]);
//         free(map->grid);
//     }
// }



// void solve_bsq(FILE *file){

//     t_map map = {0};
//     if(!(init_map(&map, file) || !read_grid(&map, file)))
//     {
//         fprintf(stderr, "map error\n");
//         free_map(&map);
//         return;
//     }
//     find_biggest_square(&map);
//     print_grid(&map);
//     free_map(&map);
// }

// int main(int ac, char **av) {
//     if (ac == 1) {
//         solve_bsq(stdin);
//     }
//     else{
//         for(int i = 1; i < ac; i++){
//             FILE *file = fopen(av[i], "r");
//             if(!file)
//                 fprintf(stderr, "map error\n");
//             else {
//                 solve_bsq(file);
//                 fclose(file);
//             }

//             if(i < ac -1)
//                 fprintf(stdout, "\n");
//         }
//     }
//   return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Global variables - simple and clean
char **map;
int rows, cols;
char empty_char, obstacle_char, full_char;

// Get string length
int ft_strlen(char *str) {
    int len = 0;
    while (str[len])
        len++;
    return len;
}

// Parse the first line to get map info
int parse_first_line(char *line) {
    int len = ft_strlen(line);
    if (len < 4) return 0;
    
    // Remove newline
    if (line[len - 1] == '\n') line[len - 1] = '\0';
    len--;
    
    // Last 3 characters are empty, obstacle, full
    full_char = line[len - 1];
    obstacle_char = line[len - 2];
    empty_char = line[len - 3];
    
    // Rest is number of rows
    line[len - 3] = '\0';
    rows = atoi(line);
    
    // Check validity
    return (rows > 0 && empty_char != obstacle_char && 
            empty_char != full_char && obstacle_char != full_char);
}

// Read the entire map
int read_map(FILE *file) {
    char *line = NULL;
    size_t len = 0;
    
    map = malloc(rows * sizeof(char*));
    
    for (int i = 0; i < rows; i++) {
        if (getline(&line, &len, file) == -1) return 0;
        
        // Remove newline
        int line_len = ft_strlen(line);
        if (line[line_len - 1] == '\n') line[line_len - 1] = '\0';
        
        // Set columns from first row
        if (i == 0) cols = ft_strlen(line);
        else if (ft_strlen(line) != cols) return 0;
        
        // Copy the line
        map[i] = malloc(cols + 1);
        strcpy(map[i], line);
    }
    
    if (line) free(line);
    return 1;
}

// Check if we can place a square of given size at position
int can_place_square(int row, int col, int size) {
    if (row + size > rows || col + size > cols) return 0;
    
    for (int i = row; i < row + size; i++) {
        for (int j = col; j < col + size; j++) {
            if (map[i][j] != empty_char) return 0;
        }
    }
    return 1;
}

// Find and place the biggest square
void find_biggest_square() {
    int max_size = 0;
    int best_row = 0, best_col = 0;
    
    // Try every position and every size
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int size = max_size + 1; size <= rows && size <= cols; size++) {
                if (can_place_square(i, j, size)) {
                    max_size = size;
                    best_row = i;
                    best_col = j;
                } else {
                    break; // Can't go bigger from this position
                }
            }
        }
    }
    
    // Fill the biggest square
    for (int i = best_row; i < best_row + max_size; i++) {
        for (int j = best_col; j < best_col + max_size; j++) {
            map[i][j] = full_char;
        }
    }
}

// Print the final map
void print_map() {
    for (int i = 0; i < rows; i++) {
        printf("%s\n", map[i]);
    }
}

// Free the map memory
void free_map() {
    if (map) {
        for (int i = 0; i < rows; i++) {
            if (map[i]) free(map[i]);
        }
        free(map);
        map = NULL;
    }
}

// Solve one BSQ file
void solve_bsq(FILE *file) {
    char *line = NULL;
    size_t len = 0;
    
    // Read first line
    if (getline(&line, &len, file) == -1 || !parse_first_line(line)) {
        fprintf(stderr, "map error\n");
        if (line) free(line);
        return;
    }
    free(line);
    
    // Read map
    if (!read_map(file)) {
        fprintf(stderr, "map error\n");
        free_map(); // Free any allocated memory
        return;
    }
    
    // Find and place biggest square
    find_biggest_square();
    
    // Print result
    print_map();
    
    // Free memory
    free_map();
}

int main(int argc, char **argv) {
    if (argc == 1) {
        // Read from stdin
        solve_bsq(stdin);
    } else {
        // Read from files
        for (int i = 1; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (!file) {
                fprintf(stderr, "map error\n");
                continue;
            }
            solve_bsq(file);
            fclose(file);
            if (i < argc - 1) printf("\n");
        }
    }
    return 0;
}