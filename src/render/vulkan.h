#ifndef vulkan_h
#define vulkan_h

#include <vector>

#include <xcb/xcb.h>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_xcb.h>

class VulkanInstance {
private:
	// Member Variables
	
	VkInstance instance;
public:
	// Constructors & Destructors

	VulkanInstance();
	~VulkanInstance();

	// Member Functions

	bool init();

	void exit_on_error(const char* msg);
};

extern VulkanInstance vk;

#endif

