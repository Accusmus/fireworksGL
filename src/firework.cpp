#include "firework.h"

firework::firework()
{
    gravity = glm::vec3(0.0f, -0.002f, 0.0f);
    size = 1.0f;
    alive = true;
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
