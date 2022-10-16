/**
 * @file Level.cpp
 * @author Western Tanager
 *
 * The level class will load the level from an XML file and display it on the screen.
 */

#include "pch.h"
#include <b2_polygon_shape.h>
#include <b2_circle_shape.h>
#include <b2_mouse_joint.h>
#include "Level.h"
#include "Obstacle.h"

class Item;

/// Gravity in meters per second per second
const float Gravity = -9.8f;

/// Number of velocity update iterations per step
const int VelocityIterations = 6;

/// Number of position update iterations per step
const int PositionIterations = 2;

/**
 * Loads a specified XML file into the level
 * @param filename The location of the XML file on disk
 */
void Level::Load(const std::wstring &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Level file");
        return;
    }

    Clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();

        // TODO change this to each of item's derived classes when completed
        if(name == L"items")
        {
            auto grandChild = child->GetChildren();
            for ( ; grandChild; grandChild = grandChild->GetNext())
            {
                XmlItem(grandChild);
            }
        }
    }
}

/**
 * Handle a node of type item.
 * TODO create seperate functions for each of the item types (block, poly, foe, sling)
 * @param node XML node
 */
void Level::XmlItem(wxXmlNode *node)
{
    // A pointer for the item we are loading
    std::shared_ptr<Item> item;

    // We have an item. What type?
    auto type = node->GetName();
    if (type == "obstacle") {
        item = std::make_shared<Obstacle>(this);
    }
//    TODO Comment this back in when the other item types are created.
//    else if (type == "block")
//    {
//        item = std::make_shared<Block>(this);
//    }
//    else if (type == "poly")
//    {
//        item = std::make_shared<Poly>(this);
//    }
//    else if (type == "foe")
//    {
//        item = std::make_shared<Foe>(this);
//    }
//    else if (type == "sling")
//    {
//        item = std::make_shared<Sling>(this);
//    }
    else
    {
//        wxMessageBox(L"Unknown item type: " + type);
//        return;
        item = std::make_shared<Obstacle>(this);
    }
    item->XmlLoad(node);


    if (item != nullptr)
    {
        mItems.push_back(item);
    }
}

/**
 * Clears the Items from the level
 */
void Level::Clear()
{
    mItems.clear();
}

/**
 * Constructor for the level, requires an XML file path
 * @param filename Path to the XML file
 */
Level::Level(const std::wstring &filename) :mWorld(b2Vec2(0.0f, Gravity))
{
    // The size of the playing area in meters
    auto size = mSize;

    // Create a ground body at 0,0 to use as a reference
    b2BodyDef bodyDefinition;
    bodyDefinition.position.Set(0, -0.1);
    bodyDefinition.type = b2_staticBody;
    mGround = mWorld.CreateBody(&bodyDefinition);

    // Bottom
    b2PolygonShape box;
    box.SetAsBox(size.x*2, 0.1);
    mGround->CreateFixture(&box, 0.0f);

    // Right side
    box.SetAsBox(0.1, size.y, b2Vec2(size.x, size.y), 0);
    mGround->CreateFixture(&box, 0.0f);

    // Left side
    box.SetAsBox(0.1, size.y, b2Vec2(-size.x, size.y), 0);
    mGround->CreateFixture(&box, 0.0f);

    Load(filename);
}

/**
 * Handles drawing the items from the level on GameView
 * @param dc The wxDC object to write to
 */
void Level::OnDraw(std::shared_ptr<wxGraphicsContext> graphics)
{
    std::cout << "The item received the pointer to Level" << '\n';
    for(auto each_item : mItems){
        each_item->OnDraw(graphics);
    }
}
