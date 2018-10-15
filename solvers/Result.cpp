#include "Result.h"
#include "../CImg.h"

solver::Result::Result() {}
solver::Result::Result(TestCase* testcase) : origin(testcase->origin), basePath(testcase->basePath) {}

void solver::Result::visualize() {
    using cimg_library::CImg;
    using cimg_library::CImgDisplay;
    CImg<unsigned char> frame((this->basePath + "/" + this->origin).data());
    frame.normalize(0, 64);
    for (auto &part : this->items) {
        CImg<unsigned char> imgPart((this->basePath + "/" + part.name).data());
        if (part.r) {
            imgPart.rotate(part.r, 0, 0);
        }
        frame.draw_image(part.x, part.y, imgPart);
    }
    CImgDisplay display(frame, "Visualized", 0);
    while (!display.is_closed()) {
        display.wait();
    }e
}