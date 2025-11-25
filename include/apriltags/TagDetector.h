#ifndef TAGDETECTOR_H
#define TAGDETECTOR_H

#include "apriltags/MathUtil.h"
#include "apriltags//TagDetection.h"
#include "apriltags//TagFamily.h"
#include "apriltags//FloatImage.h"

#include <vector>

#include "opencv2/opencv.hpp"


namespace AprilTags {

class TagDetector {
public:

	const TagFamily thisTagFamily;

	//! Constructor
  // note: TagFamily is instantiated here from TagCodes
	TagDetector(const TagCodes& tagCodes, const size_t blackBorder=2) : thisTagFamily(tagCodes, blackBorder) {}

	std::vector<TagDetection> extractTags(const cv::Mat& image);

};

} // namespace

#endif
