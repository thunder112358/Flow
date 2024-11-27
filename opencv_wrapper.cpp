#include <opencv2/opencv.hpp>
#include "opencv_wrapper.h"
#include <iostream>
extern "C" {
    // Function to visualize optical flow

/* Arrow 
void visualize_optical_flow( float *u1,  float *u2, int nx, int ny) {
    cv::Mat canvas(ny, nx, CV_8UC3, cv::Scalar(0, 0, 0));

    int step = 10; // Skip every 'step' pixels to draw fewer vectors
    for (int y = 0; y < ny; y += step) {
        for (int x = 0; x < nx; x += step) {
            cv::Point2f pt1(x, y);
            std::cout << pt1 << std::endl; 
            cv::Point2f pt2(x + u1[y * nx + x], y + u2[y * nx + x]);
            cv::arrowedLine(canvas, pt1, pt2, cv::Scalar(0, 255, 0), 1, cv::LINE_AA);
        }
    }

    cv::imshow("Motion Vectors", canvas);
    cv::waitKey(0);
}
*/

    void visualize_optical_flow(const char *window_name, float *flow_x, float *flow_y, int width, int height) {
        cv::Mat flow_x_mat(height, width, CV_32F, flow_x); 
        cv::Mat flow_y_mat(height, width, CV_32F, flow_y); 

        cv::Mat mag, ang;
        cv::cartToPolar(flow_x_mat, flow_y_mat, mag, ang, true);

        cv::normalize(mag, mag, 0, 1, cv::NORM_MINMAX);

        cv::Mat hsv(height, width, CV_8UC3);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                hsv.at<cv::Vec3b>(y, x)[0] = static_cast<uchar>(ang.at<float>(y, x) / 2);  
                hsv.at<cv::Vec3b>(y, x)[1] = 255;                                          
                hsv.at<cv::Vec3b>(y, x)[2] = static_cast<uchar>(mag.at<float>(y, x) * 255); 
            }
        }
        cv::cvtColor(hsv, hsv, cv::COLOR_HSV2BGR);

        cv::imshow(window_name, hsv);
        cv::waitKey(0);
    }
}
