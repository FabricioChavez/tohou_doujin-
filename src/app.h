//
// Created by Jesus Egusquiza on 7/24/2023.
//

#ifndef PROJECT_TOUHOU_APP_H
#define PROJECT_TOUHOU_APP_H
#include "raylib.h"
#include "global.h"
#include "Player.h"
using namespace std;
Music music;
bool paused = false;
struct app{
    static void runApp(){
        InitAudioDevice();
        InitWindow(screenWidth, screenHeight, "Blockchain Visualization");

        Texture2D MarisaObject = LoadTexture("../assets/Marisa/RIGHT.png");
        int spriteWidth = MarisaObject.width/8;
        int spretHeigth = MarisaObject.height;
        Rectangle sourceRect ={0,0,static_cast<float> (spriteWidth), static_cast<float > (spretHeigth)}; // Square to draw sprite in
        float currentFrame =0; // set current frame
        float frameTime = 0.0f; // set frame time
        Vector2 position = { 720, 200 }; // windows postion intial
        SetTargetFPS(60);
        Player Marisa(position);
        while (!WindowShouldClose()) {

            frameTime += GetFrameTime();
            //pra dibujar el frame




            BeginDrawing();
            ClearBackground(BLACK);
            Marisa.drawPlayer(frameTime);
                EndDrawing();
            }
        CloseWindow();
        }
        // Liberar recursos y cerrar la aplicación
};

#endif //PROJECT_TOUHOU_APP_H
