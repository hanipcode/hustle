#include "level.h"
#include "box2d/box2d.h"
#include "memory"
#include "string"
#include "tilemap.h"

void Level::initializeMap(std::string mapPath) {
  tileMap = std::make_unique<TileMap>();
  tileMap->init(mapPath);
}

Level::Level(std::string mapPath) : mapPath(mapPath), world(b2Vec2(0.0, 0.0)) {
  initializeMap(mapPath);
}

Level::Level(std::string mapPath, Player *player)
    : mapPath(mapPath), world(b2Vec2(0.0, 0.0)), player(player) {
  initializeMap(mapPath);
}

Level::Level(std::string mapPath, Player *player, Vector2 initialPosition)
    : mapPath(mapPath), world(b2Vec2(0.0, 0.0)), player(player) {
  initializeMap(mapPath);
}

void Level::update() {
  if (player == nullptr)
    return;
  player->update();
}
void Level::draw() {
  if (tileMap == nullptr)
    return;
  tileMap->draw();

  if (player == nullptr)
    return;
  player->draw();
}