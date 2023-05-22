#include "box2d/box2d.h"
#include "memory"
#include "raylib.h"
#include "vector"
#include <map>

#ifndef PLAYER_H
#define PLAYER_H

struct AnimationFrames {
  std::vector<Rectangle> frames;

  AnimationFrames();
  AnimationFrames(int numOfFrames, ...);
  AnimationFrames(Vector2 startOffset, int numOfFrames, float textureWidth,
                  float textureHeight);
};

template <typename T> class AnimationMap {

  typedef std::map<T, AnimationFrames> MapType;
  MapType map;

public:
  AnimationMap();
  AnimationMap(MapType _map);
  void set(T key, AnimationFrames value);
  AnimationFrames get(T key);
};

template <typename AnimEnum> struct AnimationPlayData {
  bool active = false;
  AnimationFrames activeAnimationFrames;
  AnimationMap<AnimEnum> animationMap;
  int currentFrameIndex = 0;
  int framesCounter = 0;
  int animationSpeed = 8;

  void reset();

  void nextFrame();

  Rectangle getCurrentFrameRect();
  bool isHaveFrame();

  void update();
  void setAnimationMap(AnimationMap<AnimEnum> map);
  void play(AnimEnum animationEnum);
};

enum PlayerAnimation {
  ANIM_IDLE_LEFT,
  ANIM_IDLE_UP,
  ANIM_IDLE_RIGHT,
  ANIM_IDLE_DOWN,
  ANIM_WALK_LEFT,
  ANIM_WALK_UP,
  ANIM_WALK_RIGHT,
  ANIM_WALK_DOWN,
};

class Player {
  b2Body *body;
  b2Fixture *fixture;

public:
  Texture2D texture;
  Rectangle frameRec;
  float textureWidth = 16;
  float textureHeight = 32;
  float moveSpeed = 30;
  AnimationFrames idleFrames;
  AnimationPlayData<PlayerAnimation> animation;

  Player();
  Player(Vector2 initialPos, b2World *world);

  void update();
  void draw();
  void initBody(b2World *world);
};

#endif