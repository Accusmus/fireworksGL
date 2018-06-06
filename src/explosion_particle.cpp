#include "explosion_particle.h"

explosion_particle::explosion_particle()
{
    gravity = glm::vec3(0.0f, -0.002f, 0.0f);
    alive = true;
}

explosion_particle::~explosion_particle()
{
    //dtor
}

void explosion_particle::initExplosionParticle(float sz, glm::vec3 pos){
    float xAcc, yAcc, zAcc;
    glm::vec3 speed;

    xAcc = (rand() % 60 - 30)* 0.006;
    yAcc = (rand() % 20 - 10) * 0.02f;
    zAcc = (rand() % 60 - 30)* 0.006;

    speed = glm::vec3(xAcc,yAcc,zAcc);

    setSize(sz);
    setPosition(pos);
    setAcceleration(speed);
}

void explosion_particle::update(){
    velocity += acceleration + gravity;
    acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    position += velocity;

    if(velocity.y <= -0.2f){
        alive = false;
    }
}
