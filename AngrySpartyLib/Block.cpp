/**
 * @file Block.cpp
 * @author Western Tanager
 */

#include "pch.h"

#include <b2_polygon_shape.h>
#include <b2_fixture.h>

#include "Block.h"
#include "Consts.h"

using namespace std;

/**
 * Constructor for a block object
 *
 * @param level The level this block is contained in
 */
Block::Block(Level* level) : PhysicalObject(level)
{
}

/**
 * Load the attributes for a block
 *
 * Load size and repeat, which are specific to a block
 * @param node The Xml node we are loading the block from
 */
void Block::XmlLoad(wxXmlNode* node)
{
    PhysicalObject::XmlLoad(node);

    // Block-specific attributes
    mSize.x = stof(node->GetAttribute(L"width", "0.0").ToStdWstring());
    mSize.y = stof(node->GetAttribute(L"height", "0.0").ToStdWstring());
    node->GetAttribute(L"repeat-x", L"1").ToInt(&mRepeatX);
}

/**
 * Create a shape for a block's body
 *
 * @return The b2PolygonShape for a block
 */
unique_ptr<b2Shape> Block::CreateShape()
{
    unique_ptr<b2PolygonShape> box = make_unique<b2PolygonShape>();
    box->SetAsBox(mSize.x/2, mSize.y/2);
    return box;
}

/**
 * Draw the block.
 * @param graphics The drawing context to draw on.
 */
void Block::Draw(shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    b2Body* body = GetBody();
    auto position = body->GetPosition();
    auto angle = body->GetAngle();

    graphics->Translate(position.x * Consts::MtoCM,
            position.y * Consts::MtoCM);
    graphics->Rotate(angle);

    // Make this is left side of the rectangle
    double x = -mSize.x/2 * Consts::MtoCM;

    // And the top
    double y = mSize.y/2 * Consts::MtoCM;

    // The width of each repeated block
    double xw = mSize.x / mRepeatX * Consts::MtoCM;

    shared_ptr<wxBitmap> bitmap = GetBitmap();

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    for(int ix=0; ix<mRepeatX;  ix++)
    {
        graphics->DrawBitmap(*bitmap,
                x,
                0,
                xw, mSize.y * Consts::MtoCM);

        x += xw;
    }

    graphics->PopState();
}