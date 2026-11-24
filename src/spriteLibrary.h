#pragma once

#include "SDL3/SDL_render.h"

enum class SPRITE_ID{
  Fallback,
   black_1x1,
   Button_Basic,
   Snake,
   Wall,
   Ground,
   Ground2,
   Ground3,
   Ground4,
   Ground5,
   Ground6,
   Ground7,
   Ground8,
   Apple,

  Card,
  HigherButton,
  LowerButton,

  Ace_of_diamonds,

  Ace_of_club,
  Ace_of_diamond,
  Ace_of_heart,
  Ace_of_spade,

  Two_of_club,
  Two_of_diamond,
  Two_of_heart,
  Two_of_spade,

  Three_of_club,
  Three_of_diamond,
  Three_of_heart,
  Three_of_spade,

  Four_of_club,
  Four_of_diamond,
  Four_of_heart,
  Four_of_spade,

  Five_of_club,
  Five_of_diamond,
  Five_of_heart,
  Five_of_spade,

  Six_of_club,
  Six_of_diamond,
  Six_of_heart,
  Six_of_spade,

  Seven_of_club,
  Seven_of_diamond,
  Seven_of_heart,
  Seven_of_spade,

  Eight_of_club,
  Eight_of_diamond,
  Eight_of_heart,
  Eight_of_spade,

  Nine_of_club,
  Nine_of_diamond,
  Nine_of_heart,
  Nine_of_spade,

  Ten_of_club,
  Ten_of_diamond,
  Ten_of_heart,
  Ten_of_spade,

  Jack_of_club,
  Jack_of_diamond,
  Jack_of_heart,
  Jack_of_spade,

  Queen_of_club,
  Queen_of_diamond,
  Queen_of_heart,
  Queen_of_spade,

  King_of_club,
  King_of_diamond,
  King_of_heart,
  King_of_spade,

  Higher,
  Lower,
  PlayerGuessedWrong,
  BothCardsWereEqual,
  layoutTest,
  GameOverScreen,
  VictoryScreen,

  buttonTest01
};

const int NOT_SET = -1;

struct Sprite{
  SDL_Texture* texture;
  int width;
  int height;
  int pivot_x;
  int pivot_y;
  int sprite_count_x;
  int sprite_count_y;
  int framerate;
};

struct SpriteRenderInfo{
  Sprite* sprite;
  int frame;
  bool flipped_x;

  SpriteRenderInfo(){
    this->sprite = nullptr;
    this->frame = 0;
    this->flipped_x = false;
  }

  SpriteRenderInfo(int frame, Sprite* sprite){
    this->frame = frame;
    this->sprite = sprite;
    this->flipped_x = false;
  }

  SpriteRenderInfo(int frame, Sprite* sprite, bool flipped_x){
    this->frame = frame;
    this->sprite = sprite;
    this->flipped_x = flipped_x;
  }

  SpriteRenderInfo(Sprite* sprite){
    this->sprite = sprite;
    this->frame = 0;
    this->flipped_x = false;
  }  
};

inline int GetSpriteCount(Sprite* sprite){
  if(sprite->sprite_count_x == NOT_SET) return 1;
  if(sprite->sprite_count_y == NOT_SET) return 1;
  return sprite->sprite_count_x * sprite->sprite_count_y;
}

struct SpriteDataEntry{
  SPRITE_ID id;
  const char* path;
  int pivot_x = NOT_SET;
  int pivot_y = NOT_SET;
  int tileset_cell_count_x = NOT_SET;
  int tileset_cell_count_y = NOT_SET;
  int framerate = NOT_SET;
};


Sprite* GetSprite(SPRITE_ID sprite_id, Sprite* spriteBuffer);

namespace AssetManagement
{
  void LoadSprite(Sprite* spriteBuffer, SpriteDataEntry entry, SDL_Renderer* renderer);
  void LoadAllSprites(Sprite* spriteBuffer, SDL_Renderer* renderer);
}
