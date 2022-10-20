/**
 * @file Shooter.h
 * @author Western Tanager
 *
 * The shooter class of the game.
 *
 * Can shoot angry sparties towards the enemies.
 */

#ifndef ANGRYSPARTY_SHOOTER_H
#define ANGRYSPARTY_SHOOTER_H

#include "Item.h"

/**
 * The shooter class of the game.
 *
 * Can shoot angry sparties towards the enemies.
 */
class Shooter : public Item {
private:
    /// The physics system body
    b2Body* mBody = nullptr;

    /// The box2d fixture
    b2Fixture* mFixture;

    /// The box2d body definition
    b2BodyDef* mBodyDef;

    b2Vec2 mPosition;                      ///< The position vector of the shooter
    bool mStatic = true;                   ///< Whether or not the shooter is static
    std::vector<b2Vec2> mVertices;         ///< Vertices that denote this shooter

public:
    Shooter(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void XmlLoad(wxXmlNode* node) override;

    /**
     * Retruns the body of the shooter
     * @return the body of the shooter
     */
    b2Body* GetBody() { return mBody; }

    /**
     * Create the fixture of the shooter.
     * @param shape A polygon shape.
     * @return Fixture of the shooter.
     */
    b2Fixture* CreateFixture(b2Shape* shape) { return nullptr; }

    /**
     * Returns the fixture of the shooter
     * @return the fixture of the shooter
     */
    b2Fixture* GetFixture() { return mFixture; }

    void InstallPhysics() override;
};

#endif //ANGRYSPARTY_SHOOTER_H
