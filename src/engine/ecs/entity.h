#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "common.h"

class Core;

class Entity{

public:


    Entity( string name );
    ~Entity() {}

    virtual void init() {}
    virtual void loadMedia() {}
    virtual void handleEvents( SDL_Event* e ) {}
    virtual void tick() {}
    virtual void render() {}
    virtual void closeMedia() {}
    virtual void shutdown() {}

    void onInit();
    void onHandleEvents( SDL_Event* e );
    void onTick();
    void onRender();
    void onShutdown();

    Core* core;
    string entityName;

    bool visible;
};

#endif