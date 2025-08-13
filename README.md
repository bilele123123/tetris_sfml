# Tetris in C++

### Background
Simple and small project to learn C++, and just to see if I can.

### Overview
The Tetris implementation will be a simple MVP


### Requirements
| Business | Technical |
| --- | --- |
| User can start game | Package the application into an executable (.exe) |
| User can rotate pieces| Implement logic to rotate pieces 90 degrees left and right |
| User can stash pieces | Implement logic to store temporary pieces |
| User can restart game | Retry logic |
| Pieces are random at start | Generate randomized number, and associate each piece with a dedicated number |
| User can clear lines when pieces are aligned| Logic to check when all pieces are aligned in a straight line horizontally and clear it, bottom up |


### High-Level Design

1. C++ Platform and libraries
    - SFML
2. Rendering style
    - 10 x 20 grid

### Low-Level Design

#### Components:
1. Creating a 480 x 640 window
2. Board array: 10x20 grid
3. Randomized objects falling from top of the grid down with gravity
4. Menu screen (start button, quit)
5. Packaging the application into an executable (.exe)
6. Game graphical display
7. Game logic