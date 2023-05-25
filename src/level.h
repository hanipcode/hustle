#ifndef LEVEL_H
#define LEVEL_H

#include "box2d/box2d.h"
#include "memory"
#include "player.h"
#include "string"
#include "tilemap.h"

class Level {
  b2World world;
  std::string mapPath;
  void initializeMap(std::string mapPath);
  Player *player = nullptr;
  std::unique_ptr<TileMap> tileMap;

public:
  Level(std::string mapPath);
  Level(std::string mapPath, Player *player);
  Level(std::string mapPath, Player *player, Vector2 initialPosition);
  virtual void update();
  virtual void draw();
};

#endif