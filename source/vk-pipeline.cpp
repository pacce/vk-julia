#include "vk/vk-pipeline.hpp"

#include <stdexcept>
#include <vector>

namespace vk {
namespace pipeline {
    VkPipeline
    create(const VkDevice& device, const VkShaderModule& shader, const VkPipelineLayout& layout) {
        VkPipeline pipeline;

        VkComputePipelineCreateInfo info{};
        info.sType          = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        info.stage.sType    = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        info.stage.stage    = VK_SHADER_STAGE_COMPUTE_BIT;
        info.stage.module   = shader;
        info.stage.pName    = "main";
        info.layout         = layout;

        VkResult result = vkCreateComputePipelines(
                device
                , VK_NULL_HANDLE
                , 1
                , &info
                , nullptr
                , &pipeline
                );
        if (VK_SUCCESS != result) {
            throw std::runtime_error("failed to create pipeline");
        }
        return pipeline;
    }

    void
    destroy(const VkDevice& device, VkPipeline pipeline) {
        vkDestroyPipeline(device, pipeline, nullptr);
    }

namespace layout {
    VkPipelineLayout
    create(VkDevice device, VkDescriptorSetLayout set) {
        VkPipelineLayout layout;

        VkPipelineLayoutCreateInfo info{};
        info.sType          = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        info.setLayoutCount = 1;
        info.pSetLayouts    = &set;

        VkResult result = vkCreatePipelineLayout(device, &info, nullptr, &layout);
        if (VK_SUCCESS != result) {
            throw std::runtime_error("failed to create pipeline layout");
        }
        return layout;
    }

    void
    destroy(const VkDevice& device, VkPipelineLayout layout) {
        vkDestroyPipelineLayout(device, layout, nullptr);
    }
} // namespace layout

} // namespace pipeline
} // namespace vk
