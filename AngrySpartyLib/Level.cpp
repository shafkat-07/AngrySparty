/**
 * @file Level.cpp
 * @author Western Tanager
 *
 * The level class will load the level from an XML file and display it on the screen.
 */

#include "pch.h"

#include "Level.h"
#include "Background.h"
#include "Block.h"
#include "Foe.h"
#include "Slingshot.h"
#include "Goalpost.h"
#include "Poly.h"
#include "Sparty.h"

using namespace std;

/// Gravity in meters per second per second
const float Gravity = -9.8f;

/// Number of velocity update iterations per step
const int VelocityIterations = 6;

/// Number of position update iterations per step
const int PositionIterations = 2;

/**
 * Loads a specified XML file into the level
 * @param filename The location of the XML file on disk
 */
void Level::Load(const std::wstring &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Level file");
        return;
    }

    Clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();
    mSize.x = stof(root->GetAttribute(L"width", "0.0").ToStdWstring());
    mSize.y = stof(root->GetAttribute(L"height", "0.0").ToStdWstring());

    //
    // Traverse the children of the root
    // node of the XML document in memory
    //

    // Traverse the items tag first
    auto child = root->GetChildren();
    auto grandChild = child->GetChildren();
    for ( ; grandChild; grandChild = grandChild->GetNext())
    {
        XmlItem(grandChild);
    }

    // Traverse the angry tag
    child = child->GetNext();
    grandChild = child->GetChildren();
    for ( ; grandChild; grandChild = grandChild->GetNext())
    {
        XmlItem(grandChild);
    }
    TransferSpartiesToShooter();
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Level::XmlItem(wxXmlNode *node)
{
    // A pointer for the item we are loading
    shared_ptr<Item> item;

    // We have an item. What type?
    auto type = node->GetName();
    if (type == "background")
    {
        item = make_shared<Background>(this);
    }
    else if (type == "block")
    {
        item = make_shared<Block>(this);
    }
    else if (type == "poly")
    {
        item = make_shared<Poly>(this);
    }
    else if (type == "foe")
    {
        item = make_shared<Foe>(this);
    }
    else if (type == "slingshot")
    {
        item = make_shared<Slingshot>(this);
        mShooterIndex = mItems.size();
    }
    else if (type == "goalposts")
    {
        item = make_shared<Goalpost>(this);
        mShooterIndex = mItems.size();
    }
    else if (type == "gruff-sparty" || type == "helmet-sparty")
    {
        auto spartyItem = make_shared<Sparty>(this);
        spartyItem->XmlLoad(node);
        mSpartyCount++;
        mSparties.push_back(spartyItem);
        return;
    }
    else
    {
        //wxMessageBox(L"Unknown item type: " + type);
        return;
    }

    if (item != nullptr)
    {
        item->XmlLoad(node);
        // The sand image needs to be behind the shooter for the sparties to load properly.
        if (node->GetAttribute("image", "") == "sand.png")
        {
            mItems.insert(mItems.begin()+1, item);
            mShooterIndex++;
        }
        else
        {
            mItems.push_back(item);
        }
    }
}

/**
 * Send the Sparties down to the shooter for handling of drawing and physics
 */
void Level::TransferSpartiesToShooter()
{
    mItems[mShooterIndex]->SetSparties(mSparties);
}

/**
 * Launch the sparty that was loaded.
 */
void Level::LaunchSparty()
{
    mItems[mShooterIndex]->LaunchSparty();
}

/**
 * Clears the Items from the level
 */
void Level::Clear()
{
    // Sync the clear with the Shooter.
    if (mShooterIndex >= 0)
    {
        mItems[mShooterIndex]->Clear();
    }
    // Clean up items in this level.
    mItems.clear();
    mSparties.clear();
}

/**
 * Constructor for the level, requires an XML file path
 * @param filename Path to the XML file
 */
Level::Level(const std::wstring &filename)
{
    Load(filename); // Load from XML first to have playing area dimensions
}

/**
 * Handles drawing the items from the level on GameView
 * @param graphics The wxGraphicsContext object to write to
 */
void Level::OnDraw(shared_ptr<wxGraphicsContext> graphics)
{
    for(auto item : mItems)
    {
        item->Draw(graphics);
    }
}


/**
 * Handles the mouse down event
 * @param x X coordinate of the mouse
 * @param y Y coordinate of the mouse
 * @return True if the mouse down event hit anything.
 */
shared_ptr<Item> Level::HitTest(double x, double y)
{
    // TODO Comment out this first loop to disable user grabbing blocks
    for(auto item : mItems){
        if (item->IsAlive())
        {
            if(item->HitTest(x,y))
            {
                return item;
            }
        }
    }

    for(auto sparty : mSparties){
        if (sparty->IsAlive())
        {
            if (sparty->HitTest(x, y))
            {
                return sparty;
            }
        }
    }
    return nullptr;
}

/**
 * Accept a visitor and handle the visit.
 * @param visitor The visitor to accept.
 */
void Level::Accept(ItemVisitor* visitor)
{
    for(auto item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
 * Sets up a level and its items in a physics world,
 * setting all of the items to alive
 */
void Level::SetLevel()
{
    mPhysics = make_shared<World>(mSize);

    // Install in all the items
    for(auto item: mItems)
    {
        item->SetAlive(true);
        item->InstallPhysics(mPhysics);
    }
    // Do the same for the sparties
    for (auto sparty : mSparties)
    {
        sparty->SetAlive(true);
        sparty->InstallPhysics(mPhysics);
    }


    // Anything else needed to start the level
}

/**
 * Resets a level to its default state
 *
 * Uninstalls physics for each item,
 * sets them to "dead", and resets the score
 */
void Level::ResetLevel()
{
    for (auto item : mItems)
    {
        item->Reset();
    }

    for (auto sparty : mSparties)
    {
        sparty->Reset();
    }

    mPhysics = nullptr;
    mScore = 0;
}

/**
 * Update the level
 * @param elapsed The time elapsed since the last update
 */
void Level::Update(double elapsed)
{
    for (auto item : mItems)
    {
        item->Update(elapsed);
    }
    mPhysics->GetWorld()->Step(elapsed, VelocityIterations, PositionIterations);
}
