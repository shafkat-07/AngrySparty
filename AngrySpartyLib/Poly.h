/**
 * @file Poly.h
 * @author kabir
 *
 *
 */

#pragma once

#include "Obstacle.h"

class Poly : public Obstacle {
private:

public:
    Poly(Level *level, const std::wstring& filename);
};
