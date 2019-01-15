#include"bmp_info.hpp"

std::vector<unsigned> byte_vector(unsigned int value, unsigned int n_byte){
    std::vector<unsigned int> byte(n_byte);
    for(unsigned i=0;i<n_byte;++i){
        byte[i]=value%256;
        value=(value-byte[i])/256;
    }
    return byte;
}

std::vector<unsigned> BMP_INFO::get_byte_vector(unsigned char parameter, unsigned n_byte) const{
    unsigned value;
    switch(parameter){
        case FILE_SIZE:
            value=file_size_;
            break;
        case WIDTH:
            value=image_width_;
            break;
        case HEIGHT:
            value=image_height_;
            break;
        case IMAGE_SIZE:
            value=image_size_;
            break;
        default: break;
    }
    return byte_vector(value, n_byte);
}

void BMP_INFO::clear(){
    signature_=0;
    file_size_=0;
    offset_size_=0;
    header_size_=0;
    image_width_=image_height_=0;
    bits_per_pixel_=0;
    image_size_=0;
}

void BMP_INFO::Info() const{
    std::cout<<"File size : "<<file_size_<<'\n';
    std::cout<<"Offset size : "<<offset_size_<<'\n';
    std::cout<<"Header size : "<<header_size_<<'\n';
    std::cout<<"Image width : "<<image_width_<<'\n';
    std::cout<<"Image height : "<<image_height_<<'\n';
    std::cout<<"Bits per pixel : "<<bits_per_pixel_<<'\n';
    std::cout<<"Image size : "<<image_size_<<'\n';
}
