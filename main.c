#include <stdbool.h>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

//Struct Definitions---------------------------------------------------
struct Cell {
  bool alive;
  Vector2 position;
};

typedef struct Grid {
  int rows;
  int cols;
  struct Cell **cells;
} Grid;
//Functions------------------------------------------------------------
//---------------------------------------------------------------------
// Program Main Entry Point
//---------------------------------------------------------------------
int main(void){
  //Window and Camera Initializations
  const int windowWidth = 800;
  const int windowHeight = 600;

  InitWindow(windowWidth,windowHeight,"Test");

  Camera2D camera = {0};
  camera.target = (Vector2){0.0f, 0.0f};
  camera.offset = (Vector2){windowWidth / 2.0f, windowHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

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
  // Render------------------------------------------------------------
    BeginDrawing();
      ClearBackground(WHITE);
      BeginMode2D(camera);
        rlPushMatrix();
          rlTranslatef(0,25*25,0);
          rlRotatef(90,1,0,0);
          DrawGrid(100, 50);
        rlPopMatrix();
    EndDrawing();
  }

  CloseWindow();
}
