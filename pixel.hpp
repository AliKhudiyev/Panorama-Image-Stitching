
#pragma once

#define X_POS 0
#define Y_POS 1

typedef unsigned char uchar;

struct Color{
    uchar r_=0, g_=0, b_=0, a_=1;

    Color()=default;
    Color(uchar r, uchar g, uchar b, uchar a=1): 
        r_(r), g_(g), b_(b), a_(a) {}
    void Info() const;
    ~Color(){}

    Color multiply(double coef) const;

    Color operator+(const Color& color) const;
    Color operator*(double coef) const;

    private:
    void check();
};

class Pixel{
    typedef int position;

    private:
    Color color_;
    position x_, y_;

    public:
    Pixel()=default;
    Pixel(const Color& color): 
        color_(color) {}
    void set(char color_name, uchar value);
    void set(uchar r, uchar g, uchar b);
    uchar get(char color_name) const;
    position get_pos(bool pos) const;
    const Color& color() const;
    ~Pixel(){}
};
