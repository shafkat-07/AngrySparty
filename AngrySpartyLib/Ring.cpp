/**
 * @file Ring.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include <random>
#include "Ring.h"
#include "Level.h"
#include "Consts.h"

using namespace std;

/// The ratio between the ring's radius and the level size
const double RingRadiusRatio = 0.075;

/// Maximum speed in the Y direction in
/// in pixels per second for the Ring
const double RingMaxSpeedY = 2.1;

/// Minimum speed in the Y direction in
/// pixels per second for the Ring
const double RingMinSpeedY = 2;

/// Distance from the edge of the screen
/// to flip the direction of the motion
const double MetersToEdge = 0.05;

/// Number of degrees that the ring rotates at
/// every frame
const double DegreesPerFrame = 3;

/// Ring filename
const wstring RingFileName = L"images/ring.png";

/**
 * Constructor for a ring
 *
 * @param level The level this ring is contained in
 */
 Ring::Ring(Level* level) : Item(level)
{
    mRadius = GetLevel()->GetSize().y * RingRadiusRatio;
    mX = -GetLevel()->GetSize().x / 5;
    mRingImage = make_unique<wxImage>(RingFileName, wxBITMAP_TYPE_ANY);
    mRingBitmap = make_unique<wxBitmap>(*mRingImage);
    mY = GetLevel()->GetSize().y/2; // Inital ring position
    uniform_real_distribution<> distribution(RingMinSpeedY, RingMaxSpeedY);
    mSpeedY = distribution(level->GetRandom());
}

void Ring::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    // Physical object common attributes
    mX = stof(node->GetAttribute(L"x", "-10.0").ToStdWstring());
}

/**
 * Handle updates in time for the Ring
 *
 * This is called before we draw and allows us to
 * move our ring. We increase its speed by 10% every
 * update until it reaches the max speed for the Ring,
 * where it will reset to the minimum speed for the Ring
 * taking into account it's direction.
 * @param elapsed Time elapsed since the class call
 */
void Ring::Update(double elapsed)
{
    mY += mSpeedY * elapsed;

    // Reversing the ring in the Y direction
    if (mSpeedY > 0 && mY + mRadius + MetersToEdge >= GetLevel()->GetSize().y / 2 ||
        mSpeedY < 0 && mY - mRadius - MetersToEdge < 0)
    {
        mSpeedY = -mSpeedY;
    }

    mAngle += DegreesPerFrame * Consts::DtoR;
}

/**
 * Draw the ring
 * @param graphics The graphics context to draw on
 */
void Ring::Draw(shared_ptr<wxGraphicsContext> graphics)
{
    auto wid = mRadius * Consts::MtoCM * 2;

    shared_ptr<wxBitmap> bitmap = GetBitmap();

    graphics->PushState();
    graphics->Translate(mX * Consts::MtoCM, mY * Consts::MtoCM);
    graphics->Rotate(mAngle);
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
            -wid/2,
            -wid/2,
            wid, wid);
    graphics->PopState();

    std::cout << mAngle << '\n';
}

/**
 * Resets the ring
 *
 * Sets it back to the middle of the screen and
 * assigns it a new speed randomly
 */
void Ring::Reset()
{
    mY = GetLevel()->GetSize().y/2; // Inital ring position
    uniform_real_distribution<> distribution(RingMinSpeedY, RingMaxSpeedY);
    mSpeedY = distribution(GetLevel()->GetRandom());
}

/**
 * Compute the distance between 2 points
 * @param x1 x-coordinate of point 1
 * @param y1 y-coordinate of point 1
 * @param x2 x-coordinate of point 2
 * @param y2 y-coordinate of point 2
 * @return Computed distance
 */
double Distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow((x1-x2),2) + pow((y1-y2),2));
}

/**
 * Test if the sparty's underlying circle touches
 * the ring's underlying circle
 * @param spartyX The x position of the sparty
 * @param spartyY The y position of the sparty
 * @param spartyRadius The radius of the sparty
 * @return True if the sparty touches the ring
 */
bool Ring::SpartyHitRingTest(double spartyX, double spartyY, double spartyRadius)
{
    if (!IsAlive())
    {
        return false;
    }
    double distance = Distance(spartyX, spartyY, mX, mY);
    double sumOfRadii = spartyRadius + mRadius;
    return distance < sumOfRadii;
}
