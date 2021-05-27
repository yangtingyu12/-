#ifndef _IMAGE_CONVERT_H_
#define _IMAGE_CONVERT_H_

#include "config.h"
#include <QImage>

#ifdef BACKGROUND_APP
#include <opencv2/opencv.hpp>  
#include <opencv2/core.hpp>
#include <opencv2/imgproc/types_c.h> 
#endif

QImage jpeg_to_QImage(uint8_t *data, int len);

#ifdef BACKGROUND_APP
cv::Mat QImage_to_cvMat(QImage image);
QImage cvMat_to_QImage(const cv::Mat& mat);
#endif

#endif	// _IMAGE_CONVERT_H_
