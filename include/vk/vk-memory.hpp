#ifndef VK_MEMORY_HPP__
#define VK_MEMORY_HPP__

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>

namespace vk {
namespace memory {
    VkDeviceMemory
    create(
            const VkPhysicalDevice& physical
            , const VkDevice& device
            , const std::vector<VkBuffer>& buffers
            );

    void
    destroy(const VkDevice& device, VkDeviceMemory memory);

    void
    bind(
            const VkDevice&                 device
            , const VkDeviceMemory&         memory
            , const std::vector<VkBuffer>&  buffers
        );

    template<typename T>
    T *
    map(const VkDevice& device, const VkDeviceMemory& memory) {
        T * xs = nullptr;
        VkResult result = vkMapMemory(
                device
                , memory
                , 0
                , VK_WHOLE_SIZE
                , 0
                , reinterpret_cast<void **>(&xs)
                );
        if (VK_SUCCESS != result) {
            throw std::runtime_error("failed to map memory");
        }
        return xs;
    }

    void
    unmap(const VkDevice& device, const VkDeviceMemory& memory);
} // namespace memory
} // namespace vk

#endif // VK_MEMORY_HPP__
