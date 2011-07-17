#ifndef CRYSTALLIZER_FRACTAL__COLOUR_COMPUTABLE_H
#define CRYSTALLIZER_FRACTAL__COLOUR_COMPUTABLE_H

#include "DataPoint.h"

namespace Crystallizer {
namespace Fractal {

/** Computable class to give DataPoints a nice colour. */
class ColourComputable {
public:
	virtual ~ColourComputable() {}
	
	/** Colour a point.
		@param p The point to colour.
		@param iterations The number of iterations @a p went through before reaching bailout.
		@param result Pointer to a real[3] array.
	*/
	virtual void colourPoint(DataPoint p, int iterations, real *result) = 0;
};

}  // namespace Fractal
}  // namespace Crystallizer

#endif
