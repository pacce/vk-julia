#ifndef VK_SHADER_HPP__
#define VK_SHADER_HPP__

#include <string>
#include <vulkan/vulkan.h>

namespace vk {
namespace shader {
    VkShaderModule
    create(const std::string& file, VkDevice& device);

    void
    destroy(const VkDevice& device, VkShaderModule shader);
} // namespace shader
} // namespace vk

#endif // VK_SHADER_HPP__
