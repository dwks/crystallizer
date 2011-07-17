#include "WarmColourComputable.h"

namespace Crystallizer {
namespace Fractal {

void WarmColourComputable::colourPoint(DataPoint p, int iterations, real *result) {
	int i = iterations % (colouring_interval*2);
	int side = i / colouring_interval;
	i %= colouring_interval;
	
	if(side == 0) {
		result[0] = 0.5 + .5*((real)i)/(colouring_interval*2);
		result[1] = 0.0;
		result[2] = 0.5 + .5*((real)i)/colouring_interval;
	}
	else {
		result[0] = 1.0 - .5*((real)i)/(colouring_interval*2);
		result[1] = 0.0;
		result[2] = 1.0 - .5*((real)i)/colouring_interval;
	}
}

}  // namespace Fractal
}  // namespace Crystallizer
