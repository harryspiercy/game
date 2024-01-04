#include "engine.h"
#include "levels/demo.h"

//
// --- Program --- //
//
int main( int argc, char* args[] ){

	// Start up SDL and create window
	if( !ENG::core->init() ){
		cout << "Failed to init core" << endl;
	}
	else{
		cout << "Successfully initialised core" << endl;

		//
		// -- Game loop --
		//
		cout << "Entering the game loop" << endl;
		while( !ENG::core->quit ){

			// Get the current key states
			ENG::core->tick();

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
	}
	//
	// -- Close engine --
	//
	ENG::core->close();
	cout << "Shutdown the core" << endl;

	return 0;
}