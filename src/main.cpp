#include <xcb/xcb.h>

#include "dir/file.h"
#include "dir/debug.h"
#include "dir/config.h"

Config conf;

int main(int argc, char **argv) {
    // parse arguments

    std::vector<std::string> arguments;

    for (int i = 0; i < argc; i++) arguments.push_back(argv[i]);

    //conf.parse(arguments);

    // load configuration

    bool success = false;

    std::vector<std::string> configPaths{ "~/.config/liblynx/conf", "/usr/share/liblynx/conf", "conf" };

    for (std::string configPath : configPaths) {
        file.parse_path(configPath);

        if (conf.load(configPath)) {
            debug.info("loaded config file at " + configPath);

            success = true;

            break;
        }

        debug.warn("failed to load config file at " + configPath);
    }

    if (!success) {
        debug.error("failed to load all provided config files");

        return 1;
    }

    // create x11 window using xcb

    // open connection to xserver on default display

    int defaultScreen = 0;
    
    xcb_connection_t* connection = xcb_connect(NULL, &defaultScreen);

    if (xcb_connection_has_error(connection) > 0) {
        debug.error("failed to open default display");

        return 1;
    }

    debug.info("opened x11 connection to default display");

    // get connection information && screen iterator

    const xcb_setup_t* setup = xcb_get_setup(connection);

    xcb_screen_iterator_t screens = xcb_setup_roots_iterator(setup);

    xcb_screen_t* screen = screens.data;

    debug.info("connected x11 display has " + std::to_string(screens.rem)+ " screens");

    // create new window on given screen

    xcb_window_t window = xcb_generate_id(connection);

    xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen->root, 10, 10, 800, 500, 1, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, 0, NULL);

    // map window & flush

    xcb_map_window(connection, window);

    xcb_flush(connection);

    while (true) { };

    // exit

    xcb_disconnect(connection);

    debug.info("closed x11 connection");
}
