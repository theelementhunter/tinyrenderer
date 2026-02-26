#include <cmath>
#include "tgaimage.h"

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};

void line_maker_1(int ax, int ay, int bx, int by, TGAImage &framebuffer, TGAColor color) {
    // framebuff.set(x-coord, y-coord, color)
    // x-coord and y-coord are changing as t goes from 0 to 1
    // Eqns:
    // x(t) = a_x + t * (b_x - a_x)
    // y(t) = a_y + t * (b_y - a_y)
    for (float t=0.; t<1.; t+=0.02) {
        int x_t = std::round(ax + (t * (bx - ax)));
        int y_t = std::round(ay + (t * (by - ay)));
        framebuffer.set(x_t, y_t, color);
    }
}

void line_maker_2(int x1, int y1, int x2, int y2, TGAImage &framebuffer, TGAColor color) {

    for (float x=x1; x<=x2; x++) {
        float t_x = (x - x1) / static_cast<float>(x2 -x1); //t is always a float
        int y_t = std::round(y1 + (t_x * (y2 - y1)));
        framebuffer.set(x, y_t, color);
    }
}

void line_maker_3_my_try(int x1, int y1, int x2, int y2, TGAImage &framebuffer, TGAColor color) {

    int x1t = y1;
    int y1t = x1;
    int x2t = y2;
    int y2t = x2;

    for (float x=x1t; x<=x2t; x++) {
        float t_x = (x - x1t) / static_cast<float>(x2t -x1t); //t is always a float
        int y_t = std::round(y1t + (t_x * (y2t - y1t)));
        framebuffer.set(x, y_t, color);
    }
}

void line_maker_3(int x1, int y1, int x2, int y2, TGAImage &framebuffer, TGAColor color) {
    bool steep = std::abs(y2 - y1) > std::abs(x2 - x1);

    if (steep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }
    if (x1>x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    for (float x=x1; x<=x2; x++) {
        float t_x = (x - x1) / static_cast<float>(x2 -x1); //t is always a float
        int y_t = std::round(y1 + (t_x * (y2 - y1)));
        if (steep) {
            framebuffer.set(y_t, x, color);
        }
        else {
            framebuffer.set(x, y_t, color);
        }
    }
}

int main(int argc, char** argv) {
    constexpr int width  = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    int ax =  7, ay =  3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;


    //
    line_maker_3(ax, ay, bx, by, framebuffer, blue);
    line_maker_3(bx, by, cx, cy, framebuffer, green);
    line_maker_3(cx, cy, ax, ay, framebuffer, yellow);
    line_maker_3(ax, ay, cx, cy, framebuffer, red);

    framebuffer.set(ax, ay, white);
    framebuffer.set(bx, by, white);
    framebuffer.set(cx, cy, white);


    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}
