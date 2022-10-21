/**
 * @file Poly.cpp
 * @author kabir
 */

#include "Poly.h"

/**
 * Constructor
 * @param level The level this item is a member of
 * @param filename The filename for the image to use
 */
Poly::Poly(Level *level, const std::wstring& filename) : Obstacle(level, filename)
{
}