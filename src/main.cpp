#include "common.h"
#include "texture.h"
#include "button.h"

//
// -- Engine globals --
//
// Create the core object
Core core;
SDL_Renderer* gRenderer = NULL;
Resolution* gResolution = NULL;

//
// -- Game globals --
//
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
LTexture gBackground;
LTexture gFadeTexture;

// Overlay: example of rotation and flipping the texture
LTexture gCompassTexture;

// Overlay: example of using text
LTexture gSceneGuideText;

// Overlay: example of some mouse inputs
LButton gButtons[ TOTAL_BUTTONS ];

//
// -- Game methods --
//
// load media
bool loadMedia();
// Frees media and shuts down SDL
void closeMedia();

//
// --- Program --//
//
int main( int argc, char* args[] ){

	// Start up SDL and create window
	if( !core.init() ){
		cout << "Failed to init" << endl;
	}
	else{
		// Set engine globals once successfully initialised
		gRenderer = core.getRenderer();
		gResolution = core.getResolution();

		// Load media
		if( !loadMedia() ){
			cout << "Failed to load media" << endl;
		}
		else{
			cout << "Successfully loaded media" << endl;
			//
			// -- Pregame --
			// Load the default state of the game loop
			//

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

			// Button positions
			gButtons[ 0 ].setPosition( 0, 0 );
			gButtons[ 1 ].setPosition( gResolution->x / 2, 0 );
			gButtons[ 2 ].setPosition( 0, gResolution->y / 2 );
			gButtons[ 3 ].setPosition( gResolution->x / 2, gResolution->y / 2 );

			// Current rendered texture
			LTexture* currentTexture = NULL;

			//
			// -- Game loop --
			//
			cout << "Entering the game loop" << endl;
			while( !quit ){

				// Poll hardware events
				while( SDL_PollEvent( &e ) != 0 ){

					// Handle exit event
					if( e.type == SDL_QUIT ){
						quit = true;
					}

					// Handle button events
					for( int i = 0; i < TOTAL_BUTTONS; ++i ){
						gButtons[ i ].handleEvent( &e );
					}
				}

				// Get the current key states
				//const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
				core.updateKeyState();

				// Set exit flag
				if( core.getKeyState( SDL_SCANCODE_ESCAPE ) == KEY_RELEASED ){
					quit = true;
				}
				// Test key states to change scene
				if( core.getKeyState( SDL_SCANCODE_0 ) == KEY_PRESSED ){
					scene = 0;
				}
				else if( core.getKeyState( SDL_SCANCODE_1 ) == KEY_PRESSED ){
					scene = 1;
				}
				else if( core.getKeyState( SDL_SCANCODE_2 ) == KEY_PRESSED ){
					scene = 2;
				}
				else if( core.getKeyState( SDL_SCANCODE_3 ) == KEY_PRESSED ){
					scene = 3;
				}
				else if( core.getKeyState( SDL_SCANCODE_4 ) == KEY_PRESSED ){
					scene = 4;
				}
				else if( core.getKeyState( SDL_SCANCODE_5 ) == KEY_PRESSED ){
					scene = 5;
				}

				// ------
				// Start of draw call
				// ------

				// Clear the screen
				core.setDrawColour( 0xFF, 0xFF, 0xFF, 0xFF );
				core.clearRenderer();

				// ---
				// Title screen scene
				if( scene == 0 ){
					// Draw the title
					gTitleTexture.render( gRenderer, 0, 0 );
				}

				// ---
				// Sprite animation example
				else if( scene == 1 ){
					// Render the current frame
					SDL_Rect* currentClip = &gAnimSpriteClips[ frame / 4 ];
					gSpriteTextureSheet.render( gRenderer, ( gResolution->x - currentClip->w ) / 2, ( gResolution->y - currentClip->h) / 2, currentClip);

					// Go te the next frame
					++frame;

					// Cycle Animation
					if ( frame / 4 >= WALKING_ANIMATION_FRAMES ) frame = 0;
				}

				// ---
				// Colour mod example
				else if( scene == 2 ){
					if( core.getKeyState( SDL_SCANCODE_Q ) == KEY_DOWN ){
						red += 4;
					}
					else if( core.getKeyState( SDL_SCANCODE_A ) == KEY_DOWN ){
						red -= 4;
					}
					if( core.getKeyState( SDL_SCANCODE_W ) == KEY_DOWN ){
						green += 4;
					}
					else if( core.getKeyState( SDL_SCANCODE_S ) == KEY_DOWN ){
						green -= 4;
					}
					if( core.getKeyState( SDL_SCANCODE_E ) == KEY_DOWN ){
						blue += 4;
					}
					else if( core.getKeyState( SDL_SCANCODE_D ) == KEY_DOWN ){
						blue -= 4;
					}

					gColourCircleClipSheet.setColour( red, green, blue );

					gColourCircleClipSheet.render( gRenderer, 0, 0, &gColourCircleClips[0] );
					gColourCircleClipSheet.render( gRenderer, gResolution->x - gColourCircleClips[1].w, 0, &gColourCircleClips[1] );
					gColourCircleClipSheet.render( gRenderer, 0, gResolution->y - gColourCircleClips[2].h, &gColourCircleClips[2] );
					gColourCircleClipSheet.render( gRenderer, gResolution->x - gColourCircleClips[3].w, gResolution->y - gColourCircleClips[3].h, &gColourCircleClips[3] );
				}

				// ---
				// Alpha fading example
				else if( scene == 3 ){
					if( core.getKeyState( SDL_SCANCODE_W ) == KEY_DOWN ){
						if( alpha + 32 > 255 ) alpha = 255;
						else alpha += 32;
					}
					else if( core.getKeyState( SDL_SCANCODE_S ) == KEY_DOWN ){
						if( alpha - 32 < 0 ) alpha = 0;
						else alpha -= 32;
					}

					// Draw the background
					gBackground.render( gRenderer, 0, 0);
					// Draw the fader forground
					gFadeTexture.setAlpha( alpha );
					gFadeTexture.render( gRenderer, 0, 0 );
				}

				// ---
				// Texture flip and rotation example
				else if( scene == 4 ){
					if( core.getKeyState( SDL_SCANCODE_A ) == KEY_DOWN ){
						angle -= 20;
					}
					else if ( core.getKeyState( SDL_SCANCODE_D ) == KEY_DOWN ){
						angle += 20;
					}

					if( core.getKeyState( SDL_SCANCODE_LEFT ) == KEY_PRESSED
					|| core.getKeyState( SDL_SCANCODE_RIGHT ) == KEY_PRESSED ){
						if( flipType != SDL_FLIP_HORIZONTAL ) flipType = SDL_FLIP_HORIZONTAL;
						else flipType = SDL_FLIP_NONE;
					}
					if( core.getKeyState( SDL_SCANCODE_UP ) == KEY_PRESSED
					|| core.getKeyState( SDL_SCANCODE_DOWN ) == KEY_PRESSED ){
						if ( flipType != SDL_FLIP_VERTICAL ) flipType = SDL_FLIP_VERTICAL;
						else flipType = SDL_FLIP_NONE;
					}

					// Draw the compass texture
					gCompassTexture.render( gRenderer, 0, 0, NULL, angle, NULL, flipType );
				}

				// ---
				// Mouse button example
				else if( scene == 5 ){
					// Render all the buttons
					for( int i = 0; i < TOTAL_BUTTONS; ++i){
						gButtons[ i ].render( gRenderer );
					}
				}

				// ---
				// Title scene
				else if( scene == 0 ){
					// Draw the title
					gTitleTexture.render( gRenderer, 0, 0 );
				}

				// Render the text
				if( scene ) gSceneGuideText.render( gRenderer, ( gResolution->x - gSceneGuideText.getWidth() ) / 2, ( gResolution->y - gSceneGuideText.getHeight() - 20 ) );

				// Update screen
				core.present();

				// -----
				// End of draw call
				// -----
			}
			//
			// -- Close game --
			//
		}
		//
		// -- Close media --
		//
		closeMedia();
	}
	//
	// -- Close engine --
	//
	core.close();

	return 0;
}

bool loadMedia(){
	// Loading success flag
	bool success = true;

	// Load title page
	string path( "media/title.png" );
	if( !gTitleTexture.loadFromFile( gRenderer, path.c_str() ) ){
		cout << "loadMedia Failure: Couldn't load " << path.c_str() << endl;
		success = false;
	}

	// Load animation example media
	path = string( "media/SpriteSheetTemplate.png" );
	if( !gSpriteTextureSheet.loadFromFile( gRenderer, path.c_str() ) ){
		cout << "loadMedia Failure: Couldn't load " << path.c_str() << endl;
		success = false;
	}
	gAnimSpriteClips[0] = { 0, 0, 100, 200 };
	gAnimSpriteClips[1] = { 100, 0, 100, 200 };
	gAnimSpriteClips[2] = { 200, 0, 100, 200 };
	gAnimSpriteClips[3] = { 300, 0, 100, 200 };

	// Load circle sprite sheet for colour mod example
	path = string( "media/spriteSheet.png" );
	if( !gColourCircleClipSheet.loadFromFile( gRenderer, path.c_str() ) ){
		cout << "loadMedia Failure: Couldn't load " << path.c_str() << endl;
		success = false;
	}
	gColourCircleClips[0] = { 0, 0, 200, 200 };
	gColourCircleClips[1] = { 200, 0, 200, 200 };
	gColourCircleClips[2] = { 0, 200, 200, 200 };
	gColourCircleClips[3] = { 200, 200, 200, 200 };

	path = string( "media/background.png" );
	if( !gBackground.loadFromFile( gRenderer, path.c_str() ) ){
		cout << "loadMedia Failure: Couldn't load " << path.c_str() << endl;
		success = false;
	}

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
		if( !gSceneGuideText.loadFromRenderedText( gRenderer, "1. Anim - 2. Colour Modulation - 3. Alpha fade - 4. Rotation and flipping - 5. Mouse", textColour ) ){
			cout << "Failed to render text texture!" << endl;
			success = false;
		}
	}

	path = string( "media/compass.png" );
	if( !gCompassTexture.loadFromFile( gRenderer, path.c_str() ) ){
		cout << "loadMedia Failure: Couldn't load " << path.c_str() << endl;
		success = false;
	}


	if( !gButtons[ 0 ].loadButtonSprites( gRenderer )){
		cout << "Button failed to open" << endl;
		success = false;
	}
	if( !gButtons[ 1 ].loadButtonSprites( gRenderer )){
		cout << "Button failed to open" << endl;
		success = false;
	}
	if( !gButtons[ 2 ].loadButtonSprites( gRenderer )){
		cout << "Button failed to open" << endl;
		success = false;
	}
	if( !gButtons[ 3 ].loadButtonSprites( gRenderer )){
		cout << "Button failed to open" << endl;
		success = false;
	}

	return success;
}

void closeMedia(){
	// Free loaded textures
	gTitleTexture.free();
	gColourCircleClipSheet.free();
	gSpriteTextureSheet.free();
	gFadeTexture.free();
	gSceneGuideText.free();
	gCompassTexture.free();

	TTF_CloseFont( gSceneGuideText.mFont );
	gSceneGuideText.mFont = NULL;
}
