#include "level.h"
#include "core.h"

bool LLevel::onInit(){

    // Load the level media
    cout << "Load level media" << endl;
    loadMedia();

    // Initialise the level
    cout << "Initialise level" << endl;
    init();

    return true;
}

void LLevel::onTick(){

    // Tick the level
    tick();

    // Tick all the entities
    for( auto& entity : entities ){
        entity->onTick();
    }
}

void LLevel::onHandleEvent( SDL_Event* e ){

    // Update the buttons on screen
//    for( auto const& b : buttons ){
//        b->handleEvent( e );
//    }

    // handle all entity events
    for( auto const& entity : entities ){
        entity->onHandleEvents( e );
    }

}

void LLevel::onRender(){

    // Render the level
    render();

    // Render all entities
    for( auto& entity : entities ){
        entity->onRender();
    }

    // Render all buttons
//	if( renderButton ){
//		for( auto& button :  buttons ) {
//			button->render( gRenderer );
//		}
//	}
}

void LLevel::onShutdown(){
    
    // Shutdown all level entities
    for( auto& entity : entities ){
        entity->onShutdown();
    }

    // Shutdown the level
    cout << "Shutdown level" << endl;
    shutdown();

    // Close the media of the level
    cout << "Close level media" << endl;
    closeMedia();
}