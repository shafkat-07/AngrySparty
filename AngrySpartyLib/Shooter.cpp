/**
 * @file Shooter.cpp
 * @author Western Tanager
 *
 * The function definitions for the shooter class.
 */

#include "pch.h"

#include <b2_fixture.h>
#include <cmath>

#include "Shooter.h"
#include "Consts.h"
#include "Sparty.h"
#include "Level.h"
#include "KillFoeVisitor.h"

using namespace std;

/// Velocity below which a Sparty is considered as still
const float VelocityTolerance = 0.01f;

/// Points awarded per Foe eliminated
const int PointsPerKill = 100;

/// The velocity boost that the sparty gets when it collides with a ring.
const float RingBoost = 5.0f;

/**
 * Constructor for a shooter object
 *
 * Initiates the shooter.
 * @param level The level this item is contained in
 */
Shooter::Shooter(Level* level) : Item(level)
{
}

/**
 * Draw a shooter
 *
 * @param graphics
 */
void Shooter::Draw(shared_ptr<wxGraphicsContext> graphics)
{

    graphics->PushState();

    graphics->Translate(mX * Consts::MtoCM,
            mY * Consts::MtoCM);

    // Make this is left side of the rectangle
    double x = -mWidth/2 * Consts::MtoCM;

    // And the top
    double y = mHeight * Consts::MtoCM;

    shared_ptr<wxBitmap> bitmap = GetBitmap();

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
            x,
            0,
            mWidth * Consts::MtoCM, mHeight * Consts::MtoCM);

    graphics->PopState();
}

/**
 *  * Draw the specific shooter.
 * @param graphics The graphics context to draw with.
 * @param AttachShooterBack The back position to attach the band to.
 * @param AttachShooterFront The front position to attach the band to.
 * @param BandColor The color of the band being drawn.
 * @param ShooterBandThickness The thickness of the band being drawn.
 */
void Shooter::DrawSpecificShooter(
        shared_ptr<wxGraphicsContext> graphics,
        const b2Vec2 AttachShooterBack,
        const b2Vec2 AttachShooterFront,
        const wxColor BandColor,
        const int ShooterBandThickness
        )
{
    graphics->PushState();
    wxPen pen(BandColor, ShooterBandThickness);

    graphics->Translate(mX * Consts::MtoCM,
            mY * Consts::MtoCM);

    // Make this is left side of the rectangle
    double x = -mWidth/2 * Consts::MtoCM;

    // And the top
    double y = mHeight * Consts::MtoCM;

    if (mSparty == nullptr)
    {
        // Draw the band of the shooter.
        graphics->Scale(1, -1);
        graphics->SetPen(pen);
        graphics->StrokeLine(
                AttachShooterBack.x * Consts::MtoCM,
                -AttachShooterBack.y * Consts::MtoCM,
                AttachShooterFront.x * Consts::MtoCM,
                -AttachShooterFront.y * Consts::MtoCM
        );
    }
    else if (mLaunched)
    {
        // Draw the band of the shooter.
        graphics->Scale(1, -1);
        graphics->SetPen(pen);
        graphics->StrokeLine(
                AttachShooterBack.x * Consts::MtoCM,
                -AttachShooterBack.y * Consts::MtoCM,
                AttachShooterFront.x * Consts::MtoCM,
                -AttachShooterFront.y * Consts::MtoCM
        );
        // Draw the sparty
        graphics->PopState();
        mSparty->Draw(graphics);
        graphics->PushState();
        // Return the graphics context to the state it was in.
        graphics->Translate(mX*Consts::MtoCM,
                mY*Consts::MtoCM);
        graphics->Scale(1, -1);
        graphics->SetPen(pen);
    }
    else
    {
        auto spartyPosition = mSparty->GetBodyPosition();
        // Compensate for graphics translation.
        spartyPosition.x -= GetX();
        spartyPosition.y -= GetY();
        // Draw the back of the band
        graphics->Scale(1, -1);
        graphics->SetPen(pen);
        graphics->StrokeLine(
                AttachShooterBack.x * Consts::MtoCM,
                -AttachShooterBack.y * Consts::MtoCM,
                spartyPosition.x * Consts::MtoCM,
                -spartyPosition.y * Consts::MtoCM
        );
        // Draw the Sparty
        // Must have a fresh state for graphics or else sparty won't draw.
        graphics->PopState();
        mSparty->Draw(graphics);
        graphics->PushState();

        // Return the graphics context to the state it was in.
        graphics->Translate(mX*Consts::MtoCM,
                mY*Consts::MtoCM);
        graphics->Scale(1, -1);
        graphics->SetPen(pen);

        // Draw the cross section of the band.
        graphics->StrokeLine(
                spartyPosition.x * Consts::MtoCM,
                -spartyPosition.y * Consts::MtoCM,
                spartyPosition.x * Consts::MtoCM - ((mSparty->GetRadius() * Consts::MtoCM) / 2),
                -spartyPosition.y * Consts::MtoCM
        );
        // Draw the front of the band
        graphics->StrokeLine(
                spartyPosition.x * Consts::MtoCM,
                -spartyPosition.y * Consts::MtoCM,
                AttachShooterFront.x * Consts::MtoCM,
                -AttachShooterFront.y * Consts::MtoCM
        );
    }

    // Draw the front of the shooter.
    auto bitmap = mFrontBitmap;
    graphics->Translate(0, -y);
    graphics->DrawBitmap(*bitmap,
            x,
            0,
            mWidth * Consts::MtoCM, mHeight * Consts::MtoCM);

    graphics->PopState();
}

/**
 * Load the XML according to the shooter type.
 * @param node XML node to load from.
 */
void Shooter::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    // Get the attributes for this item
    node->GetAttribute(L"x", L"0.0").ToDouble(&mX);
    node->GetAttribute(L"y", L"0.0").ToDouble(&mY);

    auto name = L"images/" + node->GetName() + L"-front.png";
    mFrontImage = make_shared<wxImage>(name);
    mFrontBitmap = make_shared<wxBitmap>(*mFrontImage);
}

/**
 * Update the Shooter.
 * @param elapsed time elapsed since last clock tick.
 */
void Shooter::Update(double elapsed)
{
    if (mSparty == nullptr && GetLevel()->GetSpartiesLeft() != 0)
    {
        mSparty = GetLevel()->GetSparty();
        mSparty->ModifyBodyToDynamic();
    }
    else if (mLaunched)
    {
        // Get the current velocity from the launched sparty
        auto velocity = mSparty->GetBody()->GetLinearVelocity();
        auto hit = GetLevel()->GetRing()->SpartyHitRingTest(
                mSparty->GetBodyPosition().x,
                mSparty->GetBodyPosition().y,
                mSparty->GetRadius()
        );
        if (abs(velocity.x) < VelocityTolerance && abs(velocity.y) < VelocityTolerance)
        {
            GetWorld()->DestroyBody(mSparty->GetBody());
            mSparty->SetAlive(false);
            GetLevel()->ReduceSpartiesLeft();
            GetLevel()->IncrementSpartyIndex();
            mSparty = nullptr;
            mLaunched = false;
            mLoaded = false;
            KillDownedEnemies();
            // Recursive call to update the next sparty to load.
            Shooter::Update(elapsed);
        }
        else if (hit && !mSparty->GetBoosted())
        {
            mSparty->GetBody()->SetLinearVelocity(b2Vec2(velocity.x * RingBoost, velocity.y * RingBoost));
            // Set the boosted parameter so that the sparty doesn't get boosted again.
            mSparty->SetBoosted(true);
        }
    }
}

/**
 * Launch a sparty according to which type it is and what shooter is being used.
 * @param AttachShooterBack The vector of the back of the shooter.
 * @param AttachShooterFront The vector of the front of the shooter.
 */
void Shooter::LaunchSpecificSparty(
        const b2Vec2 AttachShooterBack,
        const b2Vec2 AttachShooterFront
        )
{
    const b2Vec2 centerPos = b2Vec2(GetX(),
                    (AttachShooterFront.y + AttachShooterBack.y) / 2 +
                    mSparty->GetRadius()
    );

    if (mSparty != nullptr)
    {
        // Get the angle and distance between the shooter and the sparty
        auto distance = mSparty->DistanceBetweenBodies(centerPos);
        double angle = mSparty->AngleBetweenBodies(centerPos);

        // Make the sparty movable
        mSparty->GetBody()->SetFixedRotation(false);
        mSparty->GetBody()->SetGravityScale(1.0f);
        // Set the sparty's velocity based on the angle and distance pulled back.
        auto velocityFactor = mSparty->GetVelocityFactor();
        mSparty->GetBody()->SetLinearVelocity(
                b2Vec2(
                        cos(angle) * distance * velocityFactor,
                        sin(angle) * distance * velocityFactor
                        ));

        // Set the sparty to not be loaded, but launched.
        mLoaded = false;
        mLaunched = true;
    }
}

/**
 * Update this specific shooter
 * @param AttachShooterBack The vector of the back of the shooter.
 * @param AttachShooterFront The vector of the front of the shooter.
 * @param MaxNegativePullAngle The maximum negative angle the shooter can pull back.
 * @param MinPositivePullAngle The maximum positive angle the shooter can pull back.
 * @param MaxPull The maximum distance the shooter can pull back.
 */
void Shooter::UpdateSpecificShooter(
        const b2Vec2 AttachShooterBack,
        const b2Vec2 AttachShooterFront,
        const double MaxNegativePullAngle,
        const double MinPositivePullAngle,
        const double MaxPull
        )
{
    if (GetLevel()->GetSpartiesLeft() == 0)
    {
        return;
    }
    const b2Vec2 centerPos = b2Vec2(GetX(),
                    (AttachShooterFront.y + AttachShooterBack.y) / 2 +
                    mSparty->GetRadius()
    );
    if (mSparty != nullptr && !mLoaded)
    {
        // Set the sparty position to the center of the shooter.
        mSparty->SetTransform(centerPos, 0.0f);
        mLoaded = true;
    }
}

/**
 * Resets the shooter to its default state
 */
void Shooter::Reset()
{
    mLoaded = false;
    mLaunched = false;
    mSparty = nullptr;

    Item::Reset();
}

/**
 * Kill the enemies that have been downed.
 */
void Shooter::KillDownedEnemies()
{
    KillFoeVisitor visitor;
    GetLevel()->Accept(&visitor);
    int totalKills = visitor.GetTotalKills();
    GetLevel()->UpdateScore(totalKills * PointsPerKill);
}

/**
 * Compute a location based on the center of this slingshot
 * @param x The x location to be used in the computation (from the mouse)
 * @param y The y location to be used in the computation (from the mouse)
 * @param AttachShooterBack The vector of the back of the shooter.
 * @param AttachShooterFront The vector of the front of the shooter.
 * @param MaxNegativePullAngle The maximum negative angle the shooter can pull back.
 * @param MinPositivePullAngle The minimum positive angle the shooter can pull back.
 * @param MaxPull The maximum distance the shooter can pull back.
 * @return The computed location
 */
b2Vec2 Shooter::ComputeSpecificLocation(
        double x,
        double y,
        const b2Vec2 AttachShooterBack,
        const b2Vec2 AttachShooterFront,
        const double MaxNegativePullAngle,
        const double MinPositivePullAngle,
        const double MaxPull
        )
{
    auto slingOriginX = mX;
    auto slingOriginY = (AttachShooterFront.y + AttachShooterBack.y) / 2 + mSparty->GetRadius();

    auto computedDistance = sqrt(pow((x - slingOriginX),2) +
            pow((y - slingOriginY),2));
    double finalDistance = min(computedDistance, MaxPull);

    auto computedAngle = atan2(y - slingOriginY, x - slingOriginX);

    double finalAngle;
    if (computedAngle >= 0)
    {
        finalAngle = max(computedAngle, MinPositivePullAngle);
    }
    else
    {
        finalAngle = min(computedAngle, MaxNegativePullAngle);
    }

    b2Vec2 computedLocation = b2Vec2(finalDistance * cos(finalAngle) + slingOriginX,
            finalDistance * sin(finalAngle) + slingOriginY);

    return computedLocation;
}
