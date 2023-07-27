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
    Vector2 velocity;
    bool active;
    Projectile(float x, float y, float width, float height, float speed, float angle) {
        rect = { x, y, width, height };
        float radians = DEG2RAD * angle;
        velocity = { speed * std::cos(radians)*GetFrameTime(), -speed * std::sin(radians)*GetFrameTime() };
        active = true;
    }
    void Draw() {
        if (active) {

            DrawRectangleRec(rect, RED);
            rect.x += velocity.x;
            rect.y += velocity.y;
        }
    }
};

class Projectile_c {
public:
    float  radius ;
    Vector2 velocity;
    Vector2 current_postion;
    bool active;
    Projectile_c(float x, float y, float radius ,  float speed, float angle):radius(radius) {
        current_postion = {x ,y };
        float radians = DEG2RAD * angle;
        velocity = { speed * std::cos(radians)*GetFrameTime(), -speed * std::sin(radians)*GetFrameTime() };
        active = true;
    }
    void Draw() {
        if (active) {

            DrawCircle(current_postion.x,current_postion.y,radius,MAGENTA);
            current_postion.x += velocity.x;
            current_postion.y += velocity.y;
        }
    }
};
#endif //PROJECT_TOUHOU_PROJECTILE_H
