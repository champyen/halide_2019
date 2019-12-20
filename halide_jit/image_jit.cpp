#include <unistd.h>

#include "Halide.h"
#include "halide_image_io.h"

using namespace Halide;
using namespace Halide::ConciseCasts;
using namespace Halide::Tools;

int main(int argc, char **argv) {

    Halide::Buffer<uint8_t> image = load_image(argv[1]);

    Halide::Func input, blur;
    Halide::Var x, y, c;

	input(x, y, c) = cast<uint16_t>(BoundaryConditions::repeat_edge(image)(x, y, c));

	// DO 3x3 blur HERE, currenly just bypass the image to output
    blur(x, y, c) = u8(input(x, y, c));

    Halide::Buffer<uint8_t> output = blur.realize(image.width(), image.height(), image.channels());

    save_image(output, "blur.png");

    printf("Success!\n");
    return 0;
}
