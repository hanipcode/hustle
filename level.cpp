#include "level.h"
#include "box2d/box2d.h"
#include "memory"
#include "string"
#include "tilemap.h"

void Level::initializeMap(std::string mapPath) {
  tileMap = std::unique_ptr<TileMap>();
  tileMap->init(mapPath);
}

Level::Level(std::string mapPath) : mapPath(mapPath), world(b2Vec2(0.0, 0.0)) {
  initializeMap(mapPath);
}

Level::Level(std::string mapPath, Vector2 playerPos)
    : mapPath(mapPath), world(b2Vec2(0.0, 0.0)) {
  initializeMap(mapPath);
  player = std::make_unique<Player>(playerPos, &world);
}

Level::Level(std::string mapPath, std::unique_ptr<Player> &player)
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