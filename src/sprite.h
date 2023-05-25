#ifndef HUSTLE_SPRITE_H
#define HUSTLE_SPRITE_H
#include "raylib.h"

enum class SpriteOrigin {
  TOP_LEFT,
  TOP_CENTER,
  TOP_RIGHT,
  CENTER_LEFT,
  CENTER,
  CENTER_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_CENTER,
  BOTTOM_RIGHT,
};

class Sprite {
private:
  Vector2 m_position;
  Texture2D m_texture;
  Vector2 m_tileSize;
  Rectangle m_frameRect;

public:
  SpriteOrigin originType = SpriteOrigin::TOP_LEFT;

  Sprite(const Vector2 &position, const Texture2D &texture);
  Sprite(const Vector2 &position, const Texture2D &texture,
         const Vector2 &tileSize);
  Vector2 getOrigin() const;
  void draw() const;
  bool isTiled() const;
  void setPosition(const Vector2 &position);
  Vector2 getPosition() const;
  void setTexture(const Texture2D &texture);
  Texture2D getTexture() const;
  void setFrameRect(const Rectangle &frameRect);
  Rectangle getFrameRect() const;
};

#endif