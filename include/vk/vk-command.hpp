#ifndef VK_COMMAND_HPP__
#define VK_COMMAND_HPP__

#include <vulkan/vulkan.h>
#include <cstdint>

namespace vk {
namespace command {
namespace pool {
    VkCommandPool
    create(const VkDevice& device, uint32_t family);

    void
    destroy(const VkDevice& device, VkCommandPool& pool);
} // namespace pool

namespace buffer {
    VkCommandBuffer
    create(const VkDevice& device, const VkCommandPool& pool);

    void
    begin(VkCommandBuffer& buffer);

    void
    dispatch(VkCommandBuffer& buffer, std::size_t count);

    void
    dispatch(VkCommandBuffer& buffer, std::size_t width, std::size_t height);

    void
    end(VkCommandBuffer& buffer);

    void
    bind_pipeline(VkCommandBuffer& buffer, const VkPipeline& pipeline);

    void
    bind_descriptor(
            VkCommandBuffer&            buffer
            , const VkPipelineLayout&   layout
            , const VkDescriptorSet&    descriptor
            );
}
} // namespace command
} // namespace vk

#endif // VK_COMMAND_HPP__
