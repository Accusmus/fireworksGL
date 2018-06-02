#include "firework_manager.h"

firework_manager::firework_manager()
{
    //ctor
}

firework_manager::~firework_manager()
{
    //dtor
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

void firework_manager::createFirework(glm::vec3 pos, glm::vec3 acc){
    firework firewk = firework();
    firewk.setPosition(pos);
    firewk.setAcceleration(acc);
    fireworks.push_back(firewk);
}

int firework_manager::getNumOfFireworks(){
    return fireworks.size();
}

glm::vec3 firework_manager::getFireworkPos(int id){
    return fireworks[id].getPosition();
}
