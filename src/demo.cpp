#include "demo.h"


void Demo::init( Core* core ){

    // Set engine globals once successfully initialised
    gCore = core;
    gRenderer = gCore->getRenderer();
    gViewport = gCore->getResolution();

    // Load in the demo media
    if( !loadMedia() ){
        cout << "Failed to load media" << endl;
    }
    else{
        // Make the buttons
        gCore->makeButton( 0, 0 );
        gCore->makeButton( gViewport->x / 2, 0 );
        gCore->makeButton( 0, gViewport->y / 2 );
        gCore->makeButton( gViewport->x / 2, gViewport->y / 2 );
    }

    // Start the demo timer
    fpsTimer.start();
}

void Demo::tick(){

    // Test key states to change scene
    if( gCore->getKeyState( SDL_SCANCODE_0 ) == KEY_PRESSED ){
        scene = 0;
    }
    else if( gCore->getKeyState( SDL_SCANCODE_1 ) == KEY_PRESSED ){
        scene = 1;
    }
    else if( gCore->getKeyState( SDL_SCANCODE_2 ) == KEY_PRESSED ){
        scene = 2;
    }
    else if( gCore->getKeyState( SDL_SCANCODE_3 ) == KEY_PRESSED ){
        scene = 3;
    }
    else if( gCore->getKeyState( SDL_SCANCODE_4 ) == KEY_PRESSED ){
        scene = 4;
    }
    else if( gCore->getKeyState( SDL_SCANCODE_5 ) == KEY_PRESSED ){
        scene = 5;
        gCore->renderButton = !gCore->renderButton;
    }
    else if( gCore->getKeyState( SDL_SCANCODE_6 ) == KEY_PRESSED ){
        scene = 6;
    }

    // ------
    // Start of draw call
    // ------

    // Clear the screen
    gCore->setDrawColour( 0xFF, 0xFF, 0xFF, 0xFF );
    gCore->clearRenderer();

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
        gSpriteTextureSheet.render( gRenderer, ( gViewport->x - currentClip->w ) / 2, ( gViewport->y - currentClip->h) / 2, currentClip);

        // Go te the next frame
        ++frame;

        // Cycle Animation
        if ( frame / 4 >= WALKING_ANIMATION_FRAMES ) frame = 0;
    }

    // ---
    // Colour mod example
    else if( scene == 2 ){
        if( gCore->getKeyState( SDL_SCANCODE_Q ) == KEY_DOWN ){
            red += 4;
        }
        else if( gCore->getKeyState( SDL_SCANCODE_A ) == KEY_DOWN ){
            red -= 4;
        }
        if( gCore->getKeyState( SDL_SCANCODE_W ) == KEY_DOWN ){
            green += 4;
        }
        else if( gCore->getKeyState( SDL_SCANCODE_S ) == KEY_DOWN ){
            green -= 4;
        }
        if( gCore->getKeyState( SDL_SCANCODE_E ) == KEY_DOWN ){
            blue += 4;
        }
        else if( gCore->getKeyState( SDL_SCANCODE_D ) == KEY_DOWN ){
            blue -= 4;
        }

        gColourCircleClipSheet.setColour( red, green, blue );

        gColourCircleClipSheet.render( gRenderer, 0, 0, &gColourCircleClips[0] );
        gColourCircleClipSheet.render( gRenderer, gViewport->x - gColourCircleClips[1].w, 0, &gColourCircleClips[1] );
        gColourCircleClipSheet.render( gRenderer, 0, gViewport->y - gColourCircleClips[2].h, &gColourCircleClips[2] );
        gColourCircleClipSheet.render( gRenderer, gViewport->x - gColourCircleClips[3].w, gViewport->y - gColourCircleClips[3].h, &gColourCircleClips[3] );
    }

    // ---
    // Alpha fading example
    else if( scene == 3 ){
        if( gCore->getKeyState( SDL_SCANCODE_UP ) == KEY_DOWN ){
            if( alpha + 32 > 255 ) alpha = 255;
            else alpha += 32;
        }
        else if( gCore->getKeyState( SDL_SCANCODE_DOWN ) == KEY_DOWN ){
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
        if( gCore->getKeyState( SDL_SCANCODE_A ) == KEY_DOWN ){
            angle -= 20;
        }
        else if ( gCore->getKeyState( SDL_SCANCODE_D ) == KEY_DOWN ){
            angle += 20;
        }

        if( gCore->getKeyState( SDL_SCANCODE_LEFT ) == KEY_PRESSED
        || gCore->getKeyState( SDL_SCANCODE_RIGHT ) == KEY_PRESSED ){
            if( flipType != SDL_FLIP_HORIZONTAL ) flipType = SDL_FLIP_HORIZONTAL;
            else flipType = SDL_FLIP_NONE;
        }
        if( gCore->getKeyState( SDL_SCANCODE_UP ) == KEY_PRESSED
        || gCore->getKeyState( SDL_SCANCODE_DOWN ) == KEY_PRESSED ){
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
        if( gCore->getKeyState( SDL_SCANCODE_S ) == KEY_PRESSED ){
            if( userTimer.isStarted() ) userTimer.stop();
            else userTimer.start();
        }
        else if( gCore->getKeyState( SDL_SCANCODE_P ) == KEY_PRESSED ){
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
        gPromptTexture.render( gRenderer, ( gViewport->x - gPromptTexture.getWidth() ) / 2, 0 ); 
        gUserTimerTexture.render( gRenderer, ( gViewport->x - gUserTimerTexture.getWidth() ) / 2, gPromptTexture.getHeight() );
    }

    // Render the text
    if( scene ) gSceneGuideText.render( gRenderer, ( gViewport->x - gSceneGuideText.getWidth() ) / 2, ( gViewport->y - gSceneGuideText.getHeight() - 20 ) );

}

bool Demo::loadMedia(){
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

void Demo::closeMedia(){

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