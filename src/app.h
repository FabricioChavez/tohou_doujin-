//
// Created by Jesus Egusquiza on 7/24/2023.
//

#ifndef PROJECT_TOUHOU_APP_H
#define PROJECT_TOUHOU_APP_H
#include "Player.h"
#include "Spawner.h"
using namespace std;
Music music;
bool paused = false;
struct app{
    static void runApp(){
        InitAudioDevice();
        InitWindow(screenWidth, screenHeight, "Touhou Doujin");

        Global& globaldata = Global::GetInstance();
        std::cout << "peto " << std::endl;

        float frameTime = 0.0f; // set frame time
        Vector2 position = { screenWidth/2, screenHeight/2 }; // windows postion intial
        Vector2 spawner_position = {position.x , position.y-100};
        SetTargetFPS(60);
        Player Marisa(position);
        Spawner Ring(spawner_position,10 , 5.0f ,PINK); // PATTERN 1
        Spawner Ring2(spawner_position,3 , -5.0f ,SKYBLUE); //PATTER 2
    //    Spawner Ring3(spawner_position,8,0.0f,BLUE);
        //BOTH PATTERNS COMPOSE THE FLOWER PATTERN


        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(BLACK);
            Marisa.drawPlayer(frameTime);
            Ring.Spawn_action_manager(GetFrameTime());
            Ring2.Spawn_action_manager(GetFrameTime());
//            Ring3.Spawn_action_manager(GetFrameTime());
             EndDrawing();
            }
        CloseWindow();
        }
        // Liberar recursos y cerrar la aplicación
};

#endif //PROJECT_TOUHOU_APP_H
