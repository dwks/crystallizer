#ifndef CRYSTALLIZER_FRACTAL__COMPUTABLE_RANGE_H
#define CRYSTALLIZER_FRACTAL__COMPUTABLE_RANGE_H

#include "DataPoint.h"

namespace Crystallizer {
namespace Fractal {

/** Iterable range of data points. */
class ComputableRange {
public:
	class Iterator {
	private:
		ComputableRange &range;
		DataPoint point;
	public:
		Iterator(ComputableRange &range) : range(range), point(range.getStart()) {}
		
		DataPoint next();
		bool hasNext();
	private:
		DataPoint calcNext();
	};
private:
	DataPoint start;
	DataPoint end;
	DataPoint granularity;
public:
	ComputableRange(DataPoint start, DataPoint end, DataPoint granularity)
		: start(start), end(end), granularity(granularity) { checkGranularity(); }
	
	DataPoint getStart() const { return start; }
	void setStart(DataPoint start) { this->start = start; checkGranularity(); }
	
	DataPoint getEnd() const { return end; }
	void setEnd(DataPoint end) { this->end = end; checkGranularity(); }
	
	DataPoint getGranularity() const { return granularity; }
	void setGranularity(DataPoint granularity) { this->granularity = granularity; checkGranularity(); }
	
	bool isInside(DataPoint point) const;
	
	Iterator getIterator() { return Iterator(*this); }
private:
	void checkGranularity();
};

}  // namespace Fractal
}  // namespace Crystallizer

#endif
