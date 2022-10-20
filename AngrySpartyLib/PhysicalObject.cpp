/**
 * @file PhysicalObject.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include <b2_body.h>
#include <b2_fixture.h>
#include <b2_polygon_shape.h>
#include "PhysicalObject.h"
#include "Level.h"
#include "Consts.h"

/**
 * Constructor for a physical object
 * @param level The level this object is in
 * @param x The x location of the object
 * @param y The y location of the object
 */
PhysicalObject::PhysicalObject(Level* level, const std::wstring& filename) : Item(level)
{
    mPicture = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mBitmap = std::make_unique<wxBitmap>(*mPicture);
    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = mPosition;
    bodyDefinition.angle = mAngle;
    bodyDefinition.type = b2_staticBody;
    auto body = level->GetWorld()->CreateBody(&bodyDefinition);
    mBody = body;
}

void PhysicalObject::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    b2Body* body = GetBody();
    auto position = body->GetPosition();
    auto angle = body->GetAngle();

    graphics->Translate(position.x * Consts::MtoCM,
            position.y * Consts::MtoCM);
    graphics->Rotate(angle);

    // Make this is left side of the rectangle
    double x = -mPosition.x/2 * Consts::MtoCM;

    // And the top
    double y = mPosition.y/2 * Consts::MtoCM;

    // The width of each repeated block
    double xw = mPosition.x / mRepeatX * Consts::MtoCM;

    //std::shared_ptr<wxBitmap> bitmap = redacted

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    for(int ix = 0; ix < mRepeatX;  ix++)
    {
        graphics->DrawBitmap(*mBitmap,
                x,
                0,
                xw, mPosition.y * Consts::MtoCM);

        x += xw;
    }

    graphics->PopState();
}


/**
 * Update the object
 * @param elapsed time since last update
 */
void PhysicalObject::Update(double elapsed) {}

/**
 * Load the attributes for a physical object
 *
 * @param node The Xml node we are loading the item from
 */
void PhysicalObject::XmlLoad(wxXmlNode* node) {}

/**
 * Save the attributes for a physical object
 * @param node The node we are saving the item to
 */
wxXmlNode *PhysicalObject::XmlSave(wxXmlNode* node) { return nullptr; }