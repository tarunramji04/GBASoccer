# GBASoccer

GBASoccer is a game for the Game Boy Advance that uses a state machine to navigate display, accesses GBA components such as the screen, DMA, and buttons through memory-mapped I/O, and utilizes bit manipulation and optimization techniques to create a tear-free experience.

How the Game Works
- The purpose of the game is to score a goal before the timer (displayed on the screen) runs out and without colliding into a moving defender.
- Defenders have varying movement patterns. Some move in accordance with the player's movements, while others move independently. 
- The ball or defenders will not move beyond the boundaries of the field (marked by black lines).

Controls
- Press enter from the start screen to play easy mode, z to play medium mode, and x to play hard mode.
- Use arrows to control the ball.
- Press backspace at any time to restart the game.