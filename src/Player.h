//
// Created by USER on 7/24/2023.
//

#ifndef PROJECT_TOUHOU_PLAYER_H
#define PROJECT_TOUHOU_PLAYER_H
#include "iostream"
#include "raylib.h"
#include "global.h"
class  Player {

private:
    //Load player textures
    Texture2D left{};
    Texture2D right{};
    Texture2D down{} ;
    Texture2D up{};
    //Player atributos
    Rectangle sourceRect{}; //Place to draw player
    int currentFrame; // set current frame
    float framesCounter ;
    float framesSpeed; // Velocidad de la animación (menor es más rápido)
    Vector2 initialPosition;
    int spriteHeight;
    int divider;
    int idleSpriteWidth;
    int movingSpriteWidth;


    const float playerSpeed = 5.0f;

public:

    explicit Player(const Vector2 &initialPosition) : initialPosition(initialPosition) {
        left = LoadTexture("../assets/Marisa/LEFT.png");
        right = LoadTexture("../assets/Marisa/RIGHT.png");
        down = LoadTexture("../assets/Marisa/DOWN.png");
        up = LoadTexture("../assets/Marisa/UP.png");
         idleSpriteWidth = up.width / 4;
         movingSpriteWidth = left.width / 8;
         spriteHeight = up.height;

        // Variables para la animación
         currentFrame = 0;
         framesCounter = 0.0f;
         framesSpeed = 0.2f; // Velocidad de la animación (menor es más rápido)
        sourceRect = {0, 0, static_cast<float>(idleSpriteWidth), static_cast<float>(spriteHeight)};
        divider = 4;
    }

  void FrameManager(float  new_frame )
  {
      // Detectar teclas presionadas
      bool isMovingLeft = IsKeyDown(KEY_A);
      bool isMovingRight = IsKeyDown(KEY_D);
      bool isMovingUp = IsKeyDown(KEY_W);
      bool isMovingDown = IsKeyDown(KEY_S);
      framesCounter += GetFrameTime();

      // Actualizar animación
      if (framesCounter >= framesSpeed)
      {
          framesCounter = 0.0f;

          if (currentFrame < divider - 1)
          {
              currentFrame++;
          }
          else
          {
              currentFrame = 0;
          }

          sourceRect.x = currentFrame * idleSpriteWidth;
      }

      // Mover al jugador
      if (isMovingLeft && isMovingRight) // Ambas teclas están presionadas, detener el movimiento
      {
          isMovingLeft = false;
          isMovingRight = false;
      }

      if (isMovingLeft && initialPosition.x > 0)
      {
          sourceRect.width = static_cast<float>(movingSpriteWidth);
          divider = 8; // Cambiar a 8 para animación de LEFT
          initialPosition.x -= playerSpeed;
          currentFrame = 0; // Animación cuando se mueve hacia la izquierda
      }
      else if (isMovingRight && initialPosition.x + sourceRect.width < screenWidth)
      {
          sourceRect.width = static_cast<float>(movingSpriteWidth);
          divider = 8; // Cambiar a 8 para animación de RIGHT
          initialPosition.x += playerSpeed;
          currentFrame = 0; // Animación cuando se mueve hacia la derecha
      }
      else if (isMovingUp && initialPosition.y > 0){
          sourceRect.width = static_cast<float>(idleSpriteWidth);
          divider = 4; // Cambiar a 8 para animación de RIGHT
          initialPosition.y -= playerSpeed;
          currentFrame = 0; // Animación cuando se mueve hacia la derecha
      }
      else if (isMovingDown && initialPosition.y + sourceRect.height < screenHeight){
          sourceRect.width = static_cast<float>(idleSpriteWidth);
          divider = 4; // Cambiar a 8 para animación de RIGHT
          initialPosition.y += playerSpeed;
          currentFrame = 0; // Animación cuando se mueve hacia la derecha
      }
      else
      {
          // Si el jugador no se está moviendo, mostrar el sprite de idle
          sourceRect.width = static_cast<float>(idleSpriteWidth);
          divider = 4; // Cambiar a 4 para animación de IDLE
      }


  }
    void drawPlayer(float  new_frame ){
        FrameManager(new_frame);
        bool isMovingLeft = IsKeyDown(KEY_A);
        bool isMovingRight = IsKeyDown(KEY_D);
        bool isMovingUp = IsKeyDown(KEY_W);
        bool isMovingDown = IsKeyDown(KEY_S);
        // Dibujar al jugador según la animación y el estado de movimiento
        if (isMovingLeft)
        {
            DrawTextureRec(left, sourceRect, initialPosition, WHITE);
        }
        else if (isMovingRight)
        {
            DrawTextureRec(right, sourceRect, initialPosition, WHITE);
        }
        else if (isMovingUp){
            DrawTextureRec(up, sourceRect, initialPosition, WHITE);

        }
        else if (isMovingDown){
            DrawTextureRec(down, sourceRect, initialPosition, WHITE);
        }
        else
        {
            // Si el jugador no se está moviendo, mostrar el sprite de idle
            DrawTextureRec(up, sourceRect, initialPosition, WHITE);
        }

    }


};


#endif //PROJECT_TOUHOU_PLAYER_H
