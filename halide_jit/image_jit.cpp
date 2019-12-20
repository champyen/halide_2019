#include "Halide.h"
#include "halide_image_io.h"

using namespace Halide;
using namespace Halide::ConciseCasts;
using namespace Halide::Tools;

int main(int argc, char **argv) {

    Halide::Buffer<uint8_t> image = load_image(argv[1]);

    Halide::Func in, cast_u16, blur;
    Halide::Var x, y, c;

	in = BoundaryConditions::repeat_edge(image);
	cast_u16(x, y, c) = u16(in(x, y, c));
    blur(x, y, c) = 
		(	cast_u16(x-1, y-1, c) + cast_u16(x, y-1, c) + cast_u16(x+1, y-1, c) +
			cast_u16(x-1, y  , c) + cast_u16(x, y  , c) + cast_u16(x+1, y  , c) +
			cast_u16(x-1, y+1, c) + cast_u16(x, y+1, c) + cast_u16(x+1, y+1, c)
		)/9;

    Halide::Buffer<uint8_t> output =
        blur.realize(image.width(), image.height(), image.channels());

    save_image(output, "blur.png");

    printf("Success!\n");
    return 0;
}
