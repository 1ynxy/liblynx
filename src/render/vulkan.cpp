#include "vulkan.h"

// Contructors & Destructors

VulkanInstance::VulkanInstance() {
    

    // construct create info and create instance

    VkResult res = vkCreateInstance(&createInfo, NULL, &instance);

    // check result of create call


}

VulkanInstance::~VulkanInstance() {
    vkDestroyInstance(instance, NULL);
}

// Member Functions

