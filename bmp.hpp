/*
 * BMP header file.
 * Holds all .bmp image data inside the class BMP or Image.
 * Holds detailed information only about the necessary part of .bmp images.
 * For detailed information, visit my github: https://github.com/AliKhudiyev/Panorama-Image-Stitching
*/

#pragma once

#include<vector>
#include<string>
#include"bmp_info.hpp"
#include"pixel.hpp"
#include"exception.hpp"

#define Image BMP
#define exts ".bmp"

#define VERTICAL_STITCH 0
#define HORIZONTAL_STITCH 1

using iName=const std::string;
const std::string errchar="/";

class BMP{
    typedef char byte;
    typedef uint32_t byte4;

    static unsigned int n_image;
    static const std::string image_name;

    private:
    unsigned int n_img;
    mutable std::string name_=errchar;
    BMP_INFO info_{0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<byte> header_;
    std::vector<Color> color_;

    public:
    BMP(){
        n_img=(++n_image);
    }
    explicit BMP(iName& name): 
        BMP() 
    {
        try{
            set(name);
        } catch(Exception& exception){
            std::cout<<exception.get()<<'\n';
        }
    }
    explicit BMP(const char* file_name, const std::string& name=errchar): 
        BMP() 
    {
        try{
            try{
                set(name);
            } catch(Exception& exception){
                if(name.compare(errchar)){
                    std::cout<<exception.get()<<'\n';
                }
            }
            init(file_name);
        } catch(Exception& exception){
            throw exception;
        }
    }

    void set(std::string name) const;
    void modify(const std::vector<Color>& color, unsigned value=0, bool side=IMAGE_WIDTH);
    const std::string& get() const;
    const BMP_INFO& info() const;
    void Info() const;

    ~BMP(){}

    void read(const char* file_name);
    void vertical_stitch(const BMP& image);
    void horizontal_stitch(const BMP& image);
    static BMP elongate(const std::vector<double>& sf, const BMP& image);
    void create(std::string name="") const;
    void remove();

    void operator=(const BMP& image);
    BMP operator+(const BMP& image) const;
    BMP& operator+=(const BMP& image);

    private:
    void init(const char* file_name);
    void init(const std::string& file_name);
    void write(const std::string& name) const;
    void update();
    void stitch(const BMP& image, bool stitch_type=HORIZONTAL_STITCH);
    void allocate(std::vector<Color>::size_type size);
};
