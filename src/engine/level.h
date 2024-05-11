#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "common.h"

#include "button.h"

class LLevel{
    //
    // -- Engine globals --
    //
public:
    //! Reference to the game core
    class Core* gCore = NULL;
    //! Reference to the game renderer
    SDL_Renderer* gRenderer = NULL;
    //! Reference to the viewport size.
    struct Resolution* gViewport = NULL;

    // 
    // -- Level functions --
    //
public:
    //! Construct the demo level
    LLevel() {}

    //! Set up references 
    /** \param core reference to the engine core 
    */
    void setup( Core* core );

    //! On demo level destroyed
    ~LLevel() {}

    //! Child defined initialisation function
    /** \return success of initialisation
    */ 
    virtual bool init() { return true; }

    //! Child defined media loading function
    /** \return success of loading media
    */
    virtual bool loadMedia() { return true; }

    //! Child defined tick function
    virtual void tick() {} 

    //! Child defined render function
    virtual void render() {} 

    //! Child defined shutdown function
    virtual void shutdown() {}

    //! Child defined media closing function
    virtual void closeMedia() {}

public:
    //! Process for initialising a level
    /** \return success of level initiailisation process
    */
    bool onInit();

    //! Process for handling input events for a level
    void onHandleEvent( SDL_Event* e );

    //! Process for ticking a level
    void onTick();

    //! Process for rendering a level
    void onRender();

    //! Process for shutingdown a level  
    void onShutdown();

    //
    // -- Level containers
    //
private:
    //! List of buttons associated with the level.
    list< LButton* > buttons;

public:
    //! Make a button and add to list in level.
    LButton* makeButton( int x, int y, string path = string( "../media/buttonSpriteSheet.png" ) );

    //! TEMP
    bool renderButton = false;

};

#endif