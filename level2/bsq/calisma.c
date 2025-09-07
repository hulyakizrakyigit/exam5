#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct s_map{
int row;
int col;
char empty;
char obst;
char full;
char **grid;
}t_map;

int white_space(char c){
    return (c == ' ' || c == '\t'  || c == '\r' || c == '\v' || c == '\f');
}


int init_map(t_map *map, FILE *file){
    if(!file || !map)
        return 1;
    
        size_t len = 0;
        ssize_t read;
        char *line = NULL;

        read = getline(&line, &len, file);
        if (read == -1)
        {
            free(line);
            return 0;
        }
        int i = 0;
        map->row = 0;

        while(line[i] >= '0' && line[i] <= '9')
        {
            map->row = map->row * 10 + (line[i] - '0');
            i++;
        }

        if(i == 0 || map->row <= 0){
            free(line);
            return 0;
        }
        while(white_space(line[i])){
            i++;
        }

        int reaming = read - i;
        if(reaming < 3){
            free(line);
            return 0;
        }
        
        map->empty = line[i++];

        while(white_space(line[i])){
            i++;
        }

        map->obst = line[i++];

        while(white_space(line[i])){
            i++;
        }

        map->full = line[i++];

        if(!map->empty || !map->obst || !map->full || map->empty == map->obst || map->empty == map->full || map->obst == map->full){
            free(line);
            return 0;
        }
    free(line);
    return 1;
}

void free_map(t_map *map){
    if(map->grid){
        for(int i = 0; i < map->row; i++)
            if(map->grid[i])
                free(map->grid[i]);
        free(map->grid);
        map->grid = NULL;   
    }
}

int min3(int a, int b, int c){
    int result = a;
    if (b < result)
        result = b;
    if (c < result)
        result = c;
    return (result);
}

void find_biggest_square(t_map * map){
    int max_size = 0;
    int best_left = 0;
    int best_top = 0;

    int **dp = calloc(map->row, sizeof(int *));
    for(int i = 0; i < map->row; i++){
        dp[i] = calloc(map->col, sizeof(int));
    }

    for(int i = 0; i < map->row; i++){
        for(int j = 0; j < map->col; j++){
            if(map->grid[i][j] == map->empty){
                if(i == 0 || j == 0)
                    dp[i][j] = 1;
                else{
                    dp[i][j] = 1 + min3(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
                }

                int top = i - dp[i][j] + 1;
                int left = j - dp[i][j] + 1;

                if(dp[i][j] > max_size || (dp[i][j] == max_size && top < best_top) || (dp[i][j] == max_size && top == best_top && left < best_left)){
                    max_size = dp[i][j];
                    best_top = top;
                    best_left = left;
                } 
            }
        }
    }

    if(max_size == 0){
        for(int i = 0; i < map->row && max_size == 0; i++){
            for(int j = 0; j < map->col; j++){
                if(map->grid[i][j] == map->empty){
                    max_size = 1;
                    best_top = i;
                    best_left = j;
                    break;
                }
            }
        }
    }

    for(int i = best_top; i < best_top + max_size; i++){
        for(int j = best_left; j < best_left + max_size; j++){
            map->grid[i][j] = map->full;
        }
    }

    for(int i = 0; i < map->row; i++)
        free(dp[i]);
    free(dp);

}

void print_grid(t_map *map){
    if(!map || !map->grid)
        return;

    for(int i = 0; i < map->row; i++){
        printf("%s\n", map->grid[i]);
    }
}



int read_grid(t_map *map, FILE *file){
    if(!map || !file)
        return 0;

    size_t len = 0;
    ssize_t read;
    char *line = NULL;
    int row = 0;

    map->grid = calloc(map->row, sizeof(char *));
    if(!map->grid)
        return 0;

    while((read = getline(&line, &len, file)) != -1 && row < map->row ){
        if(row == 0)
            map->col = read - 1;
        else if(read - 1 != map->col){
            free(line);
            return 0;
            }

        map->grid[row] = malloc(sizeof(char) * map->col + 1);

        if(!map->grid[row]){
            free(line);
            return 0;
        }

        for(int col = 0; col < map->col; col++){
            if(line[col] != map->empty && line[col] != map->obst){
                free(line);
                return 0;
            }
            map->grid[row][col] = line[col];
        }
        map->grid[row][map->col] = '\0';
        row++;
    }
    free(line);
    return (row == map->row);
}

int main(int ac, char **av){
    if(ac == 1){
        t_map map = {0};

        if(!init_map(&map, stdin) || !read_grid(&map, stdin)){
            fprintf(stderr, "map error\n");
            free_map(&map);
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
            else {
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