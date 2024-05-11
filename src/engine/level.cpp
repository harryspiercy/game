#include "level.h"
#include "core.h"

void LLevel::setup( Core* core ){

    gCore = core;
    gRenderer = gCore->getRenderer();
    gViewport = gCore->getResolution();

}

bool LLevel::onInit(){

    cout << "Load level media" << endl;
    loadMedia();

    cout << "Initialise level" << endl;
    init();

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
    
    cout << "Shutdown level" << endl;
    shutdown();

    cout << "Close level media" << endl;
    closeMedia();
}

shared_ptr< LButton > LLevel::makeButton( int x, int y, string path ){

	// Create a button object and then add to buttons list
    shared_ptr< LButton > rtn = make_shared< LButton >();
	rtn->setPosition( x, y );
	rtn->loadButtonSprites( gRenderer, path );
	buttons.push_back( rtn );
	return rtn;
}