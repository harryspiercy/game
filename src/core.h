#ifndef _CORE_H_
#define _CORE_H_

#include "common.h"

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

    //! List of keys that are down
    /*!
    */
    map<SDL_Scancode, bool> downKeys;

    //! Address of the current state of the keys
    /*!
    */
    const Uint8* currentKeyStates;

public:
    //! Initialise variables
    /*!
    */
    Core( int x = 800, int y = 600 );

    //! Release variable memeory
    /*! 
    */
    ~Core();

    //! Initialise SDL and create window
    /*! 
    */
    bool init();

    //! Shutdown SDL and destroy window.
    /*! 
    */
    void close();

    //! Return the address of the game window
    /*! 
    */
    inline SDL_Window* getWindow() { return window; }

    //! Return the address of the game window renderer
    /*! 
    */
    inline SDL_Renderer* getRenderer() { return renderer; }

    //! Return the resolution of the display
    /*! 
    */
    inline Resolution* getResolution() { return &resolution; }

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

    //! Get the pressed state of a spefified key scancode
    /*!
    */
    KeyState getKeyState( SDL_Scancode scancode );

    //! Get the latest key states for the core
    /*!
    */
    void updateKeyState();

};

#endif