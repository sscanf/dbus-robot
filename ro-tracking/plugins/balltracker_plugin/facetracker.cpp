#include "QDebug"
#include "opencv2/cudawarping.hpp"
#include "qvector3d.h"
#include <opencv2/cudaarithm.hpp>
#include "facetracker.h"

#ifdef QT_DEBUG
#pragma GCC push_options
#pragma GCC optimize("O0")
#endif

using namespace std;

faceTracker::faceTracker(const VideoCapture &capture, QObject *parent)
    : QObject{parent}
    , m_capture(capture) {

    qDebug() << cv::cuda::getCudaEnabledDeviceCount();
    if (cv::cuda::getCudaEnabledDeviceCount() == 0) {
        qDebug() << "No GPU found or the library is compiled without CUDA support";
    }


    Ptr<cuda::CascadeClassifier> cascade_gpu_upperbody, cascade_gpu_lowerbody, cascade_gpu_fullbody;
    cv::cuda::printShortCudaDeviceInfo(cv::cuda::getDevice());

    cout << cv::getBuildInformation() << endl;

    QString opencv_path = "/usr/share/opencv/";

    QString upperbody_cascade_name = opencv_path + "/data/HS22x20/HS.xml"; //head and sholders
    //The below are CUDA Classisfier does not work with older format Cascade xmls; the below are from OpenCV source
    QString cuda_lowerbody_cascade_name = opencv_path + "/data/haarcascades_cuda/haarcascade_lowerbody.xml";
    QString cuda_fullbody_cascade_name = opencv_path + "/data/haarcascades_cuda/haarcascade_fullbody.xml";

    qDebug() << "head and Shoulder Cascade Name" << upperbody_cascade_name << "Colored GREEN Rectangle";
    qDebug() << "lowerbody_cascade_name" << cuda_lowerbody_cascade_name << "Colored BLUE Rectangle";
    qDebug() << "fullbody_cascade_name" << cuda_fullbody_cascade_name << "Colored RED Rectangle";

    //Load the GPU/CUdA Compliant  video cascaders
    cascade_gpu_upperbody = cuda::CascadeClassifier::create(upperbody_cascade_name.toLocal8Bit().constData());
    cascade_gpu_lowerbody = cuda::CascadeClassifier::create(cuda_lowerbody_cascade_name.toLocal8Bit().constData());
    cascade_gpu_fullbody = cuda::CascadeClassifier::create(cuda_fullbody_cascade_name.toLocal8Bit().constData());
    cout << "Created the CUDA HAAR Classifiers" << endl;



    Ptr<cuda::CascadeClassifier> m_cascade = cuda::CascadeClassifier::create("/usr/share/opencv4/cuda/haarcascade_frontalface_alt.xml");




    qDebug() << "faceTracker constructor";
}

void faceTracker::convertAndResize(const Mat &src, Mat &gray, Mat &resized, double scale) {
    if (src.channels() == 3) {
        cv::cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src;
    }

    Size sz(cvRound(gray.cols * scale), cvRound(gray.rows * scale));

    if (scale != 1) {
        cv::resize(gray, resized, sz);
    } else {
        resized = gray;
    }
}

void faceTracker::convertAndResize(const cuda::GpuMat &src, cuda::GpuMat &gray, cuda::GpuMat &resized, double scale) {
    if (src.channels() == 3) {
        cv::cuda::cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src;
    }
    Size sz(cvRound(gray.cols * scale), cvRound(gray.rows * scale));
    if (scale != 1) {
        cv::cuda::resize(gray, resized, sz);
    } else {
        resized = gray;
    }
}

void faceTracker::capture(Mat &dst, QVector3D &point3D) {
    vector<Rect> faces, faces2;
    Mat          src;
    cuda::GpuMat frame_gpu, gray_gpu, resized_gpu, facesBuf_gpu;
    bool         findLargestObject = false;
    Size         minSize           = Size(30, 30);

    bool bSuccess = m_capture.read(src); // read a new frame from video
    if (!bSuccess) {                     // if not success, break loop
        qDebug() << "Cannot read a frame from video stream";
    } else {

        frame_gpu.upload(src);
//        cuda::cvtColor(src, dst, COLOR_BGR2GRAY);
//        cuda::equalizeHist(dst, dst);

        convertAndResize(frame_gpu, gray_gpu, resized_gpu, 1.0);
        m_cascade->setScaleFactor(1.2);
        m_cascade->detectMultiScale(resized_gpu, facesBuf_gpu);

        //        m_cascade->detectMultiScale(dst, //
        //                                   faces,
        //                                   1.1,
        //                                   3,
        //                                   (findLargestObject ? CASCADE_FIND_BIGGEST_OBJECT : 0) | CASCADE_SCALE_IMAGE,
        //                                   minSize);
    }

    if (faces.size()) {
        Point center(faces[0].x + faces[0].width / 2, faces[0].y + faces[0].height / 2);

        int    areaFrame = faces[0].width * faces[1].height;
        int    areaSrc   = src.cols * src.rows;
        double dist      = (double)areaFrame / areaSrc * 100;
        qDebug() << areaFrame << areaSrc << (double)dist;
        point3D = QVector3D(center.x, center.y, dist);

        rectangle(dst, faces[0], Scalar(255));
    }
}

#ifdef QT_DEBUG
#pragma GCC pop_options
#endif
