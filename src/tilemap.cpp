#include "tilemap.h"
#include "raylib.h"
#include "tileson.h"

void TileMap::init(const std::string &mapPath) {
  tson::Tileson t;
  map = t.parse(fs::path(mapPath));
  for (const auto &tileset : map->getTilesets()) {
    std::string imagePath =
        "resources/" + tileset.getImagePath().generic_string();
    Texture2D texture = LoadTexture(imagePath.c_str());
    tilesetTextures.push_back(texture);
  }
};

void TileMap::traverseTile(const tson::LayerType &layerType,
                           const TileCallback &callback) {
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
        tson::Tileset &tileset = map->getTilesets()[i];
        if (tileId >= tileset.getFirstgid() &&
            tileId < tileset.getFirstgid() + tileset.getTileCount()) {
          tilesetIndex = i;
          break;
        }
      }

      if (tilesetIndex != -1) {
        tson::Tileset &tileset = map->getTilesets()[tilesetIndex];
        // Calculate the position of the tile
        int posX = std::get<0>(pos);
        int posY = std::get<1>(pos);
        int tileSize = tileset.getTileSize().x;

        // Calculate the source rectangle within the tileset texture
        int tilesetId = tileId - tileset.getFirstgid();
        int tilesetColumns = tileset.getColumns();
        tson::Rect drawingRect = tile->getDrawingRect();
        Rectangle sourceRect = {drawingRect.x, drawingRect.y, drawingRect.width,
                                drawingRect.height};
        Vector2 destPos = {posX * tileSize, posY * tileSize};
        DrawTextureRec(tilesetTextures[tilesetIndex], sourceRect, destPos,
                       WHITE);
      }
    }
  };

  traverseTile(tson::LayerType::TileLayer, handleDraw);
}