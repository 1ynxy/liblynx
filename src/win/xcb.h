#ifndef xcb_h
#define xcb_h

#include <string>
#include <vector>

#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>

#include <xcb/xcb.h>

#include <GL/glx.h>
#include <GL/gl.h>

struct XCBConn {
    // Member Variables

    int defaultScreen = 0;
    
    xcb_connection_t* connection = nullptr;

    std::vector<xcb_screen_t> screens;

    // Constructors & Destructors

    XCBConn();
    ~XCBConn();

    // Member Functions

    xcb_window_t create_window(int screenNum, int x, int y, int width, int height, std::string name);
};

extern XCBConn display;

#endif
