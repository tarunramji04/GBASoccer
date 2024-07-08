# GBASoccer

GBASoccer is a game for the Game Boy Advance that uses a state machine to navigate display, accesses GBA devices such as the screen, DMA, and buttons through memory-mapped I/O, and utilizes bit manipulation and optimization techniques to create a tear-free experience.

How the Game Works
- The purpose of the game is to score a goal before the timer (displayed on the screen) runs out and without colliding into a moving defender.
- The defender moves in the same direction as the ball, but can only cover half as much ground.
- The ball or defenders will not move beyond the boundaries of the field (marked by black lines).

Controls
- Press enter from the start screen to play easy mode.
- Press z from the start screen to play hard mode.
- Use arrows to move the ball.
- Press backspace at any time to restart the game.