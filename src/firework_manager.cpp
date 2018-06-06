#include "firework_manager.h"

firework_manager::firework_manager()
{

}

firework_manager::~firework_manager()
{

}

void firework_manager::update(){
    std::vector<int> deadFireworks, deadExpParticle;
    for(size_t i = 0; i < fireworks.size(); i++){
        fireworks[i].update();
        if(!fireworks[i].isAlive()){
            deadFireworks.push_back(i);
        }
    }

    for(size_t i = 0; i < expParticle.size(); i++){
        expParticle[i].update();
        if(!expParticle[i].isAlive()){
            deadExpParticle.push_back(i);
        }
    }

    for(auto a = deadFireworks.begin(); a != deadFireworks.end(); a++){
        fireworks.erase(fireworks.begin() + *a);
        createNumExplosionParticles(10, 0.5);
    }

    for(auto a = deadExpParticle.begin(); a != deadExpParticle.end(); a++){
        expParticle.erase(expParticle.begin() + *a);
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
    fireworks.push_back(firewk);
}

void firework_manager::createNumFireworks(int num, float size){
    for(int i = 0; i < num; i++){
        createFirework(size);
        glm::vec3 col = createRandomColour();
        fireworks.back().setColour(col);
    }
}

void firework_manager::createExplosionParticle(float size){
    float xAcc, yAcc, zAcc;
    glm::vec3 pos, speed;

    xAcc = (rand() % 60 - 30)* 0.002;
    yAcc = (rand() % 20 + 10) * 0.015f;
    zAcc = (rand() % 60 - 30)* 0.002;

    pos = glm::vec3(20.0f,-20.0f,-30.0f);
    speed = glm::vec3(xAcc,yAcc,zAcc);

    explosion_particle exp = explosion_particle();
    exp.setSize(size);
    exp.setPosition(pos);
    exp.setAcceleration(speed);
    expParticle.push_back(exp);
}

void firework_manager::createNumExplosionParticles(int num, float size){
    for(int i = 0; i < num; i++){
        createExplosionParticle(size);
        glm::vec3 col = glm::vec3(1.0, 1.0, 1.0);
        expParticle.back().setColour(col);
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

void firework_manager::render(glm::mat4 viewMat){

    for(size_t i = 0; i < fireworks.size(); i++){
        float tr[16], sc[16], res[16];
        float fwSize = getFireworkSize(i);
        glm::vec3 fwPos = getFireworkPos(i);

        //calculate transform
        translate(fwPos.x, fwPos.y, fwPos.z, tr);
        scale(fwSize, fwSize, fwSize, sc);
        multiply44(tr, sc, res);

        //render each object
        glm::vec3 fwCol = getFireworkColour(i);

        renderer.renderObj(fwCol, res, viewMat);
    }

    for(size_t i = 0; i < expParticle.size(); i++){
        float tr[16], sc[16], res[16];
        float expSize = expParticle[i].getSize();
        glm::vec3 expPos = expParticle[i].getPosition();

        //calculate transform
        translate(expPos.x, expPos.y, expPos.z, tr);
        scale(expSize, expSize, expSize, sc);
        multiply44(tr, sc, res);

        //render each object
        glm::vec3 expCol = expParticle[i].getColour();

        renderer.renderObj(expCol, res, viewMat);
    }
}

void firework_manager::deleteRenderObj(){
    renderer.deleteObjects();
}
