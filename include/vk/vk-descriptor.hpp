#ifndef VK_DESCRIPTOR_HPP__
#define VK_DESCRIPTOR_HPP__

#include <vulkan/vulkan.h>
#include <vector>

namespace vk {
namespace descriptor {
    VkDescriptorSet
    create(
            const VkDevice&                 device
            , const VkDescriptorPool&       pool
            , const VkDescriptorSetLayout&  layout
            );

    void
    destroy(const VkDevice& device, const VkDescriptorPool& pool, VkDescriptorSet set);
namespace pool {
    VkDescriptorPool
    create(const VkDevice& device, const std::vector<VkBuffer>& buffers);

    void
    destroy(const VkDevice& device, VkDescriptorPool pool);
} // namespace pool

namespace layout {
    VkDescriptorSetLayout
    create(const VkDevice& device, std::size_t bindings);

    void
    destroy(const VkDevice& device, VkDescriptorSetLayout set);
} // namespace layout

namespace write {
    void
    create(
            const VkDevice&                 device
            , const std::vector<VkBuffer>&  buffers
            , const VkDescriptorSet&        set
            );
} // namespace write

} // namespace descriptor
} // namespace vk

#endif // VK_DESCRIPTOR_HPP__
