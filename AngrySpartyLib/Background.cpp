/**
 * @file Background.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include "Background.h"
#include "Consts.h"
#include "Level.h"

/// Background filename
const std::wstring BackgroundImageName = L"images/background1.png";

/**
 * Constructor for a background item
 *
 * Does not contain any physics
 * @param level The level this item is contained in
 */
Background::Background(Level* level) : Item(level, BackgroundImageName)
{

}

/**
 * Draw the background.
 * @param graphics The drawing context to draw on.
 */
void Background::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    auto wid = GetWidth() * Consts::MtoCM;
    auto hit = GetHeight() * Consts::MtoCM;

    std::shared_ptr<wxBitmap> bitmap = std::make_shared<wxBitmap>(*GetPicture());

    graphics->PushState();
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
            -wid/2,
            -hit,
            wid, hit);
    graphics->PopState();

}