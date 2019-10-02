#ifndef vulkan_h
#define vulkan_h

#include <string>
#include <vector>

#include <xcb/xcb.h>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_xcb.h>

class VulkanInstance {
private:
	// Member Variables
	
	VkInstance instance;
public:

	// Member Functions

	bool init(std::string* err = nullptr);
	void term();

	std::string geterr(int err);
};

extern VulkanInstance vk;

#endif

