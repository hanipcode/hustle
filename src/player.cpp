#include "player.h"
#include "animation.h"
#include "constants.h"
#include "memory"
#include "resource.h"
#include "sprite.h"
#include "string"

Player::Player() : animation() {
  Resource *res = Resource::getInstance();
  sprite = new Sprite(Vector2{0.0, 0.0},
                      LoadTexture(res->get(ResourceId::CHARACTER).c_str()),
                      Vector2{textureWidth, textureHeight});
  sprite->setFrameRect({0.0f, 0.0f, textureWidth, textureHeight});
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

  playerAnimationMap.set(PlayerAnimation::WALK_DOWN, walkDownFrames);
  playerAnimationMap.set(PlayerAnimation::WALK_UP, walkUpFrames);
  playerAnimationMap.set(PlayerAnimation::WALK_RIGHT, walkRightFrames);
  playerAnimationMap.set(PlayerAnimation::WALK_LEFT, walkLeftFrames);
  playerAnimationMap.set(PlayerAnimation::IDLE_DOWN, idleDownFrames);
  playerAnimationMap.set(PlayerAnimation::IDLE_UP, idleUpFrames);
  playerAnimationMap.set(PlayerAnimation::IDLE_RIGHT, idleRightFrames);
  playerAnimationMap.set(PlayerAnimation::IDLE_LEFT, idleLeftFrames);

  animation.setAnimationMap(playerAnimationMap);
  animation.play(PlayerAnimation::WALK_DOWN);

  sprite->setFrameRect(animation.getCurrentFrameRect());
}

Player::Player(const Vector2 &initialPos, b2World *world) {
  Resource *res = Resource::getInstance();
  sprite = new Sprite(Vector2{0.0, 0.0},
                      LoadTexture(res->get(ResourceId::CHARACTER).c_str()));
  sprite->setFrameRect({0.0f, 0.0f, textureWidth, textureHeight});
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

  playerAnimationMap.set(PlayerAnimation::WALK_DOWN, walkDownFrames);
  playerAnimationMap.set(PlayerAnimation::WALK_UP, walkUpFrames);
  playerAnimationMap.set(PlayerAnimation::WALK_RIGHT, walkRightFrames);
  playerAnimationMap.set(PlayerAnimation::WALK_LEFT, walkLeftFrames);
  playerAnimationMap.set(PlayerAnimation::IDLE_DOWN, idleDownFrames);
  playerAnimationMap.set(PlayerAnimation::IDLE_UP, idleUpFrames);
  playerAnimationMap.set(PlayerAnimation::IDLE_RIGHT, idleRightFrames);
  playerAnimationMap.set(PlayerAnimation::IDLE_LEFT, idleLeftFrames);

  animation.setAnimationMap(playerAnimationMap);
  animation.play(PlayerAnimation::WALK_DOWN);

  sprite->setFrameRect(animation.getCurrentFrameRect());

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

PlayerAnimation Player::getAnimation() {
  b2Vec2 velocity = body->GetLinearVelocity();
  if (!Vector2Equals(Vector2{velocity.x, velocity.y}, Vector2Zero())) {
    if (direction == PlayerDirection::UP)
      return PlayerAnimation::WALK_UP;
    if (direction == PlayerDirection::DOWN)
      return PlayerAnimation::WALK_DOWN;
    if (direction == PlayerDirection::LEFT)
      return PlayerAnimation::WALK_LEFT;
    if (direction == PlayerDirection::RIGHT)
      return PlayerAnimation::WALK_RIGHT;
  }
  if (direction == PlayerDirection::UP)
    return PlayerAnimation::IDLE_UP;
  if (direction == PlayerDirection::DOWN)
    return PlayerAnimation::IDLE_DOWN;
  if (direction == PlayerDirection::LEFT)
    return PlayerAnimation::IDLE_LEFT;
  if (direction == PlayerDirection::RIGHT)
    return PlayerAnimation::IDLE_RIGHT;

  return PlayerAnimation::IDLE_DOWN;
}

void Player::initBody(b2World *world) {
  Resource *res = Resource::getInstance();
  sprite->setTexture(LoadTexture(res->get(ResourceId::CHARACTER).c_str()));
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0, 0);
  body = world->CreateBody(&bodyDef);
  b2CircleShape shape;
  shape.m_radius = pixelsToMeters(textureWidth / 2);
  shape.m_p = {pixelsToMeters(textureWidth / 2),
               pixelsToMeters(textureHeight) - shape.m_radius};
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;
  fixture = body->CreateFixture(&fixtureDef);
}

void Player::update() {
  b2Vec2 bposition = body->GetPosition();
  b2Vec2 v = body->GetLinearVelocity();

  sprite->setPosition(
      Vector2{metersToPixels(bposition.x), metersToPixels(bposition.y)});

  if (sprite != nullptr) {
    sprite->setPosition(Vector2{round(metersToPixels(bposition.x)),
                                round(metersToPixels(bposition.y))});
  }

  if (IsKeyDown(KEY_W)) {
    body->SetLinearVelocity(b2Vec2{0.0f, -pixelsToMeters(moveSpeed)});
    direction = PlayerDirection::UP;
  }
  if (IsKeyDown(KEY_S)) {
    body->SetLinearVelocity(b2Vec2{0.0f, pixelsToMeters(moveSpeed)});
    direction = PlayerDirection::DOWN;
  }
  if (IsKeyDown(KEY_A)) {
    body->SetLinearVelocity(b2Vec2{pixelsToMeters(-moveSpeed), 0.0f});
    direction = PlayerDirection::LEFT;
  }
  if (IsKeyDown(KEY_D)) {
    body->SetLinearVelocity(b2Vec2{pixelsToMeters(moveSpeed), 0.0f});
    direction = PlayerDirection::RIGHT;
  }
  if (IsKeyReleased(KEY_W) || IsKeyReleased(KEY_S)) {
    body->SetLinearVelocity(b2Vec2{v.x, 0.0f});
  }

  if (IsKeyReleased(KEY_A) || IsKeyReleased(KEY_D)) {
    body->SetLinearVelocity(b2Vec2{0.0f, v.y});
  }
  if (animation.isHaveFrame() && animation.active) {
    if (animation.playedAnimationKey != getAnimation()) {
      animation.play(getAnimation());
    }
    animation.update();
    sprite->setFrameRect(animation.getCurrentFrameRect());
  }
}

void Player::draw() {
  if (sprite != nullptr) {
    sprite->draw();
  }
}