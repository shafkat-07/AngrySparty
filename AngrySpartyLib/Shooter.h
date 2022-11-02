/**
 * @file Shooter.h
 * @author Western Tanager
 *
 * The shooter class of the game.
 *
 * Can shoot angry sparties towards the enemies.
 */

#ifndef ANGRYSPARTY_SHOOTER_H
#define ANGRYSPARTY_SHOOTER_H

#include "Item.h"
#include "ItemVisitor.h"
#include "Level.h"

class Sparty;

/**
 * The shooter class of the game.
 *
 * Can shoot angry sparties towards the enemies.
 */
class Shooter : public Item {
private:
    double mX = 0; ///< X location of the shooter
    double mY = 0; ///< Y location of the shooter
    double mWidth = 0; ///< Width of the shooter
    double mHeight = 0; ///< Height of the shooter
    bool mLoaded = false; ///< If the shooter is currently loaded.
    bool mLaunched = false; ///< If the shooter has launched its sparty.
    std::shared_ptr<wxImage> mFrontImage; ///< The front image for the shooter
    std::shared_ptr<wxBitmap> mFrontBitmap; ///< The front bitmap for the shooter
    int mSpartyIndex = 0; ///< Tracks the current sparty's index in the vector of sparties
    std::shared_ptr<Sparty> mSparty; ///< The sparty currently being shot by the shooter.

public:
    Shooter(Level* level);
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    virtual void XmlLoad(wxXmlNode* node) override;
    void Update(double elapsed) override;
    void Reset() override;
    void KillDownedEnemies();
    void DrawSpecificShooter(
            std::shared_ptr<wxGraphicsContext> graphics,
            const b2Vec2 AttachShooterBack,
            const b2Vec2 AttachShooterFront,
            const wxColor BandColor,
            const int ShooterBandThickness
            );

    void LaunchSpecificSparty(
            const b2Vec2 AttachShooterBack,
            const b2Vec2 AttachShooterFront
    );

    void UpdateSpecificShooter(
            const b2Vec2 AttachShooterBack,
            const b2Vec2 AttachShooterFront,
            const double MaxNegativePullAngle,
            const double MaxPositivePullAngle,
            const double MaxPull
    );

    b2Vec2 ComputeSpecificLocation(
            double x,
            double y,
            const b2Vec2 AttachShooterBack,
            const b2Vec2 AttachShooterFront,
            const double MaxNegativePullAngle,
            const double MinPositivePullAngle,
            const double MaxPull
    );

    /**
     * Get the width of the shooter
     * @return Width of the shooter
     */
    double GetWidth() const {return mWidth;}

    /**
     * Set the width of the shooter
     * @param width The width of the shooter
     */
    void SetWidth(double width) { mWidth = width;}

    /**
     * Get the height of the shooter
     * @return Height of the shooter
     */
    double GetHeight() const {return mHeight;}

    /**
     * Set the height of the shooter
     * @param height The height of the shooter
     */
    void SetHeight(double height) { mHeight = height;}

    /**
     * Get the x position of the shooter
     * @return X position of the shooter
     */
    double GetX() const {return mX;}
    /**
     * Get the y position of the shooter
     * @return Y position of the shooter
     */
    double GetY() const {return mY;}

    /**
     * Whether or not the shooter is loaded
     * @return True if the shooter is loaded
     */
    bool IsLoaded() { return mLoaded; }

    /**
     * Whether or not the shooter has launched
     * @return True if the shooter has launched
     */
    bool IsLaunched() { return mLaunched; }

    /**
     * Sets the shooter's loaded status
     * @param load The shooter's loaded status
     */
    void SetLoaded(bool load) { mLoaded = load; }

    /**
     * Get the pointer to the sparty currently being shot.
     * @return Pointer to the current sparty
     */
    std::shared_ptr<Sparty> GetSparty() {return mSparty;}

    /**
     * The front bitmap for this shooter
     * @return The front wxBitmap for this shooter
     */
    std::shared_ptr<wxBitmap> GetFrontBitmap() { return mFrontBitmap; }

    /**
     * Accept a visitor to this item
     * @param visitor The visitor we accept
     *
     * Does nothing.
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitShooter(this); }

    /**
     * Compute a location based on the center of the shooter
     * @param x The x location to be used in the computation (from the mouse)
     * @param y The y location to be used in the computation (from the mouse)
     * @return The computed location
     */
    virtual b2Vec2 ComputeLocation(double x, double y) { return b2Vec2(0,0); }
};

#endif //ANGRYSPARTY_SHOOTER_H
