/**
 * @file Slingshot.h
 * @author brend
 *
 *
 */

#ifndef ANGRYSPARTY_SLINGSHOT_H
#define ANGRYSPARTY_SLINGSHOT_H

#include "Shooter.h"

class Slingshot : public Shooter
{
private:
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

public:
    Slingshot(Level* level);
};

};

#endif //ANGRYSPARTY_SLINGSHOT_H
