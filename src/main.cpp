#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<string>
#include"texture.h"

using std::cout;
using std::endl;
using std::string;

//
// -- Engine globals --
//
// Engine window
SDL_Window* gWindow = NULL;
const int SCREENWIDTH = 640;
const int SCREENHEIGHT = 480;

// Texture renderer to link to window
SDL_Renderer* gRenderer = NULL;

// Texture to load image to
LTexture gColourCircleClipSheet;
const int COLOUR_CIRCLE_CLIPS = 4;
SDL_Rect gColourCircleClips[ COLOUR_CIRCLE_CLIPS ];

LTexture gSpriteTextureSheet;
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gAnimSpriteClips[ WALKING_ANIMATION_FRAMES ];

// Other example content
LTexture gFadeTexture;



//
// -- Engine methods --
//

//
// -- Game globals --
//


//
// -- Game methods --
//
// Start up sdl and create a window
bool init();
// load media
bool loadMedia();
// Frees media and shuts down SDL
void close();


//
// --- Program --//
//
int main( int argc, char* args[] ){
	// Start up SDL and create window
	if( !init() ){
		cout << "Failed to init" << endl;
	}
	else{
		// Load media
		if( !loadMedia() ){
			cout << "Failed to load media" << endl;
		}
		else{
			//
			// -- Pregame --
			//

			// Load the default state

			// Create an event handler
			SDL_Event e;
			// Create an exit flag
			bool quit = false;

			// Modulation components
			Uint8 red = 255;
			Uint8 green = 255;
			Uint8 blue = 255;

			Uint8 alpha = 255;

			int frame = 0;
			//
			// -- Game loop --
			//
			while( !quit ){
				// Poll hardware events
				while( SDL_PollEvent( &e )){
					// Exit event
					if( e.type == SDL_QUIT ){
						quit = true;
					}
					else if( e.type == SDL_KEYDOWN ){
						switch( e.key.keysym.sym ){

							case SDLK_UP:
							if( alpha + 32 > 255 ) alpha = 255;
							else alpha += 32;
							break;

							case SDLK_DOWN:
							if( alpha - 32 < 0 ) alpha = 0;
							else alpha -= 32;
							break;

							case SDLK_LEFT:
							break;

							case SDLK_RIGHT:
							break;

							case SDLK_ESCAPE:
							quit = true;
							break;

							case SDLK_q:
							red += 32;
							break;

							case SDLK_a:
							red -= 32;
							break;

							case SDLK_w:
							green += 32;
							break;

							case SDLK_s:
							green -= 32;
							break;

							case SDLK_e:
							blue += 32;
							break;

							case SDLK_d:
							blue -= 32;
							break;
							default:
							break;
						}
					}
				}

				// Clear the screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				// Draw the modular background
				gColourCircleClipSheet.setColour( red, green, blue );

				gColourCircleClipSheet.render( gRenderer, 0, 0, &gColourCircleClips[0] );
				gColourCircleClipSheet.render( gRenderer, SCREENWIDTH - gColourCircleClips[1].w, 0, &gColourCircleClips[1] );
				gColourCircleClipSheet.render( gRenderer, 0, SCREENHEIGHT - gColourCircleClips[2].h, &gColourCircleClips[2] );
				gColourCircleClipSheet.render( gRenderer, SCREENWIDTH - gColourCircleClips[3].w, SCREENHEIGHT - gColourCircleClips[3].h, &gColourCircleClips[3] );

				// Render the current frame
				SDL_Rect* currentClip = &gAnimSpriteClips[ frame / 4 ];
				gSpriteTextureSheet.render( gRenderer, ( SCREENWIDTH - currentClip->w ) / 2, ( SCREENHEIGHT - currentClip->h) / 2, currentClip );

				// Go te the next frame
				++frame;

				// Cycle Animation
				if ( frame / 4 >= WALKING_ANIMATION_FRAMES ) frame = 0;

				// Draw the fader forground
				gFadeTexture.setAlpha( alpha );
				gFadeTexture.render( gRenderer, 0, 0 );

				// Update screen
				SDL_RenderPresent( gRenderer );
			}
			//
			// -- Close game --
			//
		}
		//
		// -- Close media --
		//
	}
	//
	// -- Close engine --
	//

	// Free resources and close SDL
	close();

	return 0;
}

bool init(){
	// Inisitialise flag
	bool success = true;

	// Initialise SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		cout << "SDL could not initialise! SDL Error :" << SDL_GetError() << endl;
		success = false;
	}
	else{
		// Create window
		gWindow = SDL_CreateWindow(
			"SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN
		);

		if( gWindow == NULL ){
			cout << "Window could not be created! SDL Error : " << SDL_GetError() << endl;
			success = false;
		}
		else{
			// create renderer for widow.
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL ){
				cout << "Renderer could not be created! SDL Error : " << SDL_GetError() << endl;
				success = false;
			}
			else{
				// Initialise renderer colour to white
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				// initialise png loading
				int imgFlags = IMG_INIT_PNG;
				if( !(IMG_Init(imgFlags) & imgFlags) ){
					cout << "SDL_image could not be initialised! SDL_image error : " << IMG_GetError() << endl;
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia(){
	// Loading success flag
	bool success = true;

	string path( "media/SpriteSheetTemplate.png" );
	if( !gSpriteTextureSheet.loadFromFile( gRenderer, path.c_str() ) ){
		cout << "loadMedia Failure: Couldn't load " << path.c_str() << endl;
		success = false;
	}

	path = string( "media/spriteSheet.png" );
	if( !gColourCircleClipSheet.loadFromFile( gRenderer, path.c_str() ) ){
		cout << "loadMedia Failure: Couldn't load " << path.c_str() << endl;
		success = false;
	}

	gColourCircleClips[0] = { 0, 0, 200, 200 };
	gColourCircleClips[1] = { 200, 0, 200, 200 };
	gColourCircleClips[2] = { 0, 200, 200, 200 };
	gColourCircleClips[3] = { 200, 200, 200, 200 };

	gAnimSpriteClips[0] = { 0, 0, 100, 200 };
	gAnimSpriteClips[1] = { 100, 0, 100, 200 };
	gAnimSpriteClips[2] = { 200, 0, 100, 200 };
	gAnimSpriteClips[3] = { 300, 0, 100, 200 };

	path = string( "media/fadeIn.png" );
	if( !gFadeTexture.loadFromFile( gRenderer, path.c_str() ) ){
		cout << "loadMedia Failure: Couldn't load " << path.c_str() << endl;
		success = false;
	}
	else{
		// Setup blending
		gFadeTexture.setBlendMode( SDL_BLENDMODE_BLEND );
	}

	return success;
}

void close(){
	// Free loaded textures
	gSpriteTextureSheet.free();

	// Destroy renderer
	SDL_DestroyRenderer( gRenderer );
	gRenderer = NULL;

	// Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	// Quit SDL Subsystems
	IMG_Quit();
	SDL_Quit();
}
