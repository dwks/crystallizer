#include <cmath>
#include <cstdlib>

#include "log/Logger.h"
#include "ComputableRange.h"

namespace Crystallizer {
namespace Fractal {

DataPoint ComputableRange::Iterator::next() {
	DataPoint ret = point;
	point = calcNext();
	return ret;
}

bool ComputableRange::Iterator::hasNext() {
	DataPoint dp = calcNext();
	return range.isInside(dp);
}

DataPoint ComputableRange::Iterator::calcNext() {
	DataPoint p = point + DataPoint(range.getGranularity().real());
	if(!range.isInside(p))
		p = DataPoint(
			range.getStart().real(),
			point + DataPoint(
				0.0,
				range.getGranularity().imag()));
	return p;
}

bool ComputableRange::isInside(DataPoint point) const {
	if(point.real() < start.real() || point.real() > end.real()) return false;
	if(point.imag() < start.imag() || point.imag() > end.imag()) return false;
	return true;
}

void ComputableRange::checkGranularity() {
	double r_diff = end.real() - start.real();
	double i_diff = end.imag() - start.imag();
	
	if(std::fmod(r_diff, granularity.real()) > FP_ERROR) {
		LOG(FRACTAL, "ComputableRange: real size does not match granularity.");
		std::exit(0);
	}
	if(std::fmod(i_diff, granularity.imag()) > FP_ERROR) {
		LOG(FRACTAL, "ComputableRange: imaginary size does not match granularity.");
		std::exit(0);
	}
}

}  // namespace Fractal
}  // namespace Crystallizer
