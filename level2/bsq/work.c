#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

typedef struct{
    int row;
    int col;
    char empty;
    char obst;
    char full;
    char** grid;
} t_map;

void find_biggest_square(t_map *map){
    int maxsize = 0;
    int besttop = 0;
    int bestleft = 0;

    int** dp = calloc(sizeof(int *), map->row);
    for(int i = 0; i < map->row; i++)
        dp[i] = calloc(sizeof(int), map->col);
    
    for(int i = 0; i < map->row; i++){
        for(int j = 0; j < map->col; j++){
            if(map->grid[i][j] == map->empty){
                if(i == 0 || j == 0){
                    dp[i][j] = 1
                }
                else{
                    dp[i][j] = 1 + min3();
                }

                int top = i - dp[i][j] + 1;
                int left = j - dp[i][j] + 1;

                if()
            }
        }
    }
}

int read_grid(t_map *map, FILE *file){
    if(!map || !file)
        return 0;

    map->grid = calloc(sizeof(char*), map->row);
    if(!map->grid)
        return 0;
    char *line= NULL;
    size_t len = 0;
    int has_empty = 0;

    for(int i = 0; i< map->row; i++){
        ssize_t read = getline(&line, len, file);
        if(read == -1)
            return 0;

        if(read > 0  line[read -1] != '\n')
        {
            free(line);
            return 0;
        }

        if(i == 0)
            map->col = read - 1;
        else if(read -1 != map->col){
             free(line);
            return 0;
        }

        if(map->col <= 0){
             free(line);
            return 0;
        }

        for(int j = 0; j < map->col; j++){
            if(line[j] != map->empty && line[j] != map->obst){
                free(line);
                return 0;
            }
            if(map->grid[i][j] == map->empty)
                has_empty = 1;
            map->grid[i][j] = line[j];
        }
        map->grid[i][map->col]= '\0';
    }
    if(!has_empty)
        return 0;
    free(line);
    return 1;
}

int init_map(t_map *map, FILE *file){
    if(!map || !file)
        return 0;
    
    char *line= NULL;
    size_t len = 0;
    if(getline(&line, len, file) == -1){
        free(line);
        return 0;
    }

    char *ptr = line;
    map->row = 0;

    while((*ptr) >= 0 && (*ptr) <= 9){
        map->row = map->row * 10 + (*ptr - '0');
        ptr++;
    }

    if(map->row <= 0){
        free(line);
        return 0;

    }

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

int main(int ac, char **av){
    if(ac == 1){
    t_map map = {0};
    if(!init_map(&map, stdin) || !read_grid(&map,stdin)){
        fprintf(stderr, "map error\n");
        return 1;
    }
    else{
        find_biggest_square(&map);
        print_grid(&map);
        free_map(&map);
        return 0;
    }
    }
    else{
        for(int i = 1; i < ac; i++){
            t_map map = {};
            FILE *file = fopen(av[i], "r");
            if(file){
                fprintf(stderr, "map error\n");
                continue;;
            }
            if(!init_map(&map, file) || !read_grid(&map,file)){
            fprintf(stderr, "map error\n");
            free_map(&map);
            fclose(file);
                return 1;
    }
    else{
        find_biggest_square(&map);
        print_grid(&map);
        free_map(&map);
        fclose(file);
        return 0;
    }
            
                if(i < ac -1)
                    printf("\n");
            
        }
    }
    return 0;
}