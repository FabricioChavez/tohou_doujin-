//
// Created by Jesus Egusquiza on 7/24/2023.
//

#ifndef PROJECT_TOUHOU_APP_H
#define PROJECT_TOUHOU_APP_H
#include "raylib.h"
const int screenWidth = 2000;
const int screenHeight = 1000;
using namespace std;
Music music;
bool paused = false;
struct app{
    static void runApp(){
        InitAudioDevice();
        InitWindow(screenWidth, screenHeight, "Blockchain Visualization");
        SetTargetFPS(60);
        bool showMenu = true;
        bool shouldExit = false;
        music  = LoadMusicStream("../sounds/sound2.mp3");
//         PlayMusicStream(music);

        // Redimensionar la imagen a un tamaño más pequeño
        int temp = 0;
        // Reproducir la música en bucle


//    // Reproducir la música en bucle
        Image iconKAWAI = LoadImage("../textures/icon_windowscompress.png");
        SetWindowIcon(iconKAWAI);
        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(BLACK);

                EndDrawing();
            }
        CloseWindow();
        }
        // Liberar recursos y cerrar la aplicación
};

#endif //PROJECT_TOUHOU_APP_H
