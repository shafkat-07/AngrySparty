/**
 * @file Item.cpp
 * @author Western Tanager
 *
 * The base class for items in the game.
 */

#include "pch.h"
#include "Item.h"
#include "Level.h"

/**
 * Constructor with a body definition.
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
//    if (mBody != nullptr)
//    {
//        mLevel->GetWorld()->DestroyBody(mBody);
//    }
}

/**
 * Draw the item.
 * @param graphics The drawing context to draw on.
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
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
    mItemImage = std::make_shared<wxImage>(filename, wxBITMAP_TYPE_ANY);
}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode* Item::XmlSave(wxXmlNode* node)
{
    return nullptr;
}
