#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct{
    int row;
    int col;
    char empty;
    char obst;
    char full;
    char** grid;
} t_map;

int issspace(char c){
    return (c == ' ' || c == '\r' || c == '\t' || c == '\v' || c == '\f');
}

void print_grid(t_map *map){
    if(!map || !map->grid)
        return;
    for(int i = 0; i < map->row; i++){
        printf("%s\n", map->grid[i]);
    }
}

void free_map(t_map *map){
    if(!map)
        return;
    for(int i = 0; i < map->row; i++){
            free(map->grid[i]);
    }
    free(map->grid);
}

int min3(int a, int b, int c){
    int res = a;
    if(b < a)
        res = b;
    if(c < b)
        res = c;
    return res;
}

int read_grid(t_map *map, FILE *file){
    if(!map || !file)
        return 0;
    map->grid = calloc(map->row, sizeof(char *));
    if(!map->grid)
        return 0;
    
    size_t len = 0;
    char *line = NULL;
    int has_empty = 0;

    for(int i = 0; i < map->row; i++){
        ssize_t read = getline(&line, &len, file);
        if(!read){
            free(line);
            return 0;
        }

        if(read > 0 && line[read - 1] != '\n'){
            free(line);
            return 0;
        }

        if(i == 0)
            map->col = read - 1;
        else if(read - 1 != map->col){
            free(line);
            return 0;
        }

        if(map->col <= 0){
            free(line);
            return 0;
        }

        map->grid[i] = malloc(map->col + 1);
        if(!map->grid[i]){
            free(line);
            return 0;
        }

        for(int j = 0; j < map->col; j++){
            if(line[j] != map->empty && line[j] != map->obst){
                free(line);
                return 0;
            }
            if(line[j] == map->empty)
                has_empty = 1;
            map->grid[i][j] = line[j];  // Düzeltildi: = (atama)
        }
        map->grid[i][map->col] = '\0';
    }
    free(line);

    if(!has_empty)
        return 0;
    
    return 1;
}

int isprintable(char c){
    return c >= 32 && c <= 126;
}

void find_biggest_square(t_map *map){
    printf("DEBUG: Starting find_biggest_square\n");
    int maxsize = 0;
    int best_top = 0;
    int best_left = 0;

    int **dp = calloc(map->row, sizeof(int *));
    for(int i = 0; i < map->row; i++){
        dp[i] = calloc(map->col, sizeof(int));
    }

    for(int i = 0; i < map->row; i++){
        for(int j = 0; j < map->col; j++){
            if(map->grid[i][j] == map->empty){
                if(i == 0 || j == 0){
                    dp[i][j] = 1;
                }
                else{
                    dp[i][j] = 1 + min3(dp[i - 1][j], dp[i][j-1], dp[i-1][j-1]);
                }
            
        
            int top = i - dp[i][j] + 1;
            int left = j - dp[i][j] + 1;

            if(dp[i][j] > maxsize || dp[i][j] == maxsize && top < best_top || dp[i][j] == maxsize && top == best_top && left < best_left){
                maxsize = dp[i][j];
                best_left = left;
                best_top = top;
            }
        }
    }
        
    }

    if(maxsize == 0){
        for(int i = 0; i < map->row && maxsize == 0; i++){
            for(int j = 0; j < map->col; j++){
            if(map->grid[i][j] == map->empty){
                maxsize = 1;
                best_left = j;
                best_top = i;
                break;
            }
        }
    }
}

    for(int i = best_top; i < best_top + maxsize; i++){
        for(int j = best_left; j < best_left + maxsize; j++){
            map->grid[i][j] = map->full;
        }
    }
    
    // Debug: Print what we found
    printf("DEBUG: maxsize=%d, best_top=%d, best_left=%d\n", maxsize, best_top, best_left);
   
    // Free DP table
    for (int i = 0; i < map->row; i++)
        free(dp[i]);
    free(dp);
}


int init_map(t_map *map, FILE *file){
    if(!map || !file)
        return 0;

    char *line = NULL;
    size_t len = 0;
   if(getline(&line, &len,file) == -1){
    free(line);
    return 0;
   }

   char *ptr = line;
   map->row = strtol(ptr, &ptr, 10);

   if(map->row <= 0){
    free(line);
    return 0;
   }

   while(issspace(*ptr))
        ptr++;
    map->empty = *ptr++;
    while(issspace(*ptr))
        ptr++;
    map->obst = *ptr++;
    while(issspace(*ptr))
        ptr++;
    map->full = *ptr;


    free(line);

    return (map->empty && map->obst && map->full && map->empty != map->obst && map->empty != map->full && map->obst != map->full && isprintable(map->empty) && isprintable(map->obst) && isprintable(map->full));
}

int main(int ac, char **av){
    if(ac == 1){
        t_map map = {0};
        if(!init_map(&map, stdin) || !read_grid(&map,stdin)){
            fprintf(stderr, "map error\n");
            return 1;
        }
        find_biggest_square(&map);
        print_grid(&map);
        free_map(&map);
        return 0;
    }
    else{
        for(int i = 1; i < ac; i++){
            t_map map = {0};
            FILE *file = fopen(av[i], "r");
            if(!file){
                fprintf(stderr, "map error\n");
                continue;
            }

            if(!init_map(&map, file) || !read_grid(&map, file)){
                fprintf(stderr, "map error\n");
                free_map(&map);
                fclose(file);
            }
            else{
                printf("DEBUG: About to call find_biggest_square\n");
                find_biggest_square(&map);
                print_grid(&map);
                free_map(&map);
                fclose(file);
            }

            if(i < ac - 1)
                printf("\n");
        }
    }
    return 0;
}