#ifndef xcb_h
#define xcb_h

#include <vector>

#include <xcb/xcb.h>

struct XCBConn {
    // Member Variables

    int defaultScreen = 0;
    
    xcb_connection_t* connection = nullptr;

    std::vector<xcb_screen_t> screens;

    // Constructors & Destructors

    XCBConn();
    ~XCBConn();

    // Member Functions

    xcb_window_t create_window(int screenNum, int x, int y, int width, int height);
};

extern XCBConn display;

#endif
