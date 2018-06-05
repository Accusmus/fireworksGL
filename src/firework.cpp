#include "firework.h"

firework::firework()
{
    gravity = glm::vec3(0.0f, -0.002f, 0.0f);
    alive = true;
}

firework::~firework()
{
    //dtor
}

void firework::setPosition(glm::vec3 pos){
    position = pos;
}

void firework::setAcceleration(glm::vec3 acc){
    acceleration = acc;
    velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

void firework::update(){
    velocity += acceleration + gravity;
    acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    position += velocity;

    if(velocity.y <= -0.05f){
        alive = false;
    }
}

void firework::setColour(glm::vec3 col){
    colour = col;
}

glm::vec3 firework::getPosition(){
    return position;
}

glm::vec3 firework::getColour(){
    return colour;
}

bool firework::isAlive(){
    return alive;
}
