#include <iostream>
#include <vk/vk.hpp>

#include "julia-png.hpp"

const std::size_t WIDTH     = 2560;
const std::size_t HEIGHT    = 1080;

int
main(int argc, char **argv) {
    VkInstance instance = vk::instance::create();

    std::vector<VkPhysicalDevice> devices = vk::instance::get_devices(instance);
    VkPhysicalDevice physical   = vk::device::select(devices);
    uint32_t family             = vk::device::get_queue_index(physical);
    VkDevice device             = vk::device::create(physical, family);

    VkShaderModule shader                   = vk::shader::create("build/shader.comp.spv", device);
    VkDescriptorSetLayout descriptorLayout  = vk::descriptor::layout::create(device, 1);
    VkPipelineLayout layout                 = vk::pipeline::layout::create(device, descriptorLayout);
    VkPipeline pipeline                     = vk::pipeline::create(device, shader, layout);

   std::size_t elements = WIDTH * HEIGHT * 4;
   std::vector<VkBuffer> buffers;
   {
       VkBuffer buffer = vk::buffer::create<uint8_t>(device, elements, family);
       buffers.push_back(buffer);
   }
   VkDeviceMemory memory = vk::memory::create(physical, device, buffers);
   vk::memory::bind(device, memory, buffers);

   VkDescriptorPool descriptorPool = vk::descriptor::pool::create(device, buffers);
   VkDescriptorSet descriptorSet   = vk::descriptor::create(
           device
           , descriptorPool
           , descriptorLayout
           );
   vk::descriptor::write::create(device, buffers, descriptorSet);
   VkCommandPool commandPool       = vk::command::pool::create(device, family);
   VkCommandBuffer commandBuffer   = vk::command::buffer::create(device, commandPool);

   vk::command::buffer::begin(commandBuffer);
   vk::command::buffer::bind_pipeline(commandBuffer, pipeline);
   vk::command::buffer::bind_descriptor(commandBuffer, layout, descriptorSet);
   vk::command::buffer::dispatch(commandBuffer, WIDTH, HEIGHT);
   vk::command::buffer::end(commandBuffer);

   uint8_t * dataset = nullptr;
   dataset = vk::memory::map<uint8_t>(device, memory);
   for (std::size_t i = 0; i < elements; i++) {
       dataset[i] = 0;
   }
   vk::memory::unmap(device, memory);
   dataset = nullptr;

   VkQueue queue;
   vkGetDeviceQueue(device, family, 0, &queue);

   VkSubmitInfo submit{};
   submit.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO;
   submit.commandBufferCount   = 1;
   submit.pCommandBuffers      = &commandBuffer;
   vkQueueSubmit(queue, 1, &submit, VK_NULL_HANDLE);
   vkQueueWaitIdle(queue);

   dataset  = vk::memory::map<uint8_t>(device, memory);
   julia::png::write("hello.png", dataset, WIDTH, HEIGHT);
   vk::memory::unmap(device, memory);

   vk::command::pool::destroy(device, commandPool);
   vk::descriptor::destroy(device, descriptorPool, descriptorSet);
   vk::descriptor::pool::destroy(device, descriptorPool);

   vk::memory::destroy(device, memory);
   for (VkBuffer buffer : buffers) {
       vk::buffer::destroy(device, buffer);
   }

   vk::pipeline::destroy(device, pipeline);
   vk::pipeline::layout::destroy(device, layout);
   vk::descriptor::layout::destroy(device, descriptorLayout);
   vk::shader::destroy(device, shader);

   vk::device::destroy(device);

   vk::instance::destroy(instance);

   return 0;
}
