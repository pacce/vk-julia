#ifndef VK_PIPELINE_HPP__
#define VK_PIPELINE_HPP__

#include <vulkan/vulkan.h>
#include <cstdint>

namespace vk {
namespace pipeline {
    VkPipeline
    create(const VkDevice& device, const VkShaderModule& shader, const VkPipelineLayout& layout);

    void
    destroy(const VkDevice& device, VkPipeline pipeline);
namespace layout {
    VkPipelineLayout
    create(VkDevice device, VkDescriptorSetLayout descriptor);

    void
    destroy(const VkDevice& device, VkPipelineLayout layout);
} // namespace layout

} // namespace pipeline
} // namespace vk

#endif //  VK_PIPELINE_HPP__
