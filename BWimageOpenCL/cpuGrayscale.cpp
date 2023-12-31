#include "cpuGrayscale.h"

cv::Mat getGrayPtr(cv::Mat image)
{
    cv::Mat _img(image.rows, image.cols, CV_8UC1);
    uchar _imgPix;
    for (int x = 0; x < image.rows; x++)
    {
        cv::Vec3b* imageRow = image.ptr<cv::Vec3b>(x);
        uchar* _imgRow = _img.ptr<uchar>(x);
        for (int y = 0; y < image.cols; y++)
        {
            _imgPix = getGrayscaledPixel(imageRow[y][2], imageRow[y][1], imageRow[y][0]); 
            _imgRow[y] = _imgPix;
        }
    }
    return _img;
}

cv::Mat getGrayPtrParallel_for(cv::Mat image)
{
    cv::Mat imageGray(image.rows, image.cols, CV_8UC1);
    Concurrency::parallel_for(size_t(0), size_t(image.rows), [&image, &imageGray](size_t x)
        {
            uchar _imgPix;
            cv::Vec3b* _imageOriginRow = image.ptr<cv::Vec3b>(x);
            uchar* _imgRow = imageGray.ptr<uchar>(x);
            for (int y = 0; y < image.cols; y++)
            {
                _imgPix = getGrayscaledPixel(_imageOriginRow[y][2], _imageOriginRow[y][1], _imageOriginRow[y][0]);
                _imgRow[y] = _imgPix;
            }
        });
    return imageGray;
}

[[Deprecated("This isn't working. Method from docs")]]
cv::Mat pixelNormalization(cv::Mat image)
{
    cv::Mat _image;
    double _minRange, _MaxRange;
    cv::Point _mLoc, _MLoc;
    try
    {
        cv::minMaxLoc(image, &_minRange, &_MaxRange, &_mLoc, &_MLoc);
        image.convertTo(_image, CV_8U, 255.0 / (_MaxRange - _minRange), -255 / _minRange);
        return _image;
    }
    catch (cv::Exception cvExp)
    {
        std::cout << "Exception: " << cvExp.what() << " (" << cvExp.err << ")\n";
    }
    return image;
}

cv::Mat getGrayByEveryPixel(cv::Mat image)
{
    int _rows = image.size[0]; // ���-�� �������� �� ���������
    int _columns = image.size[1]; // �� ���������
    cv::Mat _imageResult(_rows, _columns, CV_8UC1);
    for (int x = 0; x < _rows; x++)
    {
        for (int y = 0; y < _columns; y++)
        {
            cv::Vec3b pix = image.at<cv::Vec3b>(x, y);
            float gray = getGrayscaledPixel(pix[0], pix[1], pix[2]);
            _imageResult.at<uchar>(x, y) = uchar(gray);
        }
    }
    return _imageResult;
}

float getGrayscaledPixel(int R, int G, int B)
{
    return 0.299 * R + 0.587 * G + 0.114 * B;
}