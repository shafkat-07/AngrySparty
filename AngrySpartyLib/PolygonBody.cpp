/**
 * @file PolygonBody.cpp
 * @author Western Tanager
 */

#include "pch.h"

#include <b2_polygon_shape.h>
#include "PolygonBody.h"

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
b2PolygonShape PolygonBody::CreateShape()
{
    b2PolygonShape poly;
    poly.Set(&mVertices[0], mVertices.size());
    return poly;
}
