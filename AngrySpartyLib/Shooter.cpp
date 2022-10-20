/**
 * @file Shooter.cpp
 * @author Western Tanager
 *
 * The function definitions for the shooter class.
 */

#include "pch.h"
#include <b2_world.h>
#include <b2_circle_shape.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#include "Shooter.h"
#include "Consts.h"

/// File pointer to the image for the shooter
const std::wstring imageFilename = L"images/slingshot.png";

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

Shooter::Shooter(Level* level) : Item(level)
{
    mHeight = WoodSlingshotSize.y * Consts::MtoCM;
    mWidth = WoodSlingshotSize.x * Consts::MtoCM;
}

void Shooter::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Draw the slingshot
    std::shared_ptr<wxBitmap> bitmap = std::make_shared<wxBitmap>(*GetPicture());

    graphics->PushState();
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
            mPosition.x,
            -mPosition.y,
            mWidth, mHeight);
    graphics->PopState();
}

void Shooter::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    double x;
    double y;

    // Get the attributes for this item
    node->GetAttribute(L"x", L"0.0").ToDouble(&x);
    node->GetAttribute(L"y", L"0.0").ToDouble(&y);
    mPosition.x = (x * Consts::MtoCM) + mWidth;
    mPosition.y = (y * Consts::MtoCM) + mHeight;
}


