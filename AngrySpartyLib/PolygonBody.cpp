/**
 * @file PolygonBody.cpp
 * @author Western Tanager
 */

#include "pch.h"

#include <b2_polygon_shape.h>
#include "PolygonBody.h"

using namespace std;

/**
 * Constructor for a polygon body
 *
 * @param level The level this object is in
 */
PolygonBody::PolygonBody(Level *level) : PhysicalObject(level)
{
}

/**
 * Create a shape for a polygon body
 *
 * @return The b2PolygonShape for a polygon body
 */
unique_ptr<b2Shape> PolygonBody::CreateShape()
{
    unique_ptr<b2PolygonShape> poly = make_unique<b2PolygonShape>();
    poly->Set(&mVertices[0], mVertices.size());
    return poly;
}