#include <stdio.h>
#include <string.h>
#include "image_convert.h"

/* C++ include C */
#ifdef __cplusplus
extern "C" {
#endif
/* C头文件 */
#ifdef __cplusplus
}
#endif

//using namespace cv;


/* jpge/mjpge convert to QImage */
QImage jpeg_to_QImage(unsigned char *data, int len)
{
	QImage qtImage;

	if(data==NULL || len<=0)
		return qtImage;

	qtImage.loadFromData(data, len);
	if(qtImage.isNull())
	{
		printf("ERROR: %s: QImage is null !\n", __FUNCTION__);
	}

	return qtImage;
}

#ifdef BACKGROUND_APP
/* 调用时要加.clone(), testMat = QImage_to_cvMat(qiamge).clone() */
cv::Mat QImage_to_cvMat(QImage qimage)
{
    cv::Mat mat;

	if(qimage.isNull())
	{
		printf("ERROR: %s: QImage is null !\n", __FUNCTION__);
		return mat;
	}
	
    switch(qimage.format())
    {
	    case QImage::Format_ARGB32:
	    case QImage::Format_RGB32:
	    case QImage::Format_ARGB32_Premultiplied:
	        mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC4, (void*)qimage.bits(), qimage.bytesPerLine());
	        break;
	    case QImage::Format_RGB888:
	        mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC3, (void*)qimage.bits(), qimage.bytesPerLine());
	        cv::cvtColor(mat, mat, CV_BGR2RGB);
	        break;
	    case QImage::Format_Indexed8:
	        mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC1, (void*)qimage.bits(), qimage.bytesPerLine());
	        break;

		default:
	        printf("ERROR: %s case default !\n", __FUNCTION__);
    }

	if(mat.empty())
	{
        printf("ERROR: %s: Mat is empty !\n", __FUNCTION__);
	}

    return mat;
}

QImage cvMat_to_QImage(const cv::Mat& mat)
{

	if(mat.empty())
		printf("Mat is empty.\n");

    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
//        qDebug() << "CV_8UC1";
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        //printf("set colors\n");
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
//        qDebug() << "CV_8UC3";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
//        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
//        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }

}

#endif
