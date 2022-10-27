/**
 * @file Goalpost.cpp
 * @author Western Tanager
 *
 * The function definitions for the goalpost class.
 */

#include "pch.h"
#include "Consts.h"
#include "Goalpost.h"
#include "Sparty.h"

/// Size of the Goalpost image in meters
const b2Vec2 GoalpostsSize = b2Vec2(1, 2.649);

/// Back band attachment point
const b2Vec2 GoalpostsBandAttachBack = b2Vec2(-0.42f, 2.3f);

/// Front band attachment point
const b2Vec2 GoalpostsBandAttachFront = b2Vec2(0.34f, 2.32f);

/// Maximum amount the Goalpost can be pulled in meters
const double GoalpostsMaximumPull = 2;

/// Pull angles from -pi to this value are allowed
const double GoalpostMaximumNegativePullAngle = -1.7;

/// Pull angles from +pi to this value are allowed
const double GoalpostMinimumPositivePullAngle = 2.42;

/// Width of the goalpost band in centimeters
const int GoalpostBandWidth = 5;

/// The goalpost green band colour
const wxColour GoalpostsBandColor = wxColour(0, 255, 0);

/**
 * Constructor
 * @param level The level we are in
 */
Goalpost::Goalpost(Level* level) : Shooter(level)
{
    SetHeight(GoalpostsSize.y);
    SetWidth(GoalpostsSize.x);
}

/**
 * Draw the goalpost components.
 * @param graphics The graphics context to draw on
 */
void Goalpost::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Shooter::Draw(graphics);

    DrawSpecificShooter(
            graphics,
            GoalpostsBandAttachBack,
            GoalpostsBandAttachFront,
            GoalpostsBandColor,
            GoalpostBandWidth
    );
}

/**
 * Load the xml for goalpost.
 * @param node the node to load the xml from.
 */
void Goalpost::XmlLoad(wxXmlNode* node)
{
    Shooter::XmlLoad(node);
}

/**
 * Handle updates in time of the goalposts
 *
 * @param elapsed Time elapsed since the class call
 */
void Goalpost::Update(double elapsed)
{
    Shooter::Update(elapsed);
    std::shared_ptr<Sparty> sparty = GetSparty();
    if (sparty != nullptr)
    {
        sparty->SetXPosition(GetX());
        sparty->SetYPosition(
                GoalpostsBandAttachBack.y +
                (GoalpostsBandAttachFront.y - GoalpostsBandAttachBack.y) / 2 +
                sparty->GetRadius());
        sparty->ModifyBodyToDynamic();
    }
}
