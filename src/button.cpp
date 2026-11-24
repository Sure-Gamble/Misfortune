#include "button.h"
#include "collision.h"
#include "common.h"
#include "gameState.h"
#include "rendering.h"
#include "spriteLibrary.h"

bool IsHoveredOver(Button* button, float x, float y){
  if(button == nullptr) return false;
  if(button->is_active == false) return false;
  assert(button->type != ButtonType::NONE);
  
  return CheckCollisionInsideBounds(button->rect, x, y);
}

void SetupButton(Button* button, ButtonType type, Sprite* spriteBuffer, SDL_FRect rect, Alignment mode, FontAtlas* font, const char* text){
  assert(type != ButtonType::NONE);
  button->type = type;
  button->rect = rect;

  //This moves button origo to the center of the button
  if(mode == Alignment::Centered){
    button->rect.x -= button->rect.w / 2;
    button->rect.y -= button->rect.h / 2;
  }
  button->is_active = true;

  //resets buttons
  button->state = ButtonState::NEUTRAL;
  button->armed = false;

//What graphics should be used?
  switch(button->type){
  case ButtonType::START_GAME:
    button->sprite = GetSprite(SPRITE_ID::Button_Basic, spriteBuffer);
    break;
  case ButtonType::HIGHER:
    button->sprite = GetSprite(SPRITE_ID::buttonTest01, spriteBuffer);
    break;
  case ButtonType::LOWER:
    button->sprite = GetSprite(SPRITE_ID::Fallback, spriteBuffer);
    break;
  case ButtonType::CONVERT_SCRIP:
    button->sprite = GetSprite(SPRITE_ID::Fallback, spriteBuffer);
    break;
  case ButtonType::CONVERT_LUCKY:
    button->sprite = GetSprite(SPRITE_ID::Fallback, spriteBuffer);
    break;
  case ButtonType::BET_5:
    button->sprite = GetSprite(SPRITE_ID::Fallback, spriteBuffer);
    break;
  case ButtonType::BET_10:
    button->sprite = GetSprite(SPRITE_ID::Fallback, spriteBuffer);
    break;
  case ButtonType::BET_25:
    button->sprite = GetSprite(SPRITE_ID::Fallback, spriteBuffer);
    break;
  case ButtonType::BET_50:
    button->sprite = GetSprite(SPRITE_ID::Fallback, spriteBuffer);
    break;
  case ButtonType::BET_100:
    button->sprite = GetSprite(SPRITE_ID::Fallback, spriteBuffer);
    break;
  case ButtonType::QUIT:
    button->sprite = GetSprite(SPRITE_ID::Fallback, spriteBuffer);
    break;
  default:
    button->sprite = GetSprite(SPRITE_ID::Fallback, spriteBuffer);
  break;
  }
  bool hasText = !IsStringEmpty(text);

  if(font == nullptr){
    assert(!hasText);
  }
  if(hasText){
    assert(font != nullptr);
  }

  button->font = font;
  button->text = text;
}

void PressButton(Button *button, GameData *data){
  if(button == nullptr){
    return;
  }
  assert(button->is_active);
  switch(button->type){
  case ButtonType::NONE:
    assert(false);
    break;
  case ButtonType::START_GAME:
    break;
  case ButtonType::HIGHER:
    break;
  case ButtonType::LOWER:
    break;
  case ButtonType::CONVERT_SCRIP:
    break;
  case ButtonType::CONVERT_LUCKY:
    break;
  case ButtonType::BET_5:
    break;
  case ButtonType::BET_10:
    break;
  case ButtonType::BET_25:
    break;
  case ButtonType::BET_50:
    break;
  case ButtonType::BET_100:
    break;   
  case ButtonType::QUIT:
    data->running = false;
    break;
  }
}

int GetActiveButtonCount(Button *buttons, int count){
  if(count == 0){
    return 0;
  }
  int amount = 0;
  for (int i = 0; i < count; i++) {
    if(buttons[i].is_active){
      amount++;
    }    
  }
  return amount;
}

void UpdateButton(Button* b, GameData* data, float mx, float my, bool mouseDown, bool mousePressedNow, bool mouseReleasedNow){
  if(b == nullptr || !b->is_active) return;

  bool hovered = IsHoveredOver(b, mx, my);

//Mouse press aborted.
  if(!hovered){
    b->state = ButtonState::NEUTRAL;
    b->armed = false;
    return;
  }

  if(mousePressedNow) b->armed = true;
  b->state = (mouseDown && b->armed)  ? ButtonState::PRESSED : ButtonState::HOVER; //Pressed only if pressed on button, else hoover

//pressed only if mouse released over button
if(mouseReleasedNow && b->armed){
  PressButton(b, data);
  b->armed = false;
  }
}