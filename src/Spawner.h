//
// Created by USER on 7/27/2023.
//

#ifndef PROJECT_TOUHOU_SPAWNER_H
#define PROJECT_TOUHOU_SPAWNER_H
#include <iostream>
#include <algorithm>
#include "raylib.h"
#include "global.h"
#include <vector>
#include <cmath>
#include "Projectile.h"

class Spawner{

    Vector2 initialPosition; //Spawner initial postion
    float spawn_ratio=0.20f; // Rate at wich bullets might appear
    float last_shoot_elapsed_time=0.0; // Time elapsed since last shooted bullet

    float BulletSpeed=180;

    float angle_offset =90.0f; // The number of degress deviated from the normal coordinate position
    float angle_change_rate = 20.0f; //rate of change that the angle increments
    int number_of_bullets=3; //Number of bullets in the pattern /default value must be 3 in order  to this for being a ring
    std::vector<Projectile_c> Ring_configuration; // Array of bullets that will be released in an n-ring configuration

    Color color_;//Bullet's color

public:
    Spawner(const Vector2 &initialPosition, int numberOfBullets , float angle_change , Color color) : initialPosition(initialPosition),
                                                                   number_of_bullets(numberOfBullets),angle_change_rate(angle_change),
                                                                                                      color_(color) {}

    Spawner(const Vector2 &initialPosition, float spawnRatio, float bulletSpeed, int numberOfBullets) : initialPosition(
            initialPosition), spawn_ratio(spawnRatio), BulletSpeed(bulletSpeed), number_of_bullets(numberOfBullets) {}


    void Generate_ring() {
        // Crear un nuevo n-ring con el siguiente numero de balas y con divider como separador entre los streams de balas
        auto divider = float(360.0/number_of_bullets);

        for (int i = 0; i < number_of_bullets; ++i) {
            Projectile_c newProjectile(initialPosition.x , initialPosition.y ,3.0f,BulletSpeed , float((divider-90.0)+float(divider*(float(i+1)))) + angle_offset,color_ );
            Ring_configuration.push_back(newProjectile);
        }


    }

    void Generate_ring2(float angle) {
        // Crear un nuevo n-ring con el siguiente numero de balas y con divider como separador entre los streams de balas
        auto divider = float(360.0 / number_of_bullets);
        auto barrido = float(angle / float(number_of_bullets - 1));
        if (number_of_bullets == 1){
            barrido = 0;
        }
        for (int i = 0; i < number_of_bullets; ++i) {
            Projectile_c newProjectile(initialPosition.x , initialPosition.y ,6.0f,180 , -105 + barrido*i,color_ );
            Ring_configuration.push_back(newProjectile);
        }


    }
    void DrawPattern() { //dt es Getframe para poder actualizar el tiempo elapsed

        for(auto & unique_projectile : Ring_configuration)
        {
            unique_projectile.Draw();
        }

        Ring_configuration.erase(std::remove_if(Ring_configuration.begin(),Ring_configuration.end(), [](const Projectile_c& proj) {
            return !proj.active;

        }), Ring_configuration.end()   );
    }

    void Spawn_action_manager(float dt)
    {
        last_shoot_elapsed_time+=dt;
            if (last_shoot_elapsed_time >= spawn_ratio) {
//                std::cout<<"DISPARO"<<std::endl;
                Generate_ring();
//                Generate_ring2(45);
                angle_offset+=angle_change_rate;
                last_shoot_elapsed_time = 0.0f;
            }

        DrawPattern();
    }

};


class Spawner_temp{

    Vector2 initialPosition; //Spawner initial postion
    float spawn_ratio=0.20f; // Rate at wich bullets might appear
    float last_shoot_elapsed_time=0.0; // Time elapsed since last shooted bullet

    float BulletSpeed=180;
    int number_of_uses =0;
    int max_numer_of_uses=1;
    float angle_offset =90.0f; // The number of degress deviated from the normal coordinate position
    float angle_change_rate = 20.0f; //rate of change that the angle increments
    int number_of_bullets=3; //Number of bullets in the pattern /default value must be 3 in order  to this for being a ring
    std::vector<Projectile_c> Ring_configuration; // Array of bullets that will be released in an n-ring configuration

    Color color_;//Bullet's color

public:
    Spawner_temp(const Vector2 &initialPosition, int numberOfBullets , float angle_change , Color color) : initialPosition(initialPosition),
                                                                                                      number_of_bullets(numberOfBullets),angle_change_rate(angle_change),
                                                                                                      color_(color) {}

    Spawner_temp(const Vector2 &initialPosition, float spawnRatio, float bulletSpeed, int numberOfBullets) : initialPosition(
            initialPosition), spawn_ratio(spawnRatio), BulletSpeed(bulletSpeed), number_of_bullets(numberOfBullets) {}


    void Generate_ring() {
        // Crear un nuevo n-ring con el siguiente numero de balas y con divider como separador entre los streams de balas
        auto divider = float(360.0/number_of_bullets);

        for (int i = 0; i < number_of_bullets; ++i) {
            Projectile_c newProjectile(initialPosition.x , initialPosition.y ,3.0f,BulletSpeed , float((divider-90.0)+float(divider*(float(i+1)))) + angle_offset,color_ );
            Ring_configuration.push_back(newProjectile);
        }


    }

    void Generate_ring2(float angle) {
        // Crear un nuevo n-ring con el siguiente numero de balas y con divider como separador entre los streams de balas
        auto divider = float(360.0 / number_of_bullets);
        auto barrido = float(angle / float(number_of_bullets - 1));
        if (number_of_bullets == 1){
            barrido = 0;
        }
        for (int i = 0; i < number_of_bullets; ++i) {
            Projectile_c newProjectile(initialPosition.x , initialPosition.y ,6.0f,180 , -105 + barrido*i,color_ );
            Ring_configuration.push_back(newProjectile);
        }


    }
    void DrawPattern() { //dt es Getframe para poder actualizar el tiempo elapsed
        std::cout<<"NUMER OF USES :"<<max_numer_of_uses<<std::endl;

            for (auto &unique_projectile: Ring_configuration) {
                unique_projectile.Draw();
            }

            Ring_configuration.erase(
                    std::remove_if(Ring_configuration.begin(), Ring_configuration.end(), [](const Projectile_c &proj) {
                        return !proj.active;

                    }), Ring_configuration.end());

    }
    void Spawn_action_manager(float dt)
    {
        last_shoot_elapsed_time+=dt;

        if (last_shoot_elapsed_time >= spawn_ratio) {
            number_of_uses++;
            if ( number_of_uses<=max_numer_of_uses)
            Generate_ring();

            angle_offset+=angle_change_rate;
            last_shoot_elapsed_time = 0.0f;
        }


            DrawPattern();
    }

};




#endif //PROJECT_TOUHOU_SPAWNER_H
