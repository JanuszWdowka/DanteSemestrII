#include <stdio.h>
#include "board.h"

int main() {
    struct board_t* board;
    int sizex, sizey;
    int result;
    char option = 'z';
    printf("Enter width and height of the board: ");
    if(!scanf("%d", &sizex)){
        printf("Incorrect input");
        return 1;
    }
    if(!scanf("%d", &sizey)){
        printf("Incorrect input");
        return 1;
    }
    if(sizey < 1 || sizex < 1){
        printf("Incorrect input data");
        return 2;
    }
    result = create_board(&board, sizex, sizey);
    if(result == 2){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Enter player's initial coordinates (x, y): ");
    if(!scanf("%d", &sizex)){
        printf("Incorrect input");
        free_board(board);
        return 1;
    }
    if(!scanf("%d", &sizey)){
        printf("Incorrect input");
        free_board(board);
        return 1;
    }
    if(sizey < 0 || sizex < 0 || sizey >= board->height || sizex >= board->width){
        printf("Incorrect input data");
        free_board(board);
        return 2;
    }
    set_player(board, sizex, sizey);
    display_board(board);
    while (option != 'q'){
        while ( getchar() != '\n' );
        printf("Choose your action: ");
        if(!scanf("%c", &option)){
            printf("Incorrect input");
            free_board(board);
            return 1;
        }
        switch (option) {
            case 'a':
                board->move_player_left(board);
                break;
            case 's':
                board->move_player_down(board);
                break;
            case 'd':
                board->move_player_right(board);
                break;
            case 'w':
                board->move_player_up(board);
                break;
            case 'q':
                continue;
            default:
                printf("Incorrect choice\n");
                continue;
        }
        display_board(board);
    }
    free_board(board);
    return 0;
}
