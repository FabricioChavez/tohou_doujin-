//
// Created by Jesus Egusquiza on 7/24/2023.
//

#ifndef PROJECT_TOUHOU_GLOBAL_H
#define PROJECT_TOUHOU_GLOBAL_H
const int screenWidth = 480;
const int screenHeight = 640;
#include "raylib.h"


#include "raylib.h"

class Global {
public:
    static Global& GetInstance();

    // Evitar la copia y asignación
    Global(Global const&) = delete;
    void operator=(Global const&) = delete;

    Texture2D bull;
    Texture2D bala;
    Sound leftSound{};

private:
    Global(); // Constructor privado para evitar que se cree directamente
};

#endif //PROJECT_TOUHOU_GLOBAL_H
