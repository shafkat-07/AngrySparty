/**
 * @file Goalpost.h
 * @author Western Tanager
 *
 * The goalpost class for the Angry Sparty game.
 *
 * The goalpost can launch angry sparties at the foes.
 */


#ifndef ANGRYSPARTY_GOALPOST_H
#define ANGRYSPARTY_GOALPOST_H

#include "Shooter.h"

/**
 * The goalpost class for the Angry Sparty game.
 *
 * The goalpost can launch angry sparties at the foes.
 */
class Goalpost : public Shooter
{
private:


public:
    Goalpost(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void XmlLoad(wxXmlNode* node) override;
    void Update(double elapsed) override;

    void LaunchSparty() override;
};

#endif //ANGRYSPARTY_GOALPOST_H
