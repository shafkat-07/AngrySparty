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

    wxPen pen(SlingshotBandColor, SlingshotBandWidth);
    graphics->PushState();

    graphics->Translate(GetX()*Consts::MtoCM,
            GetY()*Consts::MtoCM);

    // Make this is left side of the rectangle
    double x = -GetWidth()/2*Consts::MtoCM;

    // And the top
    double y = GetHeight()*Consts::MtoCM;
    auto sparty = GetSparty();
    if (sparty == nullptr) {
        // Draw the band of the slingshot.
        graphics->Scale(1, -1);
        graphics->SetPen(pen);
        graphics->StrokeLine(
                WoodSlingshotBandAttachBack.x*Consts::MtoCM,
                -WoodSlingshotBandAttachBack.y*Consts::MtoCM,
                WoodSlingshotBandAttachFront.x*Consts::MtoCM,
                -WoodSlingshotBandAttachFront.y*Consts::MtoCM
        );
    }
    else
    {
        auto position = sparty->GetPosition();
        // Compensate for graphics translation.
        position.x -= GetX();
        position.y -= GetY();
        // Draw the back of the band
        graphics->Scale(1, -1);
        graphics->SetPen(pen);
        graphics->StrokeLine(
                WoodSlingshotBandAttachBack.x*Consts::MtoCM,
                -WoodSlingshotBandAttachBack.y*Consts::MtoCM,
                position.x * Consts::MtoCM,
                -position.y * Consts::MtoCM
        );
        // Draw the Sparty
        graphics->PushState();
        sparty->Draw(graphics);
        graphics->PopState();
        // Draw the cross section of the band.
        graphics->StrokeLine(
                position.x * Consts::MtoCM,
                -position.y * Consts::MtoCM,
                position.x * Consts::MtoCM + ((sparty->GetRadius() * Consts::MtoCM) / 2),
                -position.y * Consts::MtoCM
                );
        // Draw the front of the band
        graphics->StrokeLine(
                position.x * Consts::MtoCM + ((sparty->GetRadius() * Consts::MtoCM) / 2),
                -position.y * Consts::MtoCM,
                WoodSlingshotBandAttachFront.x * Consts::MtoCM,
                -WoodSlingshotBandAttachFront.y * Consts::MtoCM
        );
    }

    // Draw the front of the slingshot.
    auto bitmap = GetFrontBitmap();
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

/**
 * Handle updates in time of the slingshot
 *
 * @param elapsed Time elapsed since the class call
 */
void Slingshot::Update(double elapsed)
{
    Shooter::Update(elapsed);
    std::shared_ptr<Sparty> sparty = GetSparty();
    if (sparty != nullptr)
    {
        sparty->SetXPosition(GetX());
        sparty->SetYPosition(WoodSlingshotBandAttachBack.y + (WoodSlingshotBandAttachFront.y - WoodSlingshotBandAttachBack.y) / 2 + sparty->GetRadius());
        sparty->ModifyBodyToDynamic();
    }
}
