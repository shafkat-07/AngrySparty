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
    b2Body* mBody = nullptr; ///< The Box2D body of the object
    b2Vec2 mPosition = b2Vec2(0.0f, 0.0f); ///< The position vector of the object
    double mAngle = 0; ///< Angle of the object
    double mDensity = 0; ///< Density of the object
    double mFriction = 0; ///< Friction of the object
    double mRestitution = 0; ///< Restitution of the object
    bool mStatic; ///< True if the object is static

public:
    PhysicalObject(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override = 0;
    void InstallPhysics(std::shared_ptr<World>) override;
    virtual void Update(double elapsed) override;
    wxXmlNode* XmlSave(wxXmlNode* node) override;
    void XmlLoad(wxXmlNode* node) override;
    virtual b2Body* DefineBody(b2Shape* shape, b2World* world);
    bool HitTest(double x, double y) override;

    /**
     * Creates a shape for a physical body
     * @return The b2Shape for the body
     */
    virtual std::unique_ptr<b2Shape> CreateShape() = 0;

    /**
     * The angle of the item.
     * @return Angle in degrees.
     */
    double GetAngle() const { return mAngle; }

    /**
     * Get the physical object's body
     * @return The physical object's body
     */
    b2Body* GetBody() override { return mBody; }

    /**
     * Set the physical object's body
     * @param body The body to update to.
     */
    void SetBody(b2Body* body) { mBody = body; }

    /**
     * Set the x position of this physical object
     * @param x The x position in meters
     */
    void SetXPosition(float x) { mPosition.x = x; }

    /**
     * Set the y position of this physical object
     * @param y The x position in meters
     */
    void SetYPosition(float y) { mPosition.y = y; }

    /**
     * Get the position of this physical object.
     * @return The position of this physical object.
     */
    b2Vec2 GetPosition() { return mPosition; }

    /**
     * Get the static boolean.
     * @return Whether or not this object is static
     */
    bool IsStatic() { return mStatic; }

    /**
     * Set if the object is static.
     * @param isStatic True for static, false for dynamic.
     */
    void SetStatic(bool isStatic) { mStatic = isStatic; }

    void SetTransform(const b2Vec2& location, double angle);
};

#endif //ANGRYSPARTY_PHYSICALOBJECT_H