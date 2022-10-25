/**
 * @file Sparty.cpp
 * @author Western Tanager
 *
 * Class to represent the Angry Sparty
*/

#include "pch.h"
#include "Sparty.h"
#include "Level.h"
#include "Consts.h"

#include <b2_world.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>

/**
 * Constructor for a sparty object
 * @param level The level this item is contained in
 */
Sparty::Sparty(Level* level) : CircleBody(level)
{
}

/**
 * Load the attributes for a sparty
 *
 * Load radius and down, which are specific to a sparty
 * @param node The Xml node we are loading the sparty from
 */
void Sparty::XmlLoad(wxXmlNode* node)
{
    CircleBody::XmlLoad(node);

    // Sparty-specific attributes
    // dust... for now.
}
