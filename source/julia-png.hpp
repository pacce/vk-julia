#ifndef JULIA_PNG_HPP__
#define JULIA_PNG_HPP__

#include <png.h>
#include <cstdint>
#include <string>
#include <vector>

namespace julia {
namespace png {
    using Path      = const std::string&;
    using Colors    = const std::vector<uint8_t>&;
    using Width     = std::size_t;
    using Height    = std::size_t;

    void
    write(Path path, Colors cs, Width width, Height height);

    void
    write(Path path, const uint8_t * cs, Width width, Height height);
}
}

#endif // JULIA_PNG_HPP__
