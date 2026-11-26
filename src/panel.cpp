#include "panel.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "spriteLibrary.h"
#include "button.h"
#include "common.h"
#include "rendering.h"
#include "valuebox.h"
#include "gameState.h"

namespace PanelLayouts{
    constexpr NormalizedRect MAIN_PANEL = {0.0f, 0.0f, 1.0f, 1.0f};
    constexpr NormalizedRect SIDE_PANEL = {0.0000f, 0.0000f, 0.1836f, 1.000f};
    constexpr NormalizedRect GAME_PANEL = {0.1836f, 0.000f, 0.8164f, 0.6759f};
    constexpr NormalizedRect BET_PANEL = {0.1836f, 0.6759f, 0.8164f, 0.3241f};
}
namespace ElementLayout{
    //side panel
    constexpr NormalizedRect QUOTA_INT_1 = {0.1880f, 0.1390f, 0.1400f, 0.0867f};
    constexpr NormalizedRect QUOTA_INT_2 = {0.3480f, 0.1390f, 0.1400f, 0.0867f};
    constexpr NormalizedRect QUOTA_INT_3 = {0.5080f, 0.1390f, 0.1400f, 0.0867f};
    constexpr NormalizedRect QUOTA_INT_4 = {0.6680f, 0.1390f, 0.1400f, 0.0867f};
    constexpr NormalizedRect PAY_OFF_1 = {0.2620f, 0.3208f, 0.0863f, 0.0303f};
    constexpr NormalizedRect PAY_OFF_2 = {0.3035f, 0.2800f, 0.0958f, 0.0334f};
    constexpr NormalizedRect PAY_OFF_3= {0.4281f, 0.2602f, 0.0958f, 0.0334f};
    constexpr NormalizedRect PAY_OFF_4 = {0.5623f, 0.2685f, 0.0895f, 0.0334f};
    constexpr NormalizedRect PAY_OFF_5 = {0.6262f, 0.3145f, 0.1182f, 0.0334f};
    constexpr NormalizedRect COIN_SLOT = {0.4121f, 0.3103f, 0.1789f, 0.0606f};
    constexpr NormalizedRect CONVERSION_RATIO = {0.1981f, 0.6082f, 0.6070f, 0.0679f}; 
    constexpr NormalizedRect TOKEN_CONVERT = {0.2428f, 0.6928f, 0.0863f, 0.0251f}; 
    constexpr NormalizedRect SCRIP_CONVERT = {0.3546f, 0.7304f, 0.0927f, 0.0230f}; 
    constexpr NormalizedRect TOKEN_UP = {0.3450f, 0.8130f, 0.1182f, 0.0219f};
    constexpr NormalizedRect TOKEN_DOWN = {0.3482f, 0.8422f, 0.1118f, 0.0261f};
    constexpr NormalizedRect SCRIP_UP = {0.7284f, 0.8088f, 0.0990f, 0.0251f};
    constexpr NormalizedRect SCRIP_DOWN = {0.7252f, 0.8422f, 0.0990f, 0.0261f};
    constexpr NormalizedRect CONVERT = {0.1949f, 0.8913f, 0.6518f, 0.0867f};
    // game panel
    constexpr NormalizedRect ROUND_COUNTER = {0.3006f, 0.0415f, 0.2138f, 0.1046f};
    constexpr NormalizedRect COVERED_CARD = {0.1829f, 0.2431f, 0.1808f, 0.5600f};
    constexpr NormalizedRect OPEN_CARD = {0.4326f, 0.2415f, 0.1822f, 0.5662f};
    constexpr NormalizedRect HIGHER = {0.7956f, 0.6462f, 0.1801f, 0.1662f};
    constexpr NormalizedRect LOWER = {0.7956f, 0.8308f, 0.1801f, 0.1646f};
    // bet panel
    constexpr NormalizedRect TOKEN_VALUE = {0.016f, 0.082f, 0.055f, 0.145f};
    constexpr NormalizedRect SCRIP_VALUE = {0.081f, 0.082f, 0.055f, 0.145f};
    constexpr NormalizedRect TOKEN = {0.016f, 0.245f, 0.055f, 0.735f};
    constexpr NormalizedRect SCRIP = {0.081f, 0.245f, 0.055f, 0.735f};
    constexpr NormalizedRect MAKE_BET_PROMPT = {0.345f, 0.238f, 0.261f, 0.218f};
    constexpr NormalizedRect VALUE_1 = {0.267f, 0.524f, 0.071f, 0.276f};
    constexpr NormalizedRect VALUE_2 = {0.344f, 0.524f, 0.071f, 0.276f};
    constexpr NormalizedRect VALUE_3 = {0.421f, 0.524f, 0.071f, 0.276f};
    constexpr NormalizedRect VALUE_4 = {0.498f, 0.524f, 0.071f, 0.276f};
    constexpr NormalizedRect BET_BUTTON = {0.575f, 0.524f, 0.110f, 0.130f};
    constexpr NormalizedRect RESET_BUTTON = {0.575f, 0.670f, 0.110f, 0.130f};
    constexpr NormalizedRect BET_INT_1 = {0.820f, 0.432f, 0.032f, 0.252f};
    constexpr NormalizedRect BET_INT_2 = {0.858f, 0.432f, 0.032f, 0.252f};
    constexpr NormalizedRect BET_INT_3 = {0.896f, 0.432f, 0.032f, 0.252f};
    constexpr NormalizedRect BET_INT_4 = {0.934f, 0.432f, 0.032f, 0.252f};
    
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


SDL_FRect ToScreenRect(NormalizedRect layout){
    return {layout.x * SCREEN_WIDTH, layout.y * SCREEN_HEIGHT, layout.width * SCREEN_WIDTH, layout.height * SCREEN_HEIGHT};
}

//void RenderPanel(Panel* panel, SDL_Renderer* renderer, Camera* camera){
//    if(!panel->is_active || panel->sprite == nullptr) return;
//    RenderSprite_World(SpriteRenderInfo(panel->sprite), renderer, camera, panel->rect.x, panel->rect.y, 1.0f, 1.0f, false);
//}

void RenderPanel(Panel* panel, SDL_Renderer* renderer){
    if(!panel->is_active || panel->sprite == nullptr) return;
    SDL_FRect rect = panel->rect;
    SDL_SetRenderDrawColor(renderer, 190,190,190,255);
    SDL_RenderFillRect(renderer, &rect);
}

void InitializeSidePanel(SidePanel* side_panel, GameData* data, FontAtlas* font){
    SDL_FRect parent = side_panel->rect;
	side_panel-> quota_int_1.box = GetElementRect(parent, ElementLayout::QUOTA_INT_1);
    side_panel-> quota_int_2.box = GetElementRect(parent, ElementLayout::QUOTA_INT_2);
    side_panel-> quota_int_3.box = GetElementRect(parent, ElementLayout::QUOTA_INT_3);
    side_panel-> quota_int_4.box = GetElementRect(parent, ElementLayout::QUOTA_INT_4);
    ValueBox_INIT(&side_panel->quota_int_1);
    ValueBox_INIT(&side_panel->quota_int_2);
    ValueBox_INIT(&side_panel->quota_int_3);
    ValueBox_INIT(&side_panel->quota_int_4);

	SetupButton (&side_panel-> pay_off_1, ButtonType::VALUE_BUTTON, data->spriteBuffer, GetElementRect(parent, ElementLayout::PAY_OFF_1), Alignment::Left, font, "10");
    SetupButton (&side_panel-> pay_off_2, ButtonType::VALUE_BUTTON, data->spriteBuffer, GetElementRect(parent, ElementLayout::PAY_OFF_2), Alignment::Left, font, "20");
    SetupButton (&side_panel-> pay_off_3, ButtonType::VALUE_BUTTON, data->spriteBuffer, GetElementRect(parent, ElementLayout::PAY_OFF_3), Alignment::Left, font, "30");
    SetupButton (&side_panel-> pay_off_4, ButtonType::VALUE_BUTTON, data->spriteBuffer, GetElementRect(parent, ElementLayout::PAY_OFF_4), Alignment::Left, font, "40");
    SetupButton (&side_panel-> pay_off_5, ButtonType::VALUE_BUTTON, data->spriteBuffer, GetElementRect(parent, ElementLayout::PAY_OFF_5), Alignment::Left, font, "50");
    SetupButton (&side_panel-> coin_slot_button, ButtonType::CONFIRM, data->spriteBuffer, GetElementRect(parent, ElementLayout::COIN_SLOT), Alignment::Left, font, "coin slot");

    side_panel-> conversion_ratio.box = GetElementRect(parent, ElementLayout::CONVERSION_RATIO);
    side_panel-> token_convert.box = GetElementRect(parent, ElementLayout::TOKEN_CONVERT);
    side_panel-> scrip_convert.box = GetElementRect(parent, ElementLayout::SCRIP_CONVERT);

	SetupButton (&side_panel-> lucky_token_up, ButtonType::VALUE_UP, data->spriteBuffer, GetElementRect(parent, ElementLayout::TOKEN_UP), Alignment::Left, font, "LT up");
	SetupButton (&side_panel-> lucky_token_down, ButtonType::VALUE_DOWN, data->spriteBuffer, GetElementRect(parent, ElementLayout::TOKEN_DOWN), Alignment::Left, font, "LT down");
	SetupButton (&side_panel-> scrip_up, ButtonType::VALUE_UP, data->spriteBuffer, GetElementRect(parent, ElementLayout::SCRIP_UP), Alignment::Left, font, "scrip up");
	SetupButton (&side_panel-> scrip_down, ButtonType::VALUE_DOWN, data->spriteBuffer, GetElementRect(parent, ElementLayout::SCRIP_DOWN), Alignment::Left, font, "scrip down");
	SetupButton (&side_panel-> convert, ButtonType::CONFIRM, data->spriteBuffer, GetElementRect(parent, ElementLayout::CONVERT), Alignment::Left, font, "convert");
}

void RenderSidePanel(SidePanel* side_panel, SDL_Renderer* renderer, FontAtlas* font, Camera* camera){
    if (!side_panel->is_active)return;

    ValueBox_Display(&side_panel->quota_int_1, renderer, font, camera);
    ValueBox_Display(&side_panel->quota_int_2, renderer, font, camera);
    ValueBox_Display(&side_panel->quota_int_3, renderer, font, camera);
    ValueBox_Display(&side_panel->quota_int_4, renderer, font, camera);

	RenderButton (&side_panel-> pay_off_1, false, renderer);
    RenderButton (&side_panel-> pay_off_2, false, renderer);
    RenderButton (&side_panel-> pay_off_3, false, renderer);
    RenderButton (&side_panel-> pay_off_4, false, renderer);
    RenderButton (&side_panel-> pay_off_5, false, renderer);
    RenderButton (&side_panel-> coin_slot_button, false, renderer);

    ValueBox_Display(&side_panel->conversion_ratio, renderer, font, camera);
    ValueBox_Display(&side_panel->token_convert, renderer, font, camera);
    ValueBox_Display(&side_panel->scrip_convert, renderer, font, camera);

	RenderButton (&side_panel-> lucky_token_up, false, renderer);
	RenderButton (&side_panel-> lucky_token_down, false, renderer);
	RenderButton (&side_panel-> scrip_up, false, renderer);
	RenderButton (&side_panel-> scrip_down, false, renderer);
	RenderButton (&side_panel-> convert,false, renderer);

}

void InitializeGamePanel(GamePanel* game_panel, GameData* data, FontAtlas* font){

	game_panel-> round_counter_texture = GetSprite(SPRITE_ID::Fallback, data->spriteBuffer);
    game_panel-> covererd_card = GetSprite(SPRITE_ID::Snake, data->spriteBuffer);
    game_panel-> open_card = GetSprite(SPRITE_ID::Card, data->spriteBuffer);

    SDL_FRect parent = game_panel->rect;

    game_panel->round_counter_icon_rect = GetElementRect(parent, ElementLayout::ROUND_COUNTER);
    game_panel->covererd_card_icon_rect = GetElementRect(parent, ElementLayout::COVERED_CARD);
    game_panel->open_card_icon_rect = GetElementRect(parent, ElementLayout::OPEN_CARD);

	SetupButton (&game_panel-> higher_button, ButtonType::VALUE_UP, data->spriteBuffer, GetElementRect(parent, ElementLayout::HIGHER), Alignment::Left, font, "higher");
	SetupButton (&game_panel-> lower_button, ButtonType::VALUE_DOWN, data->spriteBuffer, GetElementRect(parent, ElementLayout::LOWER), Alignment::Left, font, "lower");
}

void RenderGamePanel(GamePanel* game_panel, SDL_Renderer* renderer, FontAtlas* font, Camera* camera){
    if (!game_panel->is_active)return;

    SDL_RenderTexture(renderer, game_panel->round_counter_texture->texture, nullptr, &game_panel->round_counter_icon_rect);
	SDL_RenderTexture(renderer, game_panel->covererd_card->texture, nullptr, &game_panel->covererd_card_icon_rect);
	SDL_RenderTexture(renderer, game_panel->open_card->texture, nullptr, &game_panel->open_card_icon_rect);
	RenderButton (&game_panel-> higher_button, false, renderer);
	RenderButton (&game_panel-> lower_button, false, renderer);
}

void InitializeBetPanel(BetPanel* bet_panel, GameData* data, FontAtlas* font){
    bet_panel->token_texture = GetSprite(SPRITE_ID::Apple, data->spriteBuffer);
    bet_panel->scrip_texture = GetSprite(SPRITE_ID::Apple, data->spriteBuffer);
    bet_panel->prompt_bet_texture = GetSprite(SPRITE_ID::Fallback, data->spriteBuffer);

    SDL_FRect parent = bet_panel->rect;

    bet_panel-> token_icon_rect = GetElementRect(parent, ElementLayout::TOKEN);
    bet_panel-> scrip_icon_rect = GetElementRect(parent, ElementLayout::SCRIP);
    bet_panel-> prompt_bet_rect = GetElementRect(parent, ElementLayout::MAKE_BET_PROMPT);

	bet_panel-> token_value.box = GetElementRect(parent, ElementLayout::TOKEN_VALUE);
    bet_panel-> scrip_value.box = GetElementRect(parent, ElementLayout::SCRIP_VALUE);
    ValueBox_INIT(&bet_panel->token_value);
    ValueBox_INIT(&bet_panel->scrip_value);

    SetupButton (&bet_panel-> bet_scrip_button, ButtonType::CONFIRM, data->spriteBuffer, GetElementRect(parent, ElementLayout::BET_BUTTON), Alignment::Left, font, "bet");
	SetupButton (&bet_panel-> reset_bet_button, ButtonType::RESET, data->spriteBuffer, GetElementRect(parent, ElementLayout::RESET_BUTTON),  Alignment::Left, font, "reset");
	SetupButton (&bet_panel-> value_1_button, ButtonType::VALUE_BUTTON, data->spriteBuffer, GetElementRect(parent, ElementLayout::VALUE_1), Alignment::Left, font, "Value 1");
	SetupButton (&bet_panel-> value_2_button, ButtonType::VALUE_BUTTON, data->spriteBuffer, GetElementRect(parent, ElementLayout::VALUE_2), Alignment::Left, font, "value 2");
	SetupButton (&bet_panel-> value_3_button, ButtonType::VALUE_BUTTON, data->spriteBuffer, GetElementRect(parent, ElementLayout::VALUE_3), Alignment::Left, font, "value 3");
	SetupButton (&bet_panel-> value_4_button, ButtonType::VALUE_BUTTON, data->spriteBuffer, GetElementRect(parent, ElementLayout::VALUE_4), Alignment::Left, font, "value 3");

    bet_panel-> bet_int_1.box = GetElementRect(parent, ElementLayout::BET_INT_1);
    bet_panel-> bet_int_2.box = GetElementRect(parent, ElementLayout::BET_INT_2);
    bet_panel-> bet_int_3.box = GetElementRect(parent, ElementLayout::BET_INT_3);
    bet_panel-> bet_int_4.box = GetElementRect(parent, ElementLayout::BET_INT_4);
    ValueBox_INIT(&bet_panel->bet_int_1);
    ValueBox_INIT(&bet_panel->bet_int_2);
    ValueBox_INIT(&bet_panel->bet_int_3);
    ValueBox_INIT(&bet_panel->bet_int_4);
}

void RenderBetPanel(BetPanel* bet_panel, SDL_Renderer* renderer, FontAtlas* font, Camera* camera){

    if (!bet_panel->is_active)return;
    
    SDL_RenderTexture(renderer, bet_panel->token_texture->texture, nullptr, &bet_panel->token_icon_rect);
    SDL_RenderTexture(renderer, bet_panel->scrip_texture->texture, nullptr, &bet_panel->scrip_icon_rect);
    SDL_RenderTexture(renderer, bet_panel->prompt_bet_texture->texture, nullptr, &bet_panel->prompt_bet_rect);

    ValueBox_Display(&bet_panel->token_value, renderer, font, camera);
    ValueBox_Display(&bet_panel->scrip_value, renderer, font, camera);

    RenderButton (&bet_panel-> bet_scrip_button, false, renderer);
	RenderButton (&bet_panel-> reset_bet_button, false, renderer);
	RenderButton (&bet_panel-> value_1_button, false, renderer);
	RenderButton (&bet_panel-> value_2_button, false, renderer);
	RenderButton (&bet_panel-> value_3_button, false, renderer);
	RenderButton (&bet_panel-> value_4_button, false, renderer);

	ValueBox_Display(&bet_panel->bet_int_1, renderer, font, camera);
    ValueBox_Display(&bet_panel->bet_int_2, renderer, font, camera);
    ValueBox_Display(&bet_panel->bet_int_3, renderer, font, camera);
    ValueBox_Display(&bet_panel->bet_int_4, renderer, font, camera);
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

    InitializeSidePanel(&main_panel->sidePanel, data, &data->font);
    InitializeGamePanel(&main_panel->gamePanel, data, &data->font);
    InitializeBetPanel(&main_panel->betPanel, data, &data->font);
};

void RenderMainPanel(MainPanel* main_panel, SDL_Renderer* renderer, GameData* data, FontAtlas* font, Camera* camera){
    if (!main_panel->is_active) return;
    RenderPanel(&main_panel->sidePanel, renderer);
    RenderPanel(&main_panel->gamePanel, renderer);
    RenderPanel(&main_panel->betPanel, renderer);
    RenderSidePanel(&main_panel->sidePanel, renderer, font, camera);
    RenderGamePanel(&main_panel->gamePanel, renderer, font, camera);
    RenderBetPanel(&main_panel->betPanel, renderer, font, camera);
    
}