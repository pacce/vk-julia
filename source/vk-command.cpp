#include "vk/vk-command.hpp"
#include <stdexcept>

namespace vk {
namespace command {
namespace pool {
    VkCommandPool
    create(const VkDevice& device, uint32_t family) {
        VkCommandPool pool;

        VkCommandPoolCreateInfo info{};
        info.sType              = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        info.flags              = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
        info.queueFamilyIndex   = family;

        VkResult result = vkCreateCommandPool(device, &info, nullptr, &pool);
        if (VK_SUCCESS != result) {
            throw std::runtime_error("failed to create command pool");
        }
        return pool;
    }

    void
    destroy(const VkDevice& device, VkCommandPool& pool) {
        vkDestroyCommandPool(device, pool, nullptr);
    }
} // namespace pool

namespace buffer {
    VkCommandBuffer
    create(const VkDevice& device, const VkCommandPool& pool) {
        VkCommandBuffer buffer;

        VkCommandBufferAllocateInfo info{};
        info.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        info.commandPool        = pool;
        info.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        info.commandBufferCount = 1;

        VkResult result = vkAllocateCommandBuffers(device, &info, &buffer);
        if (VK_SUCCESS != result) {
            throw std::runtime_error("failed to allocate command buffer");
        }
        return buffer;
    }

    void
    begin(VkCommandBuffer& buffer) {
        VkCommandBufferBeginInfo info{};
        info.sType  = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        info.flags  = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(buffer, &info);
    }

    void
    dispatch(VkCommandBuffer& buffer, std::size_t count) {
        vkCmdDispatch(buffer, static_cast<uint32_t>(count), 1, 1);
    }

    void
    dispatch(VkCommandBuffer& buffer, std::size_t width, std::size_t height) {
        vkCmdDispatch(
                buffer
                , static_cast<uint32_t>(width)
                , static_cast<uint32_t>(height)
                , 1
                );
    }

    void
    end(VkCommandBuffer& buffer) {
        VkResult result = vkEndCommandBuffer(buffer);
        if (VK_SUCCESS != result) {
            throw std::runtime_error("failed to end command buffer");
        }
    }

    void
    bind_pipeline(VkCommandBuffer& buffer, const VkPipeline& pipeline) {
        vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
    }

    void
    bind_descriptor(
            VkCommandBuffer&            buffer
            , const VkPipelineLayout&   layout
            , const VkDescriptorSet&    descriptor
            )
    {
        vkCmdBindDescriptorSets(
                buffer
                , VK_PIPELINE_BIND_POINT_COMPUTE
                , layout
                , 0
                , 1
                , &descriptor
                , 0
                , nullptr
                );
    }
} // namespace buffer
} // namespace command
} // namespace vk
