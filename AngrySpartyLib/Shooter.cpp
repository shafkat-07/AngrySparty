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

const std::wstring imageFilename = L"images/slingshot.png";

Shooter::Shooter(Level* level)
        :Item(level)
{

}

void Shooter::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    auto body = GetBody();
    auto position = body->GetPosition();

    graphics->Translate(mPosition.x * Consts::MtoCM,
            mPosition.y * Consts::MtoCM); // TODO change to position.x and position.y ?
    // Make this is left side of the rectangle
    double x = -mSize.x/2 * Consts::MtoCM;

    // And the top
    double y = mSize.y/2 * Consts::MtoCM;

    // The width of each repeated block
    double xw = mSize.x * Consts::MtoCM;

    std::shared_ptr<wxBitmap> bitmap = std::make_shared<wxBitmap>(*GetPicture());

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap, x, 0, xw, mSize.y * Consts::MtoCM);

    x += xw;

    graphics->PopState();
}

/**
 * Load the attributes for a shooter
 *
 * @param node The node we are loading the shooter from
 */
void Shooter::XmlLoad(wxXmlNode* node)
{
    Item::SetImage(imageFilename);

    mPosition.x = std::stof(node->GetAttribute(L"x", "0.0").ToStdWstring());
    mPosition.y = std::stof(node->GetAttribute(L"y", "0.0").ToStdWstring());
    mSize.x = GetPicture()->GetWidth() * Consts::MtoCM;
    mSize.y = GetPicture()->GetHeight() * Consts::MtoCM;
}
