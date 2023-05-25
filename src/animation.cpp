#include "animation.h"
#include "raymath.h"

template <typename T> Rectangle AnimationPlayData<T>::getCurrentFrameRect() {
  return activeAnimationFrames.frames.at(currentFrameIndex);
}

template <typename T> bool AnimationPlayData<T>::isHaveFrame() {
  return activeAnimationFrames.frames.size() > 0;
}

template <typename T> void AnimationPlayData<T>::update() {
  framesCounter += 1;
  if (!active)
    return;
  if (framesCounter >= 60 / animationSpeed) {
    framesCounter = 0;
    nextFrame();
  }
}

template <typename T> void AnimationPlayData<T>::play(T animationKey) {
  framesCounter = 0;
  currentFrameIndex = 0;
  activeAnimationFrames = animationMap.get(animationKey);
  active = true;
  playedAnimationKey = animationKey;
}

template <typename T>
void AnimationPlayData<T>::setAnimationMap(AnimationMap<T> map) {
  animationMap = map;
}