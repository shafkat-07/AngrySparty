/**
 * @file Background.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include "Background.h"
#include "Consts.h"
#include "Level.h"

using namespace std;

/**
 * Constructor for a background item
 *
 * Does not contain any physics
 * @param level The level this item is contained in
 */
Background::Background(Level* level) : Item(level)
{

}

/**
 * Draw the background.
 * @param graphics The drawing context to draw on.
 */
void Background::Draw(shared_ptr<wxGraphicsContext> graphics)
{

    auto wid = mWidth * Consts::MtoCM;
    auto hit = mHeight * Consts::MtoCM;

    shared_ptr<wxBitmap> bitmap = GetBitmap();

    graphics->PushState();
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
            -wid/2,
            -hit,
            wid, hit);
    graphics->PopState();

}

/**
 * Load the attributes for the background
 *
 * @param node The Xml node we are loading the item from
 */
void Background::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    // Get the attributes for this item
    node->GetAttribute(L"width", L"0").ToDouble(&mWidth);
    node->GetAttribute(L"height", L"0").ToDouble(&mHeight);
}

/**
 * Hit test for the background.
 * @param x x position to test.
 * @param y y position to test.
 * @return if the background was hit.
 */
bool Background::HitTest(double x, double y)
{
    return false;
}
