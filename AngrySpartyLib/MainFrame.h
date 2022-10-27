/**
 * @file MainFrame.h
 * @author Western Tanager
 *
 * The top-level (main) frame of the application
 */

#ifndef ANGRYSPARTY_MAINFRAME_H
#define ANGRYSPARTY_MAINFRAME_H

class GameView;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:
    /// View class for our project
    GameView *mGameView;

public:
    void Initialize();
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
};

#endif //ANGRYSPARTY_MAINFRAME_H
