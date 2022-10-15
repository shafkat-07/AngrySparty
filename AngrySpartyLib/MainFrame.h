/**
 * @file MainFrame.h
 * @author Western Tanager
 *
 * The top-level (main) frame of the application
 */

#ifndef ANGRYSPARTY_MAINFRAME_H
#define ANGRYSPARTY_MAINFRAME_H

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:

public:
    void Initialize();
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

#endif //ANGRYSPARTY_MAINFRAME_H
