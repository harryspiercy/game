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
const int SCREENWIDTH = 800;
const int SCREENHEIGHT = 600;

// Texture renderer to link to window
SDL_Renderer* gRenderer = NULL;

// Texture for the title
LTexture gTitleTexture;

// Sprites: the coloured cirles sprite sheet
LTexture gColourCircleClipSheet;
const int COLOUR_CIRCLE_CLIPS = 4;
SDL_Rect gColourCircleClips[ COLOUR_CIRCLE_CLIPS ];

// Sprites: the animated man running
LTexture gSpriteTextureSheet;
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gAnimSpriteClips[ WALKING_ANIMATION_FRAMES ];

// Overlay: example of alpha blending
LTexture gFadeTexture;

// Overlay: example of rotation and flipping the texture
LTexture gCompassTexture;

// Overlay: example of using text
LTexture gSceneGuideText;

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

			// Fade alpha variable
			Uint8 alpha = 255;

			// Animation frame
			int frame = 0;

			// Scene ids
			int scene = 0;

			// Texture rotational angle
			double angle = 0;
			SDL_RendererFlip flipType = SDL_FLIP_NONE;

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

							case SDLK_z:
							if( flipType != SDL_FLIP_HORIZONTAL ) flipType = SDL_FLIP_HORIZONTAL;
							else flipType = SDL_FLIP_NONE;
							break;

							case SDLK_x:
							if ( flipType != SDL_FLIP_VERTICAL ) flipType = SDL_FLIP_VERTICAL;
							else flipType = SDL_FLIP_NONE;
							break;

							case SDLK_LEFT:
							angle += 20;
							break;

							case SDLK_RIGHT:
							angle -= 20;
							break;

							case SDLK_0:
							scene = 0;
							break;
							
							case SDLK_1:
							scene = 1;
							break;

							case SDLK_2:
							scene = 2;
							break;

							case SDLK_3:
							scene = 3;
							break;

							case SDLK_4:
							scene = 4;
							break;

							default:
							break;
						}
					}
				}

				// Clear the screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				if( scene == 0 ){
					// Draw the title
					gTitleTexture.render( gRenderer, 0, 0 );
				}
				else if( scene == 1 ){
					// Render the current frame
					SDL_Rect* currentClip = &gAnimSpriteClips[ frame / 4 ];
					gSpriteTextureSheet.render( gRenderer, ( SCREENWIDTH - currentClip->w ) / 2, ( SCREENHEIGHT - currentClip->h) / 2, currentClip);

					// Go te the next frame
					++frame;

					// Cycle Animation
					if ( frame / 4 >= WALKING_ANIMATION_FRAMES ) frame = 0;
				}
				else if( scene == 2 ){
					// Modular code example
					gColourCircleClipSheet.setColour( red, green, blue );

					gColourCircleClipSheet.render( gRenderer, 0, 0, &gColourCircleClips[0] );
					gColourCircleClipSheet.render( gRenderer, SCREENWIDTH - gColourCircleClips[1].w, 0, &gColourCircleClips[1] );
					gColourCircleClipSheet.render( gRenderer, 0, SCREENHEIGHT - gColourCircleClips[2].h, &gColourCircleClips[2] );
					gColourCircleClipSheet.render( gRenderer, SCREENWIDTH - gColourCircleClips[3].w, SCREENHEIGHT - gColourCircleClips[3].h, &gColourCircleClips[3] );
				}
				else if( scene == 3){
					// Draw the fader forground
					gFadeTexture.setAlpha( alpha );
					gFadeTexture.render( gRenderer, 0, 0 );
				}
				else if( scene == 4){
					// Draw the compass texture
					gCompassTexture.render( gRenderer, 0, 0, NULL, angle, NULL, flipType );
				}
				else if( scene == 0 ){
					// Draw the title
					gTitleTexture.render( gRenderer, 0, 0 );
				}

				// Render the text
				if( scene ) gSceneGuideText.render( gRenderer, ( SCREENWIDTH - gSceneGuideText.getWidth() ) / 2, ( SCREENHEIGHT - gSceneGuideText.getHeight() - 20 ) );

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
			}
		}
	}

	return success;
}

bool loadMedia(){
	// Loading success flag
	bool success = true;

	string path( "media/title.png" );
	if( !gTitleTexture.loadFromFile( gRenderer, path.c_str() ) ){
		cout << "loadMedia Failure: Couldn't load " << path.c_str() << endl;
		success = false;
	}

	path = string( "media/SpriteSheetTemplate.png" );
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

	path = string( "media/lazy.ttf" );
	gSceneGuideText.mFont = TTF_OpenFont( path.c_str(), 18 );
	if( gSceneGuideText.mFont == NULL ){
		cout << "loadMedia Failure: Couldn't load " << path.c_str() << endl;
		success = false;
	}
	else{
		// Render text
		SDL_Color textColour = { 0, 0, 0 };
		if( !gSceneGuideText.loadFromRenderedText( gRenderer, "1. Anim - 2. Colour Modulation - 3. Alpha fade - 4. Rotation and flipping", textColour ) ){
			cout << "Failed to render text texture!" << endl;
			success = false;
		}
	}

	path = string( "media/compass.png" );
	if( !gCompassTexture.loadFromFile( gRenderer, path.c_str() ) ){
		cout << "loadMedia Failure: Couldn't load " << path.c_str() << endl;
		success = false;
	}

	return success;
}

void close(){
	// Free loaded textures
	gTitleTexture.free();
	gColourCircleClipSheet.free();
	gSpriteTextureSheet.free();
	gFadeTexture.free();
	gSceneGuideText.free();
	gCompassTexture.free();

	// Free global font
	TTF_CloseFont( gSceneGuideText.mFont );
	gSceneGuideText.mFont = NULL;

	// Destroy renderer
	SDL_DestroyRenderer( gRenderer );
	gRenderer = NULL;

	// Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	// Quit SDL Subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
