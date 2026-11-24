#pragma once
#include "arena.h"
#include "audioSystem.h"
#include "button.h"
#include "camera.h"
#include "fontLibrary.h"
#include "imgui/imgui_internal.h"
#include "input.h"
#include "spriteLibrary.h"
#include "card.h"

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
  ImGuiContext* imGui_context;
  const float* dt;  
  float* dt_scaler;



  static const int DECK_SIZE = 52;
  Card cards[DECK_SIZE];
  int roundIndex;
  int drawTheCorrectCardOnScreen;
  int drawThePreviousCardOnScreen;
  int higherOrLower;

//knappstuff
  bool prevMouseDown = false;         // var musknappen nedtryckt förra framen?
  static const int MAX_BUTTONS = 16;  //Max knappar
  Button buttons[MAX_BUTTONS];        //knapparna
  int buttonCount = 0;                //Hur många knappar används/ritas. Sätts sen i Initialize.
 };
