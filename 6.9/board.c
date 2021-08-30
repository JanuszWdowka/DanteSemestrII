//
// Created by root on 5/12/21.
//

#include <malloc.h>
#include "board.h"


int create_board(struct board_t **board, int width,int height){
    if(board == NULL || width < 1 || height < 1)
        return 1;
    *board = (struct board_t*) malloc(1 * sizeof(struct board_t));
    if(*board == NULL){
        return 2;
    }
    (*board)->height = height;
    (*board)->width = width;
    (*board)->is_init = 0;
    (*board)->move_player_down = move_player_down;
    (*board)->move_player_up = move_player_up;
    (*board)->move_player_left = move_player_left;
    (*board)->move_player_right = move_player_right;
    (*board)->board = (char**) malloc(height * sizeof(char*));
    if((*board)->board == NULL){
        free(*board);
        return 2;
    }
    for(int i = 0; i < height; ++i){
        *((*board)->board + i) = (char*) malloc((width + 1) * sizeof(char));
        if(*((*board)->board + i) == NULL){
            for(int j = 0; j < i; ++j){
                free(*((*board)->board + j));
            }
            free((*board)->board);
            free(*board);
            return 2;
        }
    }
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            *(*((*board)->board + i) + j) = '.';
        }
        *(*((*board)->board + i) + width) = '\0';
    }
    return 0;
}
void display_board(const struct board_t *board){
    if(board == NULL || board->board == NULL || board->height < 1 || board->width < 1){
        return;
    }
    for(int i = 0; i < board->height; ++i){
        for(int j = 0; j < board->width; ++j){
            printf("%c", *(*(board->board + i) + j));
        }
        printf("\n");
    }
}
void free_board(struct board_t *board){
    if(board == NULL)
        return;
    for(int i = 0; i < board->height; ++i){
        free(*(board->board + i));
    }
    free(board->board);
    free(board);
}
int set_player(struct board_t *board, int x, int y){
    if(board == NULL || board->board == NULL || board->width < 1 || board->height < 1 || board->height <= y || board->width <= x || x < 0 || y < 0 || board->is_init == 1)
        return 1;
    board->player.x = x;
    board->player.y = y;
    board->is_init = 1;
    *(*(board->board + y) + x) = '@';
    return 0;
}

struct board_t* move_player_up(struct board_t* board){
    if(board == NULL || board->board == NULL || board->width < 1 || board->height < 1 || board->is_init == 0 || board->player.x < 0 || board->player.y < 0 || board->player.x >= board->width || board->player.y >= board->height)
        return NULL;
    int x = board->player.x;
    int y = board->player.y;
    *(*(board->board + y) + x) = '.';
    y--;
    if(y == -1)
        board->player.y = board->height - 1;
    else
        board->player.y = y;
    *(*(board->board + board->player.y) + x) = '@';
    return board;
}
struct board_t* move_player_down(struct board_t* board){
    if(board == NULL || board->board == NULL || board->width < 1 || board->height < 1 || board->is_init == 0 || board->player.x < 0 || board->player.y < 0 || board->player.x >= board->width || board->player.y >= board->height)
        return NULL;

    int x = board->player.x;
    int y = board->player.y;
    *(*(board->board + y) + x) = '.';
    y++;
    if(y == board->height)
        board->player.y = 0;
    else
        board->player.y = y;
    *(*(board->board + board->player.y) + x) = '@';
    return board;
}
struct board_t* move_player_left(struct board_t* board){
    if(board == NULL || board->board == NULL || board->width < 1 || board->height < 1 || board->is_init == 0 || board->player.x < 0 || board->player.y < 0 || board->player.x >= board->width || board->player.y >= board->height)
        return NULL;
    int x = board->player.x;
    int y = board->player.y;
    *(*(board->board + y) + x) = '.';
    x--;
    if(x == -1)
        board->player.x = board->width - 1;
    else
        board->player.x = x;
    *(*(board->board + y) + board->player.x) = '@';
    return board;
}
struct board_t* move_player_right(struct board_t* board){
    if(board == NULL || board->board == NULL || board->width < 1 || board->height < 1 || board->is_init == 0 || board->player.x < 0 || board->player.y < 0 || board->player.x >= board->width || board->player.y >= board->height)
        return NULL;
    int x = board->player.x;
    int y = board->player.y;
    *(*(board->board + y) + x) = '.';
    x++;
    if(x == board->width)
        board->player.x = 0;
    else
        board->player.x = x;
    *(*(board->board + y) + board->player.x) = '@';
    return board;
}