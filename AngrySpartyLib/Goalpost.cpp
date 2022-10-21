/**
 * @file Goalpost.cpp
 * @author Western Tanager
 *
 * The function definitions for the goalpost class.
 */

#include "pch.h"
#include "Consts.h"
#include "Goalpost.h"

/// The front image of the goalpost.
const std::wstring goalFront = L"images/goalposts-front.png";

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
const int GoalpostBandWidth = 15;

/// The goalpost green band colour
const wxColour GoalpostsBandColor = wxColour(0, 255, 0);

/**
 * Constructor
 * @param level The level we are in
 */
Goalpost::Goalpost(Level* level) : Shooter(level)
{
    mHeight = GoalpostsSize.y;
    mWidth = GoalpostsSize.x;
}

/**
 * Draw the goalpost components.
 * @param graphics The graphics context to draw on
 */
void Goalpost::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Shooter::Draw(graphics);

    wxPen pen(GoalpostsBandColor, 5);
    graphics->PushState();

    graphics->Translate(GetX() * Consts::MtoCM,
            GetY() * Consts::MtoCM);

    // Make this is left side of the rectangle
    double x = -GoalpostsSize.x/2 * Consts::MtoCM;

    // And the top
    double y = GoalpostsSize.y * Consts::MtoCM;

    // Draw the band of the goalpost.
    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    graphics->Translate(0, y);
    graphics->SetPen(pen);
    graphics->StrokeLine(
            GoalpostsBandAttachBack.x * Consts::MtoCM,
            -GoalpostsBandAttachBack.y * Consts::MtoCM,
            GoalpostsBandAttachFront.x * Consts::MtoCM,
            -GoalpostsBandAttachFront.y * Consts::MtoCM
    );
    auto image = std::make_shared<wxImage>(goalFront);
    auto bitmap = std::make_shared<wxBitmap>(*image);
    // Draw the front of the slingshot.
    graphics->Translate(0, -y);
    graphics->DrawBitmap(*bitmap,
            x,
            0,
            GoalpostsSize.x * Consts::MtoCM, GoalpostsSize.y * Consts::MtoCM);

    graphics->PopState();
}

/**
 * Load the xml for goalpost.
 * @param node the node to load the xml from.
 */
void Goalpost::XmlLoad(wxXmlNode* node)
{
    Shooter::XmlLoad(node);
}
