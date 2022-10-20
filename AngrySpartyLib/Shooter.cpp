/**
 * @file Shooter.cpp
 * @author Western Tanager
 *
 * The function definitions for the shooter class.
 */

#include "pch.h"
#include <b2_world.h>
#include <b2_circle_shape.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#include "Shooter.h"
#include "Consts.h"

/// File pointer to the image for the shooter
const std::wstring imageFilename = L"images/slingshot.png";

/// Size of the slingshot image in meters
const b2Vec2 WoodSlingshotSize = b2Vec2(0.5, 1.446);

Shooter::Shooter(Level* level) : Item(level)
{
    mHeight = WoodSlingshotSize.y;
    mWidth = WoodSlingshotSize.x;
}

/**
 * Draw a shooter
 *
 * @param graphics
 */
void Shooter::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    graphics->PushState();

    graphics->Translate(mX * Consts::MtoCM,
            mY * Consts::MtoCM);

    // Make this is left side of the rectangle
    double x = -mWidth/2 * Consts::MtoCM;

    // And the top
    double y = mHeight * Consts::MtoCM;

    std::shared_ptr<wxBitmap> bitmap = GetBitmap();

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
            x,
            0,
            mWidth * Consts::MtoCM, mHeight * Consts::MtoCM);

    graphics->PopState();
}

/**
 * Load the XML according to the shooter type.
 * @param node XML node to load from.
 */
void Shooter::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    // Get the attributes for this item
    node->GetAttribute(L"x", L"0.0").ToDouble(&mX);
    node->GetAttribute(L"y", L"0.0").ToDouble(&mY);
}
