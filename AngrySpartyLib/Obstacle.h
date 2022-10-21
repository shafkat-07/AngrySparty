/**
 * @file Obstacle.h
 * @author Western Tanager
 *
 * The class of an obstacle in the Angry Sparty game.
 *
 */

#ifndef ANGRYSPARTY_OBSTACLE_H
#define ANGRYSPARTY_OBSTACLE_H

#include "PhysicalObject.h"

/**
 * An obstacle in the game
 */
class Obstacle : public PhysicalObject
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
    Obstacle(Level *level, const std::wstring& filename);

    void Update(double elapsed) override;

    wxXmlNode* XmlSave(wxXmlNode* node) override;

    void XmlLoad(wxXmlNode* node) override;

    bool HitTest(double x, double y) override;
};

#endif //ANGRYSPARTY_OBSTACLE_H