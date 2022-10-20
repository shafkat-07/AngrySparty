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
    double mWidth = 0; ///< Width of the shooter
    double mHeight = 0; ///< Height of the shooter
    b2Vec2 mPosition = b2Vec2(0, 0); ///< Position of the shooter
public:
    Shooter(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void XmlLoad(wxXmlNode* node) override;
};

#endif //ANGRYSPARTY_SHOOTER_H
