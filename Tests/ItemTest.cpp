/**
 * @file TestItem.cpp
 * @author Brendan Bushbaker
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
};

TEST(ItemTest, Construct)
{
    Level level(filename);
    ItemMock item(&level);
}