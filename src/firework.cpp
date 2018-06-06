#include "firework.h"

firework::firework()
{
    gravity = glm::vec3(0.0f, -0.002f, 0.0f);
    alive = true;
}

void firework::initFirework(float sz, glm::vec3 initPos){
    float xAcc, yAcc, zAcc;
    glm::vec3 speed;

    xAcc = (rand() % 60 - 30)* 0.002;
    yAcc = (rand() % 20 + 10) * 0.015f;
    zAcc = (rand() % 60 - 30)* 0.002;

    speed = glm::vec3(xAcc,yAcc,zAcc);

    setSize(sz);
    setPosition(initPos);
    setAcceleration(speed);
}


firework::~firework()
{
    //dtor
}

void firework::update(){
    velocity += acceleration + gravity;
    acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    position += velocity;

    if(velocity.y <= -0.05f){
        alive = false;
    }
}
