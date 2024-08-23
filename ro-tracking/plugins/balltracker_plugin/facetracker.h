#ifndef FACETRACKER_H
#define FACETRACKER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/core/ocl.hpp>

#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudaobjdetect.hpp>

using namespace cv;

class faceTracker : public QObject {
    Q_OBJECT
public:
    explicit faceTracker(const VideoCapture &capture, QObject *parent = nullptr);
    void capture(Mat &dst, QVector3D &point3D);

private:
    void convertAndResize(const cuda::GpuMat &src, cuda::GpuMat &gray, cuda::GpuMat &resized, double scale);
    void convertAndResize(const Mat &src, Mat &gray, Mat &resized, double scale);

public:
    VideoCapture                 m_capture;
    Ptr<cuda::CascadeClassifier> m_cascade;
    CascadeClassifier            m_nestedCascade;
    Ptr<cuda::CascadeClassifier> m_cascade_gpu;

signals:
};

#endif // FACETRACKER_H
