#include "panel.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "spriteLibrary.h"
#include "button.h"
#include "common.h"
#include "rendering.h"
#include "valuebox.h"
#include "gameState.h"
//const int SCREEN_WIDTH;
//const int SCREEN_HEIGHT;

void RenderSidePanel(SidePanel* side_panel, SDL_Renderer* renderer, GameData* data, FontAtlas* font, Camera* camera){
    Sprite* button = GetSprite(SPRITE_ID::Button_Basic, data->spriteBuffer);

	side_panel-> quota_display = ValueBox({100, 100, 600, 200}, 11);
	SetupButton (&side_panel-> coin_slot_button, ButtonType::VALUE_UP, button, {100, 300, 600, 200}, Alignment::Left, font, "coin slot");
	SetupButton (&side_panel-> lucky_token_up, ButtonType::VALUE_UP, button, {100, 600, 600, 200}, Alignment::Left, font, "LT up");
	SetupButton (&side_panel-> lucky_token_down, ButtonType::VALUE_DOWN, button, {100, 900, 600, 200}, Alignment::Left, font, "LT down");
	SetupButton (&side_panel-> scrip_up, ButtonType::VALUE_UP, button, {100, 1200, 600, 200}, Alignment::Left, font, "scrip up");
	SetupButton (&side_panel-> scrip_down, ButtonType::VALUE_DOWN, button, {100, 1500, 600, 200}, Alignment::Left, font, "scrip down");
	SetupButton (&side_panel-> convert, ButtonType::CONFIRM, button, {100, 1800, 600, 200}, Alignment::Left, font, "convert");

}

void RenderGamePanel(GamePanel* game_panel, SDL_Renderer* renderer, GameData* data, FontAtlas* font, Camera* camera){
    Sprite* round_counter = GetSprite(SPRITE_ID::Snake, data->spriteBuffer);
    Sprite* token = GetSprite(SPRITE_ID::Apple, data->spriteBuffer);
    Sprite* scrip = GetSprite(SPRITE_ID::Apple, data->spriteBuffer);
    Sprite* covered_card_texture = GetSprite(SPRITE_ID::Card, data->spriteBuffer);
    Sprite* open_card_texture = GetSprite(SPRITE_ID::Card, data->spriteBuffer);
    Sprite* button = GetSprite(SPRITE_ID::Button_Basic, data->spriteBuffer);

	game_panel-> round_counter_texture = round_counter;
    game_panel-> token_texture = token;
    game_panel-> scrip_texture = scrip;
    game_panel-> covererd_card = covered_card_texture;
    game_panel-> open_card = open_card_texture;


    RenderSprite_World(SpriteRenderInfo(round_counter), renderer, &data->camera, 100, 300, 1.0f, 1.0f, false);
	RenderSprite_World(SpriteRenderInfo(token), renderer, camera, 100, 600, 1.0f, 1.0f, false);
	RenderSprite_World(SpriteRenderInfo(scrip), renderer, camera, 100, 900, 1.0f, 1.0f, false);
	game_panel-> token_text_box = ValueBox({100, 300, 600, 200},21);
	game_panel-> scrip_text_box = ValueBox({100, 600, 600, 200},22);
	RenderSprite_World(SpriteRenderInfo(covered_card_texture), renderer, &data->camera, 1000, 600, 1.0f, 1.0f, false);
	RenderSprite_World(SpriteRenderInfo(open_card_texture), renderer, &data->camera, 1000, 1000, 1.0f, 1.0f, false);
	SetupButton (&game_panel-> higher_button, ButtonType::VALUE_UP, button, {1000, 300, 600, 200}, Alignment::Left, font, "higher");
	SetupButton (&game_panel-> lower_button, ButtonType::VALUE_DOWN,button,  {1000, 600, 600, 200}, Alignment::Left, font, "lower");
}


void RenderBetPanel(BetPanel* bet_panel, SDL_Renderer* renderer, GameData* data, FontAtlas* font, Camera* camera){
    Sprite* button = GetSprite(SPRITE_ID::Button_Basic, data->spriteBuffer);
    Sprite* total_bet_texture = GetSprite(SPRITE_ID::black_1x1, data->spriteBuffer);

    bet_panel-> total_bet_texture = total_bet_texture;

    SetupButton (&bet_panel-> bet_scrip_button, ButtonType::CONFIRM, button, {50, 50, 300, 150}, Alignment::Left, font, "bet");
	SetupButton (&bet_panel-> reset_bet_button, ButtonType::RESET, button, {50, 250, 300, 150},  Alignment::Left, font, "reset");
	SetupButton (&bet_panel-> value_1_button, ButtonType::VALUE_BUTTON, button, {400, 50, 450, 350}, Alignment::Left, font, "Value 1");
	SetupButton (&bet_panel-> value_2_button, ButtonType::VALUE_BUTTON, button, {900, 50, 450, 350}, Alignment::Left, font, "value 2");
	SetupButton (&bet_panel-> value_3_button, ButtonType::VALUE_BUTTON, button, {1400, 50, 450, 350}, Alignment::Left, font, "value 3");
	SetupButton (&bet_panel-> value_4_button, ButtonType::VALUE_BUTTON, button, {1900, 50, 450, 350}, Alignment::Left, font, "value 3");
	RenderSprite_World(SpriteRenderInfo(total_bet_texture), renderer, &data->camera, 2400, 50, 1.0f, 1.0f, false);
	bet_panel-> total_bet_display = ValueBox({2400, 200, 350, 200},33);
}

void InitializeLayout (MainPanel* main_panel, SDL_Renderer* renderer, GameData* data, FontAtlas* font, Camera* camera){

    main_panel->type = PANEL_TYPE::MAIN_PANEL;
    main_panel->is_active = true;
    main_panel->sprite = GetSprite(SPRITE_ID::Fallback, data->spriteBuffer);
    main_panel->rect = {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT};
    // SIDE PANEL BASE
    main_panel->sidePanel.type = PANEL_TYPE::SIDE_PANEL;
    main_panel->sidePanel.is_active = true;
    main_panel->sidePanel.sprite = GetSprite(SPRITE_ID::Ground, data->spriteBuffer);
    main_panel->sidePanel.rect = { 0.0f, 0.0f, 1075.0f, 2160.0f};
    RenderSidePanel(&main_panel->sidePanel, renderer, data, font, camera);
    // GAME PANEL BASE
    main_panel->gamePanel.type = PANEL_TYPE::GAME_PANEL;
    main_panel->gamePanel.is_active = true;
    main_panel->gamePanel.sprite = GetSprite(SPRITE_ID::Ground, data->spriteBuffer);
    main_panel->gamePanel.rect = {1100.0f, 0.0f, 2700.0f, 1555.0f}; 
    RenderGamePanel(&main_panel->gamePanel, renderer, data, font, camera);
    // BET PANEL BASE
    main_panel->betPanel.type = PANEL_TYPE::BET_PANEL;
    main_panel->betPanel.is_active = true;
    main_panel->betPanel.sprite = GetSprite(SPRITE_ID::Ground, data->spriteBuffer);
    main_panel->betPanel.rect = {1250.0f, 1700.0f, 2800.0f, 430.0f};
    RenderBetPanel(&main_panel->betPanel, renderer, data, font, camera);


};