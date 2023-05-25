#include "constants.h"

float pixelsToMeters(float pixel) { return pixel / GameConstants::WORLD_SCALE; }

float metersToPixels(float meters) {
  return meters * GameConstants::WORLD_SCALE;
}

Vector2 pixelsToMeters(Vector2 vPixel) {
  return Vector2Multiply(vPixel, GameConstants::V2_WORLD_SCALE);
}

Vector2 metersToPixels(Vector2 vMeter) {
  return Vector2Multiply(vMeter, GameConstants::V2_WORLD_SCALE);
}