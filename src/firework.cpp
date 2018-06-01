#include "firework.h"

firework::firework()
{
    //ctor
}

firework::~firework()
{
    //dtor
}

void firework::setPosition(glm::vec3 pos){
    position = pos;
}

void firework::setSpeed(glm::vec3 spd){
    speed = spd;
}

void firework::update(){
    position += speed;
}

glm::vec3 firework::getPosition(){
    return position;
}
