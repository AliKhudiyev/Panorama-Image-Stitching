
#pragma once

#include"bmp.hpp"
#include"pixel.hpp"

struct Panorama{
    Color background_color_;
};

std::vector<Pixel> find_corner(const BMP& image);
const BMP stitch(const BMP& image1, const BMP& image2);
const BMP stitch(const std::vector<BMP>& image);
double scaling_factor_at_height(const BMP& image1, const BMP& image2, unsigned height);
double scaling_factor_at_height(const BMP image[2], unsigned height);
// void fill_sf_vector(std::vector<double>& sf_vector, const Function& sf_function);
// void fill_sf_vector(std::vector<double>& sf_vector, );
