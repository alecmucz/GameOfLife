#include <stdbool.h>
#include "raylib.h"

struct cell {
  bool alive;
};

struct grid {
  int rows;
  int cols;
  struct cell **cells;
};

int main(void){
  struct grid grid;
  InitWindow(800,600,"Test");

  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawGrid(10, 10.0f);
    EndDrawing();
  }

  CloseWindow();
}
