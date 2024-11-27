// opencv_wrapper.h
#include <opencv2/opencv.hpp>
#include "opencv_wrapper.h"

#ifndef OPENCV_WRAPPER_H
#define OPENCV_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

// Function to visualize optical flow
// void visualize_optical_flow(float *flow_x, float *flow_y, int width, int height);
cv::Mat visualize_optical_flow(float *flow_x, float *flow_y, int width, int height);

#ifdef __cplusplus
}
#endif

#endif // OPENCV_WRAPPER_H

