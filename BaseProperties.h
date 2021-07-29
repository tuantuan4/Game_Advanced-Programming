#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

using namespace std;

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static Mix_Chunk* g_sound_exp;
static Mix_Chunk* g_sound;

//Screen
const int SCREEN_WIDTH = 480; //chieu rong man hinh
const int SCREEN_HEIGHT = 800; // chieu dai man hinh
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 255; // red
const int COLOR_KEY_G = 255; // green
const int COLOR_KEY_B = 255; // blue

const int RENDER_DRAW_COLOR = 0XFF; //255
// Road
const int ROAD_LANE_NUM = 4;
const int LANE_1 = 55;
const int LANE_2 = 160;
const int LANE_3 = 270;
const int LANE_4 = 375;

const int ROAD_LANE[ROAD_LANE_NUM] = { LANE_1, LANE_2, LANE_3, LANE_4 };

