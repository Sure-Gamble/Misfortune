#pragma once 
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_surface.h"
#include "SDL_TTF/SDL_ttf.h"
#include "camera.h"

struct ValueBox{
    SDL_FRect box;
    int value;
    
};


void ValueBox_INIT(ValueBox* valuebox);
void ValueBox_Display(ValueBox* valuebox, SDL_Renderer* renderer, FontAtlas* font, Camera* camera);
void ValueBox_Destroy(ValueBox* valuebox);