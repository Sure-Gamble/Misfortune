#pragma once
#include "SDL3/SDL_rect.h"
#include "fontLibrary.h"
#include "rendering.h"

struct Sprite;
struct GameData;

enum class ButtonType {
  NONE,
  START_GAME,
  HIGHER,
  LOWER,
  TOKEN_MORE,
  TOKEN_LESS,
  SCRIP_MORE,
  SCRIP_LESS,
  QUOTA_1,
  QUOTA_2,
  QUOTA_3,
  QUOTA_4,
  QUOTA_5,
  BET_5,
  BET_10,
  BET_25,
  BET_100,
  CONFIRM,
  QUIT
};

enum class ButtonState {
  NEUTRAL, 
  HOVER, 
  PRESSED
};

struct Button {
  ButtonType type;
  SDL_FRect rect;
  Sprite* sprite;
  bool is_active;
  bool is_dynamic;
  FontAtlas* font;
  const char* text;
  ButtonState state = ButtonState::NEUTRAL;
  bool armed = false;  //true om tryckt
};


void PressButton(Button* button, GameData* data);
int GetActiveButtonCount(Button* buttons, int count);
bool IsHoveredOver(Button* button, float x, float y);

void UpdateButton(Button* b, GameData* data, float mx, float my, bool mouseDown, bool mousePressedNow, bool mouseReleasedNow);

void SetupButton(Button* button,
                 ButtonType type,
                 Sprite* spriteBuffer,
                 SDL_FRect rect,
                 Alignment mode,
                 FontAtlas* font = nullptr,
                 const char* text = nullptr);  
