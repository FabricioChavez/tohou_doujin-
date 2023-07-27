//
// Created by USER on 7/27/2023.
//

#ifndef PROJECT_TOUHOU_SPAWNER_H
#define PROJECT_TOUHOU_SPAWNER_H
#include <iostream>
#include "raylib.h"
#include "global.h"
#include <vector>
#include <cmath>
#include "Projectile.h"
class Spawner{

    Vector2 initialPosition; //Spawner initial postion
    float spawn_ratio=0.25f; // Rate at wich bullets might appear
    float last_shoot_elapsed_time=0.0; // Time elapsed since last shooted bullet

    float BulletSpeed=180;

    float angle_offset =1.0f; // The number of degress deviated from the normal coordinate position
    float angle_change_rate = 10.0f; //rate of change that the angle increments
    int number_of_bullets=3; //Number of bullets in the pattern /default value must be 3 in order  to this for being a ring
    std::vector<Projectile_c> Ring_configuration; // Array of bullets that will be released in an n-ring configuration

public:
    Spawner(const Vector2 &initialPosition, int numberOfBullets) : initialPosition(initialPosition),
                                                                   number_of_bullets(numberOfBullets) {}

    Spawner(const Vector2 &initialPosition, float spawnRatio, float bulletSpeed, int numberOfBullets) : initialPosition(
            initialPosition), spawn_ratio(spawnRatio), BulletSpeed(bulletSpeed), number_of_bullets(numberOfBullets) {}


    void Generate_ring() {
        // Crear un nuevo proyectil en la posición del jugador
        auto divider = float(360.0/number_of_bullets);

        for (int i = 0; i < number_of_bullets; ++i) {
            Projectile_c newProjectile(initialPosition.x , initialPosition.y ,3.0f,BulletSpeed , float((divider-90.0)+float(divider*(float(i+1)))) + angle_offset );
            Ring_configuration.push_back(newProjectile);
        }


    }

    void DrawPattern() { //dt es Getframe para poder actualizar el tiempo elapsed

        for(auto & unique_projectile : Ring_configuration)
        {
            unique_projectile.Draw();
        }

    }

    void Spawn_action_manager(float dt)
    {
        last_shoot_elapsed_time+=dt;
            if (last_shoot_elapsed_time >= spawn_ratio) {
                std::cout<<"DISPARO"<<std::endl;
                Generate_ring();
                angle_offset+=angle_change_rate;
                last_shoot_elapsed_time = 0.0f;
            }

        DrawPattern();
    }

};



#endif //PROJECT_TOUHOU_SPAWNER_H
