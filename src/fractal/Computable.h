#ifndef CRYSTALLIZER_FRACTAL__COMPUTABLE_H
#define CRYSTALLIZER_FRACTAL__COMPUTABLE_H

#include "DataPoint.h"

namespace Crystallizer {
namespace Fractal {

/** Base class for fractal computation. Represents a computable function. */
class Computable {
public:
	virtual ~Computable() {}
	
	virtual DataPoint calculate(DataPoint z) = 0;
};

}  // namespace Fractal
}  // namespace Crystallizer

#endif
