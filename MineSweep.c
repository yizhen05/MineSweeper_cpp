#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*SIZEは絶対固定!!*/
#define SIZE 8
const unsigned int MINES = 10;

unsigned int life = 3;

unsigned char judgement_board[SIZE];
char display_board[SIZE][SIZE];

bool isInBoard(int x, int y) {
    return (x >= 0 && x < SIZE && y >= 0 && y < SIZE);
}

bool isFlagOrOpen(int x, int y) {
    return !(display_board[x][y] == '-' || display_board[x][y] == 'F');
}

bool isMine(int x, int y) { return (judgement_board[y] & (0x80 >> x)); }

void init_board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            judgement_board[i] = 0b00000000;
            display_board[i][j] = '-';
        }
    }
    srand(time(NULL));
    int mines_placed = 0;
    while (mines_placed < MINES) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (!isMine(x, y)) {
            judgement_board[y] |= (0x80 >> x);
            mines_placed++;
        }
    }
}

void displayBoard() {
    printf(" ");
    for (int x = 0; x < SIZE; x++) {
        printf(" %d", x);
    }
    printf("\n");
    for (int y = 0; y < SIZE; y++) {
        printf("%d ", y);
        for (int x = 0; x < SIZE; x++) {
            printf("%c ", display_board[x][y]);
        }
        printf("\n");
    }
}

int countMines(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (isInBoard(x + i, y + j) && isMine(x + i, y + j)) {
                count++;
            }
        }
    }
    return count;
}

void openCell(int x, int y) {
    if (isFlagOrOpen(x, y)) {
        return;
    }
    if (isMine(x, y)) {
        life--;
        if (life == 0) {
            printf("Game Over\n");
            exit(0);
        }
        printf("Life: %d\n", life);
        return;
    }
    int mine_num = countMines(x, y);
    if (mine_num > 0) {
        display_board[x][y] = '0' + mine_num;
    } else {
        display_board[x][y] = ' ';
    }
}

void flagOrOpen(int x, int y, int choice) {
    if (isFlagOrOpen(x, y)) {
        printf("Error: You cannot open or put a flag here\n");
        return;
    }
    if (choice == 1) {
        openCell(x, y);
    } else if (choice == 2) {
        if (display_board[x][y] == 'F') {
            display_board[x][y] = '-';
        } else {
            display_board[x][y] = 'F';
        }
    }
}

int main(void) {
    init_board();
    displayBoard();
    int x, y, choice;
    while (life > 0) {
        do {
            puts("1. Open cell 2. Put a flag");
            printf("Enter x y Open/Flag: ");
            scanf("%d %d %d", &x, &y, &choice);
            if (!isInBoard(x, y)) {
                printf("Error: Out of board\n");
            }
            if (choice != 1 && choice != 2) {
                printf("Error: Invalid choice\n");
            }
        } while (!isInBoard(x, y) || (choice != 1 && choice != 2));

        flagOrOpen(x, y, choice);
        displayBoard();
    }
    return 0;
}
