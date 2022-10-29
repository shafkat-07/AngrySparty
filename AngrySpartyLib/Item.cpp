/**
 * @file Item.cpp
 * @author Western Tanager
 *
 * The base class for items in the game.
 */

#include "pch.h"
#include "Item.h"
#include "Level.h"

using namespace std;

/**
 * Constructor for an item
 * @param level The level this item is contained in
 */
Item::Item(Level* level) : mLevel(level)
{

}

/**
 * Get the world that this item is in.
 * @return The world this item is in.
 */
b2World* Item::GetWorld()
{
    return mLevel->GetWorld();
}

/**
 * Destroy the item.
 */
Item::~Item()
{
}

/**
 * Draw the item.
 * @param graphics The drawing context to draw on.
 */
void Item::Draw(shared_ptr<wxGraphicsContext> graphics)
{
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode* node)
{
    // Get the attributes for this item
    auto  filename = "images/" +
            node->GetAttribute(L"image", L"");
    if (filename != "images/")
    {
        mItemImage = make_shared<wxImage>(filename, wxBITMAP_TYPE_ANY);
    }
    else
    {
        filename = "images/" +
                node->GetName() + ".png";
        mItemImage = make_shared<wxImage>(filename, wxBITMAP_TYPE_ANY);
    }
    mItemBitmap = make_shared<wxBitmap>(*mItemImage);
}

