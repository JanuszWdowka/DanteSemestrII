//
// Created by root on 5/12/21.
//

#ifndef INC_6_9_BOARD_H
#define INC_6_9_BOARD_H

struct point_t
{
    int x;
    int y;
};

struct board_t
{
    //pozycja gracza
    struct point_t player;

    // wskaźnik na planszę, wiersze powinny być zakończone terminatorem
    char **board;

    // szerokość oraz wysokość planszy do gry
    int width;
    int height;

    // flaga informująca o tym, czy gracz został dodany do planszy, czy nie
    unsigned char is_init:1;


    // Funkcja odpowiada za poruszenie gracza o jedną komórkę w górę.
    // W przypadku dojścia do krawędzi gracz powinien znaleźć się w ostatnim wierszu planszy.
    struct board_t* (*move_player_up)(struct board_t*);

    // funkcja odpowiada za poruszenie gracza o jedną komórkę w dół.
    // W przypadku dojścia do krawędzi gracz powinien znaleźć się w pierwszym wierszu planszy.
    struct board_t* (*move_player_down)(struct board_t*);

    // funkcja odpowiada za poruszenie gracza o jedną komórkę w lewo.
    // W przypadku dojścia do krawędzi gracz powinien znaleźć się w ostatniej kolumnie planszy.
    struct board_t* (*move_player_left)(struct board_t*);

    // funkcja odpowiada za poruszenie gracza o jedną komórkę w prawo.
    // W przypadku dojścia do krawędzi gracz powinien znaleźć się w pierwszej kolumnie planszy.
    struct board_t* (*move_player_right)(struct board_t*);
};

int create_board(struct board_t **board, int width,int height);
void display_board(const struct board_t *board);
void free_board(struct board_t *board);
int set_player(struct board_t *board, int x, int y);

struct board_t* move_player_up(struct board_t*);
struct board_t* move_player_down(struct board_t*);
struct board_t* move_player_left(struct board_t*);
struct board_t* move_player_right(struct board_t*);


#endif //INC_6_9_BOARD_H
