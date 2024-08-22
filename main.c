#include <stdbool.h>
#include <stdlib.h>
//#include <stdio.h>
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

void RenderGrid(Grid* grid, float cellSize) {
   for(int i = 0; i < grid->rows; i++){
    for(int j = 0; j < grid->cols; j++){
      Vector2 worldPosition = (Vector2)grid->cells[i][j].position;
      if (grid->cells[i][j].alive){
        DrawRectangle((int)worldPosition.x,(int)worldPosition.y,(int)cellSize,(int)cellSize,BLACK);
      } else {
        DrawRectangleLines((int)worldPosition.x,(int)worldPosition.y,(int)cellSize,(int)cellSize,BLACK);
      }
    }
  } 
}

int countLiveNeighbors(Grid* grid, int row, int col) {
  int count = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1;j <= 1; j++) {
      if(i == 0 && j == 0){
        continue;
      }
      if ((row + i) >= 0 && (row + i) < grid->rows && (col + j) >= 0 && (col + j) < grid->cols) {
        if(grid->cells[row+i][col+j].alive == true){
          count++;
        }
      }
    }
  }
  return count;
}

void GameOfLife(Grid* grid){
  for (int i = 0; i < grid->rows; i++){
    for (int j = 0; j < grid->cols; j++){
      int neighbors = countLiveNeighbors(grid,i,j);
      if (grid->cells[i][j].alive == true && neighbors < 2){
        grid->cells[i][j].alive=false;
      } else if (grid->cells[i][j].alive == true && (neighbors == 2 || neighbors == 3)) {
        grid->cells[i][j].alive = true;
      } else if (grid->cells[i][j].alive == true && neighbors > 3) {
        grid->cells[i][j].alive = false;
      } else if (grid->cells[i][j].alive == false && neighbors == 3) {
        grid->cells[i][j].alive = true;
      }
    }
  }
}
// Function Headers for game patterns
// (Found At the Bottom of the page)----------------------------------- 
void GospersGun(Grid* grid);
// Program Main Entry Point
//---------------------------------------------------------------------
int main(void){
  //Window and Camera Initializations
  const int windowWidth = 800;
  const int windowHeight = 600;

  Grid grid = InitializeGrid(100, 100,20.0f);
  GospersGun(&grid);

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
      camera.zoom = Clamp(camera.zoom*scaleFactor, 0.125f, 1.0f);
    }
  }
  
    // Render------------------------------------------------------------
    BeginDrawing();
    ClearBackground(WHITE);
      BeginMode2D(camera);
      GameOfLife(&grid);
      RenderGrid(&grid, 20.0f);
      EndMode2D();
    EndDrawing();
  }

  CloseWindow();
}
//-----------------------------------------------------------------------

void GospersGun(Grid* grid) {
    // Left square
    grid->cells[35][40].alive = true;
    grid->cells[35][41].alive = true;
    grid->cells[36][40].alive = true;
    grid->cells[36][41].alive = true;
    //Big C 
    grid->cells[35][49].alive = true;
    grid->cells[36][49].alive = true;
    grid->cells[37][49].alive = true;
    grid->cells[34][50].alive = true;
    grid->cells[33][51].alive = true;
    grid->cells[33][52].alive = true;
    grid->cells[38][50].alive = true;
    grid->cells[39][51].alive = true;
    grid->cells[39][52].alive = true;
    grid->cells[36][53].alive = true;

    grid->cells[34][54].alive = true;
    grid->cells[35][55].alive = true;
    grid->cells[36][55].alive = true;
    grid->cells[37][55].alive = true;
    grid->cells[38][54].alive = true;
    grid->cells[36][56].alive = true;

    grid->cells[33][59].alive = true;
    grid->cells[33][60].alive = true;
    grid->cells[34][59].alive = true;
    grid->cells[34][60].alive = true;
    grid->cells[35][59].alive = true;
    grid->cells[35][60].alive = true;
    grid->cells[32][61].alive = true;
    grid->cells[36][61].alive = true;
    grid->cells[31][63].alive = true;
    grid->cells[32][63].alive = true;
    grid->cells[36][63].alive = true;
    grid->cells[37][63].alive = true;

    grid->cells[33][73].alive = true;
    grid->cells[34][73].alive = true;
    grid->cells[33][74].alive = true;
    grid->cells[34][74].alive = true;



}
