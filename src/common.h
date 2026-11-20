#pragma once

#define KILOBYTES(n) ((size_t)n * 1024)
#define MEGABYTES(n) (KILOBYTES(n) * 1024)
#define GIGABYTES(n) (MEGABYTES(n) * 1024)

#define loop(i, e) for(int i = 0; i < e; i++)

constexpr size_t GAME_MEMORY_ALLOWANCE = MEGABYTES(14);
constexpr size_t AUDIO_MEMORY_ALLOWANCE = MEGABYTES(5);
constexpr int FPS = 240;
constexpr double FRAME_TIME_MS = 1000.0 / FPS;

const float UNDO_REPEAT_TIME = 0.15;
const int SCREEN_WIDTH = 3840;
const int SCREEN_HEIGHT = 2160;
const int UPSCALE_FACTOR = 8;
const int SPRITE_SIZE = 8;


inline void Convert1DTo2D(int flatIndex, int width, int* x, int* y){
    *x = flatIndex % width;
    *y = flatIndex / width;
}
inline void Convert1DTo2D(int flatIndex, int width, float* x, float* y){
    *x = (float)(flatIndex % width);
    *y = (float)(flatIndex / width);
}

static const char STOP_CHAR = '\0';
inline bool IsStringEmpty(const char* str){
    return str == nullptr || str[0] == STOP_CHAR;
}

