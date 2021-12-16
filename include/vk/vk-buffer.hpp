#ifndef VK_BUFFER_HPP__
#define VK_BUFFER_HPP__

#include <vulkan/vulkan.h>
#include <cstdint>
#include <stdexcept>

namespace vk {
namespace buffer {
    template<typename T>
    VkBuffer
    create(const VkDevice& device, uint64_t size, uint32_t family) {
        VkBuffer buffer;

        VkBufferCreateInfo info{};
        info.sType                  = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        info.size                   = sizeof(T) * size;
        info.usage                  = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
        info.sharingMode            = VK_SHARING_MODE_EXCLUSIVE;
        info.queueFamilyIndexCount  = 1;
        info.pQueueFamilyIndices    = &family;

        VkResult result = vkCreateBuffer(device, &info, nullptr, &buffer);
        if (VK_SUCCESS != result) {
            throw std::runtime_error("failed to create buffers");
        }
        return buffer;
    }

    void
    destroy(const VkDevice& device, VkBuffer buffer);

    VkMemoryRequirements
    get_requirements(const VkDevice& device, const VkBuffer& buffer);
} // namespace buffer
} // namespace vk

#endif // VK_BUFFER_HPP__
