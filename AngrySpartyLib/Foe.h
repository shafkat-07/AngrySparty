/**
 * @file Foe.h
 * @author Western Tanager
 *
 * Class to represent a Foe
 */

#ifndef ANGRYSPARTY_FOE_H
#define ANGRYSPARTY_FOE_H

#include "Item.h"

/**
 * Class to represent a foe
 */
class Foe : public Item {
private:
    /// The physics system body
    b2Body* mBody = nullptr;

    /// The box2d fixture
    b2Fixture* mFixture;

    /// The box2d body definition
    b2BodyDef* mBodyDef;

    b2Vec2 mPosition = b2Vec2(0.0f, 0.0f); ///< The position vector of the foe
    double mAngle = 0; ///< Angle of the item
    double mRadius = 0; ///< Times this item repeats
    double mDown = 0; ///< Times this item repeats
    double mDensity = 0; ///< Density of the item
    double mFriction = 0; ///< Friction of the item
    double mRestitution = 0; ///< Restitution of the item
    bool mStatic = true; ///< Whether or not the foe is static
    std::vector<b2Vec2> mVertices; ///< Vertices that denote this foe

public:
    Foe(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void XmlLoad(wxXmlNode* node);

    /**
     * The height of the item.
     * @return Height in pixels.
     */
    double GetAngle() const { return mAngle; }

    b2Fixture* CreateFixture(b2Shape* shape);

    /**
     * Get the body of the item
     * @return body of the item
     */
    b2Body* GetBody() { return mBody; }

    /**
     * Get the fixture of the foe
     * @return fixture of the foe
     */
    b2Fixture* GetFixture() { return mFixture; }

    void SetTransform(const b2Vec2& location, double angle);

    void InstallPhysics() override;

    bool HitTest(double x, double y) override;
};

#endif //ANGRYSPARTY_FOE_H
