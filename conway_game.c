#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SIZE 50

bool world[SIZE][SIZE] = {0};

bool is_wall(int x, int y) {
  if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
    return false;
  }
  
  return true;
}

int counter(int x, int y) {
  int counter = 0;

  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if ((i != 0 || j != 0) && !is_wall(x + i, y + j) && world[x + i][y + j]) {
        counter++;
      }
    }
  }

  return counter;
}

int main() {
  srand(time(NULL));

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      world[i][j] = rand() % 2;
    }
  }

  while (true) {
    bool w[SIZE][SIZE] = {0};

    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        w[i][j] = world[i][j];

        int count = counter(i, j);
        if (count != 2) {
          w[i][j] = (count == 3);
        }

        printf(world[i][j] ? "\u25A0 " : "  ");
      }

      printf("\n");
    }

    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        world[i][j] = w[i][j];
      }
    }

    usleep(100000);

    printf("\033[H\033[J");
  }

  return 0;
}
