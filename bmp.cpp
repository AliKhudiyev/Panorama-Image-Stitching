#include<iostream>
#include<fstream>
#include<cmath>
#include"bmp.hpp"

unsigned int BMP::n_image=0;
const std::string BMP::image_name="image";

void BMP::set(std::string name) const{
    name=name.substr(0, name.find(".bmp"));
    if(name.size()<1 || name.find('/')!=std::string::npos){
        name_=(image_name+std::to_string(n_img)+exts);
        throw Exception("Inappropriate name.", LIGHT);
    }
    name_=name+exts;
}

void BMP::modify(const std::vector<Color>& color, unsigned value, bool side){
    if(side==IMAGE_WIDTH){
        info_.image_width_=value;      
    } else{
        info_.image_height_=value;
    }
    info_.image_size_=info_.image_width_*info_.image_height_*info_.bits_per_pixel_/8;
    info_.file_size_=info_.image_size_+info_.offset_size_;
    update();

    if(color.size()!=info_.image_size_/(info_.bits_per_pixel_/8)){
        throw Exception("Inappropriate color data loading detected.", LOGIC);
    }
    color_=color;
}

const std::string& BMP::get() const{
    return name_;
}

const BMP_INFO& BMP::info() const{
    return info_;
}

void BMP::Info() const{
    std::cout<<"\n=== General Information ===\n\n";
    std::cout<<"Image name : "<<name_<<'\n';
    info_.Info();
    std::cout<<std::endl;
}

void BMP::read(const char* file_name){
    try{
        init(file_name);
    } catch(Exception& exception){
        throw exception;
    }
}

void BMP::vertical_stitch(const BMP& image){
    stitch(image, VERTICAL_STITCH);
}

void BMP::horizontal_stitch(const BMP& image){
    stitch(image, HORIZONTAL_STITCH);
}

BMP BMP::elongate(const std::vector<double>& sf, const BMP& image){
    BMP elongated_image;
    double csf;
    // auto eit=elongated_image.color_.begin();
    auto it=image.color_.begin();
    unsigned diff=image.info_.image_height_/sf.size();

    elongated_image.info_=image.info_;
    elongated_image.header_=image.header_;
    elongated_image.info_.image_width_=(double)image.info_.image_width_*sf[0];
    elongated_image.info_.file_size_=elongated_image.info_.image_width_*image.info_.image_height_*4+54;
    elongated_image.info_.image_size_=elongated_image.info_.file_size_-54;
    elongated_image.update();
    // elongated_image.allocate(elongated_image.info_.image_width_*elongated_image.info_.image_height_);
    elongated_image.color_.resize(elongated_image.info_.image_width_*image.info_.image_height_, Color(0,255,0,255));
    auto eit=elongated_image.color_.begin();

    elongated_image.Info();
    // std::cout<<"expected eit color size : "<<elongated_image.info_.image_width_*image.info_.image_height_<<'\n';
    // std::cout<<"updated new image width : "<<elongated_image.info_.image_width_<<'\n';
    std::cout<<"eit color size : "<<elongated_image.color_.size()<<'\n';
    // std::cout<<"image width : "<<image.info_.image_width_<<'\n';
    // std::cout<<"image height : "<<image.info_.image_height_<<'\n';
    // exit(0);
    unsigned width=elongated_image.info_.image_width_;
    unsigned iwidth=image.info_.image_width_;
    std::cout<<"diff : "<<diff<<'\n';
    // std::cout<<"1.7*iwidth="<<1.7*(double)iwidth<<'\n';
    
    bool pass=true;
    for(unsigned s=0;s<sf.size();++s){
        pass=true;
        // std::cout<<"approximated filled space width : "<<sf[s]*(double)iwidth<<'\n';
        std::cout<<"null filled space width : "<<(width-sf[s]*(double)iwidth)/2<<'\n';
        for(unsigned i=0;i<diff;++i){
            for(unsigned npos=0;npos<(width-sf[s]*(double)iwidth)/2;++npos, ++eit){
                *eit=Color(0,0,0,255);
            }
            csf=sf[s];
            if(pass){ std::cout<<"csf : "<<csf<<'\n'; pass=false; }
            for(unsigned l=0;l<image.info_.image_width_;++l, ++it){
                for(unsigned t=0;t<floor(csf);++t, ++eit){
                    // std::cout<<"o\n";
                    *eit=*it;
                }
                if(csf-floor(csf)<0.0001){ csf=sf[s]; continue; }
                // it->Info(); (it+1)->Info(); (it+2)->Info();
                *(eit++)=(*it).multiply(csf-floor(csf))+(*(it+1)).multiply(ceil(csf)-csf);
                double ccsf=csf;
                csf=sf[s]-ceil(ccsf)+ccsf;
                // std::cout<<"updated csf = "<<csf<<'\n';
                // (eit-1)->Info();
                // exit(0);
            }
            for(unsigned npos=0;npos<(width-sf[s]*(double)iwidth)/2;++npos, ++eit){
                *eit=Color(0,0,0,255);
            }
        }
    }
    return elongated_image;
}

void BMP::create(std::string name) const{
    if(info_.file_size_==0){
        throw Exception("Image data doesn't exist.", LOGIC);
    }
    if(!name.empty()){
        try{
            set(name);
        } catch(Exception& exception){
            std::cout<<exception.get()<<'\n';
        }
    } else if(name_[0]==errchar.c_str()[0]){
        try{
            set(errchar);
        } catch(Exception& exception){
            std::cout<<exception.get()<<'\n';
        }
    }
    write(name_);
}

void BMP::remove(){
    info_.clear();
    header_.clear();
    color_.clear();
}

void BMP::operator=(const BMP& image){
    info_=image.info_;
    header_=image.header_;
    color_=image.color_;
}

BMP BMP::operator+(const BMP& image) const{
    BMP bmp;
    bmp=*this;
    bmp.stitch(image);
    return bmp;
}

BMP& BMP::operator+=(const BMP& image){
    stitch(image);
    return *this;
}

void BMP::init(const char* file_name){
    std::ifstream image(file_name, std::ios::in | std::ios::binary);
    if(!image) throw Exception("File couldn't be opened.", FATAL);

    image.read((char*)&info_.signature_, 2);
    if(info_.signature_!=19778) throw Exception("Not a BMP file.");

    image.read((char*)&info_.file_size_, sizeof(unsigned int));

    image.seekg(10, image.beg);
    image.read((char*)&info_.offset_size_, sizeof(unsigned int));
    
    image.seekg(18, image.beg);
    image.read((char*)&info_.image_width_, 4);

    image.seekg(28, image.beg);
    image.read((char*)&info_.bits_per_pixel_, 2);

    info_.header_size_=info_.offset_size_-14;
    info_.image_size_=info_.file_size_-info_.offset_size_;
    info_.image_height_=info_.image_size_/info_.image_width_/(info_.bits_per_pixel_/8);

    header_.resize(info_.offset_size_);
    color_.resize(info_.image_size_/4);

    image.seekg(0, image.beg);
    image.read((char*)&header_[0], info_.offset_size_);
    image.read((char*)&color_[0], info_.image_size_); // /(info_.bits_per_pixel_/4)
    
    std::cout<<"init called with color values : ";
    
    std::cout<<(int)color_[0].r_<<", "<<(int)color_[0].g_<<", ";
    std::cout<<(int)color_[0].b_<<", "<<(int)color_[0].a_<<'\n';

    image.close();
}

void BMP::init(const std::string& file_name){
    try{
        init(file_name.c_str());
    } catch(Exception& exception){
        throw exception;
    }
}

void BMP::write(const std::string& name) const{
    std::ofstream image(name, std::ios::out | std::ios::binary);
    image.write((char*)&header_[0], header_.size());
    image.write((char*)&color_[0], info_.image_size_);
    image.close();
}

void BMP::update(){
    std::vector<byte4> updated_file_size(4);
    std::vector<byte4> updated_image_width(4);
    std::vector<byte4> updated_image_height(4);
    std::vector<byte4> updated_image_size(4);

    updated_file_size=info_.get_byte_vector(FILE_SIZE, 4);
    updated_image_width=info_.get_byte_vector(WIDTH, 4);
    updated_image_height=info_.get_byte_vector(HEIGHT, 4);
    updated_image_size=info_.get_byte_vector(IMAGE_SIZE, 4);

    for(unsigned pos=2, i=0;i<4;++pos, ++i){
        header_[pos]=updated_file_size[i];
    }
    for(unsigned pos=18, i=0;i<4;++pos, ++i){
        header_[pos]=updated_image_width[i];
    }
    for(unsigned pos=22, i=0;i<4;++pos, ++i){
        header_[pos]=updated_image_height[i];
    }
    // for(unsigned pos=34, i=0;i<4;++pos, ++i){
    //     header_[pos]=updated_image_size[i];
    // }
}

void BMP::stitch(const BMP& image, bool stitch_type){
    std::cout<<"\n=== Stitching started. ===\n";
    
    std::vector<Color> color(color_.size()+image.color_.size());
    auto cit=color.begin();
    auto it1=color_.begin();
    auto it2=image.color_.begin();

    if(stitch_type==VERTICAL_STITCH){
        for(;it1<color_.end();++it1, ++cit) *cit=*it1;
        for(;it2<image.color_.end();++it2, ++cit) *cit=*it2;
        modify(color,info_.image_height_+image.info_.image_height_, IMAGE_HEIGHT);
    } else if(stitch_type==HORIZONTAL_STITCH){
        unsigned int width=info_.image_width_;
        unsigned int iwidth=image.info_.image_width_;
    
        for(unsigned k=0;cit<color.end();++k){
            for(unsigned w=0;w<width;++cit, ++it1, ++w){ *cit=*it1; }
            for(unsigned iw=0;iw<iwidth;++cit, ++it2, ++iw){ *cit=*it2; }
        }
        modify(color,info_.image_width_+image.info_.image_width_);
    }
    std::cout<<" ||| Images have been stitched succesfully.\n";
}

void BMP::allocate(std::vector<Color>::size_type size){
    color_.resize(size);
}
