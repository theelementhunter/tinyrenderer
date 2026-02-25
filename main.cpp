#include <cmath>
#include "tgaimage.h"

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};

int main(int argc, char** argv) {
    constexpr int width  = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    int ax =  7, ay =  3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    framebuffer.set(ax, ay, white);
    framebuffer.set(bx, by, white);
    framebuffer.set(cx, cy, white);

    // framebuff.set(x-coord, y-coord, color)
    // x-coord and y-coord are changing as t goes from 0 to 1
    // Eqns:
    // x(t) = a_x + t * (b_x - a_x)
    // y(t) = a_y + t * (b_y - a_y)

    //blue from point a to b
    for (int i = 0; i < 50; i++) {
        double t = i / 50.0;

        // blue from point a to b
        double x1 = ax + (t * (bx - ax));
        double y1 = ay + (t * (by - ay));

        // green from c to b
        double x2 = cx + (t * (bx - cx));
        double y2 = cy + (t * (by - cy));

        // green from c to a
        double x3 = cx + (t * (ax - cx));
        double y3 = cy + (t * (ay - cy));

        // green from a to c
        double x4 = ax + (t * (cx - ax));
        double y4 = ay + (t * (cy - ay));



        framebuffer.set(x1, y1, blue);
        framebuffer.set(x2, y2, green);
        framebuffer.set(x3, y3, yellow);
        framebuffer.set(x4, y4, red);

    }


    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}
