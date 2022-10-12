/**
 * @file Level.cpp
 * @author Vetri Vijay
 */

#include "Level.h"

/**
 * Loads a specified XML file into the level
 * @param filename The location of the XML file on disk
 */
void Level::Load(const std::string& filename)
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

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"item")
        {
            XmlItem(child);
        }
    }
}

/**
 * Clears the Items from the level
 */
void Level::Clear()
{
//    mItems.clear(); //TODO Uncomment this after Item is added
}

/**
 * Handles the XML node coming into the level, passes it to the items
 * @param node XML node
 */
void Level::XmlItem(wxXmlNode *node)
{

}

/**
 * Constructor for the level, requires an XML file path
 * @param filename Path to the XML file
 */
Level::Level(const std::string& filename)
{
    Load(filename);
}

/**
 * Handles drawing the items from the level on GameView
 * @param dc The wxDC object to write to
 */
void Level::OnDraw(wxDC* dc)
{
    //TODO Uncomment this after Item is added
//    for(auto each_item : mItems){
//        each_item->Draw(dc);
//    }
}
