/**
 * @file ItemTest.cpp
 * @author Western Tanager
 *
 * Test the item class for the Angry Sparty game.
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Level.h>

const std::wstring filename = L"levels/level0.xml";

const std::wstring image = L"images/elementWood015.png";

///** Mock class for testing the class Item */
class ItemMock : public Item
{
private:
    Level *mLevel;
public:
    ItemMock(Level *level) : Item(level) { mLevel = level; }
    void Update(double elapsed) override {}
    void Accept(ItemVisitor* visitor) override {}
};

TEST(ItemTest, Construct)
{
    Level level(filename);
    ItemMock item(&level);

    ASSERT_TRUE(item.GetLevel() == &level);
}

TEST(ItemTest, HitTest)
{
    Level level(filename);
    ItemMock item(&level);

    // Test the hit test function
    ASSERT_FALSE(item.HitTest(1,1));   // Random point, items should always return false unless overridden.
}