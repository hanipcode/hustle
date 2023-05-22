#include "player.h"
#include "constants.h"
#include "memory"
#include "string"

template <typename T> AnimationMap<T>::AnimationMap(){};
template <typename T>
AnimationMap<T>::AnimationMap(MapType _map) : map{_map} {};
template <typename T> void AnimationMap<T>::set(T key, AnimationFrames value) {
  map[key] = value;
}
template <typename T> AnimationFrames AnimationMap<T>::get(T key) {
  return map[key];
}
AnimationFrames::AnimationFrames() {}
AnimationFrames::AnimationFrames(int numOfFrames, ...) {
  va_list args;
  int i = 0;
  va_start(args, numOfFrames);
  while (i < numOfFrames) {
    frames.push_back(va_arg(args, Rectangle));
    i += 1;
  }
}
AnimationFrames::AnimationFrames(Vector2 startOffset, int numOfFrames,
                                 float textureWidth, float textureHeight) {
  int i = 0;
  while (i < numOfFrames) {
    Vector2 targetOffset =
        Vector2Add(startOffset, Vector2{textureWidth * i, 0});
    frames.push_back(
        Rectangle{targetOffset.x, targetOffset.y, textureWidth, textureHeight});
    i += 1;
  }
}

template <typename T> void AnimationPlayData<T>::reset() {
  currentFrameIndex = 0;
}
template <typename T> void AnimationPlayData<T>::nextFrame() {
  if (!active)
    return;
  if (currentFrameIndex + 1 > (int)activeAnimationFrames.frames.size() - 1) {
    currentFrameIndex = 0;
    return;
  }
  currentFrameIndex += 1;
}

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

template <typename T> void AnimationPlayData<T>::play(T animationEnum) {
  activeAnimationFrames = animationMap.get(animationEnum);
  active = true;
}

template <typename T>
void AnimationPlayData<T>::setAnimationMap(AnimationMap<T> map) {
  animationMap = map;
}

Player::Player() {

  frameRec = {0.0f, 0.0f, textureWidth, textureHeight};
  AnimationFrames idleDownFrames =
      AnimationFrames(Vector2{288, 32}, 6, textureWidth, textureHeight);
  AnimationFrames idleLeftFrames =
      AnimationFrames(Vector2{192, 32}, 6, textureWidth, textureHeight);
  AnimationFrames idleUpFrames =
      AnimationFrames(Vector2{96, 32}, 6, textureWidth, textureHeight);
  AnimationFrames idleRightFrames =
      AnimationFrames(Vector2{0, 32}, 6, textureWidth, textureHeight);
  AnimationFrames walkDownFrames =
      AnimationFrames(Vector2{288, 64}, 6, textureWidth, textureHeight);
  AnimationFrames walkLeftFrames =
      AnimationFrames(Vector2{192, 64}, 6, textureWidth, textureHeight);
  AnimationFrames walkUpFrames =
      AnimationFrames(Vector2{96, 64}, 6, textureWidth, textureHeight);
  AnimationFrames walkRightFrames =
      AnimationFrames(Vector2{0, 64}, 6, textureWidth, textureHeight);
  AnimationMap<PlayerAnimation> playerAnimationMap;

  playerAnimationMap.set(ANIM_WALK_DOWN, walkDownFrames);
  playerAnimationMap.set(ANIM_WALK_UP, walkUpFrames);
  playerAnimationMap.set(ANIM_WALK_RIGHT, walkRightFrames);
  playerAnimationMap.set(ANIM_WALK_LEFT, walkLeftFrames);
  playerAnimationMap.set(ANIM_IDLE_DOWN, idleDownFrames);
  playerAnimationMap.set(ANIM_IDLE_UP, idleUpFrames);
  playerAnimationMap.set(ANIM_IDLE_RIGHT, idleRightFrames);
  playerAnimationMap.set(ANIM_IDLE_LEFT, idleLeftFrames);

  animation.setAnimationMap(playerAnimationMap);
  animation.play(ANIM_WALK_DOWN);

  frameRec = animation.getCurrentFrameRect();
}

Player::Player(Vector2 initialPos, b2World *world) {

  frameRec = {0.0f, 0.0f, textureWidth, textureHeight};
  AnimationFrames idleDownFrames =
      AnimationFrames(Vector2{288, 32}, 6, textureWidth, textureHeight);
  AnimationFrames idleLeftFrames =
      AnimationFrames(Vector2{192, 32}, 6, textureWidth, textureHeight);
  AnimationFrames idleUpFrames =
      AnimationFrames(Vector2{96, 32}, 6, textureWidth, textureHeight);
  AnimationFrames idleRightFrames =
      AnimationFrames(Vector2{0, 32}, 6, textureWidth, textureHeight);
  AnimationFrames walkDownFrames =
      AnimationFrames(Vector2{288, 64}, 6, textureWidth, textureHeight);
  AnimationFrames walkLeftFrames =
      AnimationFrames(Vector2{192, 64}, 6, textureWidth, textureHeight);
  AnimationFrames walkUpFrames =
      AnimationFrames(Vector2{96, 64}, 6, textureWidth, textureHeight);
  AnimationFrames walkRightFrames =
      AnimationFrames(Vector2{0, 64}, 6, textureWidth, textureHeight);
  AnimationMap<PlayerAnimation> playerAnimationMap;

  playerAnimationMap.set(ANIM_WALK_DOWN, walkDownFrames);
  playerAnimationMap.set(ANIM_WALK_UP, walkUpFrames);
  playerAnimationMap.set(ANIM_WALK_RIGHT, walkRightFrames);
  playerAnimationMap.set(ANIM_WALK_LEFT, walkLeftFrames);
  playerAnimationMap.set(ANIM_IDLE_DOWN, idleDownFrames);
  playerAnimationMap.set(ANIM_IDLE_UP, idleUpFrames);
  playerAnimationMap.set(ANIM_IDLE_RIGHT, idleRightFrames);
  playerAnimationMap.set(ANIM_IDLE_LEFT, idleLeftFrames);

  animation.setAnimationMap(playerAnimationMap);
  animation.play(ANIM_WALK_DOWN);

  frameRec = animation.getCurrentFrameRect();

  texture = LoadTexture("resources/character.png");
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(pixelsToMeters(initialPos.x),
                       pixelsToMeters(initialPos.y));
  body = world->CreateBody(&bodyDef);
  b2CircleShape shape;
  shape.m_radius = pixelsToMeters(textureWidth / 2);
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;
  fixture = body->CreateFixture(&fixtureDef);
}

void Player::initBody(b2World *world) {
  texture = LoadTexture("resources/character.png");
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(pixelsToMeters(textureWidth),
                       pixelsToMeters(textureHeight));
  body = world->CreateBody(&bodyDef);
  b2CircleShape shape;
  shape.m_radius = pixelsToMeters(textureWidth / 2);
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;
  fixture = body->CreateFixture(&fixtureDef);
}

void Player::update() {
  b2Vec2 v = body->GetLinearVelocity();

  if (IsKeyDown(KEY_W)) {
    body->SetLinearVelocity(b2Vec2{0.0f, -pixelsToMeters(moveSpeed)});
  }
  if (IsKeyDown(KEY_S)) {
    body->SetLinearVelocity(b2Vec2{0.0f, pixelsToMeters(moveSpeed)});
  }
  if (IsKeyDown(KEY_A)) {
    body->SetLinearVelocity(b2Vec2{pixelsToMeters(-moveSpeed), 0.0f});
  }
  if (IsKeyDown(KEY_D)) {
    body->SetLinearVelocity(b2Vec2{pixelsToMeters(moveSpeed), 0.0f});
  }
  if (IsKeyReleased(KEY_W) || IsKeyReleased(KEY_S)) {
    body->SetLinearVelocity(b2Vec2{v.x, 0.0f});
  }

  if (IsKeyReleased(KEY_A) || IsKeyReleased(KEY_D)) {
    body->SetLinearVelocity(b2Vec2{0.0f, v.y});
  }

  if (animation.isHaveFrame() && animation.active) {
    animation.update();
    frameRec = animation.getCurrentFrameRect();
  }
}

void Player::draw() {
  b2Vec2 bposition = body->GetPosition();
  DrawTexturePro(
      texture, frameRec,
      Rectangle{round(metersToPixels(bposition.x)) - textureWidth / 2,
                round(metersToPixels(bposition.y)) - textureWidth, textureWidth,
                textureHeight},
      Vector2{0, textureWidth / 2}, 0, WHITE);
}