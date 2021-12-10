#include "vk/vk-shader.hpp"

#include <fstream>
#include <stdexcept>
#include <vector>

namespace vk {
namespace shader {
    static std::vector<char>
    read(const std::string& file) {
        std::ifstream handle(file, std::ios::ate | std::ios::binary);
        if (!handle.is_open()) {
            throw std::runtime_error("failed to open file");
        }

        std::size_t size = static_cast<std::size_t>(handle.tellg());
        std::vector<char> xs(size);

        handle.seekg(0);
        handle.read(xs.data(), size);
        handle.close();

        return xs;
    }

    VkShaderModule
    create(const std::string& file, VkDevice& device) {
        VkShaderModule shader;
        std::vector<char> xs = read(file);

        VkShaderModuleCreateInfo info{};
        info.sType      = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        info.codeSize   = xs.size();
        info.pCode      = reinterpret_cast<const uint32_t*>(xs.data());

        VkResult result = vkCreateShaderModule(device, &info, nullptr, &shader);
        if (VK_SUCCESS != result) {
            throw std::runtime_error("failed to create shader module");
        }

        return shader;
    }

    void
    destroy(const VkDevice& device, VkShaderModule shader) {
        vkDestroyShaderModule(device, shader, nullptr);
    }
} // namespace shader
} // namespace vk
