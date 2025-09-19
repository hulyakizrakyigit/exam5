#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

char **create_board(int w, int h){
    char **board = malloc(sizeof(char *) * h);
    for(int i = 0;i < h; i++){
        board[i] = malloc(sizeof(char) * (w + 1 )); //kontrol
        for(int j = 0; j < w; j++)
            board[i][j] = ' ';
        board[i][w] = '\0';
    }
    return board;
}

int cn(char **board, int w, int h, int x, int y){
    int count = 0;
    for(int i = y -1; i <= y+1; i++){
        for(int j = x-1; j <= x+1; j++){
            if(i == y && j == x)
                continue;
            //kontrol
            if(i >= 0 && j >= 0 && i < h && j < w && board[i][j] == 'o')
                count++;
        }
    }
    return count;
}

void iter_game(char **board, int w, int h){

    char **newb = create_board(w,h);

    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            int n = cn(board, w, h, j, i);
            if(board[i][j] == 'o'){
                if(n == 2 || n== 3)
                    newb[i][j] = 'o';
            }
            else{
                if(n== 3)
                    newb[i][j] = 'o';
            }
        }
    }
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++)
            board[i][j] = newb[i][j];
    }
}

int main(int ac, char **av){
    if(ac != 4)
        return 1;
    
    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int iter = atoi(av[3]);

    char cmd;

    int x = 0, y = 0, isdraw = 0;

    char **board = create_board(w,h);

    while(read(0,&cmd,1) > 0){
        if(cmd == 'x')
            isdraw = !isdraw;
        if(cmd == 'a')
            x--;
        if(cmd == 'd')
            x++;
        if(cmd == 'w')
            y--;
        if(cmd == 's')
            y++;

        if(isdraw && x >= 0 && y >= 0 && x < w && y < h)
            board[y][x] = 'o';

        
        }
        for(int i = 0; i < iter; i++)
            iter_game(board,w,h);

        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
                putchar(board[i][j]);
            putchar('\n');

    }
}

