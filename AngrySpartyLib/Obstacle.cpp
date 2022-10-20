/**
 * @file Obstacle.cpp
 * @author Western Tanager
 *
 * The class of an obstacle in the Angry Sparty game.
 */

#include "pch.h"
#include "Obstacle.h"

/**
 * Constructor for Obstacle
 * @param level The level this obstacle is in.
 */
Obstacle::Obstacle(Level* level) : Item(level)
{
}

/**
 * Save this item to an XML node
 * @param node The parent node to save attributes to.
 * @return The node we saved to.
 */
wxXmlNode* Obstacle::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);

    itemNode->AddAttribute(L"type", L"obstacle");

    return itemNode;
}

/**
 * Update the obstacle.
 * @param elapsed Time that has elapsed.
 */
void Obstacle::Update(double elapsed)
{
}

/**
 * Load the obstacle from an XML node.
 * @param node The xml node to load from.
 */
void Obstacle::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

}

bool Obstacle::HitTest(double x, double y)
{
    return false;
}