#include "audioSystem.h"
#include "button.h"
#include "common.h"
#include "dev_gui.h"
#include "fontLibrary.h"
#include "game.h"
#include "gameState.h"
#include "imgui/imgui.h"
#include "panel.h"
#include "spriteLibrary.h"
#include "valuebox.h"

#include "SDL3/SDL_blendmode.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL.h"

#include <algorithm>

#include "card.h"
#include <emmintrin.h>
#include <iostream>
#include <random>
#include <chrono>
using namespace std;
using namespace Memory;

extern "C" {
  ValueBox test_VB; // test

  bool ConfigureGameViewport(SDL_Window* window,SDL_Renderer* renderer, ScreenInfo* screen){
    
    if(!SDL_SetWindowFullscreen(window, true)){
      SDL_Log("Fullscreen error %s", SDL_GetError());
      return false;
    }

    if(!SDL_GetRenderOutputSize(renderer, &screen->monitor_width, &screen->monitor_height)){
      SDL_Log("Renderer output error: %s", SDL_GetError());
      return false;
    }

    float scale_x = (float)screen->monitor_width/SCREEN_WIDTH;
    float scale_y = (float)screen->monitor_height/SCREEN_HEIGHT;
    screen->scale = std::min(scale_x, scale_y);
    screen->viewport.w = SCREEN_WIDTH * screen->scale;
    screen->viewport.h = SCREEN_HEIGHT * screen->scale;
    screen->viewport.x = (screen->monitor_width - screen->viewport.w) / 2.0f;
    screen->viewport.y = (screen->monitor_height - screen->viewport.h) / 2.0f;

    if (!SDL_SetRenderLogicalPresentation(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX)){
      SDL_Log("Logical presentation error: %s", SDL_GetError());
      return false;
    }
    return true;
  }
  
  void SetUpBoilerplate(GameData* data, SDL_Window* window, SDL_Renderer* renderer){
    DEV::Initialize(window, renderer);
    InitializeAudioSystem(&data->audio, data->arena_main);
    AssetManagement::LoadAllSFX(&data->audio);
    AssetManagement::LoadAllSprites(data->spriteBuffer, renderer);
    data->imGui_context = ImGui::GetCurrentContext();
    AssetManagement::LoadFont(renderer, "assets/fonts/ByteBounce.ttf", &data->font, 48);

    SDL_Texture* blackfade = GetSprite(SPRITE_ID::black_1x1, data->spriteBuffer)->texture;
    SDL_SetTextureBlendMode(blackfade, SDL_BLENDMODE_BLEND);
    // PlaySong(SONG_ID::THEME); // just muted for my sanity
  }
  
  void Initialize(GameData* data, SDL_Window* window, SDL_Renderer* renderer){
    SetUpBoilerplate(data, window, renderer);
    if (!ConfigureGameViewport(window, renderer, &data->screen)){
      data->running = false;
      return;
    }
    data->mainPanel = new MainPanel{};
    InitializeLayout(data->mainPanel, data);
    ValueBox_INIT(&test_VB);
    
  for (int i = 0; i < data->DECK_SIZE; ++i){
  Card* card = &data->cards[i];

  data->cards[i].suit = i % 4 + 1;
  data->cards[i].rank = i % 13 + 1; 
  data->cards[i].has_been_played = false;


  card[i].suit = i % 4 + 1; // 4 suits
  card[i].rank = i % 13 + 1; // 13 values
  card[i].has_been_played = false;

  std::cout << "New Card";
  std::cout << "\n";
  std::cout << card[i].suit;
  std::cout << "\n";
  std::cout << "\n";
  std::cout << card[i].rank;
  std::cout << "\n";
  std::cout << "\n";
  std::cout << card[i].has_been_played;
  std::cout << "\n";
  std::cout << "\n";
};


    // To obtain a time-based seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();;

    int n = sizeof(data->cards) / sizeof(data->cards[0]);

    // Shuffling our array
    shuffle(data->cards, data->cards + n,
            default_random_engine(seed));

    // Printing our array
    for (int i = 0; i < n; ++i)
        std::cout << data->cards[i].rank << " ";
    std::cout << std::endl;
    std::cout << "\n";
   // std::cout << data->cards[51].rank;


    

// std::cout << "hello!";
// std::cout << data->cards[3].suit;
// std::cout << "\n";
// std::cout << data->cards[3].rank;
// std::cout << "\n";
// std::cout << data->cards[3].has_been_played;
  }
   
   bool HandleEvents(GameData *data, SDL_Event event){
    DEV::ProcessEvents(&event);

    if(event.type != SDL_EVENT_KEY_DOWN){
        return true;
    }
    if(event.key.key == SDLK_ESCAPE){
        return false;
    }

     return true;
  }

 void Update(GameData* data, float dt){
    EditorData* editorData = &data->editor_data;

   // std::cout << data->cards[51].rank;

  }
     
  void Draw(GameData* data, SDL_Renderer* renderer){
    DEV::PreDraw(data->imGui_context);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_FRect test = {0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 50, 100, 180, 255);
    SDL_RenderFillRect(renderer, &test);

    RenderMainPanel(data->mainPanel, renderer, data, &data->font, &data->camera);
    // // test draw card
    // Card card;
    // card.rank = 1;
    // card.suit = 1;
    // card.has_been_played = false;

    // // int card_x = 200;
    // // int card_y = 200;
    // SDL_FRect card_pos {200, 200, 200, 200};

    // SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::Card, data->spriteBuffer)->texture, NULL, &card_pos);

// test draw the deck of cards
int deck_x = data->cards->has_been_played = false;
int deck_y = data->cards->has_been_played = false;
SDL_FRect card_pos {(float)deck_x * 400, (float)deck_y * 400, 400, 400};





    for (int i = 0; i < data->DECK_SIZE; ++i)
    {
      if (data->cards[i].has_been_played == false)
      {
     
       if (data->cards[i].rank == 1 && data->cards[i].suit == 1)
       {
        
        // std::cout << data->cards[i].rank << "\n";
        // std::cout << data->cards[i].suit << "\n";

        data->cards[i].has_been_played = true;

        std::cout << "The Ace_of_diamonds was in postion:";
        std::cout << i;

        SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::Ace_of_diamonds, data->spriteBuffer)->texture, NULL, &card_pos);
       
       }
        
      }
    }





    // test draw higherButton
    int higherButton_x = 400;
    int higherButton_y = 500;
    SDL_FRect higherButton_pos {400, 500, 400, 500};

    SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::HigherButton, data->spriteBuffer)->texture, NULL, &higherButton_pos);
        
    // test draw lowerButton
    int lowerButton_x = 400;
    int lowerButton_y = 300;
    SDL_FRect lowerButton_pos {400, 300, 400, 300};

    SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::LowerButton, data->spriteBuffer)->texture, NULL, &lowerButton_pos);

    DEV::Draw(data, renderer);
    SDL_RenderPresent(renderer);
  }

  void OnQuit(SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
  }

}
