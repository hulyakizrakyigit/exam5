#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int x;
    int y;
    int isdraw;
} pen_t;

void free_board(char **board, int h){
    if(!board)
        return;
    for(int i = 0; i < h; i++){
        free(board[i]);
    }
    free(board);
}

void print_board(char **board, int w, int h){
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            putchar(board[i][j]);
        }
        putchar('\n');
    }
}


char** create_board(int w, int h){
    if(w <= 0 || h <= 0)
        return NULL;
    char** board = malloc(sizeof(char *) * h);
    if(!board)
    return NULL;

    for(int i = 0; i < h; i++){
        board[i] = calloc(sizeof(char) , w);
    }
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++)
        board[i][j] = ' ';
    }
    return board;
}

int count_n(char **board, int i, int j, int w, int h){
    int count = 0;
    for(int x = -1; x <= 1; x++){
        for(int y = -1; y <=1; y++){
            if(x == 0 && y == 0)
                continue;
            int ny = i + y;
            int nx = j + x;
            if(nx >= 0 && ny >= 0 && ny < h && nx < w){
                if(board[ny][nx] == 'O')
                    count++;
            }
        }
    }
    return count;
}

void iter_game(char **board, int w, int h){
    char **newb = create_board(w,h);
    if(!newb)
        return;
    
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            int n = count_n(board, i, j, w, h);
            if(board[i][j] == 'O'){
                if(n == 2 || n== 3){
                    newb[i][j] = 'O';
                }
            }
            else{
                if(n == 3)
                    newb[i][j] = 'O';
            }
        }
    }
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            board[i][j] = newb[i][j];
        }
    }
    free_board(newb, h);
}

int main(int ac, char **av){
    if(ac != 4)
        return 1;
    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int iter = atoi(av[3]);

    if(w <= 0 || h <= 0 || iter < 0)
        return 1;
    
    char **board = create_board(w,h);
    if(!board)
        return 1;

    char cmd;
    pen_t pen = {0,0,0};
    while(read(0, &cmd, 1) > 0){
        switch(cmd){
        
            case 'w':
                if(pen.y > 0)
                    pen.y--;
                    break;
            case 's':
                if(pen.y < h - 1)
                    pen.y++;
                    break;
            case 'a':
                if(pen.x > 0)
                    pen.x--;
                    break;
            case 'd':
                if(pen.x < w - 1)
                    pen.x++;
                    break;
            case 'x':
                pen.isdraw = !pen.isdraw;
        }
        if(pen.isdraw)
            board[pen.y][pen.x] = 'O';
    }

    for(int i = 0; i < iter; i++){
        iter_game(board, w, h);
    }

    print_board(board, w, h);
    free_board(board,h);
    return 0;
}