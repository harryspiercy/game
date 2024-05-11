#ifndef _DEMO_H_
#define _DEMO_H_

#include "level.h"
#include "texture.h"
#include "timer.h"
#include "button.h"

// -- Level Constants --
const int COLOUR_CIRCLE_CLIPS = 4;
const int WALKING_ANIMATION_FRAMES = 4;

//! Demo level class
/*! Class to handle engine interactions.
*/
class Demo : public LLevel {
    // 
    // -- Level functions --
    //
public:
    // Construct the demo level
    Demo();

    // On demo level destroyed
    ~Demo();

    // initialise demo
    virtual bool init();

    // load media
    virtual bool loadMedia();

    // tick demo
    virtual void tick(); 

    // render demo
    virtual void render();
    
    // close demo media down
    virtual void closeMedia();

    //
    // -- Level content --
    //
private:
    // Texture for the title
    LTexture gTitleTexture;

    // Sprites: the coloured cirles sprite sheet
    LTexture gColourCircleClipSheet;
    SDL_Rect gColourCircleClips[ COLOUR_CIRCLE_CLIPS ];

    // Sprites: the animated man running
    LTexture gSpriteTextureSheet;
    SDL_Rect gAnimSpriteClips[ WALKING_ANIMATION_FRAMES ];
    SDL_Rect* gCurrentAnimSpriteClip;

    // Overlay: example of alpha blending
    LTexture gBackground;
    LTexture gFadeTexture;

    // Overlay: example of rotation and flipping the texture
    LTexture gCompassTexture;

    // Overlay: example of using text
    LTexture gSceneGuideText;

    // Overlay: example of some mouse inputs
    //LButton* gButtons[ TOTAL_BUTTONS ];
    shared_ptr< LButton > button1;
    shared_ptr< LButton > button2;
    shared_ptr< LButton > button3;
    shared_ptr< LButton > button4;
    void setButtonVisibility( bool visible );

    // Overlay: example of timers
    LTexture gPromptTexture;
    LTexture gUserTimerTexture;
    LTexture gFpsTimerTexture;

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

};

#endif