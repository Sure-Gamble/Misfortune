#include "spriteLibrary.h"
#include "SDL3_Image/SDL_image.h"
#include <cassert>

using namespace std;

const char* FALLBACK_PATH = "assets/sprites/fallback.png";

static const SpriteDataEntry all_sprite_data[] = {
  {SPRITE_ID::Fallback, FALLBACK_PATH,8,8},
  {SPRITE_ID::black_1x1, "assets/sprites/1x1_black.png",0,0},
  {SPRITE_ID::Button_Basic, "assets/sprites/basic_button.png",0,0,3,3},
  {SPRITE_ID::Snake, "assets/sprites/snake.png"},
  {SPRITE_ID::Apple, "assets/sprites/apple.png"},
  {SPRITE_ID::Wall, "assets/sprites/wall.png"},
  {SPRITE_ID::Ground, "assets/sprites/ground.png"},

  {SPRITE_ID::Card, "assets/sprites/card.png"},
  {SPRITE_ID::HigherButton, "assets/sprites/snake.png"},
  {SPRITE_ID::LowerButton, "assets/sprites/wall.png"},

  {SPRITE_ID::Ace_of_diamonds, "assets/sprites/cards/Ace_of_diamonds.png"},

  {SPRITE_ID::Ace_of_club, "assets/sprites/cards/ace_of_club.png"},
  {SPRITE_ID::Ace_of_diamond, "assets/sprites/cards/ace_of_diamond.png"},
  {SPRITE_ID::Ace_of_heart, "assets/sprites/cards/ace_of_heart.png"},
  {SPRITE_ID::Ace_of_spade, "assets/sprites/cards/ace_of_spade.png"},

  {SPRITE_ID::Two_of_club, "assets/sprites/cards/2_of_club.png"},
  {SPRITE_ID::Two_of_diamond, "assets/sprites/cards/2_of_diamond.png"},
  {SPRITE_ID::Two_of_heart, "assets/sprites/cards/2_of_heart.png"},
  {SPRITE_ID::Two_of_spade, "assets/sprites/cards/2_of_spade.png"},

  {SPRITE_ID::Three_of_club, "assets/sprites/cards/3_of_club.png"},
  {SPRITE_ID::Three_of_diamond, "assets/sprites/cards/3_of_diamond.png"},
  {SPRITE_ID::Three_of_heart, "assets/sprites/cards/3_of_heart.png"},
  {SPRITE_ID::Three_of_spade, "assets/sprites/cards/3_of_spade.png"},

  {SPRITE_ID::Four_of_club, "assets/sprites/cards/4_of_club.png"},
  {SPRITE_ID::Four_of_diamond, "assets/sprites/cards/4_of_diamond.png"},
  {SPRITE_ID::Four_of_heart, "assets/sprites/cards/4_of_heart.png"},
  {SPRITE_ID::Four_of_spade, "assets/sprites/cards/4_of_spade.png"},

  {SPRITE_ID::Five_of_club, "assets/sprites/cards/5_of_club.png"},
  {SPRITE_ID::Five_of_diamond, "assets/sprites/cards/5_of_diamond.png"},
  {SPRITE_ID::Five_of_heart, "assets/sprites/cards/5_of_heart.png"},
  {SPRITE_ID::Five_of_spade, "assets/sprites/cards/5_of_spade.png"},

  {SPRITE_ID::Six_of_club, "assets/sprites/cards/6_of_club.png"},
  {SPRITE_ID::Six_of_diamond, "assets/sprites/cards/6_of_diamond.png"},
  {SPRITE_ID::Six_of_heart, "assets/sprites/cards/6_of_heart.png"},
  {SPRITE_ID::Six_of_spade, "assets/sprites/cards/6_of_spade.png"},

  {SPRITE_ID::Seven_of_club, "assets/sprites/cards/7_of_club.png"},
  {SPRITE_ID::Seven_of_diamond, "assets/sprites/cards/7_of_diamond.png"},
  {SPRITE_ID::Seven_of_heart, "assets/sprites/cards/7_of_heart.png"},
  {SPRITE_ID::Seven_of_spade, "assets/sprites/cards/7_of_spade.png"},

  {SPRITE_ID::Eight_of_club, "assets/sprites/cards/8_of_club.png"},
  {SPRITE_ID::Eight_of_diamond, "assets/sprites/cards/8_of_diamond.png"},
  {SPRITE_ID::Eight_of_heart, "assets/sprites/cards/8_of_heart.png"},
  {SPRITE_ID::Eight_of_spade, "assets/sprites/cards/8_of_spade.png"},

  {SPRITE_ID::Nine_of_club, "assets/sprites/cards/9_of_club.png"},
  {SPRITE_ID::Nine_of_diamond, "assets/sprites/cards/9_of_diamond.png"},
  {SPRITE_ID::Nine_of_heart, "assets/sprites/cards/9_of_heart.png"},
  {SPRITE_ID::Nine_of_spade, "assets/sprites/cards/9_of_spade.png"},

  {SPRITE_ID::Ten_of_club, "assets/sprites/cards/10_of_club.png"},
  {SPRITE_ID::Ten_of_diamond, "assets/sprites/cards/10_of_diamond.png"},
  {SPRITE_ID::Ten_of_heart, "assets/sprites/cards/10_of_heart.png"},
  {SPRITE_ID::Ten_of_spade, "assets/sprites/cards/10_of_spade.png"},

  {SPRITE_ID::Jack_of_club, "assets/sprites/cards/jack_of_club.png"},
  {SPRITE_ID::Jack_of_diamond, "assets/sprites/cards/jack_of_diamond.png"},
  {SPRITE_ID::Jack_of_heart, "assets/sprites/cards/jack_of_heart.png"},
  {SPRITE_ID::Jack_of_spade, "assets/sprites/cards/jack_of_spade.png"},

  {SPRITE_ID::Queen_of_club, "assets/sprites/cards/queen_of_club.png"},
  {SPRITE_ID::Queen_of_diamond, "assets/sprites/cards/queen_of_diamond.png"},
  {SPRITE_ID::Queen_of_heart, "assets/sprites/cards/queen_of_heart.png"},
  {SPRITE_ID::Queen_of_spade, "assets/sprites/cards/queen_of_spade.png"},

  {SPRITE_ID::King_of_club, "assets/sprites/cards/king_of_club.png"},
  {SPRITE_ID::King_of_diamond, "assets/sprites/cards/king_of_diamond.png"},
  {SPRITE_ID::King_of_heart, "assets/sprites/cards/king_of_heart.png"},
  {SPRITE_ID::King_of_spade, "assets/sprites/cards/king_of_spade.png"}
  };

Sprite* GetSprite(SPRITE_ID sprite_id, Sprite* spriteBuffer){
  Sprite* sprite = &spriteBuffer[(int)sprite_id];
  if(sprite == nullptr || sprite->texture == nullptr){
    assert(sprite_id != SPRITE_ID::Fallback);
    return GetSprite(SPRITE_ID::Fallback, spriteBuffer);
  }
  return &spriteBuffer[(int)sprite_id];
}

namespace AssetManagement{
  void LoadAllSprites(Sprite* spriteBuffer, SDL_Renderer *renderer){
    for (SpriteDataEntry entry : all_sprite_data) {
      LoadSprite(spriteBuffer, entry, renderer);
    }
  }

  void LoadSprite(Sprite* spriteBuffer, SpriteDataEntry entry, SDL_Renderer* renderer){
    SDL_Surface* surface = IMG_Load(entry.path); 
    if(surface == nullptr){
      surface = IMG_Load(FALLBACK_PATH);
    }
    assert(surface != nullptr);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    Sprite* sprite = &spriteBuffer[(int)entry.id];
    sprite->texture = texture;
    sprite->height = texture->h;
    sprite->width = texture->w;
    if(entry.pivot_x == NOT_SET || entry.pivot_y == NOT_SET){
      sprite->pivot_x = sprite->width / 2;
      sprite->pivot_y = sprite->height / 2;
    }
    else{
      sprite->pivot_x = entry.pivot_x;
      sprite->pivot_y = entry.pivot_y;
    }

    sprite->sprite_count_x = entry.tileset_cell_count_x;
    sprite->sprite_count_y = entry.tileset_cell_count_y;
    sprite->framerate = entry.framerate;
    
    SDL_DestroySurface(surface);
  }
}
