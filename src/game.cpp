#include "game.h"
#include "SDL3/SDL_blendmode.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include "SDL3/SDL_video.h"
#include "audioSystem.h"
#include "button.h"
#include "dev_gui.h"
#include "fontLibrary.h"
#include "gameState.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
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
  


    // Initialize Buttons
    SetupButton(&data->buttons[0], ButtonType::HIGHER, data->spriteBuffer, SDL_FRect{300, 600, 150, 60}, Alignment::Centered, nullptr, "");
    SetupButton(&data->buttons[1], ButtonType::LOWER, data->spriteBuffer, SDL_FRect{500, 600, 150, 60}, Alignment::Centered, nullptr, "");
    data->buttonCount = 2;
    data->prevMouseDown = false;    //start value
    data->higherOrLower = 0;        //start value



  data->equalCardBonus = 1;
  data->luckyTokenAmount = 1;
  data->quotaOfTokensRequiredToWin = 200;
  data->scripAmount = 1000;  
  data->scripAmountBetted = 25;
  data->roundIndex = 0;
  data->levelIndex = 0;
  data->drawTheCorrectCardOnScreen = 0;
  data->drawThePreviousCardOnScreen = 0;
  data->threeCorrectGuessesInARow = 0;

  for (int i = 0; i < data->DECK_SIZE; ++i){
  // Card* card = &data->cards[i];

  data->cards[i].suit = i % 4 + 1;
  data->cards[i].rank = i % 13 + 1; 
  data->cards[i].has_been_played = false;
  data->cards[i].isAce = false;

  if (data->cards[i].rank == 1)
  {
      data->cards[i].isAce = true;
  }

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

void AddButton(GameData* data, ButtonType type, SDL_FRect rect){
    if(data->buttonCount >= GameData::MAX_BUTTONS) return;   // skydd mot att fylla arrayen
    SetupButton(&data->buttons[data->buttonCount], type, data->spriteBuffer, rect, Alignment::Centered, nullptr, "");
    data->buttonCount++;                                      // ökar automatiskt
}

  void ShuffleDeck(GameData* data){
    // To obtain a time-based seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();;

    int n = sizeof(data->cards) / sizeof(data->cards[0]);

    // Shuffling our array
    shuffle(data->cards, data->cards + n,
            default_random_engine(seed));
  }

  void Update(GameData* data, float dt){
    EditorData* editorData = &data->editor_data;

    



    if (data->roundIndex < 51 || data->luckyTokenAmount < data->quotaOfTokensRequiredToWin)
    {
        if (data->scripAmount > 0 || data->luckyTokenAmount < data->quotaOfTokensRequiredToWin)
        {
         int currentlyShownCardRank = data->cards[data->roundIndex].rank;
         int pickedCardRank = data->cards[data->roundIndex + 1].rank; // will crash if deck does not contain any cards!



         bool convertLuckyTokensToScrip = KeyPressed(&data->input, SDL_SCANCODE_S);

         if (convertLuckyTokensToScrip == true && data->luckyTokenAmount >= 1)
         {
             data->luckyTokenAmount -= 1;
             data->scripAmount += 25;
         }

         bool convertScripToLuckyTokens = KeyPressed(&data->input, SDL_SCANCODE_L);

         if (convertScripToLuckyTokens == true && data->scripAmount >= 25)
         {
             data->luckyTokenAmount += 1;
             data->scripAmount -= 25;
         }



         bool playerIncreasedBet = KeyPressed(&data->input, SDL_SCANCODE_RIGHT);
         bool playerDecreasedBet = KeyPressed(&data->input, SDL_SCANCODE_LEFT);

         if (playerIncreasedBet == true || playerDecreasedBet == true)
         {
            if (playerIncreasedBet == true && playerDecreasedBet == false)
            {
             data->scripAmountBetted += 25;
            }
            else if (playerIncreasedBet == false && playerDecreasedBet == true) 
            {
             data->scripAmountBetted -= 25;
            }
         }

         if (data->scripAmountBetted > 100)
         {
            data->scripAmountBetted = 100;
         }

         if (data->scripAmountBetted < 0)
         {
            data->scripAmountBetted = 0;
         }

       

        


         // mouse position
         float mx, my;
         SDL_MouseButtonFlags flags = SDL_GetMouseState(&mx, &my);

         bool mouseDown          = (flags & SDL_BUTTON_LMASK) !=0;
         bool mousePressedNow    = mouseDown && !data->prevMouseDown;
         bool mouseReleasedNow   = !mouseDown && data->prevMouseDown;
         data->prevMouseDown     = mouseDown;

        for(int i = 0; i<data->buttonCount; i++)
        {
            UpdateButton(&data->buttons[i], data, mx, my, mouseDown, mousePressedNow, mouseReleasedNow);
        }



        Button* b1 = &data->buttons[0];
        Button* b2 = &data->buttons[1];



        // bool playerPressedUp = data->buttons[0].is_active;
        // bool playerPressedDown = KeyPressed(&data->input, SDL_SCANCODE_DOWN);

        
    

        
         bool playerPressedUp = KeyPressed(&data->input, SDL_SCANCODE_UP);
         bool playerPressedDown = KeyPressed(&data->input, SDL_SCANCODE_DOWN);



         bool pickedCardRankIsHigher = pickedCardRank > currentlyShownCardRank;
         bool pickedCardRankIsLower = pickedCardRank < currentlyShownCardRank;

         if (playerPressedUp == true && playerPressedDown == true)
         {
             playerPressedUp = true;
             playerPressedDown = false;
         }

         if(playerPressedUp == true || playerPressedDown == true)
         {
            if (playerPressedUp == true && (pickedCardRankIsHigher == true || data->cards[data->roundIndex + 1].isAce == true) && pickedCardRank != currentlyShownCardRank)
            {
                // Player guessed right!

                data->luckyTokenAmount++;
                data->scripAmount += (data->scripAmountBetted * data->equalCardBonus);
                data->equalCardBonus = 1;
                data->threeCorrectGuessesInARow++;

                data->higherOrLower = 70;
            }
            if (playerPressedUp == true && (pickedCardRankIsHigher == false && data->cards[data->roundIndex + 1].isAce == false) && pickedCardRank != currentlyShownCardRank)
            {
                // Player guessed wrong!

                data->scripAmount -= (data->scripAmountBetted * data->equalCardBonus);
                data->equalCardBonus = 1;
                data->threeCorrectGuessesInARow = 0;

                data->higherOrLower = 72;
            }
            else if (playerPressedDown == true && (pickedCardRankIsLower == true || data->cards[data->roundIndex].isAce == true) && pickedCardRank != currentlyShownCardRank)
            {
                // Player guessed right!

                data->luckyTokenAmount++;
                data->scripAmount += (data->scripAmountBetted * data->equalCardBonus);
                data->equalCardBonus = 1;
                data->threeCorrectGuessesInARow++;

                data->higherOrLower = 71;
            }
            else if (playerPressedDown == true && (pickedCardRankIsLower == false && data->cards[data->roundIndex].isAce == false) && pickedCardRank != currentlyShownCardRank)
            {
                // Player guessed wrong!

                data->scripAmount -= (data->scripAmountBetted * data->equalCardBonus);
                data->equalCardBonus = 1;
                data->threeCorrectGuessesInARow = 0;

                data->higherOrLower = 72;
            }
            else if (pickedCardRank == currentlyShownCardRank)
            {
                    data->equalCardBonus = 2; // Player gets a bonus on their next guess if they get 2 cards of the same rank in a row.

                    data->higherOrLower = 73;
                }
                data->roundIndex++;
            }  
            if (data->threeCorrectGuessesInARow == 3)
            {
                data->scripAmount += 25;
                data->threeCorrectGuessesInARow = 0;
            }
        }
    }
    
    if (data->roundIndex > 51 || data->luckyTokenAmount < data->quotaOfTokensRequiredToWin)
    {
       data->levelIndex++;
       data->roundIndex = 0;
       data->quotaOfTokensRequiredToWin += 10;
       data->DECK_SIZE
      // data->levelDifficultyModifier += 10;
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
    SDL_FRect card_pos2 {600, 0, 500, 500};
    SDL_FRect card_pos4 {0, 0, 1920, 1080};
    SDL_FRect card_pos5 {0, 0, 1920, 1080};
    SDL_FRect card_pos6 {0, 0, 1920, 1080};
    

































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
    if (data->scripAmount <= 0 || data->roundIndex == 51)
    {
       SDL_RenderTexture(renderer, GetSprite((SPRITE_ID::GameOverScreen), data->spriteBuffer)->texture, NULL, &card_pos5); 
    }
    if (data->luckyTokenAmount >= data->quotaOfTokensRequiredToWin)
    {
       SDL_RenderTexture(renderer, GetSprite((SPRITE_ID::VictoryScreen), data->spriteBuffer)->texture, NULL, &card_pos6); 
    }
    


    // Right Button pic at the right time
    for(int i = 0; i < data->buttonCount; i++){
        Button* b = &data->buttons[i];
        Sprite* s = b->sprite;

int cols = (s->sprite_count_x < 1) ? 1 : s->sprite_count_x; //I think this is for how many sprites

        float frameW = s->width / (float)cols;      //width of one column/button
        int frame = (cols > 1) ? (int)b->state : 0; //Wich "frame" are currently showing.

 SDL_FRect src { frameW * (int)b->state, 0, frameW, (float)s->height };
        SDL_RenderTexture(renderer, s->texture, &src, &b->rect);        //Where and how big button
    }


    

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
