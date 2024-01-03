#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "common.h"
#include "core.h"

class LLevel{
    //
    // -- Engine globals --
    //
protected:
    // Reference to the game core
    Core* gCore = NULL;
    // Reference to the game renderer
    SDL_Renderer* gRenderer = NULL;
    // Reference to the viewport size.
    Resolution* gViewport = NULL;

   // 
    // -- Level functions --
    //
public:
    // Construct the demo level
    LLevel( Core* core )
    {
        gCore = core;
        gRenderer = core->getRenderer();
        gViewport = core->getResolution();
    }

    // On demo level destroyed
    ~LLevel() {}

    // initialise demo
    //void init( Core* core );
    virtual bool init() { return true; }
//private:
    // load media
    virtual bool loadMedia() { return true; }
public:
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