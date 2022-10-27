/**
 * @file Slingshot.cpp
 * @author Western Tanager
 *
 * The function definitions of a SlingShot.
 */

#include "pch.h"
#include "Consts.h"
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
    std::shared_ptr<Sparty> sparty = GetSparty();
    bool loaded = IsLoaded();
    bool launched = IsLaunched();
    const b2Vec2 centerPos = b2Vec2(GetX(),
            WoodSlingshotBandAttachBack.y -
            (WoodSlingshotBandAttachFront.y - WoodSlingshotBandAttachBack.y) / 2 +
            sparty->GetRadius()
                    );
    if (sparty != nullptr && !loaded)
    {
        // Set the sparty position to the center of the slingshot.
        sparty->SetTransform(centerPos, 0.0f);
        SetLoaded(true);
    }
    else if (loaded && !launched)
    {
        auto distance = sparty->DistanceBetweenBodies(centerPos);
        auto angle = sparty->AngleBetweenBodies(centerPos);
        if (distance > WoodSlingshotMaximumPull)
        {
            // adjust the position of the sparty so that the distance is no more than WoodSlingShotMaximumPull.
            sparty->SetTransform(
                    b2Vec2(
                            centerPos.x + cos(angle) * WoodSlingshotMaximumPull,
                            centerPos.y + sin(angle) * WoodSlingshotMaximumPull
                    ),
                    0.0f
            );
            // Ensure that the mouseJoint can no longer move the sparty.
        }
    }
}

void Slingshot::LaunchSparty()
{
    Shooter::LaunchSparty();

    std::shared_ptr<Sparty> sparty = GetSparty();
    const b2Vec2 centerPos = b2Vec2(GetX(),
            WoodSlingshotBandAttachBack.y -
                    (WoodSlingshotBandAttachFront.y - WoodSlingshotBandAttachBack.y) / 2 +
                    sparty->GetRadius()
    );
    auto distance = sparty->DistanceBetweenBodies(centerPos);
    if (sparty != nullptr)
    {
        // Get the angle between the slingshot and the mouse
        double angle = sparty->AngleBetweenBodies(centerPos);

        // If the distance is too small, do nothing
        if (distance < 0.1)
        {
            return;
        }

        // If the distance is too large, set it to the maximum
        if (distance > WoodSlingshotMaximumPull)
        {
            distance = WoodSlingshotMaximumPull;
        }

        // If the angle is too small, set it to the minimum
        if (angle < SlingshotMaximumNegativePullAngle)
        {
            angle = SlingshotMaximumNegativePullAngle;
        }

        // If the angle is too large, set it to the maximum
        if (angle > SlingshotMinimumPositivePullAngle)
        {
            angle = SlingshotMinimumPositivePullAngle;
        }

        // Make the sparty movable
        sparty->GetBody()->SetFixedRotation(false);
        sparty->GetBody()->SetGravityScale(1.0f);
        // Set the sparty's velocity based on the angle and distance
        sparty->GetBody()->SetLinearVelocity(b2Vec2(cos(angle) * distance * 12.0, sin(angle) * distance * 12.0));

        // Set the sparty to not be loaded
        SetLoaded(false);
        Shooter::LaunchSparty();
    }
}
