//
// Created by USER on 7/27/2023.
//

#ifndef PROJECT_TOUHOU_PROJECTILE_H
#define PROJECT_TOUHOU_PROJECTILE_H

#include "raylib.h"
#include "global.h"
#include <cmath>

class Projectile {
public:
    Rectangle rect;
     static  Texture2D bull;

    Vector2 velocity;
    bool active;
    Projectile(float x, float y, float width, float height, float speed, float angle) {
        rect = { x, y, width, height };
//        bull = LoadTexture("../assets/Marisa/bullte6.png");
        float radians = DEG2RAD * angle;
        velocity = { speed * std::cos(radians)*GetFrameTime(), -speed * std::sin(radians)*GetFrameTime() };
        active = true;
    }
    void Draw() {
        if (active) {
            DrawTexture(bull,rect.x,rect.y, WHITE);
            rect.x += velocity.x;
            rect.y += velocity.y;
        }
    }
    ~Projectile(){
//        std::cout << "uwu" << std::endl;
    }
};

class Projectile_c {
public:
    float  radius ;


    Vector2 velocity;
    Vector2 current_postion;
    static Texture2D bull_c;
    Color  color_;
    bool active;

    Projectile_c(float x, float y, float radius ,  float speed, float angle , Color color):radius(radius), color_(color) {
        current_postion = {x ,y};
//        bull = LoadTexture("../assets/Marisa/Capa1.png");

        float radians = DEG2RAD * angle;
        velocity = { speed * std::cos(radians)*GetFrameTime(), -speed * std::sin(radians)*GetFrameTime() };
        active = true;
    }
    void validator(){
        if(current_postion.x < 0 or current_postion.y <0 or current_postion.x> screenWidth or current_postion.y> screenHeight) {
//         std::cout<<"BORRANDO"<<std::endl;
            active = false;
        }
    }

    void Draw() {
        if (active) {
            DrawTexture(bull_c,current_postion.x,current_postion.y, WHITE);

            //DrawCircle(current_postion.x,current_postion.y,radius,color_);
            current_postion.x += velocity.x;
            current_postion.y += velocity.y;

            validator();
        }
    }

    virtual ~Projectile_c() {

    }
};


#endif //PROJECT_TOUHOU_PROJECTILE_H
