#include "engine.h"

//
// -- Engine globals --
//
// Create the core object
//Core core( 800, 600, 30 );
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
LButton* gButtons[ TOTAL_BUTTONS ];

// Overlay: example of timers
LTexture gPromptTexture;
LTexture gUserTimerTexture;
LTexture gFpsTimerTexture;

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
	if( !ENG::core->init() ){
		cout << "Failed to init core" << endl;
	}
	else{
		cout << "Successfully initialised core" << endl;
		// Set engine globals once successfully initialised
		gRenderer = ENG::core->getRenderer();
		gResolution = ENG::core->getResolution();

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
			ENG::core->makeButton( 0, 0 );
			ENG::core->makeButton( gResolution->x / 2, 0 );
			ENG::core->makeButton( 0, gResolution->y / 2 );
			ENG::core->makeButton( gResolution->x / 2, gResolution->y / 2 );

			// Global text colour
			SDL_Color textColour = { 0, 0, 0, 255 };

			// Timer example
			LTimer userTimer;
			std::stringstream userTimerText;

			// FPS timer
			LTimer fpsTimer;
			std::stringstream fpsTimerText;
			bool showFps = true;
			int countedFrames = 0;
			fpsTimer.start();

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

				// Test key states to change scene
				if( ENG::core->getKeyState( SDL_SCANCODE_0 ) == KEY_PRESSED ){
					scene = 0;
				}
				else if( ENG::core->getKeyState( SDL_SCANCODE_1 ) == KEY_PRESSED ){
					scene = 1;
				}
				else if( ENG::core->getKeyState( SDL_SCANCODE_2 ) == KEY_PRESSED ){
					scene = 2;
				}
				else if( ENG::core->getKeyState( SDL_SCANCODE_3 ) == KEY_PRESSED ){
					scene = 3;
				}
				else if( ENG::core->getKeyState( SDL_SCANCODE_4 ) == KEY_PRESSED ){
					scene = 4;
				}
				else if( ENG::core->getKeyState( SDL_SCANCODE_5 ) == KEY_PRESSED ){
					scene = 5;
					ENG::core->renderButton = !ENG::core->renderButton;
				}
				else if( ENG::core->getKeyState( SDL_SCANCODE_6 ) == KEY_PRESSED ){
					scene = 6;
				}

				// ------
				// Start of draw call
				// ------

				// Clear the screen
				ENG::core->setDrawColour( 0xFF, 0xFF, 0xFF, 0xFF );
				ENG::core->clearRenderer();

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
					if( ENG::core->getKeyState( SDL_SCANCODE_Q ) == KEY_DOWN ){
						red += 4;
					}
					else if( ENG::core->getKeyState( SDL_SCANCODE_A ) == KEY_DOWN ){
						red -= 4;
					}
					if( ENG::core->getKeyState( SDL_SCANCODE_W ) == KEY_DOWN ){
						green += 4;
					}
					else if( ENG::core->getKeyState( SDL_SCANCODE_S ) == KEY_DOWN ){
						green -= 4;
					}
					if( ENG::core->getKeyState( SDL_SCANCODE_E ) == KEY_DOWN ){
						blue += 4;
					}
					else if( ENG::core->getKeyState( SDL_SCANCODE_D ) == KEY_DOWN ){
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
					if( ENG::core->getKeyState( SDL_SCANCODE_UP ) == KEY_DOWN ){
						if( alpha + 32 > 255 ) alpha = 255;
						else alpha += 32;
					}
					else if( ENG::core->getKeyState( SDL_SCANCODE_DOWN ) == KEY_DOWN ){
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
					if( ENG::core->getKeyState( SDL_SCANCODE_A ) == KEY_DOWN ){
						angle -= 20;
					}
					else if ( ENG::core->getKeyState( SDL_SCANCODE_D ) == KEY_DOWN ){
						angle += 20;
					}

					if( ENG::core->getKeyState( SDL_SCANCODE_LEFT ) == KEY_PRESSED
					|| ENG::core->getKeyState( SDL_SCANCODE_RIGHT ) == KEY_PRESSED ){
						if( flipType != SDL_FLIP_HORIZONTAL ) flipType = SDL_FLIP_HORIZONTAL;
						else flipType = SDL_FLIP_NONE;
					}
					if( ENG::core->getKeyState( SDL_SCANCODE_UP ) == KEY_PRESSED
					|| ENG::core->getKeyState( SDL_SCANCODE_DOWN ) == KEY_PRESSED ){
						if ( flipType != SDL_FLIP_VERTICAL ) flipType = SDL_FLIP_VERTICAL;
						else flipType = SDL_FLIP_NONE;
					}

					// Draw the compass texture
					gCompassTexture.render( gRenderer, 0, 0, NULL, angle, NULL, flipType );
				}

				// ---
				// Mouse button example
				else if( scene == 5 ){
					
				}

				// ---
				// Timer example
				else if( scene == 6 ){
					if( ENG::core->getKeyState( SDL_SCANCODE_S ) == KEY_PRESSED ){
						if( userTimer.isStarted() ) userTimer.stop();
						else userTimer.start();
					}
					else if( ENG::core->getKeyState( SDL_SCANCODE_P ) == KEY_PRESSED ){
						if( userTimer.isPaused() ) userTimer.unpause();
						else userTimer.pause();
					}

					// Set text to be rendered
					userTimerText.str( "" );
					userTimerText << "Seconds since start time " << ( userTimer.getTicks() / 1000.f );

					// Render text
					if( !gUserTimerTexture.loadFromRenderedText( gRenderer, userTimerText.str().c_str(), textColour)){
						cout << "Unable to render user time texture" << endl;
					}
					gPromptTexture.render( gRenderer, ( gResolution->x - gPromptTexture.getWidth() ) / 2, 0 ); 
					gUserTimerTexture.render( gRenderer, ( gResolution->x - gUserTimerTexture.getWidth() ) / 2, gPromptTexture.getHeight() );
				}

				// Render the text
				if( scene ) gSceneGuideText.render( gRenderer, ( gResolution->x - gSceneGuideText.getWidth() ) / 2, ( gResolution->y - gSceneGuideText.getHeight() - 20 ) );

				ENG::core->stopFrameTimer();

				// Update screen
				//ENG::core->present();
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
		}
		//
		// -- Close media --
		//
		closeMedia();
		cout << "Shutdown media" << endl;
	}
	//
	// -- Close engine --
	//
	ENG::core->close();
	cout << "Shutdown the core" << endl;

	return 0;
}

bool loadMedia(){
	// Loading success flag
	bool success = true;

	// Load title page
	if( !gTitleTexture.loadFromFile( gRenderer, string( "../media/title.png" ).c_str() ) ){
		cout << "loadMedia Failure: " << SDL_GetError() << endl;
		success = false;
	}

	// Load animation example media
	if( !gSpriteTextureSheet.loadFromFile( gRenderer, string( "../media/SpriteSheetTemplate.png" ).c_str() ) ){
		cout << "loadMedia Failure: " << SDL_GetError() << endl;
		success = false;
	}
	gAnimSpriteClips[0] = { 0, 0, 100, 200 };
	gAnimSpriteClips[1] = { 100, 0, 100, 200 };
	gAnimSpriteClips[2] = { 200, 0, 100, 200 };
	gAnimSpriteClips[3] = { 300, 0, 100, 200 };

	// Load circle sprite sheet for colour mod example
	if( !gColourCircleClipSheet.loadFromFile( gRenderer, string( "../media/spriteSheet.png" ).c_str() ) ){
		cout << "loadMedia Failure: " << SDL_GetError() << endl;
		success = false;
	}
	gColourCircleClips[0] = { 0, 0, 200, 200 };
	gColourCircleClips[1] = { 200, 0, 200, 200 };
	gColourCircleClips[2] = { 0, 200, 200, 200 };
	gColourCircleClips[3] = { 200, 200, 200, 200 };

	// Load in the textures for the fade example
	if( !gBackground.loadFromFile( gRenderer, string( "../media/fadeIn.png" ).c_str() ) ){
		cout << "loadMedia Failure: " << SDL_GetError() << endl;
		success = false;
	}
	if( !gFadeTexture.loadFromFile( gRenderer, string( "../media/background.png" ).c_str() ) ){
		cout << "loadMedia Failure: " << SDL_GetError() << endl;
		success = false;
	}
	else{
		// Setup blending
		gFadeTexture.setBlendMode( SDL_BLENDMODE_BLEND );
	}

	// Load font for rendering text
	TTF_Font* font = TTF_OpenFont( string( "../media/lazy.ttf" ).c_str(), 18 );
	if( font == NULL ){
		cout << "loadMedia Failure: " <<  SDL_GetError() << endl;
		success = false;
	}
	else{
		// Render text colour
		SDL_Color textColour = { 0, 0, 0 };

		gSceneGuideText.mFont = font;
		if( !gSceneGuideText.loadFromRenderedText( gRenderer, 
		"1. Anim - 2. Colour Modulation - 3. Alpha fade - 4. Rotation and flipping - 5. Mouse", 
		textColour ) ){
			cout << "Failed to render scene guide text texture!" << endl;
			success = false;
		}

		gPromptTexture.mFont = font;
		if( !gPromptTexture.loadFromRenderedText( gRenderer, 
		"Press S to start, P to pause userTimer", textColour) ){
			cout << "Failed to render prompt text texture" << endl;
			success = false;
		}

		gUserTimerTexture.mFont = font;
		gFpsTimerTexture.mFont = font;
	}

	if( !gCompassTexture.loadFromFile( gRenderer, string( "../media/compass.png" ).c_str() ) ){
		cout << "loadMedia Failure: " << SDL_GetError() << endl;
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
