#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "common.h"
#include <SDL2/SDL.h> // remove this

class LLevel{
    //
    // -- Engine globals --
    //
public:
    // Reference to the game core
    class Core* gCore = NULL;
    // Reference to the game renderer
    SDL_Renderer* gRenderer = NULL;
    // Reference to the viewport size.
    struct Resolution* gViewport = NULL;

    // 
    // -- Level functions --
    //
public:
    // Construct the demo level
    LLevel() {}

    // Set up references 
    void setup( Core* core );

    // On demo level destroyed
    ~LLevel() {}

    // initialise demo
    virtual bool init() { return true; }

    // load media
    virtual bool loadMedia() { return true; }

    // tick demo
    virtual void tick() {} 
    
    // shutdown the level properties
    virtual void shutdown() {}

    // close demo media down
    virtual void closeMedia() {}

public:
    bool onInit();
    void onTick();
    void onShutdown();

};

#endif