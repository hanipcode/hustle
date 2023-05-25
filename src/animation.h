#ifndef HUSTLE_ANIMATION_H
#define HUSTLE_ANIMATION_H

#include "map"
#include "raylib.h"
#include "raymath.h"
#include "vector"

struct AnimationFrames {
  std::vector<Rectangle> frames;

  AnimationFrames(){};
  AnimationFrames(int numOfFrames, ...) {
    va_list args;
    int i = 0;
    va_start(args, numOfFrames);
    while (i < numOfFrames) {
      frames.push_back(va_arg(args, Rectangle));
      i += 1;
    }
  };
  AnimationFrames(const Vector2 &startOffset, int numOfFrames,
                  float textureWidth, float textureHeight) {
    int i = 0;
    while (i < numOfFrames) {
      Vector2 targetOffset =
          Vector2Add(startOffset, Vector2{textureWidth * i, 0});
      frames.push_back(Rectangle{targetOffset.x, targetOffset.y, textureWidth,
                                 textureHeight});
      i += 1;
    }
  };
};

template <typename T> class AnimationMap {

  typedef std::map<T, AnimationFrames> MapType;

public:
  AnimationMap(){};
  AnimationMap(MapType _map) : map(_map){};
  MapType map;
  void set(T key, const AnimationFrames &value) { map[key] = value; };
};

template <typename AnimKey> struct AnimationPlayData {
  bool active = false;
  AnimationFrames activeAnimationFrames;
  AnimationMap<AnimKey> animationMap;
  AnimKey playedAnimationKey;
  int currentFrameIndex = 0;
  int framesCounter = 0;
  int animationSpeed = 8;

  void reset() { currentFrameIndex = 0; };

  void nextFrame() {
    if (!active)
      return;
    if (currentFrameIndex + 1 > (int)activeAnimationFrames.frames.size() - 1) {
      currentFrameIndex = 0;
      return;
    }
    currentFrameIndex += 1;
  };

  Rectangle getCurrentFrameRect() {
    return activeAnimationFrames.frames.at(currentFrameIndex);
  };
  bool isHaveFrame() { return activeAnimationFrames.frames.size() > 0; };

  void update() {
    framesCounter += 1;
    if (!active)
      return;
    if (framesCounter >= 60 / animationSpeed) {
      framesCounter = 0;
      nextFrame();
    }
  };
  void setAnimationMap(const AnimationMap<AnimKey> &map) {
    animationMap = map;
  };
  void play(const AnimKey &animationKey) {
    framesCounter = 0;
    currentFrameIndex = 0;
    activeAnimationFrames = animationMap.map[animationKey];
    active = true;
    playedAnimationKey = animationKey;
  };
};

#endif