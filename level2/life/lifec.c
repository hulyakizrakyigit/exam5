#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int x;
    int y;
    int is_draw;
} pen_t;

char **create_board(int w, int h) {
    char **board = malloc(sizeof(char *) * h);
    for (int i = 0; i < h; i++) {
        board[i] = calloc(sizeof(char), w);
        for (int j = 0; j < w; j++)
            board[i][j] = ' ';
    }
    return board;
}

void free_board(char **board, int h) {
    for (int i = 0; i < h; i++)
        free(board[i]);
    free(board);
}

int count_neighbors(char **board, int y, int x, int w, int h) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
                continue;
            int ny = y + i;
            int nx = x + j;
            if (nx >= 0 && nx < w && ny >= 0 && ny < h)
                if (board[ny][nx] == 'O')
                    count++;
        }
    }
    return count;
}

void iter_game(char **board, int w, int h) {
    char **new_board = create_board(w, h);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int n = count_neighbors(board, y, x, w, h);
            if (board[y][x] == 'O') {
                if (n == 2 || n == 3)
                    new_board[y][x] = 'O';
            } else {
                if (n == 3)
                    new_board[y][x] = 'O';
            }
        }
    }
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            board[y][x] = new_board[y][x];
    free_board(new_board, h);
}

void print_board(char **board, int w, int h) {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++)
            putchar(board[y][x]);
        putchar('\n');
    }
}

int main(int ac, char **av) {
    if (ac != 4)
        return 1;

    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int iter = atoi(av[3]);

    char **board = create_board(w, h);
    pen_t pen = {0, 0, 0};
    char cmd;

    while (read(0, &cmd, 1) > 0) {
        if (pen.is_draw)
            board[pen.y][pen.x] = 'O';

        switch (cmd) {
            case 'w': if (pen.y > 0) pen.y--; break;
            case 's': if (pen.y < h - 1) pen.y++; break;
            case 'a': if (pen.x > 0) pen.x--; break;
            case 'd': if (pen.x < w - 1) pen.x++; break;
            case 'x': pen.is_draw = !pen.is_draw;
                      if (pen.is_draw)
                          board[pen.y][pen.x] = 'O';
                      break;
        }
    }

    for (int i = 0; i < iter; i++)
        iter_game(board, w, h);

    print_board(board, w, h);
    free_board(board, h);
    return 0;
}
