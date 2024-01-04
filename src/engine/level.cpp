#include "level.h"
#include "core.h"

void LLevel::setup( Core* core ){

    gCore = core;
}

bool LLevel::onInit(){

    init();
    loadMedia();

    gRenderer = gCore->getRenderer();
    gViewport = gCore->getResolution();
}

void LLevel::onTick(){

    tick();
}

void LLevel::onShutdown(){
    
    shutdown();
    closeMedia();
}