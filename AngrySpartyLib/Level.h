/**
 * @file Level.h
 * @author Vetri Vijay
 *
 * Contains all the items for a level
 *
 */

#ifndef ANGRYSPARTY_LEVEL_H
#define ANGRYSPARTY_LEVEL_H

//TODO Remove wx headers after pch.h is configured
#include <wx/wx.h>
#include <wx/string.h>
#include <wx/xml/xml.h>
#include <wx/dc.h>

#include <vector>
#include <memory>

/**
 * This class represents a level with it's own score and item collection
 */
class Level {
private:
    // The main vector of pointers to the items for each level
//    std::vector<std::shared_ptr<Item>> mItems; //TODO Uncomment after Item is added

    /// Score tracking for each level
    int mScore = 0;
public:
    Level(const std::string&);
    void Load(const std::string&);
    void Clear();
    void XmlItem(wxXmlNode* node);
    void OnDraw(wxDC * dc);

    /**
     * Getter for the score from this level
     * @return Score
     */
    int GetScore() const {return mScore;}

    /**
     * Updates the score by incrementing with the parameter (can be negative)
     * @param score The parameter to increment by (can be negative)
     */
    void UpdateScore(int score) {mScore += score;}
};

#endif //ANGRYSPARTY_LEVEL_H
