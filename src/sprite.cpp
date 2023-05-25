#include "sprite.h"
#include "raylib.h"
#include "raymath.h"

Sprite::Sprite(const Vector2 &position, const Texture2D &texture)
    : m_position(position), m_texture(texture) {
  m_frameRect =
      Rectangle{0.0, 0.0, (float)texture.width, (float)texture.height};
}

Sprite::Sprite(const Vector2 &position, const Texture2D &texture,
               const Vector2 &tileSize)
    : m_position(position), m_texture(texture), m_tileSize(tileSize) {
  m_frameRect = Rectangle{0.0, 0.0, tileSize.x, tileSize.y};
}

void Sprite::setPosition(const Vector2 &position) { m_position = position; };
Vector2 Sprite::getPosition() const { return m_position; };
void Sprite::setTexture(const Texture2D &texture) { m_texture = texture; };
Texture2D Sprite::getTexture() const { return m_texture; }
void Sprite::setFrameRect(const Rectangle &frameRect) {
  m_frameRect = frameRect;
}
Rectangle Sprite::getFrameRect() const { return m_frameRect; };
bool Sprite::isTiled() const { return m_tileSize.x > 0 && m_tileSize.y > 0; };

Vector2 Sprite::getOrigin() const {
  Vector2 size =
      isTiled() ? m_tileSize : Vector2{m_texture.width, m_texture.height};
  Vector2 start = {0.0, 0.0};
  Vector2 center = {size.x / 2, size.y / 2};
  Vector2 end = {size.x, size.y};
  if (originType == SpriteOrigin::TOP_LEFT) {
    return start;
  }
  if (originType == SpriteOrigin::TOP_CENTER) {
    return Vector2{center.x, start.y};
  }
  if (originType == SpriteOrigin::TOP_RIGHT) {
    return Vector2{end.x, start.y};
  }
  if (originType == SpriteOrigin::CENTER_LEFT) {
    return Vector2{start.x, center.y};
  }
  if (originType == SpriteOrigin::CENTER) {
    return center;
  }
  if (originType == SpriteOrigin::CENTER_RIGHT) {
    return Vector2{end.x, center.y};
  }
  if (originType == SpriteOrigin::BOTTOM_LEFT) {
    return Vector2{start.x, end.y};
  }
  if (originType == SpriteOrigin::BOTTOM_CENTER) {
    return Vector2{center.x, end.y};
  }
  if (originType == SpriteOrigin::BOTTOM_RIGHT) {
    return end;
  }
  return center;
}

void Sprite::draw() const {
  Vector2 size = isTiled() ? Vector2{m_tileSize.x, m_tileSize.y}
                           : Vector2{m_texture.width, m_texture.height};
  Rectangle destRec = {m_position.x + getOrigin().x,
                       m_position.y + getOrigin().y, size.x, size.y};
  Vector2 originDebug =
      Vector2Add(m_position, Vector2Add(getOrigin(), getOrigin()));
  DrawTexturePro(m_texture, m_frameRect, destRec, getOrigin(), 90, WHITE);
  DrawRectanglePro(Rectangle{m_position.x - 1, m_position.y - 1, 2, 2},
                   getOrigin(), DEG2RAD * 90, BLUE);

  DrawRectanglePro(Rectangle{originDebug.x - 1, originDebug.y - 1, 2, 2},
                   getOrigin(), 0, RED);
}
