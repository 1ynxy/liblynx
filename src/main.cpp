#include "inout/file.h"
#include "inout/debug.h"
#include "inout/node.h"

#include "render/vulkan.h"

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
}
