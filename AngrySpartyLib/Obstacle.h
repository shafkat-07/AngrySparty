/**
 * @file Obstacle.h
 * @author Western Tanager
 *
 * The class of an obstacle in the Angry Sparty game.
 *
 */

#ifndef ANGRYSPARTY_OBSTACLE_H
#define ANGRYSPARTY_OBSTACLE_H

#include "Item.h"


/**
 * An obstacle in the game
 */
class Obstacle : public Item
{
private:

protected:

public:
    /// Default constructor (disabled)
    Obstacle() = delete;

    /// Copy constructor (disabled)
    Obstacle(const Obstacle &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Obstacle &) = delete;

    /// Constructor for Obstacle
    Obstacle(Level *level);

    void Update(double elapsed) override;

    wxXmlNode* XmlSave(wxXmlNode* node) override;

    void XmlLoad(wxXmlNode* node) override;

};

#endif //ANGRYSPARTY_OBSTACLE_H