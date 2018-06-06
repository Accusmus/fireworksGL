#include "explosion_particle.h"

explosion_particle::explosion_particle()
{
    gravity = glm::vec3(0.0f, -0.002f, 0.0f);
    size = 1.0f;
    alive = true;
}

explosion_particle::~explosion_particle()
{
    //dtor
}

void explosion_particle::update(){
    velocity += acceleration + gravity;
    acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    position += velocity;

    if(velocity.y <= -0.05f){
        alive = false;
    }
}
