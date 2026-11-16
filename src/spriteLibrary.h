#pragma once

#include "SDL3/SDL_render.h"

enum class SPRITE_ID{
  Fallback,
  black_1x1,
  Button_Basic,
  Snake,
  Wall,
  Ground,
  Apple
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
