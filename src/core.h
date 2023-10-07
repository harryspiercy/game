#ifndef _CORE_H_
#define _CORE_H_

#include "common.h"

struct Resolution{
    Resolution( int newX, int newY ) : x( newX ), y( newY ) {}
    int x; int y;
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

    //! 
    /*!
    */

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

};

#endif