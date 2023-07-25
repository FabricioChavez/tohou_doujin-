//
// Created by USER on 7/24/2023.
//

#ifndef PROJECT_TOUHOU_PLAYER_H
#define PROJECT_TOUHOU_PLAYER_H
#include "iostream"
#include "raylib.h"
class  Player {

private:
    //Load player textures
    Texture2D left{};
    Texture2D right{};
    Texture2D down{} ;
    Texture2D up{};
    //Player atributos
    Rectangle sourceRect{}; //Place to draw player
    float currentFrame =0; // set current frame
    float frameTime = 0.0f; // set frame time
    Vector2 initialPosition;
    int spriteWidth_;
    int spriteHeith_;
    int divider =1 ;
    float velx =2.0;
    float vely=2.0;


public:

    explicit Player(const Vector2 &initialPosition) : initialPosition(initialPosition) {
        left = LoadTexture("../assets/Marisa/LEFT.png");
        right = LoadTexture("../assets/Marisa/RIGHT.png");
        down = LoadTexture("../assets/Marisa/DOWN.png");
        up = LoadTexture("../assets/Marisa/UP.png");

    }

  void FrameManager(float  new_frame )
  {
      spriteHeith_ = up.height;
        if(IsKeyDown(KEY_W) or IsKeyDown(KEY_S))
        {
             divider =4;

             spriteWidth_ = up.width/divider;
        }
        else if(IsKeyDown(KEY_A) or IsKeyDown(KEY_D))
        {
            divider=8;

            spriteWidth_ = left.width/divider;
        }else {
            divider =4;

            spriteWidth_ = up.width/divider;
        }
      sourceRect = {0, 0, static_cast<float>(spriteWidth_), static_cast<float>(spriteHeith_)};
       frameTime+=new_frame;
      if(frameTime > 20.0f)
      {
          frameTime =0.0f;
          currentFrame++;
           // std::cout<<"DIVIDER :"<<divider<<std::endl;
          if(currentFrame>=divider)
              currentFrame=0;




      }
      sourceRect.x = currentFrame * spriteWidth_;


  }
    void drawPlayer(float  new_frame ){
        FrameManager(new_frame);

        if(IsKeyDown(KEY_W)) {
            std::cout<<"SORUCE :"<<sourceRect.x<<std::endl;

            initialPosition.y -= vely;
            DrawTextureRec(up, sourceRect, initialPosition, WHITE);
        } else if(IsKeyDown(KEY_A)) {
            std::cout<<"SORUCE :"<<sourceRect.x<<std::endl;

            initialPosition.x -= velx;
            DrawTextureRec(left, sourceRect, initialPosition, WHITE);
        } else if(IsKeyDown(KEY_S)) {
            std::cout<<"SORUCE :"<<sourceRect.x<<std::endl;

            initialPosition.y += vely;
            DrawTextureRec(down, sourceRect, initialPosition, WHITE);
        } else if(IsKeyDown(KEY_D)) {
            std::cout<<"SORUCE :"<<sourceRect.x<<std::endl;

            initialPosition.x += velx;
            DrawTextureRec(right, sourceRect, initialPosition, WHITE);
        } else {
            std::cout<<"SORUCE :"<<sourceRect.x<<std::endl;

            DrawTextureRec(down, sourceRect, initialPosition, WHITE);
        }

    }


};


#endif //PROJECT_TOUHOU_PLAYER_H
