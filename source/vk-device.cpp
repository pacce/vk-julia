#include "vk/vk-device.hpp"
#include <stdexcept>

namespace vk {
namespace device {
    std::vector<VkQueueFamilyProperties>
    get_queues(const VkPhysicalDevice& physical) {
        uint32_t count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physical, &count, nullptr);

        std::vector<VkQueueFamilyProperties> families(count);
        vkGetPhysicalDeviceQueueFamilyProperties(physical, &count, families.data());
        return families;
    }

    uint32_t
    get_queue_index(const VkPhysicalDevice& physical) {
        std::vector<VkQueueFamilyProperties> qs = vk::device::get_queues(physical);
        for (std::size_t i = 0; i < qs.size(); i++) {
            VkQueueFamilyProperties q = qs[i];
            if (q.queueFlags & VK_QUEUE_COMPUTE_BIT) { return i; }
        }
        return 0;
    }

    uint32_t
    find_memory_type(
            const VkPhysicalDevice& physical
            , uint32_t              filter
            , VkMemoryPropertyFlags properties
            )
    {
        VkPhysicalDeviceMemoryProperties pp;
        vkGetPhysicalDeviceMemoryProperties(physical, &pp);

        for (uint32_t p = 0; p < pp.memoryTypeCount; p++) {
            VkMemoryPropertyFlags flags =  pp.memoryTypes[p].propertyFlags;
            bool success = (filter & (1 << p))
                        && ((flags & properties) == properties)
                        ;
            if (success) { return p; }
        }
        throw std::runtime_error("failed to find suitable memory");
    }

    static bool
    is_suitable(const std::vector<VkQueueFamilyProperties>& qs) {
        for (const VkQueueFamilyProperties& q : qs) {
            if (q.queueFlags & VK_QUEUE_COMPUTE_BIT) { return true; }
        }
        return false;
    }

    static bool
    is_suitable(const VkPhysicalDevice& x) {
        std::vector<VkQueueFamilyProperties> qs = vk::device::get_queues(x);
        return is_suitable(qs);
    }

    VkPhysicalDevice
    select(const std::vector<VkPhysicalDevice>& xs) {
        VkPhysicalDevice physical;

        bool suitable = false;
        for (const VkPhysicalDevice& x : xs) {
            suitable = is_suitable(x);
            if (suitable) { physical = x; break; }
        }
        if (!suitable) {
            throw std::runtime_error("could not select a suitable physical device");
        }
        return physical;
    }

    VkDevice
    create(const VkPhysicalDevice& physical, uint32_t family) {
        VkDevice device;

        float priority = 1.0;
        VkDeviceQueueCreateInfo queue{};
        queue.sType             = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue.queueFamilyIndex  = family;
        queue.queueCount        = 1;
        queue.pQueuePriorities  = &priority;

        VkDeviceCreateInfo info{};
        info.sType                  = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        info.pQueueCreateInfos      = &queue;
        info.queueCreateInfoCount   = 1;
        info.enabledLayerCount      = 0;

        VkResult result = vkCreateDevice(physical, &info, nullptr, &device);
        if (VK_SUCCESS != result) {
            throw std::runtime_error("failed to create logical device");
        }
        return device;
    }

    void
    destroy(VkDevice device) {
        vkDestroyDevice(device, nullptr);
    }
} // namespace device
} // namespace vk
