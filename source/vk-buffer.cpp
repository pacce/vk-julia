#include "vk/vk-buffer.hpp"

#include <cstdint>
#include <stdexcept>

namespace vk {
namespace buffer {
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
