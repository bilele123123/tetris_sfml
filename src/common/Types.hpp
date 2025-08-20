#pragma once

// Game grid dimensions
constexpr unsigned char CELL_SIZE = 8;
constexpr unsigned char ROWS = 10;
constexpr unsigned char COLUMNS = 20;


constexpr unsigned int BOARD_W = ROWS * CELL_SIZE;
constexpr unsigned int BOARD_H = COLUMNS * CELL_SIZE;
constexpr unsigned int SCALE = 6;

constexpr unsigned int WIN_W = BOARD_W * SCALE + 8;
constexpr unsigned int WIN_H = BOARD_H * SCALE + 8;