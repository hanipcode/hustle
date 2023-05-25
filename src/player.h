
#include "animation.h"
#include "box2d/box2d.h"
#include "memory"
#include "raylib.h"
#include "sprite.h"
#include "vector"
#include <map>

#ifndef PLAYER_H
#define PLAYER_H

enum class PlayerAnimation {
  IDLE_LEFT,
  IDLE_UP,
  IDLE_RIGHT,
  IDLE_DOWN,
  WALK_LEFT,
  WALK_UP,
  WALK_RIGHT,
  WALK_DOWN,
};

enum class PlayerDirection {
  UP,
  LEFT,
  RIGHT,
  DOWN,
};

template class AnimationMap<PlayerAnimation>;

class Player {
  b2Fixture *fixture = nullptr;
  b2Body *body = nullptr;

  PlayerAnimation getAnimation();

public:
  Sprite *sprite;
  float textureWidth = 16;
  float textureHeight = 32;
  float moveSpeed = 30;
  PlayerDirection direction = PlayerDirection::DOWN;
  AnimationPlayData<PlayerAnimation> animation;

  Player();
  Player(const Vector2 &initialPos, b2World *world);

  void update();
  void draw();
  void initBody(b2World *world);
  void resetPosition(const Vector2 &position);

  ~Player() {
    if (sprite != nullptr) {
      delete sprite;
      sprite = nullptr;
    }
  }
};

#endif