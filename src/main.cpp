#include "dir/file.h"
#include "dir/debug.h"
#include "dir/config.h"

Config conf;

int main(int argc, char **argv) {
    // parse arguments

    std::vector<std::string> arguments;

    for (int i = 0; i < argc; i++) arguments.push_back(argv[i]);

    conf.parse(arguments);

    // load configuration

    std::vector<std::string> configPaths{ "~/.config/liblynx/conf", "/usr/share/liblynx/conf", "conf" };

    for (std::string configPath : configPaths) {
        file.parse_path(configPath);

        if (conf.load(configPath)) {
            debug.info("loaded config file at " + configPath);

            break;
        }

        debug.error("failed to load config file at " + configPath);
    }
}
