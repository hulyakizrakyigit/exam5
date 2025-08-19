#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"

typedef struct {
    int x;
    int y;
    int is_draw;
} Pen;

char **create_board(int w, int h) {
    char **board = malloc(sizeof(char *) * h);
    for (int i = 0; i < h; i++){
        board[i] = calloc(sizeof(char), w);
        for (int j = 0; j < w; j++)
            board[i][j] = ' ';
    }
    return board;
}

void free_board(char **board, int h){
    for(int i = 0; i < h; i++){
        free (board[i]);
    }
    free (board);
}

int neighbour_c(char **board, int y, int x, int w, int h){
    int count = 0;
    for ( int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++){
            if (j == 0 && i == 0)
                continue;
            int new_x = x + j;
            int new_y = y + i;
            if(new_x >= 0 && new_x < w && new_y >= 0 && new_y < h) {
                if(board[new_y][new_x] == 'O')
                    count++;
            }
        }
    }
    return (count);
}

void iter_game(char **board, int w, int h){
    char **new_board = create_board(w,h);
    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++)
        {
            int count = neighbour_c(board, y,x, w, h);
            if(board[y][x] == 'O') {
                if(count == 2 || count == 3)
                    new_board[y][x] = 'O';
            }
            else {
                if (count == 3)
                    new_board[y][x] = 'O';
            }
        }
    }

    for (int i = 0; i < h;i++){
        for(int j = 0; j < w; j++)
            board[i][j] = new_board[i][j];
    }
    free_board(new_board, h);
}

void print_board(char **board, int w, int h)
{
    for(int i = 0; i< h; i++)
    {
        for(int j = 0; j < w; j++)
            putchar(board[i][j]);
        putchar('\n');
    }
    return ;
}

int main(int ac, char **av) {
    if (ac != 4)
        return (1);
    
    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int iter = atoi(av[3]);

    char **board = create_board(w,h);
    Pen pen = {0,0,0};

    char command;

    while(read(0, &command,1) > 0){
        switch(command) {
            case 'w':
            if (pen.y > 0)
                pen.y--;
            if (pen.is_draw)
                board[pen.y][pen.x] = 'O';
            break;

            case 's':
            if (pen.y < h - 1)
                pen.y++;
            if(pen.is_draw)
                board[pen.y][pen.x] = 'O';
            break;

            case 'a':
            if (pen.x > 0)
                pen.x--;
            if(pen.is_draw)
                board[pen.y][pen.x] = 'O';
            break;

            case 'd':
            if(pen.x < w - 1)
                pen.x++;
            if(pen.is_draw)
                board[pen.y][pen.x] = 'O';
            break;

            case 'x':
            pen.is_draw = !pen.is_draw;
            if(pen.is_draw)
                board[pen.y][pen.x] = 'O';
            break;
        }
    }

    // print_board(board, w, h);
    for(int i = 0; i < iter; i++)
        iter_game(board, w, h);
    print_board(board, w, h);
    free_board(board, h);

    return (0);

}
