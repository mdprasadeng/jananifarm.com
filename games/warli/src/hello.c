#include "raylib.h"



#include "rlImGui.h"	// include the API header
#include "dcimgui.h"

int main(void)
{
    InitWindow(800, 450, "raylib [core] example - basic window");
    rlImGuiSetup(true); 	// sets up ImGui with ether a dark or light default theme
    bool showDemo = false;
    while (!WindowShouldClose())
    {
        BeginDrawing();
            rlImGuiBegin();			// starts the ImGui content mode. Make all ImGui calls after this
            
            ImGui_ShowDemoWindow(&showDemo);

            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

            rlImGuiEnd();			// ends the ImGui content mode. Make all ImGui calls before this

        EndDrawing();
    }

    rlImGuiShutdown();		// cleans up ImGui
    CloseWindow();

    return 0;
}