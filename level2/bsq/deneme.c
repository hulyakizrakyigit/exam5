#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef struct{
    int row,col;
    char empty, obst, full;
} map;

int min3(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

int check_grid(char **grid, int count, map *m){
    if(count - 1 != m->row)
        return 1;

    int col = strlen(grid[1]);
    if(grid[1][col - 1] == '\n')
        col--;
    m->col = col;
    for(int i = 1; i < count; i++){//kontrol
        int len = strlen(grid[i]);
        if(grid[i][len -1] == '\n')
            len--;
        if(len != m->col)
            return 1;
        for(int j = 0; j < len; j++)
            if(grid[i][j] != m->empty && grid[i][j] != m->obst)
                return 1;
    }
    return 0;
}

void fill_square(char **grid, int row, int col, int maxsize, map *m){
    for(int i = row-maxsize+1; i <=row; i++){
        for(int j = col-maxsize+1; j <= col; j++)
            grid[i][j] = m->full;
    }
}

int solve_grid(char **grid, int count, map *m){
    if(check_grid(grid,count,m))
        return 1;

    int maxsize = 0, bestrow = 0, bestcol = 0;

    int **dp = calloc(m->row, sizeof(int *));
    for(int i = 0; i < m->col; i++)
        dp[i] = calloc(m->col, sizeof(int));

    for(int i = 0; i < m->row; i++){
        for(int j = 0; j < m->col; j++){
            char c = grid[i+1][j];
            if(c == m->obst)
                dp[i][j] = 0;
            else{
                if(i == 0 || j == 0)
                    dp[i][j] = 1;
                else
                    dp[i][j] = 1 + min3(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]);
            
//kontrol
            if(dp[i][j] > maxsize){
                maxsize = dp[i][j];
                bestcol = j;
                bestrow = i;
            }}

        }
    }

    if(maxsize > 0)
        fill_square(grid, bestrow + 1, bestcol, maxsize, m);

    for(int i = 1; i < count; i++){//kontrol
        fputs(grid[i], stdout);
    }
    return 0;
}

char **read_grid(FILE *file, int *count){//kontrol
    char *line = NULL;
    size_t len = 0;
    int n = 0;
    int read;
    char **grid = NULL;

    while((read = getline(&line,&len,file)) != -1){
        char **tmp = realloc(grid, sizeof(char *) * (n+1));
        grid = tmp;
        grid[n] = line;
        line = NULL;
        n++;
    }
    free(line);
    *count = n;
    return grid;
}

int parse_fl(FILE *file, map *m){
    if(fscanf(file, "%d %c %c %c", &m->row, &m->empty, &m->obst, &m->full) != 4)
        return 1;

    if(m->row < 1)
        return 1;
    if(m->empty == m->obst || m->empty == m->full || m->obst == m->full)
        return 1;
    if(m->empty < 32 || m->empty > 126 || m->obst < 32 || m->obst > 126 || m->full < 32 || m->full > 126)
        return 1;
    return 0;
}

int process_file(char *filename){
    FILE *file = fopen(filename, "r");
    if(!file)
        return 1;
    map m;
    int count = 0; // kontrol

    if(parse_fl(file, &m))
        return 1;
    
    char **grid = read_grid(file, &count);
    fclose(file); 

    if(!grid || count == 0)
        return 1;

    int res = solve_grid(grid,count,&m);
    return res;
    
}

int process_stdin(){
    map m;
    int count = 0; // kontrol

    if(parse_fl(stdin, &m))
        return 1;
    
    char **grid = read_grid(stdin, &count); 

    if(!grid || count == 0)
        return 1;

    int res = solve_grid(grid,count,&m);
    return res;
}

int main(int ac, char **av){
    if(ac == 1){
        if(process_stdin() != 0)
            fprintf(stderr, "Error: \n");
    }
    else{
        for(int i = 1; i < ac; i++)
        {
            if(process_file(av[i]))
            fprintf(stderr, "Error : \n");
            if(i < ac - 1)
                fputs("\n", stdout);
        }
    }
}