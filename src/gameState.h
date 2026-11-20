#pragma once
#include "arena.h"
#include "audioSystem.h"
#include "camera.h"
#include "fontLibrary.h"
#include "imgui/imgui_internal.h"
#include "input.h"
#include "spriteLibrary.h"
//#include "panel.h"
struct MainPanel;


struct EditorData{
  float* fps_buffer;
  int fps_buffer_count;
  int fps_buffer_index;
};


struct GameData {
  EditorData editor_data;
  Input input;
  Sprite* spriteBuffer;
  AudioSystem audio;
  FontAtlas font; // not relevant
  bool running;
  Memory::Arena* arena_main;
  Memory::Arena* arena_images;
  Memory::Arena* arena_commands;
  Memory::Arena* arena_input;
  Memory::Arena* arena_scratch;
  Camera camera;
  MainPanel* mainPanel;
  ImGuiContext* imGui_context;
  const float* dt;  
  float* dt_scaler;
 };
