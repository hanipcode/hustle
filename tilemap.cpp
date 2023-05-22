#include "tilemap.h"
#include "raylib.h"
#include "tileson.h"

void TileMap::init(std::string mapPath) {
  tson::Tileson t;
  map = t.parse(fs::path(mapPath));
  for (const auto &tileset : map->getTilesets()) {
    std::string imagePath =
        "resources/" + tileset.getImagePath().generic_string();
    Texture2D texture = LoadTexture(imagePath.c_str());
    tilesetTextures.push_back(texture);
  }
};

void TileMap::traverseTile(tson::LayerType layerType, TileCallback callback) {
  for (const tson::Layer &layer : map->getLayers()) {
    if (layer.getType() == layerType) {
      for (const auto &[pos, tile] : layer.getTileData()) {
        callback(pos, tile);
      };
    };
  };
};

void TileMap::draw() {
  TileCallback handleDraw = [&](const std::tuple<int, int> &pos,
                                const tson::Tile *tile) {
    int tileId = tile->getId();

    if (tileId != 0) {
      // Determine the tileset index based on the tile ID
      int tilesetIndex = -1;
      for (int i = 0; i < map->getTilesets().size(); ++i) {
        if (tileId >= map->getTilesets()[i].getFirstgid()) {
          tilesetIndex = i;
          break;
        }
      }

      if (tilesetIndex != -1) {
        // Calculate the position of the tile
        int posX = std::get<0>(pos);
        int posY = std::get<1>(pos);
        int tileSize = map->getTilesets()[tilesetIndex].getTileSize().x;

        // Calculate the source rectangle within the tileset texture
        int tilesetId = tileId - map->getTilesets()[tilesetIndex].getFirstgid();
        int tilesetColumns = map->getTilesets()[tilesetIndex].getColumns();
        Rectangle sourceRect = {(tilesetId % tilesetColumns) * tileSize,
                                (tilesetId / tilesetColumns) * tileSize,
                                tileSize, tileSize};
        Vector2 destPos = {posX * tileSize, posY * tileSize};
        DrawTextureRec(tilesetTextures[tilesetIndex], sourceRect, destPos,
                       WHITE);
      }
    }
  };

  traverseTile(tson::LayerType::TileLayer, handleDraw);
}