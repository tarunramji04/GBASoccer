#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"

#include "images/soccer_game.h"
#include "images/ball.h"
#include "images/goal.h"
#include "images/game_win.h"
#include "images/game_lose.h"
#include "images/defender.h"

enum gba_state {
  START,
  STARTTEXT,
  PLAYONE,
  PLAYTWO,
  PLAYTHREE,
  WIN,
  WINTEXT,
  LOSE,
  LOSETEXT
};

int main(void) {
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = START;  

  struct ball game_ball = {80, 20, 8, 8};
  struct defender defender_1 = {75, 100, 8, 16};
  struct defender defender_2 = {60, 210, 8, 16};
  struct defender defender_3 = {20, 50, 8, 16};
  struct defender defender_4 = {125, 50, 8, 16};

  int timer = 30;
  int goalie_direction = 1;
  int top_defender_direction = 1;
  int bottom_defender_direction = 1;

  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons

    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw

    switch (state) {
      case START:
        waitForVBlank();
        drawFullScreenImageDMA(soccer_game);
        game_ball.x = 80;
        game_ball.y = 20;
        defender_1.x = 75;
        defender_1.y = 100;
        defender_2.x = 60;
        defender_2.y = 210;
        defender_3.x = 20;
        defender_3.y = 50;
        defender_4.x = 125;
        defender_4.y = 50;
        
        timer = 30;

        state = STARTTEXT;

        break;

      case STARTTEXT: 
        drawString(70, 18, "Score the soccer ball into the goal", BLACK);
        drawString(83, 30, "Press enter to play easy mode!", BLACK);
        drawString(96, 35, "Press z to play medium mode!", BLACK);
        drawString(109, 40, "Press x to play hard mode!", BLACK);

        if (KEY_DOWN(BUTTON_START, currentButtons)) {
          state = PLAYONE;
        }

        if (KEY_DOWN(BUTTON_A, currentButtons)) {
          state = PLAYTWO;
        }

        if (KEY_DOWN(BUTTON_B, currentButtons)) {
          state = PLAYTHREE;
        }

        break;

      case PLAYONE:
        waitForVBlank();
        fillScreenDMA(DARKGREEN);
        drawRectDMA(15, 0, WIDTH - 20, 1, BLACK);
        drawRectDMA(145, 0, WIDTH - 20, 1, BLACK);
        drawRectDMA(15, 220, 2, 45, BLACK);
        drawRectDMA(100, 220, 2, 45, BLACK);
        drawImageDMA(game_ball.x, game_ball.y, game_ball.width, game_ball.height, ball);
        drawImageDMA(60, 220, 20, 40, goal);

        if (KEY_DOWN(BUTTON_LEFT, BUTTONS) && game_ball.y > 0) {
          game_ball.y -=2;
        }

        if (KEY_DOWN(BUTTON_RIGHT, BUTTONS) &&
         ((game_ball.y < WIDTH - game_ball.width - 20) || (game_ball.y < WIDTH - game_ball.width && (game_ball.x > 60 && game_ball.x < 92)))) { 
          game_ball.y +=2;
        }

        if (KEY_DOWN(BUTTON_UP, BUTTONS) && game_ball.x > 16) { 
          game_ball.x -=2;
        }

        if (KEY_DOWN(BUTTON_DOWN, BUTTONS) && game_ball.x < HEIGHT - game_ball.height - 16) { 
          game_ball.x +=2;
        }

        if ((game_ball.y > 212) && (game_ball.x > 60 && game_ball.x < 92)) {
          state = WIN;
        }

        if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {
          state = START;
        }

        if (vBlankCounter % 60 == 0) {
          timer--;
        }
    
        char time[30];
        sprintf(time, "Timer: %d", timer);
        drawString(150, 5, time, BLACK);

        if (timer == 0) {
          state = LOSE;
        }

        break;
        
      case PLAYTWO:
        waitForVBlank();
        fillScreenDMA(DARKGREEN);
        drawRectDMA(15, 0, WIDTH - 20, 1, BLACK);
        drawRectDMA(145, 0, WIDTH - 20, 1, BLACK);
        drawRectDMA(15, 220, 2, 45, BLACK);
        drawRectDMA(100, 220, 2, 45, BLACK);
        drawImageDMA(game_ball.x, game_ball.y, game_ball.width, game_ball.height, ball);
        drawImageDMA(defender_1.x, defender_1.y, 8, 16, defender);
        drawImageDMA(60, 220, 20, 40, goal);

        if (KEY_DOWN(BUTTON_LEFT, BUTTONS) && game_ball.y > 0) {
          game_ball.y -=2;
          defender_1.y -=1;
        }

        if (KEY_DOWN(BUTTON_RIGHT, BUTTONS) &&
         ((game_ball.y < WIDTH - game_ball.width - 20) || (game_ball.y < WIDTH - game_ball.width && (game_ball.x > 60 && game_ball.x < 92)))) { 
          game_ball.y +=2;
          defender_1.y +=1;
        }

        if (KEY_DOWN(BUTTON_UP, BUTTONS) && game_ball.x > 16) { 
          game_ball.x -=2;
          defender_1.x -=1;
        }

        if (KEY_DOWN(BUTTON_DOWN, BUTTONS) && game_ball.x < HEIGHT - game_ball.height - 16) { 
          game_ball.x +=2;
          defender_1.x +=1;
        }

        if ((game_ball.y > 212) && (game_ball.x > 60 && game_ball.x < 92)) {
          state = WIN;
        }

        if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {
          state = START;
        }

        if (vBlankCounter % 60 == 0) {
          timer--;
        }
    
        char timeTwo[30];
        sprintf(timeTwo, "Timer: %d", timer);
        drawString(150, 5, timeTwo, BLACK);

        if (timer == 0 || ((game_ball.x + game_ball.width >= defender_1.x && game_ball.x <= defender_1.x + defender_1.height) && (game_ball.y + game_ball.height >= defender_1.y && game_ball.y <= defender_1.y + defender_1.width))) {
          state = LOSE;
        }

        break;
      
      case PLAYTHREE:
        waitForVBlank();
        fillScreenDMA(DARKGREEN);
        drawRectDMA(15, 0, WIDTH - 20, 1, BLACK);
        drawRectDMA(145, 0, WIDTH - 20, 1, BLACK);
        drawRectDMA(15, 220, 2, 45, BLACK);
        drawRectDMA(100, 220, 2, 45, BLACK);
        drawImageDMA(game_ball.x, game_ball.y, game_ball.width, game_ball.height, ball);
        drawImageDMA(defender_1.x, defender_1.y, 8, 16, defender);
        drawImageDMA(defender_2.x, defender_2.y, 8, 16, defender);
        drawImageDMA(defender_3.x, defender_3.y, 8, 16, defender);
        drawImageDMA(defender_4.x, defender_4.y, 8, 16, defender);
        drawImageDMA(60, 220, 20, 40, goal);

        if (KEY_DOWN(BUTTON_LEFT, BUTTONS) && game_ball.y > 0) {
          game_ball.y -=2;
          defender_1.y -=1;
        }

        if (KEY_DOWN(BUTTON_RIGHT, BUTTONS) &&
         ((game_ball.y < WIDTH - game_ball.width - 20) || (game_ball.y < WIDTH - game_ball.width && (game_ball.x > 60 && game_ball.x < 92)))) { 
          game_ball.y +=2;
          defender_1.y +=1;
        }

        if (KEY_DOWN(BUTTON_UP, BUTTONS) && game_ball.x > 16) { 
          game_ball.x -=2;
          defender_1.x -=1;
        }

        if (KEY_DOWN(BUTTON_DOWN, BUTTONS) && game_ball.x < HEIGHT - game_ball.height - 16) { 
          game_ball.x +=2;
          defender_1.x +=1;
        }

        if ((game_ball.y > 212) && (game_ball.x > 60 && game_ball.x < 92)) {
          state = WIN;
        }

        if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {
          state = START;
        }

        if ((vBlankCounter % 2 == 0) && goalie_direction) {
          defender_2.x += 1;
        }
        
        if ((vBlankCounter % 2 == 0) && !goalie_direction) {
          defender_2.x -= 1;
        }

        if (defender_2.x >= 84) {
          goalie_direction = 0;
        }
        if (defender_2.x < 60) {
          goalie_direction = 1;
        }

        if ((vBlankCounter % 1 == 0) && top_defender_direction) {
          defender_3.y += 1;
        }
        
        if ((vBlankCounter % 1 == 0) && !top_defender_direction) {
          defender_3.y -= 1;
        }

        if (defender_3.y >= 150) {
          top_defender_direction = 0;
        }
        if (defender_3.y < 50) {
          top_defender_direction = 1;
        }

        if ((vBlankCounter % 1 == 0) && bottom_defender_direction) {
          defender_4.y += 1;
        }
        
        if ((vBlankCounter % 1 == 0) && !bottom_defender_direction) {
          defender_4.y -= 1;
        }

        if (defender_4.y >= 150) {
          bottom_defender_direction = 0;
        }
        if (defender_4.y < 50) {
          bottom_defender_direction = 1;
        }

        if (vBlankCounter % 60 == 0) {
          timer--;
        }
    
        char timeThree[30];
        sprintf(timeThree, "Timer: %d", timer);
        drawString(150, 5, timeThree, BLACK);

        if (timer == 0 || ((game_ball.x + game_ball.width >= defender_1.x && game_ball.x <= defender_1.x + defender_1.height) && (game_ball.y + game_ball.height >= defender_1.y && game_ball.y <= defender_1.y + defender_1.width))
         || ((game_ball.x + game_ball.width >= defender_2.x && game_ball.x <= defender_2.x + defender_2.height) && (game_ball.y + game_ball.height >= defender_2.y && game_ball.y <= defender_2.y + defender_2.width))
         || ((game_ball.x + game_ball.width >= defender_3.x && game_ball.x <= defender_3.x + defender_3.height) && (game_ball.y + game_ball.height >= defender_3.y && game_ball.y <= defender_3.y + defender_3.width))
         || (((game_ball.x + game_ball.width >= defender_4.x && game_ball.x <= defender_4.x + defender_4.height) && (game_ball.y + game_ball.height >= defender_4.y && game_ball.y <= defender_4.y + defender_4.width)))) {
          state = LOSE;
        }

        break;

      case WIN:
        waitForVBlank();
        drawFullScreenImageDMA(game_win);

        state = WINTEXT;
  
        break;

      case WINTEXT: 
        drawString(55, 90, "Press back to play again", WHITE);

        char display_str[30];
        sprintf(display_str, "You scored in %d seconds!", (30 - timer));
        drawString(35, 90, display_str, WHITE);

        if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {
          state = START;
        }
      
        break;

      case LOSE:
        waitForVBlank();
        drawFullScreenImageDMA(game_lose);

        state = LOSETEXT;

        break;
      
      case LOSETEXT:
        drawString(35, 140, "You lose", WHITE);
        drawString(55, 90, "Press back to play again", WHITE);

        if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {
          state = START;
        }

        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  UNUSED(previousButtons);

  return 0;
}
