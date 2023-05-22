/** DrawPhysics.cpp
 *
 * See header file for details.
 */

#include "draw_physics.h"

#include "constants.h"
#include "raylib.h"
#include "raymath.h"
#include <cstdio>

const Color COL_BLUE = Color{0, 121, 241, 120};

void DebugDraw::DrawPolygon(const b2Vec2 *vertices, int vertexCount,
                            const b2Color &color) {
  DrawPoly(vertices, vertexCount, color);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int vertexCount,
                                 const b2Color &color) {
  DrawPoly(vertices, vertexCount, color);
}

void DebugDraw::DrawCircle(const b2Vec2 &center, float radius,
                           const b2Color &color) {
  DrawCircleInternal(center, radius, color);
}

void DebugDraw::DrawSolidCircle(const b2Vec2 &center, float radius,
                                const b2Vec2 &axis, const b2Color &color) {
  DrawCircleInternal(center, radius, color);
}

void DebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                            const b2Color &color) {
  DrawLine(p1, p2, color);
}

void DebugDraw::DrawTransform(const b2Transform &xf) {
  // You can draw the transform if needed
}

void DebugDraw::DrawPoly(const b2Vec2 *vertices, int vertexCount,
                         const b2Color &color) {
  for (int i = 0; i < vertexCount - 1; ++i) {
    DrawLine(vertices[i], vertices[i + 1], color);
  }

  // Draw the last line connecting the last and first vertices
  DrawLine(vertices[vertexCount - 1], vertices[0], color);
}

void DebugDraw::DrawLine(const b2Vec2 &p1, const b2Vec2 &p2,
                         const b2Color &color) {
  Vector2 pixelP1 = {metersToPixels(p1.x), metersToPixels(p1.y)};
  Vector2 pixelP2 = {metersToPixels(p2.x), metersToPixels(p2.y)};

  DrawLineV(pixelP1, pixelP2, COL_BLUE);
}

void DebugDraw::DrawCircleInternal(const b2Vec2 &center, float radius,
                                   const b2Color &color) {
  Vector2 pixelCenter = {metersToPixels(center.x), metersToPixels(center.y)};
  float pixelRadius = metersToPixels(radius);

  DrawCircleV(pixelCenter, pixelRadius, COL_BLUE);
}

void DebugDraw::DrawPoint(const b2Vec2 &p, float size, const b2Color &color) {
  Vector2 pixelP = {metersToPixels(p.x), metersToPixels(p.y)};
  float pixelSize = metersToPixels(size);

  DrawCircleV(pixelP, pixelSize, COL_BLUE);
}
