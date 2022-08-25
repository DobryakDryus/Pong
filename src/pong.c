// Copyright 2022 <team>
#include <stdio.h>

void draw(int x_ball, int y_ball, int y_rack1, int y_rack2) {
  int y;
  int x;
  for (y = 0; y < 25; y++) {
    for (x = 0; x < 80; x++) {
      if (x == x_ball && y == y_ball) {
        printf("@");  // Вывод мяча
      } else {
        if (x == 10 && y == y_rack1 - 1)
          printf("|");
        else if (x == 10 && y == y_rack1)
          printf("|");
        else if (x == 10 && y == y_rack1 + 1)
          printf("|");
        else

        if (x == 70 && y == y_rack2 - 1)
          printf("|");
        else if (x == 70 && y == y_rack2)
          printf("|");
        else if (x == 70 && y == y_rack2 + 1)
          printf("|");
        else

        if (x == 40)
          printf("|");
        else if ((y == 0 || y == 24))
          printf("—");
        else if (x == 0 || x == 79)
          printf("|");
        else
          printf(" ");
      }
    }
    printf("\n");
  }
}

int Move_racket() {
  char move;
  int result;
  scanf("%c", &move);
  if (move == 'a')
    result = 1;
  else if (move == 'A')
    result = 1;
  else if (move == 'z')
    result = 0;
  else if (move == 'Z')
    result = 0;
  else if (move == 'k')
    result = 3;
  else if (move == 'K')
    result = 3;
  else if (move == 'm')
    result = 2;
  else if (move == 'M')
    result = 2;
  else if (move == 'Q')
    result = 4;
  else if (move == 'q')
    result = 4;
  else if (move == ' ')
    result = 10;
  else
    result = -1;
  fflush(stdin);  // Очистка ввода букв
  return result;
}

void draw_score(int score1, int score2) {
  for (int i = 0; i < 39; i++) {
    if (i == 38)
      printf("Score:\n");
    else
      printf(" ");
  }
  for (int i = 0; i < 38; i++) {
    if (i == 37)
      printf("%02d : %02d\n", score1, score2);
    else
      printf(" ");
  }
  for (int i = 0; i < 18; i++) {
    if (i == 17)
      printf("Если хотите завершить игру, нажмите Q, а затем Enter\n");
    else
      printf(" ");
  }
}

int main() {
  int ballx = 40;
  int bally = 12;
  int ballspeedx = 1;
  int ballspeedy = 1;
  int rackx1 = 10;
  int rackx2 = 70;
  int racky1 = 12;
  int racky2 = 12;
  int bot_wall = 24;
  int top_wall = 0;
  int score_1 = 0;
  int score_2 = 0;
  int move = 0;
  printf("\e[8;$29;$80;t");  // Вывод экрана размером 80:20
  draw_score(score_1, score_2);
  draw(ballx, bally, racky1, racky2);
  while (score_1 != 21 && score_2 != 21) {  // Победа одного из игроков
    move = Move_racket();
    if (move != -1) {
      ballx = ballx + ballspeedx;  // Перемещение шарика
      bally = bally + ballspeedy;
      if (move == 0) {
        if (racky1 + 1 < bot_wall - 1)
          racky1++;  // Перемещение первой ракетки на позицию вниз
      }
      if (move == 1) {
        if (racky1 - 1 > top_wall + 1)
          racky1--;  // Перемещение первой ракетки на позицию вверх
      }
      if (move == 2) {
        if (racky2 + 1 < bot_wall - 1)
          racky2++;  // Перемещение второй ракетки на позицию вниз
      }
      if (move == 3) {
        if (racky2 - 1 > top_wall + 1)
          racky2--;  // Перемещение второй ракетки на позицию вверх
      }
      if (move == 4)
        break;
      if (bally == bot_wall - 1 ||
          bally == top_wall + 1) {  // Попадание в горизантальные стенки
        ballspeedy = -ballspeedy;
        ballx = ballx + ballspeedx;
      }
      if ((ballx == rackx1) && (bally == racky1 || bally == racky1 + 1 ||
                bally == racky1 - 1)) {  // Попадание в ракетку 1
        ballspeedx = -ballspeedx;
        ballx = ballx + ballspeedx + ballspeedx;
      }
      if ((ballx == rackx2) && (bally == racky2 || bally == racky2 + 1 ||
                bally == racky2 - 1)) {  // Попадание в ракетку 2
        ballspeedx = -ballspeedx;
        ballx = ballx + ballspeedx + ballspeedx;
      }
      if (ballx < rackx1 &&
          (bally > racky1 + 1 || bally < racky1 - 1)) {  // Игрок 2 забивает гол
        score_2++;
        ballx = 40;
        bally = 12;
        ballspeedy = -ballspeedy;
        ballspeedx = -ballspeedx;
      }
      if (ballx > rackx2 &&
          (bally > racky2 + 1 || bally < racky2 - 1)) {  // Игрок 1 забивает гол
        score_1++;
        ballx = 40;
        bally = 12;
        ballspeedy = -ballspeedy;
        ballspeedx = -ballspeedx;
      }
    }
    draw_score(score_1, score_2);
    draw(ballx, bally, racky1, racky2);
  }
  if (score_1 == 21)
    printf("Игра окончена. Счет: %d : %d. Победа игрока №1", score_1, score_2);
  else if (score_2 == 21)
    printf("Игра окончена. Счет: %d : %d. Победа игрока №2", score_1, score_2);
  else
    printf("Игра окончена.");
  return 0;
}
