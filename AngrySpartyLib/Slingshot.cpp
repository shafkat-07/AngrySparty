/**
 * @file Slingshot.cpp
 * @author Western Tanager
 *
 * The function definitions of a SlingShot.
 */

#include "pch.h"
#include "Slingshot.h"
#include "Sparty.h"
#include <iostream>

/// Size of the slingshot image in meters
const b2Vec2 WoodSlingshotSize = b2Vec2(0.5, 1.446);

/// Back band attachment point
const b2Vec2 WoodSlingshotBandAttachBack = b2Vec2(-0.15f, 1.12f);

/// Front band attachment point
const b2Vec2 WoodSlingshotBandAttachFront = b2Vec2(0.15f, 1.2f);

/// Maximum amount the slingshot can be pulled in meters
const double WoodSlingshotMaximumPull = 1;

/// Pull angles from -pi to this value are allowed
const double SlingshotMaximumNegativePullAngle = -1.7;

/// Pull angles from +pi to this value are allowed
const double SlingshotMinimumPositivePullAngle = 2.42;

/// Width of the slingshot band in centimeters
const int SlingshotBandWidth = 15;

/// The slingshot band colour
const wxColour SlingshotBandColor = wxColour(55, 18, 1);

/**
 * Constructor
 * @param level The level we are in
 */
Slingshot::Slingshot(Level* level) : Shooter(level)
{
    SetHeight(WoodSlingshotSize.y);
    SetWidth(WoodSlingshotSize.x);
}

/**
 * Draw the slingshot components.
 * @param graphics The graphics context to draw on
 */
void Slingshot::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Shooter::Draw(graphics);

    DrawSpecificShooter(
            graphics,
            WoodSlingshotBandAttachBack,
            WoodSlingshotBandAttachFront,
            SlingshotBandColor,
            SlingshotBandWidth
    );
}

/**
 * Load the slingshot from an XML node.
 * @param node XML node to load from
 */
void Slingshot::XmlLoad(wxXmlNode* node)
{
    Shooter::XmlLoad(node);
}

/**
 * Handle updates in time of the slingshot
 *
 * @param elapsed Time elapsed since the class call
 */
void Slingshot::Update(double elapsed)
{
    Shooter::Update(elapsed);

    UpdateSpecificShooter(
            WoodSlingshotBandAttachBack,
            WoodSlingshotBandAttachFront,
            SlingshotMaximumNegativePullAngle,
            SlingshotMinimumPositivePullAngle,
            WoodSlingshotMaximumPull
            );
}

/**
 * Launch a sparty from the slingshot.
 */
void Slingshot::LaunchSparty()
{
    LaunchSpecificSparty(
            WoodSlingshotBandAttachBack,
            WoodSlingshotBandAttachFront,
            SlingshotMaximumNegativePullAngle,
            SlingshotMinimumPositivePullAngle,
            WoodSlingshotMaximumPull
            );
}
