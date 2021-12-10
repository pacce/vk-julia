#include "vk/vk-descriptor.hpp"
#include <iostream>
#include <stdexcept>

namespace vk {
namespace descriptor {
    VkDescriptorSet
    create(
            const VkDevice&                 device
            , const VkDescriptorPool&       pool
            , const VkDescriptorSetLayout&  layout
            )
    {
        VkDescriptorSet set;

        VkDescriptorSetAllocateInfo info{};
        info.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        info.descriptorPool     = pool;
        info.descriptorSetCount = 1;
        info.pSetLayouts        = &layout;

        VkResult result = vkAllocateDescriptorSets(device, &info, &set);
        if (VK_SUCCESS != result) {
            std::cerr << result << std::endl;
            throw std::runtime_error("failed to allocate descriptor sets");
        }
        return set;
    }

    void
    destroy(const VkDevice& device, const VkDescriptorPool& pool, VkDescriptorSet set) {
        vkFreeDescriptorSets(device, pool, 1, &set);
    }
namespace pool {
    VkDescriptorPool
    create(const VkDevice& device, const std::vector<VkBuffer>& buffers)
    {
        VkDescriptorPool pool;

        VkDescriptorPoolSize size{};
        size.type               = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        size.descriptorCount    = static_cast<uint32_t>(buffers.size());

        VkDescriptorPoolCreateInfo info{};
        info.sType          = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        info.maxSets        = 1;
        info.poolSizeCount  = 1;
        info.pPoolSizes     = &size;
        info.flags          = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;

        VkResult result = vkCreateDescriptorPool(device, &info, nullptr, &pool);
        if (VK_SUCCESS != result) {
            throw std::runtime_error("failed to create descriptor pool");
        }
        return pool;
    }

    void
    destroy(const VkDevice& device, VkDescriptorPool pool)
    {
        vkDestroyDescriptorPool(device, pool, nullptr);
    }
} // namespace pool

namespace layout {
    VkDescriptorSetLayout
    create(const VkDevice& device, std::size_t bindings) {
        VkDescriptorSetLayout set;

        std::vector<VkDescriptorSetLayoutBinding> layouts;
        for (std::size_t binding = 0; binding < bindings; binding++) {
            VkDescriptorSetLayoutBinding layout{};
            layout.binding          = static_cast<uint32_t>(binding);
            layout.descriptorType   = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            layout.descriptorCount  = 1;
            layout.stageFlags       = VK_SHADER_STAGE_COMPUTE_BIT;
            layouts.push_back(layout);
        }

        VkDescriptorSetLayoutCreateInfo info{};
        info.sType          = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        info.bindingCount   = static_cast<uint32_t>(layouts.size());
        info.pBindings      = layouts.data();

        VkResult result = vkCreateDescriptorSetLayout(device, &info, nullptr, &set);
        if (VK_SUCCESS != result) {
            throw std::runtime_error("failed to create descriptor set layout");
        }
        return set;
    }

    void
    destroy(const VkDevice& device, VkDescriptorSetLayout set) {
        vkDestroyDescriptorSetLayout(device, set, nullptr);
    }
} // namespace layout

namespace write {
    void
    create(
            const VkDevice&                 device
            , const std::vector<VkBuffer>&  buffers
            , const VkDescriptorSet&        set
            )
    {
        std::vector<VkWriteDescriptorSet> xs(buffers.size());
        std::vector<VkDescriptorBufferInfo> infos(buffers.size());

        uint32_t i = 0;
        for (const VkBuffer& buffer : buffers) {
            VkDescriptorBufferInfo info{};
            info.buffer = buffer;
            info.offset = 0;
            info.range  = VK_WHOLE_SIZE;
            infos[i]    = info;

            VkWriteDescriptorSet x{};
            x.sType             = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            x.dstSet            = set;
            x.dstBinding        = i;
            x.dstArrayElement   = 0;
            x.descriptorCount   = 1;
            x.descriptorType    = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            x.pBufferInfo       = &infos[i];
            xs[i] = x;

            i++;
        }
        uint32_t size = static_cast<uint32_t>(xs.size());
        vkUpdateDescriptorSets(device, size, xs.data(), 0, nullptr);
    }
} // namespace write

} // namespace descriptor
} // namespace vk
