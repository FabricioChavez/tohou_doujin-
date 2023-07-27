//
// Created by Jesus Egusquiza on 7/27/2023.
//

#include "global.h"

Global& Global::GetInstance() {
    static Global instance;
    return instance;
}

Global::Global() {
    // INICIALIZAR TEXTURAS
    bull = LoadTexture("../assets/Marisa/Capa1.png");
    bala = LoadTexture("../assets/Marisa/bullte6.png");
}