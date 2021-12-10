project('compute', 'cpp', version : '0.1.0', default_options : ['warning_level=3', 'cpp_std=c++14'])

png           = dependency('libpng')
vulkan        = dependency('vulkan')
dependencies  = [png, vulkan]

headers = include_directories('include', 'source')
sources = [
  'source/main.cpp'
  , 'source/vk-buffer.cpp'
  , 'source/vk-command.cpp'
  , 'source/vk-descriptor.cpp'
  , 'source/vk-device.cpp'
  , 'source/vk-instance.cpp'
  , 'source/vk-memory.cpp'
  , 'source/vk-pipeline.cpp'
  , 'source/vk-shader.cpp'
  , 'source/julia-png.cpp'
  ]

glsl    = find_program('glslangValidator')
shaders = []
foreach s : ['shader/shader.comp']
  shaders += custom_target(
    'shader @0@'.format(s)
    , command           : [glsl, '-V', '@INPUT@', '-o', '@OUTPUT@']
    , input             : s
    , output            : '@PLAINNAME@.spv'
    , build_by_default  : true
    )
endforeach

executable(
  meson.project_name()
  , sources
  , include_directories : headers
  , dependencies        : dependencies
  , install             : true
  )
