#include <stdio.h>
#include <stdlib.h>

// Harita ve başlık bilgisi
typedef struct {
    int row, col;
    char empty, obst, full;
    char **grid;
} t_map;

// Printable karakter kontrolü
int is_printable(char c) {
    return (c >= 32 && c <= 126);
}

// Bellek temizliği
void free_map(t_map *map) {
    if (map->grid) {
        for (int i = 0; i < map->row; i++)
            free(map->grid[i]);
        free(map->grid);
        map->grid = NULL;
    }
}

// Başlık satırını oku (sonda newline olmasa da çalışır)
    /*
    Eski init_map fonksiyonu (fscanf ile):

    int init_map(t_map *map, FILE *file) {
        if (!file || !map)
            return 0;
        if (fscanf(file, "%d %c %c %c", &map->row, &map->empty, &map->obst, &map->full) != 4)
            return 0;
        // row 0sa ne yapmalı
        if (map->row <= 0 || !is_printable(map->empty) || !is_printable(map->obst) || !is_printable(map->full) ||
            map->empty == map->obst || map->empty == map->full || map->obst == map->full)
            return 0;
        return 1;
    }
    */

    // Güncel init_map fonksiyonu (getline ile, boşluk toleranslı)
    int init_map(t_map *map, FILE *file) {
        if (!file || !map)
            return 0;
        char *line = NULL;
        size_t len = 0;
        ssize_t read = getline(&line, &len, file);
        if (read == -1) {
            free(line);
            return 0;
        }
        if (read > 0 && line[read-1] == '\n') line[--read] = '\0';
        int i = 0;
        map->row = 0;
        while (line[i] >= '0' && line[i] <= '9') {
            map->row = map->row * 10 + (line[i] - '0');
            i++;
        }
        while (line[i] == ' ' || line[i] == '\t') i++;
        map->empty = line[i++];
        while (line[i] == ' ' || line[i] == '\t') i++;
        map->obst = line[i++];
        while (line[i] == ' ' || line[i] == '\t') i++;
        map->full = line[i++];
        free(line);
        if (map->row <= 0 || !is_printable(map->empty) || !is_printable(map->obst) || !is_printable(map->full) ||
            map->empty == map->obst || map->empty == map->full || map->obst == map->full)
            return 0;
        return 1;
    }


// Harita satırlarını oku (son satırda newline olmasa da çalışır)
int read_grid(t_map *map, FILE *file) {
    map->grid = calloc(map->row + 1, sizeof(char *));
    if (!map->grid) return 0;
    char *line = NULL;
    size_t len = 0;
    for (int i = 0; i < map->row; i++) {
        ssize_t read = getline(&line, &len, file);
        if (read == -1) {
            free(line);
            free_map(map);
            return 0;
        }
        int has_newline = (read > 0 && line[read-1] == '\n');
        if (has_newline) read--;
        if (i == 0) map->col = read;
        else if (read != map->col) {
            free(line);
            free_map(map);
            return 0;
        }
        // Satır sonunda newline kontrolü: Son satır hariç tüm satırlarda olmalı
        if (i < map->row - 1 && !has_newline) {
            free(line);
            free_map(map);
            return 0;
        }
        map->grid[i] = malloc(map->col + 1);
        if (!map->grid[i]) {
            free(line);
            free_map(map);
            return 0;
        }
        for (int j = 0; j < map->col; j++) {
            // map->empty karakteri space (' ') olabilir, bu yüzden doğrudan karşılaştırma yapılmalı
            if (line[j] != map->empty && line[j] != map->obst) {
                free(line);
                free_map(map);
                return 0;
            }
            map->grid[i][j] = line[j];
        }
        map->grid[i][map->col] = '\0';
    }
    free(line);
    map->grid[map->row] = NULL; // NULL sonlandırıcı
    return 1;
}

// DP ile en büyük kareyi bul ve işaretle
int min3(int a, int b, int c) {
    int m = a < b ? a : b;
    return m < c ? m : c;
}
void find_biggest_square(t_map *map) {
    int max_size = 0, best_top = 0, best_left = 0;
    int **dp = calloc(map->row, sizeof(int*));
    for (int i = 0; i < map->row; i++)
        dp[i] = calloc(map->col, sizeof(int));
    for (int i = 0; i < map->row; i++) {
        for (int j = 0; j < map->col; j++) {
            if (map->grid[i][j] == map->empty) {
                if (i == 0 || j == 0)
                    dp[i][j] = 1;
                else
                    dp[i][j] = 1 + min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]);
                int top = i - dp[i][j] + 1;
                int left = j - dp[i][j] + 1;
                if (dp[i][j] > max_size ||
                    (dp[i][j] == max_size && (top < best_top || (top == best_top && left < best_left)))) {
                    max_size = dp[i][j];
                    best_top = top;
                    best_left = left;
                }
            }
        }
    }
    // Kareyi işaretle (sol üst köşe ve boyut ile)
    for (int i = best_top; i < best_top + max_size; i++)
        for (int j = best_left; j < best_left + max_size; j++)
            map->grid[i][j] = map->full;
    for (int i = 0; i < map->row; i++) free(dp[i]);
    free(dp);
}

// Haritayı yazdır
void print_grid(t_map *map) {
    for (int i = 0; i < map->row; i++) {
        fputs(map->grid[i], stdout);
        fputc('\n', stdout);
    }
}

int main(int argc, char **argv) {
    if (argc == 1) {
        t_map map = {0};
        if (!init_map(&map, stdin) || !read_grid(&map, stdin)) {
            fprintf(stderr, "Error: invalid map\n");
            free_map(&map);
            return 1;
        }
        find_biggest_square(&map);
        print_grid(&map);
        free_map(&map);
    } else if (argc == 2) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Error: cannot open file\n");
            return 1;
        }
        t_map map = {0};
        if (!init_map(&map, file) || !read_grid(&map, file)) {
            fprintf(stderr, "Error: invalid map\n");
            free_map(&map);
            fclose(file);
            return 1;
        }
        find_biggest_square(&map);
        print_grid(&map);
        free_map(&map);
        fclose(file);
    } else {
        fprintf(stderr, "Error: too many arguments\n");
        return 1;
    }
    return 0;
}
