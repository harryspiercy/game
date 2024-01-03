#include "level.h"

bool LLevel::onInit(){
    init();
    loadMedia();
}

void LLevel::onTick(){
    tick();
}

void LLevel::onShutdown(){
    shutdown();
    closeMedia();
}