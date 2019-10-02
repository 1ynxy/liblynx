#include "vulkan.h"

#include "../inout/debug.h"

VulkanInstance vk;

// Member Functions

bool VulkanInstance::init(std::string* err) {
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

	VkResult result = vkCreateInstance(&createInf, NULL, &instance);

	if (result != VK_SUCCESS) {
		if (err) *err = geterr(result);

		return false;
	}

	return true;
}

void VulkanInstance::term() {
	vkDestroyInstance(instance, NULL);
}

std::string VulkanInstance::geterr(int err) {
	if (err == VK_ERROR_INCOMPATIBLE_DRIVER) return "vulkan cannot find compatible driver support";

	if (err == VK_ERROR_INITIALIZATION_FAILED) return "vulkan initialisation failed";

	if (err == VK_ERROR_EXTENSION_NOT_PRESENT) return "vulkan cannot find one or more extensions";

	return "vulkan encountered an unexpected error : " + std::to_string(err);
}