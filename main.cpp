

#include "player.h"
#include "raylib.h"

#include "box2d/box2d.h"
#include "constants.h"
#include "draw_physics.h"
#include "level.h"
#include "memory"
#include "raymath.h" // Required for: Vector2Clamp()
#include "tilemap.h"
#include "tileson.h"
using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

static void UpdateDrawFrame(RenderTexture2D *target,
                            TileMap &tileMap); // Update and draw one frame
//--------------------------------------------------------------------------------------
const int screenWidth = 1280;
const int screenHeight = 720;
const int gameScreenWidth = 320;
const int gameScreenHeight = 180;

Player player;
b2World world = b2World(b2Vec2(0.0f, 0.0f));
const float meterGameScreenWidth = pixelsToMeters(gameScreenWidth);
const float meterGameScreenHeight = pixelsToMeters(gameScreenHeight);
int main() {
  // Initialization
  InitWindow(screenWidth, screenHeight, "raylib");
  SetConfigFlags(FLAG_VSYNC_HINT);
  SetWindowMinSize(gameScreenWidth, gameScreenHeight);
  RenderTexture2D target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);
  player.initBody(&world);
  //--------------------------------------------------------------------------------------

  // Tilemap
  TileMap tileMap;
  tileMap.init("resources/room_tilemap.json");

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    world.Step(1.0f / 60.0f, 8, 3);
    UpdateDrawFrame(&target, tileMap);
  }
#endif

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  UnloadRenderTexture(target);
  //--------------------------------------------------------------------------------------

  return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(RenderTexture2D *target, TileMap &tileMap) {
  // // Input

  player.update();

  SetTextureFilter((*target).texture, TEXTURE_FILTER_POINT);

  BeginTextureMode(*target);
  ClearBackground(RAYWHITE);
  tileMap.draw();
  player.draw();

  EndTextureMode();

  BeginDrawing();
  ClearBackground(RAYWHITE);

  DrawTexturePro((*target).texture,
                 (Rectangle){0.0f, 0.0f, (float)(*target).texture.width,
                             (float)-(*target).texture.height},
                 (Rectangle){0.0f, 0.0f, GetScreenWidth(), GetScreenHeight()},
                 (Vector2){0, 0}, 0.0f, WHITE);
  DrawFPS(16, 16);

  EndDrawing();
}
