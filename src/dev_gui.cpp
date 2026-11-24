#include "dev_gui.h"
#include "FMOD/fmod.h"
#include "SDL3/SDL_video.h"
#include "common.h"
#include "gameState.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include "SDL3/SDL_render.h"
#include "imgui/imgui_internal.h"
#include <cstddef>
#include <string>
using namespace Memory;
using namespace std;

void DEV::Initialize(SDL_Window* window, SDL_Renderer* renderer){
  ImGui::CreateContext();
  ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer3_Init(renderer);
  ImGuiStyle* style = &ImGui::GetStyle();
  style->FontSizeBase = 18;
  ImGuiIO& io = ImGui::GetIO();
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  io.DisplaySize = ImVec2((float)w, (float)h);
}

void DEV::ProcessEvents(SDL_Event* event){
  ImGui_ImplSDL3_ProcessEvent(event);
}
void DEV::PreDraw(ImGuiContext* saved_context){
  if(ImGui::GetCurrentContext() == nullptr){
    ImGui::SetCurrentContext(saved_context);
  }
  
  ImGui::NewFrame();
}

void Draw_Imgui_Arena_Usage(Arena* arena, string name_of_arena){
  float fraction = (float)arena->used / (float)arena->size;
  string barText = name_of_arena;
  barText += " " + to_string(arena->used);
  barText += " / " + to_string(arena->size);
  ImGui::ProgressBar(fraction, ImVec2(-1,0), barText.c_str());
}

void DrawFPS(GameData* data){
  EditorData* editor = &data->editor_data;
  editor->fps_buffer[editor->fps_buffer_index++] = 1.0 / *data->dt * *data->dt_scaler;
  editor->fps_buffer_index %= editor->fps_buffer_count;
  ImGui::PlotHistogram("fps", editor->fps_buffer, editor->fps_buffer_count,0,nullptr ,0,FPS, ImVec2(-1,35));
}

 
void DrawAudioMemoryPanel(AudioSystem* audio) {
  int current_bytes = 0;
  FMOD_Memory_GetStats(&current_bytes, NULL, false);

  float fraction = (float)current_bytes / (float)AUDIO_MEMORY_ALLOWANCE;

  char overlay[64];
  snprintf(overlay, sizeof(overlay), "%d KB / %d KB", current_bytes / 1024, (int)(AUDIO_MEMORY_ALLOWANCE / 1024));

  ImGui::Text("FMOD Memory Pool");
  ImGui::ProgressBar(fraction, ImVec2(-1, 0), overlay);
}


void DEV::Draw(GameData* data, SDL_Renderer* renderer){
  ImGui::Begin("Dev Tools");
  ImGui::Text("memory arena usage amount");
  
  Draw_Imgui_Arena_Usage(data->arena_main, "all memory");
  Draw_Imgui_Arena_Usage(data->arena_images, "images");
  Draw_Imgui_Arena_Usage(data->arena_commands, "commands");
  Draw_Imgui_Arena_Usage(data->arena_input, "input");
  Draw_Imgui_Arena_Usage(data->arena_scratch, "scratch");

  if(data->audio.initialized){
    DrawAudioMemoryPanel(&data->audio);
  }
 
  DrawFPS(data);

  ImGui::SliderFloat("deltaTimeScaler", data->dt_scaler, 0.1, 3);  

  Input* input = &data->input;
  ImGui::Text("MX:%1f MY:%1f", input->mouse_x, input->mouse_y);
  
  ImGui::Text("scripAmount: %d", data->scripAmount);
  ImGui::Text("scripAmountBetted: %d", data->scripAmountBetted);
  ImGui::Text("luckyTokenAmount: %d", data->luckyTokenAmount);
  ImGui::Text("quotaOfTokensRequiredToWin: %d", data->quotaOfTokensRequiredToWin);
  ImGui::Text("equalCardBonus: %d", data->equalCardBonus);
  ImGui::Text("roundIndex: %d", data->roundIndex);

  ImGui::End();


  ImGui::Render();
  ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer );
}



