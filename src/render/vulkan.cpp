#include "vulkan.h"

#include "../inout/debug.h"

VulkanInstance vk;

// Contructors & Destructors

VulkanInstance::VulkanInstance() {
	
}

VulkanInstance::~VulkanInstance() {
	vkDestroyInstance(instance, NULL);
}

// Member Functions

bool VulkanInstance::init() {
	// create vulkan application information struct

	VkApplicationInfo appInf = { };

	appInf.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInf.pNext = NULL;
	appInf.pApplicationName = "liblynx";
	appInf.pEngineName = "";
	appInf.apiVersion = VK_MAKE_VERSION(1, 1, 0);

	// get extensions required for drawing to a surface

	std::vector<const char*> ext = { };

	ext.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
	//ext.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);

	// create vulkan creation information struct

	VkInstanceCreateInfo createInf = { };

	createInf.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInf.pNext = NULL;
	createInf.flags = 0;
	createInf.pApplicationInfo = &appInf;
	createInf.enabledExtensionCount = ext.size();
	createInf.ppEnabledExtensionNames = ext.data();

	// create instance & check result

	VkResult res = vkCreateInstance(&createInf, NULL, &instance);

	if (res == VK_SUCCESS) return true;

	if (res == VK_ERROR_INCOMPATIBLE_DRIVER) {
		debug.error("vulkan cannot find compatible driver support");

		return false;
	}

	if (res == VK_ERROR_INITIALIZATION_FAILED) {
		debug.error("vulkan initialisation failed");

		return false;
	}

	if (res == VK_ERROR_EXTENSION_NOT_PRESENT) {
		debug.error("vulkan cannot find one or more extensions");

		return false;
	}

	debug.error("vulkan encountered an unexpected error : " + std::to_string(res));

	return false;
}