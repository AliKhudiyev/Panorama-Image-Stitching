/*
 * This header file is to save all necessary information about .bmp image.
 * Neither color data nor full header data is saved.
 * For detailed information, visit my github: https://github.com/AliKhudiyev/Panorama-Image-Stitching
*/

#pragma once

#include<iostream>
#include<vector>
#include<cstdint>

#define IMAGE_WIDTH 0
#define IMAGE_HEIGHT 1

#define FILE_SIZE 0
#define WIDTH 1
#define HEIGHT 2
#define IMAGE_SIZE 3

struct BMP_INFO{
    uint16_t signature_;
    uint32_t file_size_;
    uint32_t offset_size_;
    uint32_t header_size_;
    uint32_t image_width_, image_height_;
    uint16_t bits_per_pixel_;
    uint32_t image_size_;

    std::vector<unsigned> get_byte_vector(unsigned char parameter, unsigned n_byte) const;
    void clear();
    void Info() const;
};

std::vector<unsigned> byte_vector(unsigned int value, unsigned int n_byte);
