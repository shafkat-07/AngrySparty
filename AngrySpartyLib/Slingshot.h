/**
 * @file Slingshot.h
 * @author Western Tanager
 *
 * The slingshot class for the Angry Sparty game.
 *
 * The slingshot can launch angry sparties at the foes.
 */

#ifndef ANGRYSPARTY_SLINGSHOT_H
#define ANGRYSPARTY_SLINGSHOT_H

#include "Shooter.h"

/**
 * The slingshot class for the Angry Sparty game.
 *
 * The slingshot can launch angry sparties at the foes.
 */
class Slingshot : public Shooter
{
private:


public:
    Slingshot(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void XmlLoad(wxXmlNode* node) override;

    void Update(double elapsed) override;
};

#endif //ANGRYSPARTY_SLINGSHOT_H
