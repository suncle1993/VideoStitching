#ifndef IMAGESTITCHING_H
#define IMAGESTITCHING_H

#include <QWidget>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <QMessageBox>
using namespace cv;
using namespace std;

namespace Ui {
class imageStitching;
}

class imageStitching : public QWidget
{
    Q_OBJECT

public:
    explicit imageStitching(QWidget *parent = 0);
    ~imageStitching();
    void CalcFourCorner();

private slots:
    void on_loadImageBtn_clicked();

    void on_preProcessBtn_clicked();

    void on_featurePointDetectBtn_clicked();

    void on_featureVectorBtn_clicked();

    void on_imageMatchBtn_clicked();

    void on_findHomographyBtn_clicked();

    void on_wrapBtn_clicked();

private:
    Ui::imageStitching *ui;
    Mat image1,image2,gray_image1,gray_image2;
    vector<KeyPoint> keypoints_object,keypoints_scene;
    Mat descriptors_object, descriptors_scene;
    vector< Point2f > obj;
    vector< Point2f > scene;
    Mat H;
    //图2的四个角经矩阵H变换后的坐标
    CvPoint leftTop,leftBottom,rightTop,rightBottom;
};

#endif // IMAGESTITCHING_H
