#include "core.h"

Core::Core( int x, int y) : 
    window( NULL ), resolution( x, y ),
    renderer( NULL ){
}

Core::~Core(){
    close();
}

bool Core::init(){
	// Inisitialise flag
	bool success = true;

	int imgFlags = IMG_INIT_PNG;

	// Initialise SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		cout << "SDL could not initialise! SDL Error :" << SDL_GetError() << endl;
		success = false;
	}
	else if( !( IMG_Init( imgFlags ) & imgFlags ) ){
		cout << "SDL Image could not initialise! SDL Error :" << IMG_GetError() << endl;
		success = false;
	}
	else if( TTF_Init() == -1 ){
		cout << "SDL_ ttf could not initialise! SDL Error :" << TTF_GetError() << endl;
		success = false;
	}
	else{
		// Create window
		window = SDL_CreateWindow(
			"SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			resolution.x, resolution.y, SDL_WINDOW_SHOWN
		);

		if( window == NULL ){
			cout << "Window could not be created! SDL Error : " << SDL_GetError() << endl;
			success = false;
		}
		else{
			// create renderer for widow.
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderer == NULL ){
				cout << "Renderer could not be created! SDL Error : " << SDL_GetError() << endl;
				success = false;
			}
			else{
				// Initialise renderer colour to white
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
			}
		}
	}

	return success;
}

void Core::close(){
	// Free global font
	//TTF_CloseFont( gSceneGuideText.mFont );
	//gSceneGuideText.mFont = NULL;

	// Destroy renderer
	SDL_DestroyRenderer( renderer );
	renderer = NULL;

	// Destroy window
	SDL_DestroyWindow( window );
	window = NULL;

	// Quit SDL Subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Core::clearRenderer(){
    SDL_RenderClear( renderer );
}

void Core::setDrawColour( Uint8 x, Uint8 y, Uint8 z, Uint8 a ){
    SDL_SetRenderDrawColor( renderer, x, y, z, a );
}

void Core::present(){
    SDL_RenderPresent( renderer );
}