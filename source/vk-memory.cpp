#include "vk/vk-memory.hpp"

#include <cstdint>

#include "vk/vk-buffer.hpp"
#include "vk/vk-device.hpp"

namespace vk {
namespace memory {
    VkDeviceMemory
    create(
            const VkPhysicalDevice&         physical
            , const VkDevice&               device
            , const std::vector<VkBuffer>&  buffers
            )
    {
        VkDeviceMemory memory;

        VkDeviceSize size   = 0;
        uint32_t filter     = 0;
        for (const VkBuffer& buffer : buffers) {
            VkMemoryRequirements requirements;
            requirements = vk::buffer::get_requirements(device , buffer);
            size    += requirements.size;
            filter  |= requirements.memoryTypeBits;
        }

        uint32_t index = vk::device::find_memory_type(
                physical
                , filter
                , VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
                | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
                );

        VkMemoryAllocateInfo info{};
        info.sType              = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        info.allocationSize     = size;
        info.memoryTypeIndex    = index;

        VkResult result = vkAllocateMemory(device, &info, nullptr, &memory);
        if (VK_SUCCESS != result) {
            throw std::runtime_error("failed to allocate buffer memory");
        }
        return memory;
    }

    void
    destroy(const VkDevice& device, VkDeviceMemory memory) {
        vkFreeMemory(device, memory, nullptr);
    }

    void
    bind(
            const VkDevice&                 device
            , const VkDeviceMemory&         memory
            , const std::vector<VkBuffer>&  buffers
        )
    {
         VkDeviceSize offset = 0;
         for (const VkBuffer& buffer : buffers) {
            VkMemoryRequirements requirements;
            requirements = vk::buffer::get_requirements(device , buffer);
            VkResult result = vkBindBufferMemory(device, buffer, memory, offset);

            if (VK_SUCCESS != result) {
                throw std::runtime_error("failed to bind buffer memory");
            }
            offset += requirements.size;
         }
    }

    void
    unmap(const VkDevice& device, const VkDeviceMemory& memory) {
        vkUnmapMemory(device, memory);
    }
} // namespace memory
} // namespace vk
