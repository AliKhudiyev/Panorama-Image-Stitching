#include<iostream>
#include"pixel.hpp"
#include"exception.hpp"

void Color::Info() const{
    std::cout<<"\n=== Color info ===\n\n";
    std::cout<<"R : "<<(unsigned)r_<<'\n';
    std::cout<<"G : "<<(unsigned)g_<<'\n';
    std::cout<<"B : "<<(unsigned)b_<<'\n';
    std::cout<<"A : "<<(unsigned)a_<<'\n';
    std::cout<<std::endl;
}

Color Color::operator+(const Color& color) const{
    Color final_color;

    final_color.r_=r_+color.r_;
    final_color.g_=g_+color.g_;
    final_color.b_=b_+color.b_;
    final_color.a_=a_;

    try{
        final_color.check();
    } catch(Exception& exception){
        std::cout<<exception.get();
    }
    return final_color;
}

Color Color::operator*(double coef) const{
    Color color;

    color.r_=r_*coef;
    color.g_=g_*coef;
    color.b_=b_*coef;
    color.a_=a_;
    
    try{
        color.check();
    } catch(Exception& exception){
        std::cout<<exception.get();
    }
    return color;
}

bool Color::operator==(const Color& color) const{
    if(r_+CSDIFF>color.r_ && r_-CSDIFF<color.r_ &&
       g_+CSDIFF>color.g_ && g_-CSDIFF<color.g_ && 
       b_+CSDIFF>color.b_ && b_-CSDIFF<color.b_ && 
       a_+CSDIFF>color.a_ && a_-CSDIFF<color.a_) return true;
    return false;
}

void Color::check(){
    bool is_exception=false;
    if(r_>255){
        r_=255;
        is_exception=true;
    } else if(r_<0){
        r_=0;
        is_exception=true;
    }
    if(g_>255){
        g_=255;
        is_exception=true;
    } else if(g_<0){
        g_=0;
        is_exception=true;
    }
    if(b_>255){
        b_=255;
        is_exception=true;
    } else if(b_<0){
        b_=0;
        is_exception=true;
    }

    if(is_exception){
        throw Exception("Undefined color value.", LIGHT);
    }
}

void Pixel::set(char color_name, uchar value){
    switch(color_name){
        case 'r':
            color_.r_=value;
            break;
        case 'g':
            color_.g_=value;
            break;
        case 'b':
            color_.b_=value;
            break;
        case 'a':
            color_.a_=value;
            break;
        default:
            throw Exception("Not such a color option!");
            break;
    }
}

uchar Pixel::get(char color_name) const{
    switch(color_name){
        case 'r': return color_.r_;
        case 'g': return color_.g_;
        case 'b': return color_.b_;
        case 'a': return color_.a_;
        throw Exception("Not such a color option!");
    }
    return 0;
}

const Color& Pixel::color() const{
    return color_;
}
