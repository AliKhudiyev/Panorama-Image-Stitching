#include"panorama.hpp"

const BMP stitch(const BMP& image1, const BMP& image2){
    BMP panorama;
    panorama=image1;
    panorama+=image2;;
    return panorama;
}

const BMP stitch(const std::vector<BMP>& image){
    BMP panorama=image[0];
    for(auto it=image.begin()+1;it<image.end();++it){
        panorama+=*it;
    }
    return panorama;
}

double scaling_factor_at_height(const BMP& image1, const BMP& image2, unsigned height){
    double sf;
    std::vector<Pixel> corner1, corner2;
    
    corner1=find_corner(image1);
    corner2=find_corner(image2);

    for(;;){
        if(0) sf=0;
    }
}

double scaling_factor_at_height(const BMP image[2], unsigned height){
    return scaling_factor_at_height(image[0], image[1], height);
}
