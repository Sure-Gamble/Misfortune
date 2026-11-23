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

  }
     
  void Draw(GameData* data, SDL_Renderer* renderer){
    DEV::PreDraw(data->imGui_context);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    //ValueBox_Display(&test_VB, renderer, &data->font, &data->camera); // Test 
    //InitializeLayout (data->mainPanel, renderer, data, &data->font, &data->camera); //Test
    // test for paneling
    SDL_FRect test = {0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 50, 100, 180, 255);
    SDL_RenderFillRect(renderer, &test);

    RenderMainPanel(data->mainPanel, renderer, data, &data->font, &data->camera);
    RenderPanelMockup(data->mainPanel, renderer);


    DEV::Draw(data, renderer);
    SDL_RenderPresent(renderer);
  }

  void OnQuit(SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
  }

}
