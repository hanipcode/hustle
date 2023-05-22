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

public:
  Level(std::string mapPath);
  Level(std::string mapPath, Vector2 playerPosition);
  Level(std::string mapPath, std::unique_ptr<Player> &player);
  std::unique_ptr<Player> player;
  std::unique_ptr<TileMap> tileMap;
  virtual void update();
  virtual void draw();
};

#endif