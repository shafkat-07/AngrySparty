/**
 * @file Shooter.cpp
 * @author Western Tanager
 *
 * The function definitions for the shooter class.
 */

#include "pch.h"

#include <b2_world.h>
#include <b2_fixture.h>

#include <algorithm>

#include "Shooter.h"
#include "Consts.h"
#include "Sparty.h"

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

    for (auto sparty : mSparties)
    {
        sparty->Draw(graphics);
    }

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
/**
 * Set the sparties in the ready queue.
 * @param sparties Sparties coming in to be shot for this level.
 */
void Shooter::SetSparties(std::vector<std::shared_ptr<Sparty>>& sparties)
{
    mSparties = sparties;
}

/**
 * Called when resetting the level.
 * Will remove references to any sparties or currently loaded sparties.
 */
void Shooter::Clear()
{
    mSparty = nullptr;
    mSparties.clear();
}

/**
 * Update the Shooter.
 * @param elapsed time elapsed since last clock tick.
 */
void Shooter::Update(double elapsed)
{
    if (mSparty == nullptr && !mSparties.empty())
    {
        mSparty = mSparties[0];
        mSparties.erase(mSparties.begin(), mSparties.begin() + 1);
    }
}
