/**
 * @file PhysicalObject.h
 * @author Western Tanager
 *
 * Base class for objects that interact
 * within the physics system
 */

#ifndef ANGRYSPARTY_PHYSICALOBJECT_H
#define ANGRYSPARTY_PHYSICALOBJECT_H

#include "Item.h"
#include <b2_body.h>

/**
 * Base class for objects that interact
 * within the physics system
 *
 * Everything except the shooters and background
 * are derived from this class
 */
class PhysicalObject : public Item {
private:
    std::shared_ptr<wxImage> mPicture; ///< The image for this object
    std::shared_ptr<wxBitmap> mBitmap; ///< The bitmap for this item
    b2Body* mBody = nullptr; ///< The physics system body
    b2Vec2 mPosition = b2Vec2(0.0f, 0.0f); ///< The position vector of the foe
    double mAngle = 0; ///< Angle of the item
    double mDown = 0; ///< Times this item repeats
    double mDensity = 0; ///< Density of the item
    double mFriction = 0; ///< Friction of the item
    double mRestitution = 0; ///< Restitution of the item
    int mRepeatX = 0; ///< Times this item repeats
public:
    PhysicalObject(Level* level, const std::wstring& filename);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    b2Body* GetBody() { return mBody; }
    void Update(double elapsed) override;
    wxXmlNode* XmlSave(wxXmlNode* node) override;
    void XmlLoad(wxXmlNode* node) override;

};

#endif //ANGRYSPARTY_PHYSICALOBJECT_H
