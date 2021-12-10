#include "julia-png.hpp"

#include <stdexcept>

namespace julia {
namespace png {
    void
    write(Path path, Colors cs, Width width, Height height) {
        std::FILE * fp  = fopen(path.c_str(), "wb");
        if (NULL == fp) {
            throw std::runtime_error("could not create png file");
        }

        png_structp ptr = png_create_write_struct(
                PNG_LIBPNG_VER_STRING
                , NULL
                , NULL
                , NULL
                );
        if (NULL == ptr) {
            throw std::runtime_error("could not initialize png_struct");
        }

        png_infop information = png_create_info_struct(ptr);
        if (NULL == information) {
            throw std::runtime_error("could not initialize png_info");
        }
        png_uint_32 ws  = static_cast<png_uint_32>(width);
        png_uint_32 hs  = static_cast<png_uint_32>(height);

        png_init_io(ptr, fp);
        png_set_IHDR(
                ptr                             // png_structp
                , information                   // png_infop
                , ws                            // width
                , hs                            // height
                , 8                             // bit depth
                , PNG_COLOR_TYPE_RGBA           // color_type
                , PNG_INTERLACE_NONE            // interlace type
                , PNG_COMPRESSION_TYPE_DEFAULT  // compression type
                , PNG_FILTER_TYPE_DEFAULT       // filter type
                );
        png_write_info(ptr, information);

        png_uint_32 stride  = 4;
        png_uint_32 cols    = stride * ws;
        png_bytep row       = new png_byte[cols];

        for (png_uint_32 h = 0; h < hs; h++) {
            for (png_uint_32 w = 0; w < ws; w++) {
                png_uint_32 offset  = w * stride;

                row[offset + 0]  = cs[(h * cols + offset) + 0];  // r
                row[offset + 1]  = cs[(h * cols + offset) + 1];  // g
                row[offset + 2]  = cs[(h * cols + offset) + 2];  // b
                row[offset + 3]  = cs[(h * cols + offset) + 3];  // a
            }
            png_write_row(ptr, row);
        }
        png_write_end(ptr, information);
        png_destroy_write_struct(&ptr, &information);

        delete [] row;
        std::fclose(fp);
    }

    void
    write(Path path, const uint8_t * cs, Width width, Height height) {
        std::FILE * fp  = fopen(path.c_str(), "wb");
        if (NULL == fp) {
            throw std::runtime_error("could not create png file");
        }

        png_structp ptr = png_create_write_struct(
                PNG_LIBPNG_VER_STRING
                , NULL
                , NULL
                , NULL
                );
        if (NULL == ptr) {
            throw std::runtime_error("could not initialize png_struct");
        }

        png_infop information = png_create_info_struct(ptr);
        if (NULL == information) {
            throw std::runtime_error("could not initialize png_info");
        }
        png_uint_32 ws  = static_cast<png_uint_32>(width);
        png_uint_32 hs  = static_cast<png_uint_32>(height);

        png_init_io(ptr, fp);
        png_set_IHDR(
                ptr                             // png_structp
                , information                   // png_infop
                , ws                            // width
                , hs                            // height
                , 8                             // bit depth
                , PNG_COLOR_TYPE_RGBA           // color_type
                , PNG_INTERLACE_NONE            // interlace type
                , PNG_COMPRESSION_TYPE_DEFAULT  // compression type
                , PNG_FILTER_TYPE_DEFAULT       // filter type
                );
        png_write_info(ptr, information);

        png_uint_32 stride  = 4;
        png_uint_32 cols    = stride * ws;
        png_bytep row       = new png_byte[cols];

        for (png_uint_32 h = 0; h < hs; h++) {
            for (png_uint_32 w = 0; w < ws; w++) {
                png_uint_32 offset  = w * stride;

                row[offset + 0]  = cs[(h * cols + offset) + 0];  // r
                row[offset + 1]  = cs[(h * cols + offset) + 1];  // g
                row[offset + 2]  = cs[(h * cols + offset) + 2];  // b
                row[offset + 3]  = cs[(h * cols + offset) + 3];  // a
            }
            png_write_row(ptr, row);
        }
        png_write_end(ptr, information);
        png_destroy_write_struct(&ptr, &information);

        delete [] row;
        std::fclose(fp);
    }
}
}
