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

xcb_window_t XCBConn::create_window(int screenNum, int x, int y, int width, int height) {
    if (screenNum > screens.size()) {
        debug.error("attempted to create window on nonexistent screen");

        return -1;
    }

    // create new window on given screen, map & flush

    uint32_t eventmask = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_FOCUS_CHANGE | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE;

    uint32_t valuelist[] = { eventmask };

    uint32_t valuemask = XCB_CW_EVENT_MASK;

    xcb_screen_t screen = screens[screenNum];

    xcb_window_t window = xcb_generate_id(connection);

    xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen.root, x, y, width, height, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen.root_visual, valuemask, valuelist);

    xcb_map_window(connection, window);

    xcb_flush(connection);

    return window;
}