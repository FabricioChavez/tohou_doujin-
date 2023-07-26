//
// Created by USER on 7/24/2023.
//

#ifndef PROJECT_TOUHOU_PLAYER_H
#define PROJECT_TOUHOU_PLAYER_H

#include <algorithm>
#include "iostream"
#include "raylib.h"
#include "global.h"
#include "vector"
#include "string"
#include "queue"
#include <cmath>



class Projectile {
public:
    Rectangle rect;
    Vector2 velocity;
    bool active;

//    Projectile(float x, float y, float width, float height, float speed) {
//        rect = { x, y, width, height };
//        velocity = { 0, -speed
//        };
//        active = true;
//    }
    Projectile(float x, float y, float width, float height, float speed, float angle) {
        rect = { x, y, width, height };
        float radians = DEG2RAD * angle;
        velocity = { speed * std::cos(radians), -speed * std::sin(radians) };
        active = true;
    }
    void Update() {
        if (active) {
            rect.x += velocity.x;
            rect.y += velocity.y;
        }
    }

    void Draw() const {
        if (active) {
            DrawRectangleRec(rect, RED);
        }
    }
};


class  Player {

private:
    //Load player textures
    std::vector<Projectile> projectiles;
    bool isShooting; // Variable para controlar si el jugador está disparando

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


    void Shoot(float angle) {
        // Crear un nuevo proyectil en la posición del jugador
        Projectile newProjectile(initialPosition.x + sourceRect.width/2 - 4, initialPosition.y + sourceRect.height / 2 - 30, 10, 10, 5,angle);
        projectiles.push_back(newProjectile);
    }

    void UpdateProjectiles() {
        std::cout << projectiles.size() << std::endl;
        for (int i = 0; i < projectiles.size(); i++) {
            projectiles[i].Update();
            if (projectiles[i].rect.y < 0) {
                std::cout << "remove"<< std::endl;
                // Si el proyectil sale de la pantalla, desactivarlo y eliminarlo de la lista
                projectiles[i].active = false;
            }
        }
        // Eliminar los proyectiles inactivos de la lista
        projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](const Projectile& proj) {
            return !proj.active;
        }), projectiles.end());
    }

    void DrawProjectiles() {
        for (const auto& projectile : projectiles) {
            projectile.Draw();
        }
    }

    void FrameManager(float  new_frame )
  {
      // Detectar teclas presionadas
      bool isMovingLeft = IsKeyDown(KEY_LEFT);
      bool isMovingRight = IsKeyDown(KEY_RIGHT);
      bool isMovingUp = IsKeyDown(KEY_UP);
      bool isMovingDown = IsKeyDown(KEY_DOWN);
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
      if (isMovingUp && initialPosition.y > 0){
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



  }
    void drawPlayer(float  new_frame ){
        FrameManager(new_frame);
        bool isMovingLeft = IsKeyDown(KEY_LEFT);
        bool isMovingRight = IsKeyDown(KEY_RIGHT);
        bool isMovingUp = IsKeyDown(KEY_UP);
        bool isMovingDown = IsKeyDown(KEY_DOWN);
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
