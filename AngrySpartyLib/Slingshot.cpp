/**
 * @file Slingshot.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include "Consts.h"
#include "Slingshot.h"

/// The front image of the slingshot.
const std::wstring slingFront = L"images/slingshot-front.png";

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


Slingshot::Slingshot(Level* level) : Shooter(level)
{
}

/**
 * Draw the slingshot components.
 * @param graphics The graphics context to draw on
 */
void Slingshot::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Shooter::Draw(graphics);

// Hex for dark brown
    wxColour color = wxColour(55, 18, 1);

    wxPen pen(color, 15);
    graphics->PushState();

    graphics->Translate(GetX() * Consts::MtoCM,
            GetY() * Consts::MtoCM);

    // Make this is left side of the rectangle
    double x = -GetWidth()/2 * Consts::MtoCM;

    // And the top
    double y = GetHeight() * Consts::MtoCM;

    auto image = std::make_shared<wxImage>(slingFront);
    auto bitmap = std::make_shared<wxBitmap>(*image);

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    graphics->Translate(0, y);
    graphics->SetPen(pen);
    graphics->StrokeLine(
            WoodSlingshotBandAttachBack.x * Consts::MtoCM,
            -WoodSlingshotBandAttachBack.y * Consts::MtoCM,
            WoodSlingshotBandAttachFront.x * Consts::MtoCM,
            -WoodSlingshotBandAttachFront.y * Consts::MtoCM
    );
    graphics->Translate(0, -y);
    graphics->DrawBitmap(*bitmap,
            x,
            0,
            GetWidth() * Consts::MtoCM, GetHeight() * Consts::MtoCM);



    graphics->PopState();
}

/**
 * Load the slingshot from an XML node.
 * @param node XML node to load from
 */
void Slingshot::XmlLoad(wxXmlNode* node)
{
    Shooter::XmlLoad(node);
}
