#ifndef FOURCAMSVIDEOSTITCHING_H
#define FOURCAMSVIDEOSTITCHING_H

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
class fourCamsVideoStitching;
}

class fourCamsVideoStitching : public QWidget
{
    Q_OBJECT

public:
    explicit fourCamsVideoStitching(QWidget *parent = 0);
    ~fourCamsVideoStitching();
    Mat findHMatrix(Mat image1,Mat image2);
    void CalcFourCorner1(Mat image1);
    void CalcFourCorner2(Mat image1);
    void CalcFourCorner3(Mat image1);
    Mat imageMix1(Mat image1,Mat image2);
    Mat imageMix2(Mat image1,Mat image2);
    Mat imageMix3(Mat image1,Mat image2);
private slots:
    void on_HMatrixCalcBtn_clicked();

    void on_videoStitchingBtn_clicked();

private:
    Ui::fourCamsVideoStitching *ui;
    Mat H12,H23,H34;
    CvPoint leftTop1,leftBottom1,rightTop1,rightBottom1;
    CvPoint leftTop2,leftBottom2,rightTop2,rightBottom2;
    CvPoint leftTop3,leftBottom3,rightTop3,rightBottom3;
};

#endif // FOURCAMSVIDEOSTITCHING_H
