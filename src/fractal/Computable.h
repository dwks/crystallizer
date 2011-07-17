#ifndef CRYSTALLIZER_FRACTAL__COMPUTABLE_H
#define CRYSTALLIZER_FRACTAL__COMPUTABLE_H

#include <complex>

#include "config.h"

namespace Crystallizer {
namespace Fractal {

class Computable {
public:
	virtual ~Computable() {}
	
	virtual std::complex<real> calculate(std::complex<real> z) = 0;
};

}  // namespace Fractal
}  // namespace Crystallizer

#endif
