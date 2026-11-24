#pragma once
#include "SDL3/SDL_rect.h"
#include "button.h"
#include "rendering.h"
#include "valuebox.h"
#include "gameState.h"

struct GameData;
struct Sprite;
struct Button;

struct NormalizedRect{
	float x;
	float y;
	float width;
	float height;
};

struct PanelLayout{
	NormalizedRect bounds;
	float padding = 0.0f;
};

enum class PANEL_TYPE{
    NONE,
	MAIN_PANEL,
	GAME_PANEL,
	BET_PANEL,
    SIDE_PANEL,
};

struct Panel{	
    PANEL_TYPE type;
	//NormalizedRect layout;
	SDL_FRect rect;
    Sprite* sprite;
	bool is_active;
};


struct SidePanel : Panel {
	ValueBox quota_int_1;
	ValueBox quota_int_2;
	ValueBox quota_int_3;
	ValueBox quota_int_4;
	Button pay_off_1;
	Button pay_off_2;
	Button pay_off_3;
	Button pay_off_4;
	Button pay_off_5;
	Button coin_slot_button;
	ValueBox conversion_ratio;
	ValueBox token_convert;
	ValueBox scrip_convert;
	Button lucky_token_up;
	Button lucky_token_down;
	Button scrip_up;
	Button scrip_down;
	Button convert;
    PANEL_TYPE type = PANEL_TYPE::SIDE_PANEL;

};
	
struct GamePanel : Panel {
	Sprite* round_counter_texture;
	SDL_FRect round_counter_icon_rect;
	Sprite* covererd_card;
	SDL_FRect covererd_card_icon_rect;
	Sprite* open_card;
	SDL_FRect open_card_icon_rect;
	Button higher_button;
	Button lower_button;
    PANEL_TYPE type = PANEL_TYPE::GAME_PANEL;
    
};

struct BetPanel : Panel {
	Sprite* token_texture;
	SDL_FRect token_icon_rect;
	ValueBox token_value;
	Sprite* scrip_texture;
	SDL_FRect scrip_icon_rect;
	ValueBox scrip_value;
	Sprite* prompt_bet_texture;
	SDL_FRect prompt_bet_rect;
	Button value_1_button;
	Button value_2_button;
	Button value_3_button;
	Button value_4_button;
	Button bet_scrip_button;
	Button reset_bet_button;
	ValueBox bet_int_1;
	ValueBox bet_int_2;
	ValueBox bet_int_3;
	ValueBox bet_int_4;
    PANEL_TYPE type = PANEL_TYPE::BET_PANEL;

};

struct MainPanel : Panel {
    SidePanel sidePanel;
    GamePanel gamePanel;
    BetPanel betPanel;
    PANEL_TYPE type = PANEL_TYPE::MAIN_PANEL;

};

SDL_FRect ToScreenRect(NormalizedRect layout);
void RenderPanelMockup(MainPanel* main_panel, SDL_Renderer* renderer);
void RenderMainPanel(MainPanel* main_panel, SDL_Renderer* renderer, GameData* data, FontAtlas* font, Camera* camera);
void RenderSidePanel(SidePanel* side_panel, SDL_Renderer* renderer, GameData* data, FontAtlas* font, Camera* camera);
void RenderGamePanel(GamePanel* game_panel, SDL_Renderer* renderer, GameData* data, FontAtlas* font, Camera* camera);
void RenderBetPanel(BetPanel* bet_panel, SDL_Renderer* renderer, GameData* data, FontAtlas* font, Camera* camera);
void InitializeLayout (MainPanel* main_panel, GameData* data);