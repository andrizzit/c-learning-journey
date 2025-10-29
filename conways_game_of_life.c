#include <stdio.h>
#include <unistd.h>

#define GRID_COLS 20
#define GRID_ROWS 20
#define GRID_CELLS (GRID_COLS*GRID_ROWS)
#define ALIVE '*'
#define DEAD '.'

int cell_to_index(int x, int y) {
    if (x < 0) {
        x = (-x) % GRID_COLS;
        x = GRID_COLS - x;
    }
    if (y < 0) {
        y = (-y) % GRID_ROWS;
        y = GRID_ROWS - y;
    }
    if (x >= GRID_COLS) x = x % GRID_COLS;
    if (y >= GRID_ROWS) y = y % GRID_ROWS;
    return y*GRID_COLS+x;
}

/* The function sets the specified cell at x,y to the specified state. */
void set_cell(char *grid, int x, int y, char state) {
    grid[cell_to_index(x,y)] = state;
}

char get_cell(char *grid, int x, int y) {
    return grid[cell_to_index(x,y)];
}

void print_grid(char *grid) {
    printf("\x1b[3J\x1b[H\x1b[2J");
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            printf("%c", get_cell(grid, x,y));
        }
        printf("\n");
    }
}
 
void set_grid(char *grid, char state) {
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            set_cell(grid,x,y,state);
        }
    }
}

int count_living_neighbours(char *grid, int x, int y) {
    int alive = 0;
    for (int yo = -1; yo <= 1; yo++) {
        for (int xo = -1; xo <= 1; xo++) {
            if (xo == 0 && yo == 0) continue;
            if (get_cell(grid,x+xo,y+yo) == ALIVE) alive++;
        }
    }
    return alive;
}

void compute_new_state(char *old, char *new) {
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            int n_alive = count_living_neighbours(old,x,y);
            int new_state = DEAD;
            if (get_cell(old,x,y) == ALIVE) {
                if (n_alive == 2 || n_alive == 3)
                    new_state = ALIVE;
            } else {
                if (n_alive == 3)
                    new_state = ALIVE;
            }
            set_cell(new,x,y,new_state);
        }
    }    
}

int main(void) {
    char old_grid[GRID_CELLS];
    char new_grid[GRID_CELLS];
    set_grid(old_grid,DEAD);
    set_cell(old_grid,10,10,ALIVE);
    set_cell(old_grid,9,10,ALIVE);
    set_cell(old_grid,11,10,ALIVE);
    set_cell(old_grid,11,9,ALIVE);
    set_cell(old_grid,10,8,ALIVE);
    char *old = old_grid;
    char *new = new_grid;
    while (1) {
        compute_new_state(old,new);
        print_grid(new);
        usleep(100000);
        char *tmp = old;
        old = new;
        new = tmp;
    }
    return 0;
}
