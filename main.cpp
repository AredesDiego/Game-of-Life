#include <raylib.h>
#include <iostream>
#include "simulation.hpp"

//*******************************************************************Int main********************************************************************
int main () 
{
    Color Grey = {29, 29, 29, 255};
    const int screenWidth = 750;
    const int screenHeight = 750;
    const int CELLS_SIZE = 25;
    int FPS = 12;

    InitWindow(screenWidth, screenHeight, "Game of Life");
    SetTargetFPS(FPS); 
    Simulation simulation(screenWidth, screenHeight, CELLS_SIZE);
    
    //*******************************************************************Simulation loop*******************************************************************
    while (WindowShouldClose() == false)
    {
        //Event Handling
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 MousePosition = GetMousePosition();
            int row = MousePosition.y / CELLS_SIZE;
            int column = MousePosition.x / CELLS_SIZE;
            simulation.ToggleCell(row, column);
        }
        if(IsKeyPressed(KEY_ENTER))
        {
            simulation.Start();
            SetWindowTitle("Game Of Life Running...");
        }
        else if(IsKeyPressed(KEY_SPACE))
        {
            simulation.Stop();
            SetWindowTitle("Game Of Life has stopped.");
        }
          else if(IsKeyPressed(KEY_F))
        {
            FPS += 2;
            SetTargetFPS(FPS);
        }
          else if(IsKeyPressed(KEY_S))
        {
            if(FPS > 5)
            {
                FPS -= 2;
                SetTargetFPS(FPS);
            }
        }
        else if(IsKeyPressed(KEY_R))
        {
            simulation.CreateRandomState();
        }
        else if(IsKeyPressed(KEY_C))
        {
            simulation.ClearGrid();
        }

        //Updating State
        simulation.Update();

        //Drawing
        BeginDrawing();
        ClearBackground(Grey); 
        simulation.Draw();
        EndDrawing();
    }
    //*******************************************************************************************************************************************

    CloseWindow();
    return 0;
}
//***********************************************************************************************************************************************