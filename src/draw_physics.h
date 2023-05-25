/** DrawPhysics.h
 *
 * Draws the physics objects to screen (for debugging).
 */

#ifndef DRAW_PHYSICS_H
#define DRAW_PHYSICS_H

#include "box2d/box2d.h"
#include "raylib.h"
#include "rlgl.h"
#include <vector>

/** Draws the physics objects to screen.
 * This can be used to debug physics issues.
 */
class DebugDraw : public b2Draw {
public:
  void DrawPolygon(const b2Vec2 *vertices, int vertexCount,
                   const b2Color &color) override;
  void DrawSolidPolygon(const b2Vec2 *vertices, int vertexCount,
                        const b2Color &color) override;
  void DrawCircle(const b2Vec2 &center, float radius,
                  const b2Color &color) override;
  void DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis,
                       const b2Color &color) override;
  void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color);
  void DrawTransform(const b2Transform &xf) override;
  void DrawPoint(const b2Vec2 &p, float size, const b2Color &color) override;

private:
  void DrawPoly(const b2Vec2 *vertices, int vertexCount, const b2Color &color);
  void DrawLine(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color);
  void DrawCircleInternal(const b2Vec2 &center, float radius,
                          const b2Color &color);
};

#endif