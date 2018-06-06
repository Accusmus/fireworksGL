#include "firework_manager.h"

firework_manager::firework_manager()
{

}

firework_manager::~firework_manager()
{

}

void firework_manager::update(){
    std::vector<int> deadFireworks;
    for(size_t i = 0; i < fireworks.size(); i++){
        fireworks[i].update();
        if(!fireworks[i].isAlive()){
            deadFireworks.push_back(i);
        }
    }

    for(auto a = deadFireworks.begin(); a != deadFireworks.end(); a++){
        fireworks.erase(fireworks.begin() + *a);
    }
}

void firework_manager::createFirework(glm::vec3 pos, glm::vec3 acc, float size){
    firework firewk = firework();
    firewk.setSize(size);
    firewk.setPosition(pos);
    firewk.setAcceleration(acc);
    fireworks.push_back(firewk);
}

void firework_manager::createFirework(float size){
    float xAcc, yAcc, zAcc;
    glm::vec3 pos, speed;

    xAcc = (rand() % 60 - 30)* 0.002;
    yAcc = (rand() % 20 + 10) * 0.015f;
    zAcc = (rand() % 60 - 30)* 0.002;

    pos = glm::vec3(0.0f,-20.0f,-30.0f);
    speed = glm::vec3(xAcc,yAcc,zAcc);

    firework firewk = firework();
    firewk.setSize(size);
    firewk.setPosition(pos);
    firewk.setAcceleration(speed);
    firewk.setSize(size);
    fireworks.push_back(firewk);
}

void firework_manager::createNumFireworks(int num, float size){
    for(int i = 0; i < num; i++){
        createFirework(size);
        glm::vec3 col = createRandomColour();
        fireworks.back().setColour(col);
    }
}

//===========================================
//getters and setters
//===========================================

int firework_manager::getNumOfFireworks(){
    return fireworks.size();
}

glm::vec3 firework_manager::getFireworkColour(int id){
    return fireworks[id].getColour();
}

glm::vec3 firework_manager::getFireworkPos(int id){
    return fireworks[id].getPosition();
}

float firework_manager::getFireworkSize(int id){
    return fireworks[id].getSize();
}

void firework_manager::setFireworkSize(int id, float s){
    fireworks[id].setSize(s);
}

//======================================================
//private funcions
//======================================================

glm::vec3 firework_manager::createRandomColour(){
    float r, g, b;

    r = (rand() % 100 + 1) * 0.01f;
    g = (rand() % 100 + 1) * 0.01f;
    b = (rand() % 100 + 1) * 0.01f;

    return glm::vec3(r, g, b);
}

//====================================================
//Renderer Functions
//====================================================

void firework_manager::initRenderer(){
    renderer = firework_renderer();
}

void firework_manager::render(int id, float modelMat[16], glm::mat4 viewMat){
    glm::vec3 fwCol = getFireworkColour(id);

    renderer.renderObj(fwCol, modelMat, viewMat);
}

void firework_manager::deleteRenderObj(){
    renderer.deleteObjects();
}
