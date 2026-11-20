#pragma once
#include "SDL3/SDL_rect.h"
#include "button.h"
#include "rendering.h"
#include "valuebox.h"
#include "gameState.h"

struct Sprite;
struct Button;

enum class PANEL_TYPE{
    NONE,
	MAIN_PANEL,
	GAME_PANEL,
	BET_PANEL,
    SIDE_PANEL,
};

struct Panel{	
    PANEL_TYPE type;
	SDL_FRect rect;
    Sprite* sprite;
	bool is_active;
};


struct SidePanel : Panel {
	ValueBox quota_display;
	Button coin_slot_button;
	Button lucky_token_up;
	Button lucky_token_down;
	Button scrip_up;
	Button scrip_down;
	Button convert;
    PANEL_TYPE type = PANEL_TYPE::SIDE_PANEL;

};
	
struct GamePanel : Panel {
	Sprite* round_counter_texture;
	Sprite* token_texture;
	Sprite* scrip_texture;
	ValueBox token_text_box;
	ValueBox scrip_text_box;
	Sprite* covererd_card;
	Sprite* open_card;
	Button higher_button;
	Button lower_button;
    PANEL_TYPE type = PANEL_TYPE::GAME_PANEL;
    
};

struct BetPanel : Panel {
	Button bet_scrip_button;
	Button reset_bet_button;
	Button value_1_button;
	Button value_2_button;
	Button value_3_button;
	Button value_4_button;
	Sprite* total_bet_texture;
	ValueBox total_bet_display;
    PANEL_TYPE type = PANEL_TYPE::BET_PANEL;

};

struct MainPanel : Panel {
    SidePanel sidePanel;
    GamePanel gamePanel;
    BetPanel betPanel;
    PANEL_TYPE type = PANEL_TYPE::MAIN_PANEL;

};

void RenderSidePanel(SidePanel* side_panel, SDL_Renderer* renderer, GameData* data, FontAtlas* font, Camera* camera);
void RenderGamePanel(GamePanel* game_panel, SDL_Renderer* renderer, GameData* data, FontAtlas* font, Camera* camera);
void RenderBetPanel(BetPanel* bet_panel, SDL_Renderer* renderer, GameData* data, FontAtlas* font, Camera* camera);
void InitializeLayout (MainPanel* main_panel, SDL_Renderer* renderer, GameData* data, FontAtlas* font, Camera* camera);