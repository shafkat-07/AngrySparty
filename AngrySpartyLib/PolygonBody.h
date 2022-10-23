/**
 * @file PolygonBody.h
 * @author Western Tanager
 *
 * Class to represent classes that have
 * polygon bodies
 */

#ifndef ANGRYSPARTY_POLYGONBODY_H
#define ANGRYSPARTY_POLYGONBODY_H

#include "PhysicalObject.h"

/**
 * Class to represent classes that have
 * polygon bodies
 *
 * Foe (octagon) and Poly are derived from
 * this class
 */
class PolygonBody : public PhysicalObject {
private:
    std::vector<b2Vec2> mVertices; ///< The vertices that define this polygon body

public:
    PolygonBody(Level *level);
    std::unique_ptr<b2Shape> CreateShape() override;

    /**
     * Get the vertices for this polygon body
     * @return A reference to the vector of vertices
     */
    std::vector<b2Vec2>& GetVertices() { return mVertices; }
};

#endif //ANGRYSPARTY_POLYGONBODY_H