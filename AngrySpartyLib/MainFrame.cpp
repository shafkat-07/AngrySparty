/**
 * @file MainFrame.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "ids.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Game",
            wxDefaultPosition,  wxSize( 1100,700 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    mGameView = new GameView();
    mGameView->Initialize(this);

    // Add it to the sizer
    sizer->Add(mGameView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu();
//    auto ringMenu = new wxMenu();
    auto viewMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    fileMenu->Append(wxID_EXIT, L"&Exit\tAlt-X", "Quit this program");
    levelMenu->Append(LEVEL_0, L"&Level 0", "Go to level 0");
    levelMenu->Append(LEVEL_1, L"&Level 1", "Go to level 1");
    levelMenu->Append(LEVEL_2, L"&Level 2", "Go to level 2");
    levelMenu->Append(LEVEL_3, L"&Level 3", "Go to level 3");
//    ringMenu->Append(IDM_RING, "&Activate The Ring", "Enable to activate the 2x speed booster ring", wxITEM_CHECK);
    viewMenu->Append(IDM_DEBUG_VIEW, L"&Debug View", "Enable to see box2d outlines", wxITEM_CHECK);
    helpMenu->Append(wxID_ABOUT, L"&About\tF1", "Show about dialog");

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Level" );
//    menuBar->Append(ringMenu, L"&The Ring" );
    menuBar->Append(viewMenu, L"&View" );
    menuBar->Append(helpMenu, L"&Help");

    SetMenuBar( menuBar );

    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

    // Binding Exit and About event handlers
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
}

/**
 * Exit menu option handler
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * About menu option handler
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Angry Sparty",
            L"About Angry Sparty",
            wxOK,
            this);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mGameView->Stop();
    Destroy();
}