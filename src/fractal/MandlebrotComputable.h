#ifndef CRYSTALLIZER_FRACTAL__MANDLEBROT_COMPUTABLE_H
#define CRYSTALLIZER_FRACTAL__MANDLEBROT_COMPUTABLE_H

#include "Computable.h"

namespace Crystallizer {
namespace Fractal {

class MandlebrotComputable : public Computable {
public:
	virtual ~MandlebrotComputable() {}
	
	virtual int calculate(DataPoint c, real bailoutDistance, int bailoutIterations);
};

}  // namespace Fractal
}  // namespace Crystallizer

#endif
