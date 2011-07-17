#ifndef CRYSTALLIZER_FRACTAL__COMPUTABLE_H
#define CRYSTALLIZER_FRACTAL__COMPUTABLE_H

#include "DataPoint.h"

namespace Crystallizer {
namespace Fractal {

/** Base class for fractal computation. Represents a computable function. */
class Computable {
public:
	virtual ~Computable() {}
	
	/** Perform a single depth calculation. */
	virtual int calculate(DataPoint c, real bailoutDistance, int bailoutIterations) = 0;
};

}  // namespace Fractal
}  // namespace Crystallizer

#endif
