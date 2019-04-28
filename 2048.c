#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool full(int board[4][4]) {
    bool full = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                full = false;
            }
        }
    }
    return full;
}

void spawn(int board[4][4]) {
    bool spawn = false;
    int i, j;
    srand(time(NULL));
    if (!full(board)) {
        while (!spawn) {
            i = rand() % 4;
            j = rand() % 4;
            if (board[i][j] == 0) {
                board[i][j] = rand() % 10 == 0 ? 4 : 2;
                spawn = true;
            }
        }
    }
}

void start(int board[4][4]) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        board[i][j] = 0;
      }
    }
    for (int i = 0; i < 2; i++) {
        spawn(board);
    }
}

void draw(int board[4][4]) {
    printf("┌────┬────┬────┬────┐\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("│");
            if (board[i][j] == 0) {
                printf("    ");
            } else if (board[i][j] < 10) {
                printf("  %d ", board[i][j]);
            } else if (board[i][j] < 100) {
                printf(" %d ", board[i][j]);
            } else if (board[i][j] < 1000) {
                printf(" %d", board[i][j]);
            } else {
                printf("%d", board[i][j]);
            }
        }
        printf("│\n");
        if (i != 3) {
            printf("├────┼────┼────┼────┤\n");
        } else {
            printf("└────┴────┴────┴────┘\n");
        }
    }
}

void move(char c, int board[4][4]) {
    int aux;
    if (c == 'w') {
        for (int i = 1; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                aux = i;
                while (i > 0 && board[i-1][j] == 0) {
                    board[i-1][j] = board[i][j];
                    board[i][j] = 0;
                    i--;
                }
                if (i > 0 && board[i-1][j] == board[i][j]) {
                    board[i-1][j] = 2*board[i][j];
                    board[i][j] = 0;
                }
                i = aux;
            }
        }
        spawn(board);
    } else if (c == 's') {
        for (int i = 2; i > -1; i--) {
            for (int j = 0; j < 4; j++) {
                aux = i;
                while (i < 3 && board[i+1][j] == 0) {
                    board[i+1][j] = board[i][j];
                    board[i][j] = 0;
                    i++;
                }
                if (i < 3 && board[i+1][j] == board[i][j]) {
                    board[i+1][j] = 2*board[i][j];
                    board[i][j] = 0;
                }
                i = aux;
            }
        }
        spawn(board);
    } else if (c == 'a') {
        for (int j = 1; j < 4; j++){
            for (int i = 0; i < 4; i++) {
                aux = j;
                while (j > 0 && board[i][j-1] == 0) {
                    board[i][j-1] = board[i][j];
                    board[i][j] = 0;
                    j--;
                }
                if (j > 0 && board[i][j-1] == board[i][j]) {
                    board[i][j-1] = 2*board[i][j];
                    board[i][j] = 0;
                }
                j = aux;
            }
        }
        spawn(board);
    } else if (c == 'd') {
        for (int j = 2; j > -1; j--) {
            for (int i = 0; i < 4; i++) {
                aux = j;
                while (j < 3 && board[i][j+1] == 0) {
                    board[i][j+1] = board[i][j];
                    board[i][j] = 0;
                    j++;
                }
                if (j < 3 && board[i][j+1] == board[i][j]) {
                    board[i][j+1] = 2*board[i][j];
                    board[i][j] = 0;
                }
                j = aux;
            }
        }
        spawn(board);
    }
}

bool over(int board[4][4]) {
    bool over = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                over = false;
            }
            if (j != 3) {
                if (board[i][j] == board [i][j+1]) {
                    over = false;
                }
            }
            if (i != 3) {
                if (board[i][j] == board [i+1][j]) {
                    over = false;
                }
            }
        }
    }
    return over;
}

int main(int argc, char const *argv[]) {
    int board[4][4];
    char c;

    start(board);
    draw(board);

    while (!over(board)) {
      c = getchar();
      getchar();
      move(c, board);
      draw(board);
    }

    return 0;
}
