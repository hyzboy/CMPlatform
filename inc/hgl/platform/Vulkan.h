#ifndef HGL_PLATFORM_VULKAN_INCLUDE
#define HGL_PLATFORM_VULKAN_INCLUDE

#include<vulkan/vulkan.h>

namespace hgl
{
    class Window;
    
    VkSurfaceKHR CreateVulkanSurface(VkInstance,Window *);
}//namespace hgl
#endif//HGL_PLATFORM_VULKAN_INCLUDE
