#include "xcb.h"

#include "../dir/debug.h"

XCBConn display;

// Constructors & Destructors

XCBConn::XCBConn() {
    // open connection to xserver on default display

    connection = xcb_connect(NULL, &defaultScreen);

    if (xcb_connection_has_error(connection) > 0) {
        debug.error("failed to open default display");

        return;
    }

    // get connection information && screen iterator

    const xcb_setup_t* setup = xcb_get_setup(connection);

    xcb_screen_iterator_t screenIter = xcb_setup_roots_iterator(setup);

    for (int i = 0; i < screenIter.rem; i++) screens.push_back(screenIter.data[i]);

    debug.info("opened x11 connection to default display with " + std::to_string(screens.size())+ " screen(s)");
}

XCBConn::~XCBConn() {
    // exit

    xcb_disconnect(connection);

    debug.info("closed x11 connection");
}

// Member Functions

xcb_window_t XCBConn::create_window(int screenNum, int x, int y, int width, int height, std::string name) {
    if (screenNum > screens.size()) {
        debug.error("attempted to create window on nonexistent screen");

        return -1;
    }

    xcb_screen_t screen = screens[screenNum];

    // setup window values

    uint32_t eventmask = XCB_EVENT_MASK_EXPOSURE 
                        | XCB_EVENT_MASK_FOCUS_CHANGE 
                        | XCB_EVENT_MASK_KEY_PRESS 
                        | XCB_EVENT_MASK_KEY_RELEASE 
                        | XCB_EVENT_MASK_BUTTON_PRESS 
                        | XCB_EVENT_MASK_BUTTON_RELEASE 
                        | XCB_EVENT_MASK_ENTER_WINDOW 
                        | XCB_EVENT_MASK_LEAVE_WINDOW 
                        | XCB_EVENT_MASK_POINTER_MOTION;

    uint32_t valuelist[] = { eventmask };

    uint32_t valuemask = XCB_CW_EVENT_MASK;

    // create new window on given screen

    xcb_window_t window = xcb_generate_id(connection);

    xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen.root, x, y, width, height, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen.root_visual, valuemask, valuelist);

    // configure

    xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, name.size(), name.c_str());

    // map & flush buffer

    xcb_map_window(connection, window);

    xcb_flush(connection);

    return window;
}