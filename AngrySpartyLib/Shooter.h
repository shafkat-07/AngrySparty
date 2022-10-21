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
    double mX = 0; ///< X location of the shooter
    double mY = 0; ///< Y location of the shooter
protected:
    double mWidth = 0; ///< Width of the shooter
    double mHeight = 0; ///< Height of the shooter
public:
    Shooter(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void XmlLoad(wxXmlNode* node) override;

    /**
     * Get the width of the shooter
     * @return Width of the shooter
     */
    double GetWidth() const {return mWidth;}

    /**
     * Get the height of the shooter
     * @return Height of the shooter
     */
    double GetHeight() const {return mHeight;}
    /**
     * Get the x position of the shooter
     * @return X position of the shooter
     */
    double GetX() const {return mX;}
    /**
     * Get the y position of the shooter
     * @return Y position of the shooter
     */
    double GetY() const {return mY;}
};

#endif //ANGRYSPARTY_SHOOTER_H
