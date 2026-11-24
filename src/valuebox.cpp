#include "common.h"
#include "gameState.h"
#include "valuebox.h"
#include "rendering.h"
#include <cstdlib>


void ValueBox_INIT(ValueBox* valuebox){
    valuebox->value = 6; // for playtesting
}

void ValueBox_Display(ValueBox* valuebox, SDL_Renderer* renderer, FontAtlas* font, Camera* camera){
    char string[64];
    itoa ( valuebox->value, string, 10 );
    RenderText(font, string, renderer, camera, valuebox->box.x, valuebox->box.y, Alignment::Centered);
}

void ValueBox_Destroy(ValueBox* valuebox){

}