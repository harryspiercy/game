#ifndef _CORE_H_
#define _CORE_H_

#include "common.h"
#include "texture.h"
#include "timer.h"
#include "button.h"
#include "level.h"

typedef int IButton;

static const int FPS_VSYNC = -1;
static const int FPS_FREERUN = -2;

//! Struct to hold a window resolution
/*!
*/
struct Resolution{
    //! Create a resolution of 0, 0.
    Resolution() : x( 0 ), y( 0 ) {}
    //! Create a custom resolution.
    Resolution( int newX, int newY ) : x( newX ), y( newY ) {}
    int x; int y;
};

//! Enum to represent key states
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
    * \param x width of the window
    * \param y height of the window
    * \param fpscap frames per second. FPS_VSYNC or FPS_FREERUN
    */
    Core( int x = 800, int y = 600 , int fpscap = -1 );

    //! Release variable memeory
    /*! 
    */
    ~Core();

public:
    //! Is the game loop still running
    bool quit = false;

public:
    //! Initialise the core
    static bool start();

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

    //! Input events
    SDL_Event event; 

public:
    //! Initialise SDL and create window
    /*! 
    */
    bool init();

    //! Poll and handle events
    /*! \param event Reference to the polled SDL event
    */
    void handleEvents();

    //! Update the core
    /*!
    */
    void tick();

    //! Shutdown SDL and destroy window.
    /*! 
    */
    void close();

    //! get the address of the game window
    /*! \return window 
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

    //! Render all of the core elements.
    /*!
    */
   void render();

private:
    //! Map of keys that have been pressed in their current state
    /*! This key consists of keys have been pressed since the creation of Core
    * The map is updated by the 
    */
    map<SDL_Scancode, bool> downKeys;

    //! Uint8 array with the describing the state of the keyboard
    /*! Each Uint8 value is the down value of each key on the keybaord.
    */
    const Uint8* currentKeyStates;

public:
    //! Get the latest key states for the core
    /*! Set currentKeyStates to a new value using SDL_KeyboardState
    */
    void updateKeyState();

    //! Get the pressed state of a spefified key scancode
    /*! \param scancode the SDL scan code of a key
    * \return the state of the queried key. [ KEY_PRESSED, KEY_DOWN, KEY RELEASED, KEY_UP ]
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
    static const int FPSLINES_COUNT = 1;

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

private:
    //! A global font for all others to be set against
    TTF_Font* font;

public:
    //! Getter for the default font
    inline const TTF_Font* GetFont() { return font; }

    //! TEMP
    //bool renderButton = false;

public:
    //! Load a new level of type T.
    template< typename T >
    shared_ptr< T > openLevel(){

        // Close the open level
        shutdownLevel();

        shared_ptr< T > rtn = make_shared< T >();
        loadedLevel = rtn;
        if ( loadedLevel ) initLevel();

        return rtn;
    }

    //! Initialise a newly loaded level
    void initLevel();

    //! Close down an open level
    void shutdownLevel();

    //! Currently loaded level
    shared_ptr< LLevel > loadedLevel;
};

#endif