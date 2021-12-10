#ifndef VK_DEVICE_HPP__
#define VK_DEVICE_HPP__

#include <vulkan/vulkan.h>
#include <vector>

namespace vk {
namespace device {
    std::vector<VkQueueFamilyProperties>
    get_queues(const VkPhysicalDevice& physical);

    uint32_t
    get_queue_index(const VkPhysicalDevice& physical);

    VkPhysicalDevice
    select(const std::vector<VkPhysicalDevice>& xs);

    uint32_t
    find_memory_type(
            const VkPhysicalDevice& physical
            , uint32_t              filter
            , VkMemoryPropertyFlags properties
            );

    VkDevice
    create(const VkPhysicalDevice& physical, uint32_t family);

    void
    destroy(VkDevice device);
} // namespace device
} // namespace vk

#endif // VK_DEVICE_HPP__
