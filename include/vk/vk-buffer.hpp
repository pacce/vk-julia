#ifndef VK_BUFFER_HPP__
#define VK_BUFFER_HPP__

#include <vulkan/vulkan.h>
#include <cstdint>

namespace vk {
namespace buffer {
    VkBuffer
    create(const VkDevice& device, uint64_t size, uint32_t family);

    void
    destroy(const VkDevice& device, VkBuffer buffer);

    VkMemoryRequirements
    get_requirements(const VkDevice& device, const VkBuffer& buffer);
} // namespace buffer
} // namespace vk

#endif // VK_BUFFER_HPP__
