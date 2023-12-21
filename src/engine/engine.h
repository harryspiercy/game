#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "common.h"
#include "core.h"
#include "texture.h"
#include "timer.h"
#include "button.h"

namespace ENG{
    static Core* core = new Core( 800, 600, FPS_FREERUN );
}

#endif