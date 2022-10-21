/**
 * @file Shooter.cpp
 * @author Western Tanager
 *
 * The function definitions for the shooter class.
 */

#include "pch.h"
#include <b2_world.h>
#include <b2_fixture.h>
#include "Shooter.h"
#include "Consts.h"

/**
 * Constructor for a shooter object
 *
 * Initiates the shooter.
 * @param level The level this item is contained in
 */
Shooter::Shooter(Level* level) : Item(level)
{
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

    auto name = "images/" + node->GetName() + "-front.png";
    mFrontImage = std::make_shared<wxImage>(name);
    mFrontBitmap = std::make_shared<wxBitmap>(*mFrontImage);
}
