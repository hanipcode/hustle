#ifndef GAME_CONSTANTS
#define GAME_CONSTANTS

#include "raylib.h";
#include "raymath.h";

namespace GameConstants {
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 180;
const float WORLD_SCALE = 100.0f;
const Vector2 V2_WORLD_SCALE = {WORLD_SCALE, WORLD_SCALE};
} // namespace GameConstants

float pixelsToMeters(float pixel);
float metersToPixels(float meter);
Vector2 pixelsToMeters(Vector2 v);
Vector2 metersToPixels(Vector2 v);

#endif