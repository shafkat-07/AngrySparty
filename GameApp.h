/**
 * @file GameApp.h
 * @author Juan Camilo Sabogal Olarte
 *
 * Main application class
 */

#ifndef ANGRYSPARTAN_GAMEAPP_H
#define ANGRYSPARTAN_GAMEAPP_H


#include <wx/wx.h>

/**
 * Main application class
 */
class GameApp : public wxApp {
public:
    bool OnInit() override;
};

#endif //ANGRYSPARTAN_GAMEAPP_H
