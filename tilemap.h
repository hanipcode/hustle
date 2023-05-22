#ifndef TILEMAP_H
#define TILEMAP_H

#include "memory"
#include "raylib.h"
#include "string"
#include "tileson.h"


typedef std::function<void(const std::tuple<int, int> &pos,
                           const tson::Tile *tile)>
    TileCallback;

class TileMap {
  std::unique_ptr<tson::Map> map;
  std::vector<Texture2D> tilesetTextures;

public:
  void init(std::string mapPath);
  void traverseTile(tson::LayerType layerType, TileCallback callback);
  void initCollision();
  void draw();
};

#endif