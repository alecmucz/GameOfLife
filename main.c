#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

//Struct Definitions---------------------------------------------------
typedef struct Cell {
  bool alive;
  Vector2 position;
} Cell;

typedef struct Grid {
  int rows;
  int cols;
  struct Cell **cells;
} Grid;
//Functions------------------------------------------------------------
Grid InitializeGrid(int rows, int cols, float cellSize){
  Grid grid;
  grid.rows = rows;
  grid.cols = cols;
  grid.cells = (Cell**)malloc(sizeof(Cell*) * rows);
  for (int i = 0; i < rows; i++) {
    grid.cells[i] = (Cell*)malloc(sizeof(Cell) * cols);
    for (int j = 0; j < cols;j++) {
      grid.cells[i][j].alive = false;
      grid.cells[i][j].position = (Vector2){cellSize * i, cellSize * j};
    }
  }
  return grid;
}

void RenderGrid(Grid grid, float cellSize, Camera2D camera) {
   for(int i = 0; i < grid.rows; i++){
    for(int j = 0; j < grid.cols; j++){
      Vector2 worldPosition = (Vector2)grid.cells[i][j].position;
      if (grid.cells[i][j].alive) {
        DrawRectangle((int)worldPosition.x,(int)worldPosition.y,(int)cellSize,(int)cellSize,BLACK);
      } else {
        DrawRectangleLines((int)worldPosition.x,(int)worldPosition.y,(int)cellSize,(int)cellSize,GRAY);
      }
    }
  } 
}
//---------------------------------------------------------------------
// Program Main Entry Point
//---------------------------------------------------------------------
int main(void){
  //Window and Camera Initializations
  const int windowWidth = 800;
  const int windowHeight = 600;

  Grid grid = InitializeGrid(100, 100,20.0f);

  InitWindow(windowWidth,windowHeight,"Test");

  Camera2D camera = {0};
  camera.target = (Vector2){0.0f, 0.0f};
  camera.offset = (Vector2){windowWidth / 2.0f, windowHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  int zoomMode = 0;

  SetTargetFPS(60);
  //-------------------------------------------------------------------
  //Main Game Loop
  while (!WindowShouldClose()){
  // Movement----------------------------------------------------------
  if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
      printf("Right Button Clicked");
      Vector2 delta = GetMouseDelta();
      delta = Vector2Scale(delta, -1.0f/camera.zoom);
      camera.target = Vector2Add(camera.target, delta);
    }
  if (zoomMode == 0){
      float wheel = GetMouseWheelMove();
      if (wheel != 0) { 
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
        camera.offset = GetMousePosition();
        camera.target = mouseWorldPos;
        float scaleFactor = 1.0f + (0.25f*fabsf(wheel));
        if (wheel < 0) scaleFactor = 1.0f/scaleFactor;
        camera.zoom = Clamp(camera.zoom*scaleFactor, 0.125f, 64.0f);
      }
    }
    // Render------------------------------------------------------------
    BeginDrawing();
    ClearBackground(WHITE);
      BeginMode2D(camera);
      RenderGrid(grid, 20.0f, camera);
      EndMode2D();
    EndDrawing();
  }

  CloseWindow();
}
