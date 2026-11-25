#pragma once

enum class SCENE_TYPE{
    NONE, 
    INTRO,
    CREDITS,
    SCORE,
    NEW_SCORE,
    PAUSE,
    LOOSE,
    WIN,
    LEVEL,
    CUTSCENE,
    QUIT,
};


struct Scene {
    SCENE_TYPE type;
    Sprite* background;
    Button* button;
    // Text input here
};