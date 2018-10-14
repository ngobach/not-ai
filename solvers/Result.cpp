#include "Result.h"
#include "../CImg.h"

solver::Result::Result() {}
solver::Result::Result(TestCase* testcase) : origin(testcase->origin), basePath(testcase->basePath) {}

void solver::Result::visualize() {
    using cimg_library::CImg;
    CImg<unsigned char> frame((this->basePath + "/" + this->origin).data());
    frame.fill(0x33);
    for (auto &part : this->items) {
        CImg<unsigned char> imgPart((this->basePath + "/" + part.name).data());
        if (part.r) {
            imgPart.rotate(part.r, 0, 0);
        }
        frame.draw_image(part.x, part.y, imgPart);
    }
    frame.display("Visualized");
}