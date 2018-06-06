#include "particle.h"

particle::particle()
{
    //ctor
}

particle::~particle()
{
    //dtor
}

void particle::setPosition(glm::vec3 pos){
    position = pos;
}

void particle::setAcceleration(glm::vec3 acc){
    acceleration = acc;
    velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

void particle::setColour(glm::vec3 col){
    colour = col;
}

void particle::setSize(float s){
    size = s;
}

glm::vec3 particle::getPosition(){
    return position;
}

glm::vec3 particle::getColour(){
    return colour;
}

float particle::getSize(){
    return size;
}

bool particle::isAlive(){
    return alive;
}
