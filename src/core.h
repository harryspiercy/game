#ifndef _CORE_H_
#define _CORE_H_

#include "common.h"
#include "texture.h"
#include "timer.h"

static const int FPS_VSYNC = -1;
static const int FPS_FREERUN = -2;

struct Resolution{
    Resolution() : x( 0 ), y( 0 ) {}
    Resolution( int newX, int newY ) : x( newX ), y( newY ) {}
    int x; int y;
};

enum KeyState{
    KEY_PRESSED, KEY_DOWN, KEY_RELEASED, KEY_UP
};

//! Core engine class
/*! Class to handle engine interactions.
*/
class Core{
public:
    //! Initialise variables
    /*!
    */
    Core( int x = 800, int y = 600 , int fpscap = -1 );

    //! Release variable memeory
    /*! 
    */
    ~Core();

private:
    //! Global window address
    /*!
    */
    SDL_Window* window;

    //! Window x resolution
    /*!
    */
    Resolution resolution;

    //! Global renderer address
    /*!
    */
    SDL_Renderer* renderer;

public:
    //! Initialise SDL and create window
    /*! 
    */
    bool init();

    //! Update the core
    void tick();

    //! Shutdown SDL and destroy window.
    /*! 
    */
    void close();

    //! Return the address of the game window
    /*! 
    */
    inline SDL_Window* getWindow() { return window; }

    //! Return the resolution of the display
    /*! 
    */
    inline Resolution* getResolution() { return &resolution; }
    
    //! Return the address of the game window renderer
    /*! 
    */
    inline SDL_Renderer* getRenderer() { return renderer; }

    //! Clear the renderer
    /*! Use as the start of a new draw call
    */
    void clearRenderer();

    //! Set the renderer draw colour
    /*! 
    */
    void setDrawColour( Uint8 x, Uint8 y, Uint8 z, Uint8 a );

    //! Present the renderer to the window.
    /*!
    */
    void present();

private:
    //! List of keys that are down
    /*!
    */
    map<SDL_Scancode, bool> downKeys;

    //! Address of the current state of the keys
    /*!
    */
    const Uint8* currentKeyStates;

public:
    //! Get the latest key states for the core
    /*!
    */
    void updateKeyState();

    //! Get the pressed state of a spefified key scancode
    /*!
    */
    KeyState getKeyState( SDL_Scancode scancode );

private:
    //! FPS Cap
    /*!
    */
    int fps;

    //! Min ticks per frame
    /*!
    */
    int ticksPerFrame;

    //! Use VSync to cap fps automatically
    /*!
    */
    bool useVSync;

    //! Number of lines required to write out the FPS log
    /*!
    */
    static const int FPSLINES_COUNT = 4;

public:
    //! Return the required ticks perframe
    /*!
    */
    inline int getTicksPerFrame() { return ticksPerFrame; }

    void toggleFpsDisplay();

private:
    //! Start the frame timer
    /*!
    */
    LTimer fpsTimer;

    //! Cap timer
    LTimer capTimer;

    //! String stream to write to texture
    /*!
    */
    std::stringstream fpsTimerText;

    //! Texture to display the current fps data
    /*!
    */
    LTexture fpsTexture[FPSLINES_COUNT];

    //! fps text colour
    SDL_Color fpsTextColour;

    //! 
    bool showFps;

    //! 
    int countedFrames;
    
    //! 
    float avgFps;

public:
    //! Start the frame timer
    /*!
    */
    void startFrameTimer();

    //! Stop the frame timer
    /*!
    */
    void stopFrameTimer();

    //! Cap the framerate
    void capFrameRate();
};

#endif