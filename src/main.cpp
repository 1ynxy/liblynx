#include <xcb/xcb.h>

#include "dir/file.h"
#include "dir/debug.h"
#include "dir/node.h"

#include "win/xcb.h"

Node conf;

int main(int argc, char **argv) {
    // parse arguments

    std::vector<std::string> arguments;

    for (int i = 0; i < argc; i++) arguments.push_back(argv[i]);

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

    // get window attributes from config

    int x = conf["startup"]["window"]["x"].as_num(50);
    int y = conf["startup"]["window"]["y"].as_num(50);
    int width = conf["startup"]["window"]["width"].as_num(100);
    int height = conf["startup"]["window"]["height"].as_num(100);

    xcb_window_t window = display.create_window(0, x, y, width, height);

    while (true) {
        xcb_generic_event_t* event = xcb_wait_for_event(display.connection);

        if (!event) {
            debug.error("i/o error in xcb_wait_for_event");

            break;
        }

        free(event);

        debug.info("event happened!");
    };
}
