#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
    int w;
    int h;
    int is_draw;
} pen_t;

void free_board(char **board, int h){
    if(!board)
        return;
    for(int i = 0; i < h; i++){
        free(board[i]);
    }
    free(board);
}

int count_neighbour(char **board, int y, int x , int w, int h){
    int count = 0;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if(i == 0 && j == 0)
                continue;
            int ny = y + i;
            int nx = x + j;
            if(nx >= 0 && nx < w && ny >= 0 && ny < h)
                if(board[ny][nx] == 'O')
                    count++;
        }
    }
    return count;
}


char** create_board(int w, int h){
    char **board = malloc(sizeof(char *) * h);
    if(!board)
        return NULL;
    
    for(int i = 0; i < h; i++){
        board[i] = calloc(sizeof(char), w + 1);  // +1 for null terminator
        if(!board[i]){
        for(int j = 0; j < i; j++){
            free(board[j]);
        free(board);
        return  NULL;
        }}
        for(int j = 0; j < w; j++){
            board[i][j] = ' ';
        }
        board[i][w] = '\0';  // Null terminate string
    }
    return board;
}

void iter_game(char **board, int w, int h){
    char **newboard = create_board(w,h);
    if(!newboard)
        return;
    
    for(int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){
            int n = count_neighbour(board, y, x, w, h);

            if(board[y][x] == 'O'){
                if(n == 2 || n == 3)
                    newboard[y][x] = 'O';
            }
            else{
                if(n == 3)
                    newboard[y][x] = 'O';
            }
        }
        newboard[y][w] = '\0';  // Null terminate each row
    }
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            board[y][x] = newboard[y][x];
        }
    }
    free_board(newboard, h);
}

void print_board(char **board, int w, int h){
    for(int y = 0; y < h; y++){
        // Bu satırda ilk 'O'yu bul (left trim için)
        int first_O = -1;
        for(int x = 0; x < w; x++){
            if(board[y][x] == 'O'){
                first_O = x;
                break;
            }
        }
        
        // Eğer satırda O varsa, ilk O'dan başlayarak bas
        if(first_O >= 0){
            int prev_space = 0;
            for(int x = first_O; x < w; x++){
                if(board[y][x] == ' '){
                    if(!prev_space){  // Sadece ilk space'i bas
                        putchar(' ');
                        prev_space = 1;
                    }
                } else {
                    putchar(board[y][x]);  // 'O' bas
                    prev_space = 0;
                }
            }
        }
        putchar('\n');
    }
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
    
    pen_t pen = {0,0,0};
    char cmd;

    while(read(0, &cmd, 1) > 0){
        switch(cmd){
            case 'w':
                if(pen.h > 0)
                    pen.h--;
                break;
            case 's':
                if(pen.h < h - 1)
                    pen.h++;
                break;
            case 'a':
                if(pen.w > 0)
                    pen.w--;
                break;
            case 'd':
                if(pen.w < w - 1)
                    pen.w++;
                break;
            case 'x':
                pen.is_draw = !pen.is_draw;
                break;
        }
        
        // Hareket SONRASI çizim kontrol et
        if(pen.is_draw)
            board[pen.h][pen.w] = 'O';
}
    for(int i = 0; i < iter; i++)
        iter_game(board, w, h);
    print_board(board, w, h);
    free_board(board, h);
    return 0;
    
}