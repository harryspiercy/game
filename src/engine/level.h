#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "common.h"

#include "button.h"
#include "ecs/entity.h"

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
    //! List of entities associated with the level.
    list< shared_ptr< Entity > > entities;

    //! List of buttons associated with the level.
    list< shared_ptr< LButton > > buttons;

public:
    //! Make an entity and add to list in level.
    //shared_ptr< Entity > makeEntity( string name );

    //! Load a new level of type T.
    template< typename T >
    shared_ptr< T > makeEntity( string name ){
    
        // Create a button object and then add to buttons list
        shared_ptr< T > rtn = make_shared< T >( name );
        rtn->core = gCore;
        rtn->onInit();
    	entities.push_back( rtn );
        cout << name << " make entity" << endl;
    	return rtn;
    }

    //! TEMP
    bool renderButton = false;
};

#endif