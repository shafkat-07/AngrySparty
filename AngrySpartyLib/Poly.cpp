/**
 * @file Poly.cpp
 * @author Western Tanager
 */

#include "pch.h"

#include <b2_world.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#include "Poly.h"
#include "Consts.h"

/**
 * Constructor for a poly object
 *
 * @param level The level this item is contained in
 */
Poly::Poly(Level* level) :PolygonBody(level)
{
}

/**
 * Load the attributes for a poly
 *
 * Creates the vertices to denote the underlying polygon
 * @param node The Xml node we are loading the poly from
 */
void Poly::XmlLoad(wxXmlNode* node)
{
    PolygonBody::XmlLoad(node);

    // Create the underlying polygon
    std::vector<b2Vec2> & vertices = GetVertices();
    auto vertexNode = node->GetChildren();
    for ( ; vertexNode; vertexNode = vertexNode->GetNext())
    {
        b2Vec2 currVertex;
        currVertex.x = std::stof(vertexNode->GetAttribute(L"x", "0.0").ToStdWstring());
        currVertex.y = std::stof(vertexNode->GetAttribute(L"y", "0.0").ToStdWstring());
        vertices.push_back(currVertex);
    }
}

/**
 * Draw the poly.
 * @param graphics The drawing context to draw on.
 */
void Poly::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto body = GetBody();
    auto position = body->GetPosition();
    auto angle = body->GetAngle();

    // Create the octagon to represent the Foe
    std::vector<b2Vec2> & vertices = GetVertices();

    // Find the minimum and maximum x/y values
    b2Vec2 minimums = vertices[0];
    b2Vec2 maximums = vertices[0];
    for(auto v : vertices)
    {
        minimums.x = fmin(minimums.x, v.x);
        minimums.y = fmin(minimums.y, v.y);
        maximums.x = fmax(maximums.x, v.x);
        maximums.y = fmax(maximums.y, v.y);
    }

    auto size = maximums - minimums;

    auto x = position.x * Consts::MtoCM;
    auto y = position.y * Consts::MtoCM;

    graphics->PushState();
    graphics->Translate(x, y);
    graphics->Rotate(angle);

    std::shared_ptr<wxBitmap> bitmap = GetBitmap();

    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
            minimums.x * Consts::MtoCM,
            minimums.y * Consts::MtoCM,
            size.x * Consts::MtoCM,
            size.y * Consts::MtoCM);

    graphics->PopState();
}
