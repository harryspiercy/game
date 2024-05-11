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

    return true;
}

void LLevel::onTick(){

    tick();
}

void LLevel::onRender(){

    render();
}

void LLevel::onShutdown(){
    
    shutdown();
    closeMedia();
}

