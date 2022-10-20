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
class Shooter : public Item
{
private:
    double mWidth = 0; ///< Width of the shooter
    double mHeight = 0; ///< Height of the shooter
    b2Vec2 mPosition = b2Vec2(0, 0); ///< Position of the shooter

protected:
    /**
     * Returns the width of the shooter
     * @return The width of the shooter
     */
    double GetWidth() const {return mWidth;}

    /**
     * Returns the height of the shooter
     * @return The height of the shooter
     */
    double GetHeight() const {return mHeight;}

    /**
     * Returns the position of the shooter
     * @return The position of the shooter
     */
    b2Vec2 GetPosition() const {return mPosition;}

public:
    Shooter(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void XmlLoad(wxXmlNode* node) override;
};

#endif //ANGRYSPARTY_SHOOTER_H
