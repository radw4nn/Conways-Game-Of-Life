#include <raylib.h>
#include <iostream>
#include "simulation.hpp"

int main()
{
    // Updated variable names in snake_case
    Color grey_color = {29, 29, 29, 255}; // Grey background color
    const int window_width = 750;
    const int window_height = 750;
    const int cell_dimension = 25; // Updated from CELL_SIZE to cell_dimension for more clarity
    int frame_rate = 12; // Updated from FPS to frame_rate

    // Initialize window and set frame rate
    InitWindow(window_width, window_height, "Game of Life");
    SetTargetFPS(frame_rate);

    // Initialize simulation object
    Simulation simulation_instance{window_width, window_height, cell_dimension};

    // Simulation Loop
    while (WindowShouldClose() == false) 
    {
        // 1. Event Handling
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) 
        {
            Vector2 mouse_position = GetMousePosition();
            int row_index = mouse_position.y / cell_dimension;
            int column_index = mouse_position.x / cell_dimension;
            simulation_instance.ToggleCell(row_index, column_index);
        }
        
        // Handle keyboard input for controlling simulation
        if (IsKeyPressed(KEY_ENTER)) 
        {
            simulation_instance.Start();
            SetWindowTitle("The Game of Life is running ...");
        } 
        else if (IsKeyPressed(KEY_SPACE)) 
        {
            simulation_instance.Stop();
            SetWindowTitle("The Game of Life has stopped.");
        } 
        else if (IsKeyPressed(KEY_F)) 
        {
            frame_rate += 2;
            SetTargetFPS(frame_rate);
        } 
        else if (IsKeyPressed(KEY_S)) 
        {
            if (frame_rate > 5) 
            {
                frame_rate -= 2;
                SetTargetFPS(frame_rate);
            }
        } 
        else if (IsKeyPressed(KEY_R)) 
        {
            simulation_instance.CreateRandomState();
        } 
        else if (IsKeyPressed(KEY_C)) 
        {
            simulation_instance.ClearGrid();
        }

        // 2. Updating the state of the simulation
        simulation_instance.Update(); 

        // 3. Drawing
        BeginDrawing();
        ClearBackground(grey_color); // Clear the screen with grey
        simulation_instance.Draw(); // Draw the simulation grid and cells
        EndDrawing();
    }

    CloseWindow();
}
