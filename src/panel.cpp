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

namespace PanelLayouts{
    constexpr NormalizedRect MAIN_PANEL = {0.0f, 0.0f, 1.0f, 1.0f};
    constexpr NormalizedRect SIDE_PANEL = {0.03f, 0.03f, 0.21f, 0.94f};
    constexpr NormalizedRect GAME_PANEL = {0.27f, 0.03f, 0.70f, 0.62f};
    constexpr NormalizedRect BET_PANEL = {0.27f, 0.70f, 0.70f, 0.27f};
}
//mockup elements on panels
namespace ElementLayout{
    //side panel
    constexpr NormalizedRect QUOTA_DISPLAY = {0.10f, 0.05f, 0.80f, 0.12f};
    constexpr NormalizedRect COIN_SLOT = {0.10f, 0.22f, 0.80f, 0.10f};
    constexpr NormalizedRect TOKEN_UP = {0.10f, 0.38f, 0.35f, 0.10f};
    constexpr NormalizedRect TOKEN_DOWN = {0.55f, 0.38f, 0.35f, 0.10f};
    constexpr NormalizedRect SCRIP_UP = {0.10f, 0.54f, 0.35f, 0.10f};
    constexpr NormalizedRect SCRIP_DOWN = {0.55f, 0.54f, 0.35f, 0.10f};
    constexpr NormalizedRect CONVERT = {0.10f, 0.75f, 0.80f, 0.12f};
    // game panel
    constexpr NormalizedRect ROUND_COUNTER = {0.05f, 0.05f, 0.20f, 0.15f};
    constexpr NormalizedRect TOKEN = {0.05f, 0.30f, 0.15f, 0.20f};
    constexpr NormalizedRect SCRIP = {0.05f, 0.60f, 0.15f, 0.20f};
    constexpr NormalizedRect COVERED_CARD = {0.40f, 0.20f, 0.20f, 0.45f};
    constexpr NormalizedRect OPEN_CARD = {0.70f, 0.20f, 0.20f, 0.45f};
    constexpr NormalizedRect HIGHER = {0.40f, 0.75f, 0.20f, 0.12f};
    constexpr NormalizedRect LOWER = {0.70f, 0.75f, 0.20f, 0.12f};
    // bet panel
    constexpr NormalizedRect BET_BUTTON = {0.03f, 0.15f, 0.15f, 0.65f};
    constexpr NormalizedRect RESET_BUTTON = {0.20f, 0.15, 0.15f, 0.65f};
    constexpr NormalizedRect VALUE_1 = {0.40f, 0.15f, 0.12f, 0.65f};
    constexpr NormalizedRect VALUE_2 = {0.53f, 0.15f, 0.12f ,0.65f};
    constexpr NormalizedRect VALUE_3 = {0.66f, 0.15f, 0.12f, 0.65f};
    constexpr NormalizedRect VALUE_4 = {0.79f, 0.15f, 0.12f, 0.65f};
    constexpr NormalizedRect TOTAL_BET = {0.92f, 0.15f, 0.06f, 0.65f};
}

SDL_FRect GetElementRect(SDL_FRect parent, NormalizedRect element){
    return {
        parent.x + element.x * parent.w,
        parent.y + element.y * parent.h,
        element.width * parent.w,
        element.height * parent.h
    };
}

void DrawMockupElement(SDL_Renderer* renderer, SDL_FRect parent, NormalizedRect layout, Uint8 r, Uint8 g, Uint8 b){
    SDL_FRect rect = GetElementRect(parent, layout);
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void RenderPanelMockup(MainPanel* main_panel, SDL_Renderer* renderer){
    auto &side = main_panel->sidePanel.rect;
    auto &game = main_panel->gamePanel.rect;
    auto &bet = main_panel->betPanel.rect;

    //side panel
    DrawMockupElement(renderer, side, ElementLayout::QUOTA_DISPLAY, 255, 0, 0);
    DrawMockupElement(renderer, side, ElementLayout::COIN_SLOT, 255, 100, 0);
    DrawMockupElement(renderer, side, ElementLayout::TOKEN_UP, 255, 255, 0);
    DrawMockupElement(renderer, side, ElementLayout::TOKEN_DOWN, 150, 255, 0);
    DrawMockupElement(renderer, side, ElementLayout::SCRIP_UP, 0, 255, 0);
    DrawMockupElement(renderer, side, ElementLayout::SCRIP_DOWN, 0, 255, 150);
    DrawMockupElement(renderer, side, ElementLayout::CONVERT, 0, 200, 255);
    //game panel
    DrawMockupElement(renderer, game, ElementLayout::ROUND_COUNTER, 0, 100, 255);
    DrawMockupElement(renderer, game, ElementLayout::TOKEN, 0, 0, 255);
    DrawMockupElement(renderer, game, ElementLayout::SCRIP, 100, 0, 255);
    DrawMockupElement(renderer, game, ElementLayout::COVERED_CARD, 200, 0, 255);
    DrawMockupElement(renderer, game, ElementLayout::OPEN_CARD, 255, 0, 200);
    DrawMockupElement(renderer, game, ElementLayout::HIGHER, 255, 100, 200);
    DrawMockupElement(renderer, game, ElementLayout::LOWER, 200, 100, 100);
    //bet panel
    DrawMockupElement(renderer, bet, ElementLayout::BET_BUTTON, 255, 0, 0);
    DrawMockupElement(renderer, bet, ElementLayout::RESET_BUTTON, 255, 120, 0);
    DrawMockupElement(renderer, bet, ElementLayout::VALUE_1, 255, 255, 0);
    DrawMockupElement(renderer, bet, ElementLayout::VALUE_2, 0, 255, 0);
    DrawMockupElement(renderer, bet, ElementLayout::VALUE_3, 0, 255, 255);
    DrawMockupElement(renderer, bet, ElementLayout::VALUE_4, 0, 0, 255);
    DrawMockupElement(renderer, bet, ElementLayout::TOTAL_BET, 200, 0, 255);
}





SDL_FRect ToScreenRect(NormalizedRect layout){
    return {layout.x * SCREEN_WIDTH, layout.y * SCREEN_HEIGHT, layout.width * SCREEN_WIDTH, layout.height * SCREEN_HEIGHT};
}

//void RenderPanel(Panel* panel, SDL_Renderer* renderer, Camera* camera){
//    if(!panel->is_active || panel->sprite == nullptr) return;
//    RenderSprite_World(SpriteRenderInfo(panel->sprite), renderer, camera, panel->rect.x, panel->rect.y, 1.0f, 1.0f, false);
//}

void RenderPanel(Panel* panel, SDL_Renderer* renderer){
    if(!panel->is_active) return;
    SDL_FRect rect = panel->rect;
    SDL_SetRenderDrawColor(renderer, 190,190,190,255);
    SDL_RenderFillRect(renderer, &rect);
}

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




void InitializeLayout (MainPanel* main_panel, GameData* data){

    main_panel->type = PANEL_TYPE::MAIN_PANEL;
    main_panel->is_active = true;
    main_panel->sprite = GetSprite(SPRITE_ID::Fallback, data->spriteBuffer);
    main_panel->rect = ToScreenRect(PanelLayouts::MAIN_PANEL);
    // SIDE PANEL BASE
    main_panel->sidePanel.type = PANEL_TYPE::SIDE_PANEL;
    main_panel->sidePanel.is_active = true;
    main_panel->sidePanel.sprite = GetSprite(SPRITE_ID::Ground, data->spriteBuffer);
    main_panel->sidePanel.rect = ToScreenRect(PanelLayouts::SIDE_PANEL);
    //
    // GAME PANEL BASE
    main_panel->gamePanel.type = PANEL_TYPE::GAME_PANEL;
    main_panel->gamePanel.is_active = true;
    main_panel->gamePanel.sprite = GetSprite(SPRITE_ID::Ground, data->spriteBuffer);
    main_panel->gamePanel.rect = ToScreenRect(PanelLayouts::GAME_PANEL);
    //
    // BET PANEL BASE
    main_panel->betPanel.type = PANEL_TYPE::BET_PANEL;
    main_panel->betPanel.is_active = true;
    main_panel->betPanel.sprite = GetSprite(SPRITE_ID::Ground, data->spriteBuffer);
    main_panel->betPanel.rect = ToScreenRect(PanelLayouts::BET_PANEL);
    //
};

void RenderMainPanel(MainPanel* main_panel, SDL_Renderer* renderer, GameData* data, FontAtlas* font, Camera* camera){
    if (!main_panel->is_active) return;
    RenderPanel(&main_panel->sidePanel, renderer);
    RenderPanel(&main_panel->gamePanel, renderer);
    RenderPanel(&main_panel->betPanel, renderer);

    //RenderSidePanel(&main_panel->sidePanel, renderer, data, font, camera);
    //RenderGamePanel(&main_panel->gamePanel, renderer, data, font, camera);
    //RenderBetPanel(&main_panel->betPanel, renderer, data, font, camera);
    
}