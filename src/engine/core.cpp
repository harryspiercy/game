#include "core.h"
#include "../game/levels/demo.h"

Core::Core( int x, int y, int fpscap ) : 
window( NULL ), resolution( x, y ), fps( fpscap ), renderer( NULL ),
showFps( false ), countedFrames( 0 ){
	
	if( fps == FPS_VSYNC ){
		useVSync = true;
		ticksPerFrame = 0;
		cout << "Using VSync" << endl;
	}
	else if ( fps == FPS_FREERUN ){
		useVSync = false;
		ticksPerFrame = 0;
		cout << "Free run" << endl;
	}
	else{
		useVSync = false;
		ticksPerFrame = 1000 / fps;
		cout << "Frame cap to " << fps << " fps" << endl;
	}
}

Core::~Core(){
    close();
}

bool Core::start(){
	return 0;
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
			if( useVSync ) renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			else renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			
			if( renderer == NULL ){
				cout << "Renderer could not be created! SDL Error : " << SDL_GetError() << endl;
				success = false;
			}
			else{
				// Initialise renderer colour to white
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				// Initilaie the font for the core out
				font = TTF_OpenFont( string( "../media/lazy.ttf" ).c_str(), 18 );
				if (!font ){
					cout << "Failed to load the global default font!" << endl;
				}
				else{
					fpsTexture[0].mFont = font;
				}

				fpsTimer.start();
				capTimer.start();
			}
		}
	}

	return success;
}

void Core::handleEvents(){

	// Poll hardware events
	while( SDL_PollEvent( &event ) != 0 ){
	
		// Handle exit event
		if( event.type == SDL_QUIT ){
			quit = true;
		}

		if ( loadedLevel ) loadedLevel->onHandleEvent( &event );

	}

}

void Core::tick(){

	// Start the frame timer to calculate the duration of this frame.
	startFrameTimer();

	// Handle input events
	handleEvents();

	// Update the keyboard inputs
	updateKeyState();

	// If a level is attached, update it.
	if( loadedLevel ) loadedLevel->onTick(); 

	// ----
	// Engine level keyboard shortcuts
	// ----
	// Set exit flag
	if( getKeyState( SDL_SCANCODE_ESCAPE ) == KEY_RELEASED ){
		quit = true;
	}
	// Show FPS
	KeyState fState = getKeyState( SDL_SCANCODE_F ); KeyState laltState = getKeyState( SDL_SCANCODE_LALT );
	if( fState == KEY_PRESSED && ( laltState == KEY_DOWN || laltState == KEY_PRESSED ) ){
		showFps = !showFps;
	}
	// Run the demo if alt+d is pressed
	if( getKeyState( SDL_SCANCODE_LALT ) == KEY_DOWN 
	&& getKeyState( SDL_SCANCODE_D ) == KEY_PRESSED ){
		openLevel< Demo >();
	} 
}

void Core::close(){
	
	// Shutdown the active level 
	if( loadedLevel ) loadedLevel->onShutdown();
	cout << "Shutdown media" << endl;

	// Clear values from the down key map
    downKeys.clear();

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

void Core::render(){
    
    // Clear the screen
    setDrawColour( 0xFF, 0xFF, 0xFF, 0xFF );
    clearRenderer();

	// render the level.
	if( loadedLevel ) loadedLevel->onRender();

	// stop the timer monitoring the frame.
	stopFrameTimer();

	// Present the renderer to screen
	present();
}

KeyState Core::getKeyState( SDL_Scancode scancode ){
    // Is the key currently down?
    bool currentDownState = currentKeyStates[ scancode ];

    // Was the key marked as down in the map?
    bool previousDownState = false;
    map<SDL_Scancode, bool>::iterator mapEntry = downKeys.find( scancode );
    if( mapEntry != downKeys.end() ){
        previousDownState = mapEntry->second;
    }
    // If not present insert the scancode to the map.
    else{
        downKeys.insert( pair<SDL_Scancode, bool>( scancode, false ) );
        previousDownState = false;
    }

    // If key was just pressed
    if( currentDownState && !previousDownState ){
        mapEntry->second = true;
        return KEY_PRESSED;
    }
    // If key is held down
    else if( currentDownState && previousDownState ){
        return KEY_DOWN;
    }
    // If key is just released
    else if( !currentDownState && previousDownState ){
        mapEntry->second = false;
        return KEY_RELEASED;
    }
    // If key is up
    else{
        return KEY_UP;
    }
}

void Core::updateKeyState(){
    currentKeyStates = SDL_GetKeyboardState( NULL );
}

void Core::toggleFpsDisplay(){
	showFps = !showFps;
}

void Core::startFrameTimer(){
	capTimer.start();

	avgFps = countedFrames / ( fpsTimer.getTicks() / 1000.f );

	if( avgFps > 2000000){
		avgFps = 0;
	}
}

void Core::stopFrameTimer(){
	// Show FPS
	fpsTimerText.str( "" );
	if( showFps ) fpsTimerText << "Average FPS " << avgFps;
	else fpsTimerText << "Press alt+F to see FPS";

	if( renderer == NULL ){
	}

	if( !fpsTexture[0].loadFromRenderedText( renderer,
	fpsTimerText.str().c_str(), fpsTextColour ) ){
		cout << "Unable to render fps time texture" << endl;
	}
	else{
		fpsTexture[0].render( renderer, 10, 10 );
	}

	++countedFrames;
}

void Core::capFrameRate(){
	// Cap frame rate
	int frameTicks = capTimer.getTicks();
	if( frameTicks < getTicksPerFrame() ){
		SDL_Delay( getTicksPerFrame() - frameTicks );
	}
}

void Core::initLevel(){

	loadedLevel->gCore = this;
	loadedLevel->gRenderer = getRenderer();
	loadedLevel->gViewport = getResolution();
	loadedLevel->onInit();
}

void Core::shutdownLevel(){

	if (loadedLevel){
		loadedLevel->onShutdown();
	}

}