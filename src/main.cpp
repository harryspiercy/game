#include "engine.h"
#include "demo.h"

//
// -- Engine globals --
//
// Create the core object
SDL_Renderer* gRenderer = NULL;
Resolution* gViewport = NULL;
Demo demo;

//
// --- Program --//
//
int main( int argc, char* args[] ){

	// Start up SDL and create window
	if( !ENG::core->init() ){
		cout << "Failed to init core" << endl;
	}
	else{
		cout << "Successfully initialised core" << endl;
		
		// Demo init
		demo.init( ENG::core );
		
		//
		// -- Game loop --
		//
		cout << "Entering the game loop" << endl;
		while( !ENG::core->quit ){

			// Get the current key states
			ENG::core->tick();

			// Set exit flag
			if( ENG::core->getKeyState( SDL_SCANCODE_ESCAPE ) == KEY_RELEASED ){
				ENG::core->quit = true;
			}

			// demo tick
			demo.tick();

			// Update screen
			ENG::core->render();

			// Apply any frame rate capping
			ENG::core->capFrameRate();

			// -----
			// End of draw call
			// -----
		}
		//
		// -- Close game --
		//

		//
		// -- Close media --
		//
		demo.closeMedia();
		cout << "Shutdown media" << endl;
	}
	//
	// -- Close engine --
	//
	ENG::core->close();
	cout << "Shutdown the core" << endl;

	return 0;
}