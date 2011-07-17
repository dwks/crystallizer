#include "MandlebrotComputable.h"

namespace Crystallizer {
namespace Fractal {

int MandlebrotComputable::calculate(DataPoint c, real bailoutDistance, int bailoutIterations) {
	int iteration = 0;
	DataPoint z = c;
	for(; iteration < bailoutIterations; iteration ++) {
		z = z*z + c;
		if(abs(z) > bailoutDistance) break;
	}
	return iteration;
}

}  // namespace Fractal
}  // namespace Crystallizer
