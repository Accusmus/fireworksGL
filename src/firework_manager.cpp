#include "firework_manager.h"

firework_manager::firework_manager()
{

}

firework_manager::~firework_manager()
{

}

//=============================================
//Update method
//=============================================

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

    for(size_t a = 0; a < deadFireworks.size(); a++){
        glm::vec3 pos = fireworks.at(a).getPosition();
        createNumExplosionParticles(30, 0.1, pos);
        fireworks.erase(fireworks.begin() + a);
    }

    for(auto a = deadExpParticle.begin(); a != deadExpParticle.end(); a++){
        expParticle.erase(expParticle.begin() + *a);
    }
}

//=============================================
//Methods for creating fireworks
//=============================================

void firework_manager::createFirework(float size, glm::vec3 pos){
    firework firewk = firework();
    firewk.initFirework(size, pos);
    fireworks.push_back(firewk);
}

void firework_manager::createNumFireworks(int num, float size, glm::vec3 pos){
    for(int i = 0; i < num; i++){
        createFirework(size, pos);
        fireworks.back().setColour(glm::vec3(0.0, 0.0, 0.0));
    }
}

void firework_manager::createNumFireworks(int num, float size, glm::vec3 pos, glm::vec3 col){
    for(int i = 0; i < num; i++){
        createFirework(size, pos);
        fireworks.back().setColour(col);
    }
}

//=================================================================
//Methods for creating explosion particles
//=================================================================
void firework_manager::createExplosionParticle(float size, glm::vec3 pos){
    explosion_particle exp = explosion_particle();
    exp.initExplosionParticle(size, pos);
    expParticle.push_back(exp);
}

void firework_manager::createNumExplosionParticles(int num, float size, glm::vec3 pos){
    glm::vec3 col = createRandomColour();
    for(int i = 0; i < num; i++){
        createExplosionParticle(size, pos);
        expParticle.back().setColour(col);
    }
}

//===========================================
//getter and setter methods
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

int firework_manager::getNumOfExplosionParticles(){
    return expParticle.size();
}

//======================================================
//private methods
//======================================================

glm::vec3 firework_manager::createRandomColour(){

    glm::vec3 colList[7];
    colList[0] = glm::vec3(0.0,0.0,1.0);
    colList[1] = glm::vec3(0.0,1.0,0.0);
    colList[2] = glm::vec3(0.0,1.0,1.0);
    colList[3] = glm::vec3(1.0,0.0,0.0);
    colList[4] = glm::vec3(1.0,0.0,1.0);
    colList[5] = glm::vec3(1.0,1.0,0.0);
    colList[6] = glm::vec3(1.0,1.0,1.0);


    return colList[rand() % 7];
}

//====================================================
//Renderer Methods
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
