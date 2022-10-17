/**
 * @file Background.h
 * @author Western Tanager
 *
 * Class for a background item
 */

#ifndef ANGRYSPARTY_BACKGROUND_H
#define ANGRYSPARTY_BACKGROUND_H

#include "Item.h"

/**
 * Class for a background item
 */
class Background : public Item {
private:

public:
    Background(Level* level);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

};

#endif //ANGRYSPARTY_BACKGROUND_H
