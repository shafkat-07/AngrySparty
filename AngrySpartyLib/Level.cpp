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

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();
    mSize.x = stof(root->GetAttribute(L"width", L"0.0").ToStdWstring());
    mSize.y = stof(root->GetAttribute(L"height", L"0.0").ToStdWstring());

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
    if (type == L"background")
    {
        item = make_shared<Background>(this);
    }
    else if (type == L"block")
    {
        item = make_shared<Block>(this);
    }
    else if (type == L"poly")
    {
        item = make_shared<Poly>(this);
    }
    else if (type == L"foe")
    {
        item = make_shared<Foe>(this);
    }
    else if (type == L"slingshot")
    {
        item = make_shared<Slingshot>(this);
        mShooterIndex = mItems.size();
    }
    else if (type == L"goalposts")
    {
        item = make_shared<Goalpost>(this);
        mShooterIndex = mItems.size();
    }
    else if (type == L"ring")
    {
        item = mRing;
    }
    else if (type == L"gruff-sparty" || type == L"helmet-sparty")
    {
        auto spartyItem = make_shared<Sparty>(this);
        spartyItem->XmlLoad(node);
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
        if (node->GetAttribute(L"image", L"") == L"sand.png")
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
 * Launch the sparty that was loaded.
 */
void Level::LaunchSparty()
{
    mItems[mShooterIndex]->LaunchSparty();
}

/**
 * Constructor for the level, requires an XML file path
 * @param filename Path to the XML file
 */
Level::Level(const std::wstring &filename)
{
    random_device rd; // Seed the random number generator for the ring's speed
    mRandom.seed(rd());
    mRing = make_shared<Ring>(this); // The ring is added if defined in XML
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
        if (item->IsAlive())
        {
            item->Draw(graphics);
        }
    }

    for (auto i = 0; i < mSparties.size(); i++)
    {
        auto sparty = mSparties[i];
        if (sparty->IsAlive() && i != mSpartyIndex)
        {
            sparty->Draw(graphics);
        }
    }
}

/**
 * Test an x,y click location to see if it clicked
 * on a sparty.
 * @param x X coordinate of the mouse
 * @param y Y coordinate of the mouse
 * @return True if the mouse down event hit anything.
 */
shared_ptr<Item> Level::HitTest(double x, double y)
{
    for(auto item : mItems)
    {
        if (item->IsAlive())
        {
            if (item->HitTest(x, y))
            {
                return item;
            }
        }
    }

    for(auto sparty : mSparties)
    {
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
        item->InstallPhysics();
    }
    // Do the same for the sparties
    for (auto sparty : mSparties)
    {
        sparty->SetAlive(true);
        sparty->InstallPhysics();
    }
    mSpartiesLeft = GetTotalSparties(); // Reset to max # of sparties
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

    mRing->Reset();
    mSpartyIndex = -1;
    mPhysics = nullptr;
    mScore = 0;
}

/**
 * Update the level
 * @param elapsed The time elapsed since the last update
 */
void Level::Update(double elapsed)
{
    // Shooter is in charge of updating sparties and everything else
    auto shooter = mItems[mShooterIndex];
    if (shooter->IsAlive())
    {
        shooter->Update(elapsed);
    }

    if (mRing->IsAlive())
    {
        mRing->Update(elapsed);
    }

    mPhysics->Update(elapsed);
}
