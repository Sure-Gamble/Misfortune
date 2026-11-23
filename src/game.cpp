#include "game.h"
#include "SDL3/SDL_blendmode.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include "SDL3/SDL_video.h"
#include "audioSystem.h"
#include "button.h"
#include "dev_gui.h"
#include "fontLibrary.h"
#include "gameState.h"
#include "imgui/imgui.h"
#include "input.h"
#include "spriteLibrary.h"
#include "card.h"
#include <emmintrin.h>
#include <iostream>
#include <random>
#include <chrono>
using namespace std;
using namespace Memory;

extern "C" {

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
    
  data->roundIndex = 0;
  data->drawTheCorrectCardOnScreen = 0;
  data->drawThePreviousCardOnScreen = 0;

  for (int i = 0; i < data->DECK_SIZE; ++i){
  // Card* card = &data->cards[i];

  data->cards[i].suit = i % 4 + 1;
  data->cards[i].rank = i % 13 + 1; 
  data->cards[i].has_been_played = false;

  // card[i].suit = i % 4 + 1; // 4 suits
  // card[i].rank = i % 13 + 1; // 13 values
  // card[i].has_been_played = false;

  // std::cout << "New Card";
  // std::cout << "\n";
  // std::cout << card[i].suit;
  // std::cout << "\n";
  // std::cout << "\n";
  // std::cout << card[i].rank;
  // std::cout << "\n";
  // std::cout << "\n";
  // std::cout << card[i].has_been_played;
  // std::cout << "\n";
  // std::cout << "\n";
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

    // Loop for player's choice, simply compare it with the array, no need to loop array while player makes choice(?)

        

         int currentlyShownCardRank = data->cards[data->roundIndex].rank;
         int pickedCardRank = data->cards[data->roundIndex + 1].rank; // will crash if deck does not contain any cards!

         bool playerPressedUp = KeyPressed(&data->input, SDL_SCANCODE_UP);
         bool playerPressedDown = KeyPressed(&data->input, SDL_SCANCODE_DOWN);

         bool pickedCardRankIsHigher = pickedCardRank > currentlyShownCardRank;
         bool pickedCardRankIsLower = pickedCardRank < currentlyShownCardRank;


         if(playerPressedUp == true || playerPressedDown == true)
         {
            if (playerPressedUp == true && pickedCardRankIsHigher == true && pickedCardRank != currentlyShownCardRank)
            {
                // increase the score here

                data->higherOrLower = 70;
            }
            if (playerPressedUp == true && pickedCardRankIsHigher == false && pickedCardRank != currentlyShownCardRank)
            {
                // increase the score here

                data->higherOrLower = 72;
            }
            else if (playerPressedDown == true && pickedCardRankIsLower == true && pickedCardRank != currentlyShownCardRank)
            {
                // increase the score here

                data->higherOrLower = 71;
            }
            else if (playerPressedDown == true && pickedCardRankIsLower == false && pickedCardRank != currentlyShownCardRank)
            {
                // increase the score here

                data->higherOrLower = 72;
            }
            else if (pickedCardRank == currentlyShownCardRank)
            {
                data->higherOrLower = 73;
            }
            data->roundIndex++;
         }

         // if(KeyPressed(&data->input, SDL_SCANCODE_UP) && pickedCardRank > currentlyShownCardRank)
         // {

         //     // increase the score here

         //    data->roundIndex++;

         //     std::cout << "\n";
         //     std::cout << "The picked card was higher than the shown one! You win!";
         //     std::cout << "\n";
         //     std::cout << "test";

            
         // }

         // if (KeyPressed(&data->input, SDL_SCANCODE_DOWN) && pickedCardRank < currentlyShownCardRank)
         // {

         //     data->roundIndex++;

         //     // game over here(?)

         //     std::cout << "\n";
         //     std::cout << "The picked card was lower than the shown one! You lose!";
         //     std::cout << "\n";

             
         // }



    // fetch pointers
    

//     int i = 0;
//     while(i < data->DECK_SIZE)
//     {
//       int currentlyShownCardRank = data->cards[i].rank;
//       int pickedCardRank = data->cards[i + 1].rank; // will crash if deck does not contain any cards!

//       int currentlyShownCardSuit = data->cards[i].suit;
//       int pickedCardSuit = data->cards[i + 1].suit;

//       if (data->cards[i].has_been_played == false)
//       {

//        // std::cout << "\n";
//        // std::cout << currentlyShownCardRank;
//        // std::cout << "\n";
//        // std::cout << pickedCardRank;



//         //  bool higherOrLower = SDL_WaitEvent(KeyPressed(&data->input, SDL_SCANCODE_UP));



//         if(KeyPressed(&data->input, SDL_SCANCODE_UP) && pickedCardRank > currentlyShownCardRank)
//         {

//             // increase the score here

//             std::cout << "\n";
//             std::cout << "The picked card was higher than the shown one! You win!";
//             std::cout << "\n";
//             std::cout << "test";

//             data->cards[i].has_been_played = true;
//             i++;
//         }

//         if (KeyPressed(&data->input, SDL_SCANCODE_DOWN) && pickedCardRank <= currentlyShownCardRank)
//         {

//             // game over here(?)

//             std::cout << "\n";
//             std::cout << "The picked card was lower than the shown one! You lose!";
//             std::cout << "\n";

//             data->cards[i].has_been_played = true;        


//         }
//     }  
// }



//     for (int i = 0; i < data->DECK_SIZE; i++)
//     {
//       int currentlyShownCardRank = data->cards[i].rank;
//       int pickedCardRank = data->cards[i + 1].rank; // will crash if deck does not contain any cards!

//       int currentlyShownCardSuit = data->cards[i].suit;
//       int pickedCardSuit = data->cards[i + 1].suit;

//       if (data->cards[i].has_been_played == false)
//       {

//        // std::cout << "\n";
//        // std::cout << currentlyShownCardRank;
//        // std::cout << "\n";
//        // std::cout << pickedCardRank;



//        //  bool higherOrLower = SDL_WaitEvent(KeyPressed(&data->input, SDL_SCANCODE_UP));



//         if(KeyPressed(&data->input, SDL_SCANCODE_UP) && pickedCardRank > currentlyShownCardRank)
//         {

//             // increase the score here

//             std::cout << "\n";
//             std::cout << "The picked card was higher than the shown one! You win!";
//             std::cout << "\n";
//             std::cout << "test";

            
//         }

//         if(KeyPressed(&data->input, SDL_SCANCODE_DOWN) && pickedCardRank < currentlyShownCardRank)
//         {

//             // game over here(?)

//             std::cout << "\n";
//             std::cout << "The picked card was lower than the shown one! You lose!";
//             std::cout << "\n";

            


//         }
//     }
// }
}    

   void Draw(GameData* data, SDL_Renderer* renderer){
     DEV::PreDraw(data->imGui_context);
     SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);
     SDL_RenderClear(renderer);

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
// int deck_x = data->cards->has_been_played = false;
// int deck_y = data->cards->has_been_played = false;
    
    SDL_FRect card_pos3 {16, 256, 200, 300};
    SDL_FRect card_pos {1125, 75, 300, 400};
    SDL_FRect card_pos2 {600, 600, 600, 600};
    SDL_FRect card_pos4 {1, 1, 1920, 1080};
    



































    // for (int i = 0; i < data->DECK_SIZE; ++i)
    // {
    //   if (data->cards[i].has_been_played == false)
    //   {
     
    //    if (data->cards[i].rank == 1 && data->cards[i].suit == 1)
    //    {
        
    //     // std::cout << data->cards[i].rank << "\n";
    //     // std::cout << data->cards[i].suit << "\n";

    //     data->cards[i].has_been_played = true;

    //     std::cout << "The ace_of_diamond was in postion:";
    //     std::cout << i;

    //    // SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::Ace_of_club, data->spriteBuffer)->texture, NULL, &card_pos);
       
    //    }
        
    //   }
    // }





    // card_pos.w = 64;
    // card_pos.h = 1.5 * card_pos.w;
    // for (int i = (int)SPRITE_ID::Fallback; i <= (int)SPRITE_ID::King_of_spade; ++i) {
    //     card_pos.x = (i % 12) * card_pos.w;
    //     card_pos.y = (i / 12) * card_pos.h;
    //     SDL_RenderTexture(renderer, GetSprite((SPRITE_ID)i, data->spriteBuffer)->texture, NULL, &card_pos);
    // }

   

   if (data->cards[data->roundIndex].rank == 1 && data->cards[data->roundIndex].suit == 1)
   {
       data->drawTheCorrectCardOnScreen = 17;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 1 && data->cards[data->roundIndex].suit == 2)
   {
       data->drawTheCorrectCardOnScreen = 18;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 1 && data->cards[data->roundIndex].suit == 3)
   {
       data->drawTheCorrectCardOnScreen = 19;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 1 && data->cards[data->roundIndex].suit == 4)
   {
       data->drawTheCorrectCardOnScreen = 20;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }

   if (data->cards[data->roundIndex].rank == 2 && data->cards[data->roundIndex].suit == 1)
   {
       data->drawTheCorrectCardOnScreen = 21;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 2 && data->cards[data->roundIndex].suit == 2)
   {
       data->drawTheCorrectCardOnScreen = 22;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 2 && data->cards[data->roundIndex].suit == 3)
   {
       data->drawTheCorrectCardOnScreen = 23;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 2 && data->cards[data->roundIndex].suit == 4)
   {
       data->drawTheCorrectCardOnScreen = 24;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }

   if (data->cards[data->roundIndex].rank == 3 && data->cards[data->roundIndex].suit == 1)
   {
       data->drawTheCorrectCardOnScreen = 25;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 3 && data->cards[data->roundIndex].suit == 2)
   {
       data->drawTheCorrectCardOnScreen = 26;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 3 && data->cards[data->roundIndex].suit == 3)
   {
       data->drawTheCorrectCardOnScreen = 27;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 3 && data->cards[data->roundIndex].suit == 4)
   {
       data->drawTheCorrectCardOnScreen = 28;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }

   if (data->cards[data->roundIndex].rank == 4 && data->cards[data->roundIndex].suit == 1)
   {
       data->drawTheCorrectCardOnScreen = 29;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 4 && data->cards[data->roundIndex].suit == 2)
   {
       data->drawTheCorrectCardOnScreen = 30;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 4 && data->cards[data->roundIndex].suit == 3)
   {
       data->drawTheCorrectCardOnScreen = 31;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 4 && data->cards[data->roundIndex].suit == 4)
   {
       data->drawTheCorrectCardOnScreen = 32;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }

   if (data->cards[data->roundIndex].rank == 5 && data->cards[data->roundIndex].suit == 1)
   {
       data->drawTheCorrectCardOnScreen = 33;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 5 && data->cards[data->roundIndex].suit == 2)
   {
       data->drawTheCorrectCardOnScreen = 34;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 5 && data->cards[data->roundIndex].suit == 3)
   {
       data->drawTheCorrectCardOnScreen = 35;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 5 && data->cards[data->roundIndex].suit == 4)
   {
       data->drawTheCorrectCardOnScreen = 36;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }

   if (data->cards[data->roundIndex].rank == 6 && data->cards[data->roundIndex].suit == 1)
   {
       data->drawTheCorrectCardOnScreen = 37;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 6 && data->cards[data->roundIndex].suit == 2)
   {
       data->drawTheCorrectCardOnScreen = 38;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 6 && data->cards[data->roundIndex].suit == 3)
   {
       data->drawTheCorrectCardOnScreen = 39;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 6 && data->cards[data->roundIndex].suit == 4)
   {
       data->drawTheCorrectCardOnScreen = 40;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }

   if (data->cards[data->roundIndex].rank == 7 && data->cards[data->roundIndex].suit == 1)
   {
       data->drawTheCorrectCardOnScreen = 41;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 7 && data->cards[data->roundIndex].suit == 2)
   {
       data->drawTheCorrectCardOnScreen = 42;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 7 && data->cards[data->roundIndex].suit == 3)
   {
       data->drawTheCorrectCardOnScreen = 43;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 7 && data->cards[data->roundIndex].suit == 4)
   {
       data->drawTheCorrectCardOnScreen = 44;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }

   if (data->cards[data->roundIndex].rank == 8 && data->cards[data->roundIndex].suit == 1)
   {
       data->drawTheCorrectCardOnScreen = 45;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 8 && data->cards[data->roundIndex].suit == 2)
   {
       data->drawTheCorrectCardOnScreen = 46;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 8 && data->cards[data->roundIndex].suit == 3)
   {
       data->drawTheCorrectCardOnScreen = 47;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 8 && data->cards[data->roundIndex].suit == 4)
   {
       data->drawTheCorrectCardOnScreen = 48;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }

   if (data->cards[data->roundIndex].rank == 9 && data->cards[data->roundIndex].suit == 1)
   {
       data->drawTheCorrectCardOnScreen = 49;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 9 && data->cards[data->roundIndex].suit == 2)
   {
       data->drawTheCorrectCardOnScreen = 50;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 9 && data->cards[data->roundIndex].suit == 3)
   {
       data->drawTheCorrectCardOnScreen = 51;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 9 && data->cards[data->roundIndex].suit == 4)
   {
       data->drawTheCorrectCardOnScreen = 52;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }

   if (data->cards[data->roundIndex].rank == 10 && data->cards[data->roundIndex].suit == 1)
   {
       data->drawTheCorrectCardOnScreen = 53;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 10 && data->cards[data->roundIndex].suit == 2)
   {
       data->drawTheCorrectCardOnScreen = 54;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 10 && data->cards[data->roundIndex].suit == 3)
   {
       data->drawTheCorrectCardOnScreen = 55;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 10 && data->cards[data->roundIndex].suit == 4)
   {
       data->drawTheCorrectCardOnScreen = 56;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }

   if (data->cards[data->roundIndex].rank == 11 && data->cards[data->roundIndex].suit == 1)
   {
       data->drawTheCorrectCardOnScreen = 57;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 11 && data->cards[data->roundIndex].suit == 2)
   {
       data->drawTheCorrectCardOnScreen = 58;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 11 && data->cards[data->roundIndex].suit == 3)
   {
       data->drawTheCorrectCardOnScreen = 59;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 11 && data->cards[data->roundIndex].suit == 4)
   {
       data->drawTheCorrectCardOnScreen = 60;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }

   if (data->cards[data->roundIndex].rank == 12 && data->cards[data->roundIndex].suit == 1)
   {
       data->drawTheCorrectCardOnScreen = 61;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 12 && data->cards[data->roundIndex].suit == 2)
   {
       data->drawTheCorrectCardOnScreen = 62;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 12 && data->cards[data->roundIndex].suit == 3)
   {
       data->drawTheCorrectCardOnScreen = 63;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 12 && data->cards[data->roundIndex].suit == 4)
   {
       data->drawTheCorrectCardOnScreen = 64;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }

   if (data->cards[data->roundIndex].rank == 13 && data->cards[data->roundIndex].suit == 1)
   {
       data->drawTheCorrectCardOnScreen = 65;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 13 && data->cards[data->roundIndex].suit == 2)
   {
       data->drawTheCorrectCardOnScreen = 66;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 13 && data->cards[data->roundIndex].suit == 3)
   {
       data->drawTheCorrectCardOnScreen = 67;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }
   if (data->cards[data->roundIndex].rank == 13 && data->cards[data->roundIndex].suit == 4)
   {
       data->drawTheCorrectCardOnScreen = 68;
        std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].rank;
       std::cout << "\n";
       std::cout << ">The cards ranks was"; std::cout << data->cards[data->roundIndex].suit;
       std::cout << "\n";
   }


   data->drawThePreviousCardOnScreen = data->drawTheCorrectCardOnScreen;



   
    SDL_RenderTexture(renderer, GetSprite((SPRITE_ID::layoutTest), data->spriteBuffer)->texture, NULL, &card_pos4);
    SDL_RenderTexture(renderer, GetSprite((SPRITE_ID)(data->drawTheCorrectCardOnScreen + 1), data->spriteBuffer)->texture, NULL, &card_pos);
   // if (data->roundIndex > 0)
   // {
   //    SDL_RenderTexture(renderer, GetSprite((SPRITE_ID)(data->drawTheCorrectCardOnScreen + 1), data->spriteBuffer)->texture, NULL, &card_pos3);
   
   //    // Jag måste kolla var någonstans den är i Arrayen
   // }
    SDL_RenderTexture(renderer, GetSprite((SPRITE_ID)(data->higherOrLower), data->spriteBuffer)->texture, NULL, &card_pos2);

    

     // SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::Ace_of_diamond, data->spriteBuffer)->texture, NULL, &card_pos); card_pos.x += card_pos.w;
     // SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::Ace_of_diamond, data->spriteBuffer)->texture, NULL, &card_pos); card_pos.x += card_pos.w;
     // SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::Ace_of_diamond, data->spriteBuffer)->texture, NULL, &card_pos); card_pos.x += card_pos.w;
     // SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::Ace_of_diamond, data->spriteBuffer)->texture, NULL, &card_pos); card_pos.x += card_pos.w;
     // SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::Ace_of_spade, data->spriteBuffer)->texture, NULL, &card_pos); card_pos.x += card_pos.w;

     //SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::Ace_of_heart, data->spriteBuffer)->texture, NULL, &card_pos); card_pos.x += card_pos.w;
     //SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::Ace_of_diamond, data->spriteBuffer)->texture, NULL, &card_pos); card_pos.x += card_pos.w;
     //SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::Ace_of_spade, data->spriteBuffer)->texture, NULL, &card_pos); card_pos.x += card_pos.w;
     //SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::Ace_of_club, data->spriteBuffer)->texture, NULL, &card_pos); card_pos.x += card_pos.w;
    // SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::Ace_of_diamond, data->spriteBuffer)->texture, NULL, &card_pos2);


    // // test draw higherButton
    // int higherButton_x = 400;
    // int higherButton_y = 500;
    // SDL_FRect higherButton_pos {400, 500, 400, 500};

    // SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::HigherButton, data->spriteBuffer)->texture, NULL, &higherButton_pos);
        
    // // test draw lowerButton
    // int lowerButton_x = 400;
    // int lowerButton_y = 300;
    // SDL_FRect lowerButton_pos {400, 300, 400, 300};

    // SDL_RenderTexture(renderer, GetSprite(SPRITE_ID::LowerButton, data->spriteBuffer)->texture, NULL, &lowerButton_pos);

    DEV::Draw(data, renderer);
    SDL_RenderPresent(renderer);
  }

  void OnQuit(SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
  }

}
