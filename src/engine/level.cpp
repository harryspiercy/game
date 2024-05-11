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

void LLevel::onHandleEvent( SDL_Event* e ){

    // Update the buttons on screen
    for( auto const& b : buttons ){
        b->handleEvent( e );
    }
}

void LLevel::onRender(){

    render();

	if( renderButton ){
		for( auto& button :  buttons ) {
			button->render( gRenderer );
		}
	}
}

void LLevel::onShutdown(){
    
    shutdown();
    closeMedia();
}

LButton* LLevel::makeButton( int x, int y, string path ){
	// Create a button object and then add to buttons list
	LButton* rtn = new LButton();
	rtn->setPosition( x, y );
	rtn->loadButtonSprites( gRenderer, path );
	buttons.push_back( rtn );
	return rtn;
}