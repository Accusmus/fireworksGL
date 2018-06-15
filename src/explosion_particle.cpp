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

    total = 0.0;
    lifespanCount = 0;

    xAcc = (rand() % 30 + 10) * 0.006f;
    yAcc = (rand() % 30 + 10) * 0.006f;
    zAcc = (rand() % 30 + 10) * 0.006f;

    //set it in all directions
    int x, y, z;
    x = rand() % 2 + 1;
    y = rand() % 2 + 1;
    z = rand() % 2 + 1;

    if(x == 1){
        xAcc -= xAcc*2;
    }
    if(y == 1){
        yAcc -= yAcc*2;
    }
    if(z == 1){
        zAcc -= zAcc*2;
    }

    speed = glm::vec3(xAcc,yAcc,zAcc);

    setSize(sz);
    setPosition(pos);
    setAcceleration(speed);

    calculateFriction();

    timeOCreate = glfwGetTime();
}

void explosion_particle::update(){
    velocity += acceleration + gravity;
    acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    position += velocity + friction;

    float current = glfwGetTime();
    float dt = current - timeOCreate;
    timeOCreate = current;
    total += dt;

    if(total >= 1.5f){
        alive = false;
        total = 0.0f;
    }
}

void explosion_particle::calculateFriction(){
    if(acceleration.x > 0.0){
        friction.x = -0.17;
    }else{
        friction.x = 0.17;
    }

    if(acceleration.y > 0.0){
        friction.y = -0.17;
    }else{
        friction.y = 0.17;
    }

    if(acceleration.z > 0.0){
        friction.z = -0.17;
    }else{
        friction.z = 0.17;
    }
}
