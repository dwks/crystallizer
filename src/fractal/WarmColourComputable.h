#ifndef CRYSTALLIZER_FRACTAL__WARM_COLOUR_COMPUTABLE_H
#define CRYSTALLIZER_FRACTAL__WARM_COLOUR_COMPUTABLE_H

#include "ColourComputable.h"

namespace Crystallizer {
namespace Fractal {

class WarmColourComputable : public ColourComputable {
private:
	int colouring_interval;
public:
	WarmColourComputable(int colouring_interval = 64) : colouring_interval(colouring_interval) {}
	virtual ~WarmColourComputable() {}
	
	virtual void colourPoint(DataPoint p, int iterations, real *result);
};

}  // namespace Fractal
}  // namespace Crystallizer

#endif
