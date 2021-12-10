#include "vk/vk-buffer.hpp"

#include <cstdint>
#include <stdexcept>

namespace vk {
namespace buffer {
    VkBuffer
    create(const VkDevice& device, uint64_t size, uint32_t family) {
        VkBuffer buffer;

        VkBufferCreateInfo info{};
        info.sType                  = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        info.size                   = sizeof(uint8_t) * size;
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
    destroy(const VkDevice& device, VkBuffer buffer) {
        vkDestroyBuffer(device, buffer, nullptr);
    }

    VkMemoryRequirements
    get_requirements(const VkDevice& device, const VkBuffer& buffer) {
        VkMemoryRequirements requirements;
        vkGetBufferMemoryRequirements(device, buffer, &requirements);
        return requirements;
    }
} // namespace buffer
} // namespace vk
