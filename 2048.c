#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

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
    struct pair {
        int i;
        int j;
    };
    
    struct pair freeTiles[16];
    
    int i, j;
    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                freeTiles[k].i = i;
                freeTiles[k].j = j;
                k++;
            }
        }
    }
    if (k > 0) {
        int randomFreeTile = rand() % k;
        board[freeTiles[randomFreeTile].i][freeTiles[randomFreeTile].j] = rand() % 10 == 0 ? 4 : 2;
    }
}

void start(int board[4][4]) {
    srand(time(NULL));
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

int move(char c, int board[4][4]) {
    int merged[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    int aux;
    int score = 0;
    if (c == 'w') {
        for (int i = 1; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                aux = i;
                while (i > 0 && board[i-1][j] == 0) {
                    board[i-1][j] = board[i][j];
                    board[i][j] = 0;
                    i--;
                }
                if (i > 0 && board[i-1][j] == board[i][j] && merged[i][j] == 0) {
                    score += 2*board[i][j];
                    board[i-1][j] = 2*board[i][j];
                    board[i][j] = 0;
                    merged[i][j] = 1;
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
                if (i < 3 && board[i+1][j] == board[i][j] && merged[i][j] == 0) {
                    score += 2*board[i][j];
                    board[i+1][j] = 2*board[i][j];
                    board[i][j] = 0;
                    merged[i][j] = 1;
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
                if (j > 0 && board[i][j-1] == board[i][j] && merged[i][j] == 0) {
                    score += 2*board[i][j];
                    board[i][j-1] = 2*board[i][j];
                    board[i][j] = 0;
                    merged[i][j] = 1;
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
                if (j < 3 && board[i][j+1] == board[i][j] && merged[i][j] == 0) {
                    score += 2*board[i][j];
                    board[i][j+1] = 2*board[i][j];
                    board[i][j] = 0;
                    merged[i][j] = 1;
                }
                j = aux;
            }
        }
        spawn(board);
    }
    return score;
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

int maxTile(int board[4][4]) { // currently unused
    int max = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] > max) {
                max = board[i][j];
            }
        }
    }
    return max;
}

double ai(int board[4][4], char c, int n) {
    double avgScore = 0;
    int aux[4][4];
    
    for (int i = 0; i < n; i++) {
        memcpy(aux, board, 4*4*sizeof(int));
        
        while (!over(aux)) {
            switch(rand() % 4) {
                case 0:
                    avgScore += move('w', aux);
                    break;
                case 1:
                    avgScore += move('s', aux);
                    break;
                case 2:
                    avgScore += move('a', aux);
                    break;
                case 3:
                    avgScore += move('d', aux);
                    break;
            }
        }
    }
    return avgScore/n;
}

void bestMove(int board[4][4], int n) {
    int bestScore = 0;
    double score;
    char bestMove;
    char moves[4] = {'w','s','a','d'};

    for (int i = 0; i < 4; i++) {
        int aux[4][4];
        memcpy(aux, board, 4*4*sizeof(int));
        score = move(moves[i], aux);
        if (memcmp(aux, board, 4*4*sizeof(int)) != 0) {
            score += ai(aux, moves[i], n);
            if (score > bestScore) {
                bestMove = moves[i];
                bestScore = score;
            }
        }
    }
    move(bestMove, board);
}

int main(int argc, char const *argv[]) {
    int board[4][4];
    char c;

    start(board);
    draw(board);

    while (!over(board)) {
        // c = getchar();
        // getchar();
        // move(c, board));
        
        bestMove(board, 1000);
        printf("\n");
        draw(board);
    }

    return 0;
}