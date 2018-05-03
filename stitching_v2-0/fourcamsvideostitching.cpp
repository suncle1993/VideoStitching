#include "fourcamsvideostitching.h"
#include "ui_fourcamsvideostitching.h"

fourCamsVideoStitching::fourCamsVideoStitching(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fourCamsVideoStitching)
{
    ui->setupUi(this);
}

fourCamsVideoStitching::~fourCamsVideoStitching()
{
    delete ui;
}

void inline rotate_90n(cv::Mat &src, cv::Mat &dst, int angle)
{
    cv::transpose(src, dst);
    cv::flip(dst, dst, 0);
    /*
    dst.create(src.size(), src.type());
    if(angle == 270 || angle == -90){
        // Rotate clockwise 270 degrees
        cv::transpose(src, dst);
        cv::flip(dst, dst, 0);
    }else if(angle == 180 || angle == -180){
        // Rotate clockwise 180 degrees
        cv::flip(src, dst, -1);
    }else if(angle == 90 || angle == -270){
        // Rotate clockwise 90 degrees
        cv::transpose(src, dst);
        cv::flip(dst, dst, 1);
    }else if(angle == 360 || angle == 0){
        if(src.data != dst.data){
            src.copyTo(dst);
        }
    }
    */
}

void fourCamsVideoStitching::CalcFourCorner1(Mat image1)
{
    Mat Htmp;
    H12.copyTo(Htmp);
    CvMat cvH=Htmp;


    //计算图1的四个角经矩阵H变换后的坐标
    double v2[]={0,0,1};//左上角
    double v1[3];//变换后的坐标值
    CvMat V2 = cvMat(3,1,CV_64FC1,v2);
    CvMat V1 = cvMat(3,1,CV_64FC1,v1);

    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    leftTop1.x = cvRound(v1[0]/v1[2]);
    leftTop1.y = cvRound(v1[1]/v1[2]);
    cout<<leftTop1.x<<" "<<leftTop1.y<<endl;


    //将v2中数据设为左下角坐标
    v2[0] = 0;
    v2[1] = image1.rows;
    V2 = cvMat(3,1,CV_64FC1,v2);
    V1 = cvMat(3,1,CV_64FC1,v1);
    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    leftBottom1.x = cvRound(v1[0]/v1[2]);
    leftBottom1.y = cvRound(v1[1]/v1[2]);
    cout<<leftBottom1.x<<" "<<leftBottom1.y<<endl;

    //将v2中数据设为右上角坐标
    v2[0] = image1.cols;
    v2[1] = 0;
    V2 = cvMat(3,1,CV_64FC1,v2);
    V1 = cvMat(3,1,CV_64FC1,v1);
    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    rightTop1.x = cvRound(v1[0]/v1[2]);
    rightTop1.y = cvRound(v1[1]/v1[2]);
    cout<<rightTop1.x<<" "<<rightTop1.y<<endl;

    //将v2中数据设为右下角坐标
    v2[0] = image1.cols;
    v2[1] = image1.rows;
    V2 = cvMat(3,1,CV_64FC1,v2);
    V1 = cvMat(3,1,CV_64FC1,v1);
    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    rightBottom1.x = cvRound(v1[0]/v1[2]);
    rightBottom1.y = cvRound(v1[1]/v1[2]);
    cout<<rightBottom1.x<<" "<<rightBottom1.y<<endl;

}
void fourCamsVideoStitching::CalcFourCorner2(Mat image1)
{
    Mat Htmp;
    H23.copyTo(Htmp);
    CvMat cvH=Htmp;


    //计算图1的四个角经矩阵H变换后的坐标
    double v2[]={0,0,1};//左上角
    double v1[3];//变换后的坐标值
    CvMat V2 = cvMat(3,1,CV_64FC1,v2);
    CvMat V1 = cvMat(3,1,CV_64FC1,v1);

    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    leftTop2.x = cvRound(v1[0]/v1[2]);
    leftTop2.y = cvRound(v1[1]/v1[2]);
    cout<<leftTop2.x<<" "<<leftTop2.y<<endl;


    //将v2中数据设为左下角坐标
    v2[0] = 0;
    v2[1] = image1.rows;
    V2 = cvMat(3,1,CV_64FC1,v2);
    V1 = cvMat(3,1,CV_64FC1,v1);
    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    leftBottom2.x = cvRound(v1[0]/v1[2]);
    leftBottom2.y = cvRound(v1[1]/v1[2]);
    cout<<leftBottom2.x<<" "<<leftBottom2.y<<endl;

    //将v2中数据设为右上角坐标
    v2[0] = image1.cols;
    v2[1] = 0;
    V2 = cvMat(3,1,CV_64FC1,v2);
    V1 = cvMat(3,1,CV_64FC1,v1);
    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    rightTop2.x = cvRound(v1[0]/v1[2]);
    rightTop2.y = cvRound(v1[1]/v1[2]);
    cout<<rightTop2.x<<" "<<rightTop2.y<<endl;

    //将v2中数据设为右下角坐标
    v2[0] = image1.cols;
    v2[1] = image1.rows;
    V2 = cvMat(3,1,CV_64FC1,v2);
    V1 = cvMat(3,1,CV_64FC1,v1);
    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    rightBottom2.x = cvRound(v1[0]/v1[2]);
    rightBottom2.y = cvRound(v1[1]/v1[2]);
    cout<<rightBottom2.x<<" "<<rightBottom2.y<<endl;

}

void fourCamsVideoStitching::CalcFourCorner3(Mat image1)
{
    Mat Htmp;
    H34.copyTo(Htmp);
    CvMat cvH=Htmp;


    //计算图1的四个角经矩阵H变换后的坐标
    double v2[]={0,0,1};//左上角
    double v1[3];//变换后的坐标值
    CvMat V2 = cvMat(3,1,CV_64FC1,v2);
    CvMat V1 = cvMat(3,1,CV_64FC1,v1);

    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    leftTop3.x = cvRound(v1[0]/v1[2]);
    leftTop3.y = cvRound(v1[1]/v1[2]);
    cout<<leftTop3.x<<" "<<leftTop3.y<<endl;


    //将v2中数据设为左下角坐标
    v2[0] = 0;
    v2[1] = image1.rows;
    V2 = cvMat(3,1,CV_64FC1,v2);
    V1 = cvMat(3,1,CV_64FC1,v1);
    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    leftBottom3.x = cvRound(v1[0]/v1[2]);
    leftBottom3.y = cvRound(v1[1]/v1[2]);
    cout<<leftBottom3.x<<" "<<leftBottom3.y<<endl;

    //将v2中数据设为右上角坐标
    v2[0] = image1.cols;
    v2[1] = 0;
    V2 = cvMat(3,1,CV_64FC1,v2);
    V1 = cvMat(3,1,CV_64FC1,v1);
    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    rightTop3.x = cvRound(v1[0]/v1[2]);
    rightTop3.y = cvRound(v1[1]/v1[2]);
    cout<<rightTop3.x<<" "<<rightTop3.y<<endl;

    //将v2中数据设为右下角坐标
    v2[0] = image1.cols;
    v2[1] = image1.rows;
    V2 = cvMat(3,1,CV_64FC1,v2);
    V1 = cvMat(3,1,CV_64FC1,v1);
    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    rightBottom3.x = cvRound(v1[0]/v1[2]);
    rightBottom3.y = cvRound(v1[1]/v1[2]);
    cout<<rightBottom3.x<<" "<<rightBottom3.y<<endl;

}


Mat fourCamsVideoStitching::findHMatrix(Mat image1,Mat image2)
{
    //
    Mat H;
    Mat gray_image1,gray_image2;
    vector<KeyPoint> keypoints_object,keypoints_scene;
    Mat descriptors_object, descriptors_scene;
    vector< Point2f > obj;
    vector< Point2f > scene;


    cvtColor(image1,gray_image1,CV_RGB2GRAY);
    cvtColor(image2,gray_image2,CV_RGB2GRAY);

    int minHessian = 400;
    SurfFeatureDetector detector(minHessian);
    detector.detect(gray_image1,keypoints_object);
    detector.detect(gray_image2,keypoints_scene);

    SurfDescriptorExtractor extractor;
    extractor.compute( gray_image1, keypoints_object, descriptors_object );
    extractor.compute( gray_image2, keypoints_scene, descriptors_scene );

    FlannBasedMatcher matcher;
    vector< DMatch > matches;
    matcher.match( descriptors_object, descriptors_scene, matches );
    double max_dist = 0;
    double min_dist = 100;
    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors_object.rows; i++ )
    {
        double dist = matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }

    //-- Use only "good" matches (i.e. whose distance is less than 3*min_dist )
    vector< DMatch > good_matches;
    for( int i = 0; i < descriptors_object.rows; i++ )
    {
        if( matches[i].distance < 3*min_dist )
        {
            good_matches.push_back( matches[i]);
        }
    }

    for( unsigned int i = 0; i < good_matches.size(); i++ )
    {
        //-- Get the keypoints from the good matches
        obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
        scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
    }

    H = findHomography( obj, scene, CV_RANSAC );

    return  H;
}

Mat fourCamsVideoStitching::imageMix1(Mat image1,Mat image2)
{
    Mat result;
    //todo
    int start = MIN(leftTop1.x,leftBottom1.x) ;//开始位置，即重叠区域的左边界
    double alpha = 1;//img2中像素的权重

    warpPerspective(image1,result,H12,cv::Size(MIN(rightTop1.x,rightBottom1.x),image1.rows));

    //加权平均
    Mat image2Roi(image2,cv::Rect(0,0,MIN(leftTop1.x,leftBottom1.x),image2.rows));
    Mat resultRoi(result,cv::Rect(0,0,MIN(leftTop1.x,leftBottom1.x),result.rows));
    image2Roi.copyTo(resultRoi);
    //imshow("result12before",result);//显示为融合之前的图像

    double processWidth = image2.cols - start;//重叠区域的宽度

    for(int i=0; i<result.rows; i++)//遍历行
    {
         uchar *image2P=image2.ptr<uchar>(i);
         uchar *resultP=result.ptr<uchar>(i);
         for(int j=start; j<image2.cols; j++)//遍历重叠区域的列
         {
             if(resultP[j*3] < 50 && resultP[j*3+1] < 50 && resultP[j*3+2] < 50 )
             {
                  alpha = 1;
             }
             else
             {   //img2像素的权重，与当前处理点距重叠区域左边界的距离成正比
                 alpha = (processWidth-(j-start)) / processWidth ;
             }
             resultP[j*3] = image2P[j*3] * alpha + resultP[j*3] * (1-alpha);//B通道
             resultP[j*3+1] = image2P[j*3+1] * alpha + resultP[j*3+1] * (1-alpha);//G通道
             resultP[j*3+2] = image2P[j*3+2] * alpha + resultP[j*3+2] * (1-alpha);//R通道
         }
    }
    //imshow("result",result);
    return result;
}

Mat fourCamsVideoStitching::imageMix2(Mat image1,Mat image2)
{
    Mat result;
    //todo
    int start = MIN(leftTop2.x,leftBottom2.x) ;//开始位置，即重叠区域的左边界
    double alpha = 1;//img2中像素的权重

    warpPerspective(image1,result,H23,cv::Size(MIN(rightTop2.x,rightBottom2.x),image1.rows));

    //加权平均
    Mat image2Roi(image2,cv::Rect(0,0,MIN(leftTop2.x,leftBottom2.x),image2.rows));
    Mat resultRoi(result,cv::Rect(0,0,MIN(leftTop2.x,leftBottom2.x),result.rows));
    image2Roi.copyTo(resultRoi);
    //imshow("result1",result);//显示为融合之前的图像

    double processWidth = image2.cols - start;//重叠区域的宽度

    for(int i=0; i<result.rows; i++)//遍历行
    {
         uchar *image2P=image2.ptr<uchar>(i);
         uchar *resultP=result.ptr<uchar>(i);
         for(int j=start; j<image2.cols; j++)//遍历重叠区域的列
         {
             if(resultP[j*3] < 50 && resultP[j*3+1] < 50 && resultP[j*3+2] < 50 )
             {
                  alpha = 1;
             }
             else
             {   //img2像素的权重，与当前处理点距重叠区域左边界的距离成正比
                 alpha = (processWidth-(j-start)) / processWidth ;
             }
             resultP[j*3] = image2P[j*3] * alpha + resultP[j*3] * (1-alpha);//B通道
             resultP[j*3+1] = image2P[j*3+1] * alpha + resultP[j*3+1] * (1-alpha);//G通道
             resultP[j*3+2] = image2P[j*3+2] * alpha + resultP[j*3+2] * (1-alpha);//R通道
         }
    }
    //imshow("result",result);

    return result;
}


Mat fourCamsVideoStitching::imageMix3(Mat image1,Mat image2)
{
    Mat result;
    //todo
    int start = MIN(leftTop3.x,leftBottom3.x) ;//开始位置，即重叠区域的左边界
    double alpha = 1;//img2中像素的权重

    warpPerspective(image1,result,H34,cv::Size(MIN(rightTop3.x,rightBottom3.x),image1.rows));

    //加权平均
    Mat image2Roi(image2,cv::Rect(0,0,MIN(leftTop3.x,leftBottom3.x),image2.rows));
    Mat resultRoi(result,cv::Rect(0,0,MIN(leftTop3.x,leftBottom3.x),result.rows));
    image2Roi.copyTo(resultRoi);
    //imshow("result12before",result);//显示为融合之前的图像

    double processWidth = image2.cols - start;//重叠区域的宽度

    for(int i=0; i<result.rows; i++)//遍历行
    {
         uchar *image2P=image2.ptr<uchar>(i);
         uchar *resultP=result.ptr<uchar>(i);
         for(int j=start; j<image2.cols; j++)//遍历重叠区域的列
         {
             if(resultP[j*3] < 50 && resultP[j*3+1] < 50 && resultP[j*3+2] < 50 )
             {
                  alpha = 1;
             }
             else
             {   //img2像素的权重，与当前处理点距重叠区域左边界的距离成正比
                 alpha = (processWidth-(j-start)) / processWidth ;
             }
             resultP[j*3] = image2P[j*3] * alpha + resultP[j*3] * (1-alpha);//B通道
             resultP[j*3+1] = image2P[j*3+1] * alpha + resultP[j*3+1] * (1-alpha);//G通道
             resultP[j*3+2] = image2P[j*3+2] * alpha + resultP[j*3+2] * (1-alpha);//R通道
         }
    }
    //imshow("result",result);
    return result;
}


void fourCamsVideoStitching::on_HMatrixCalcBtn_clicked()
{

    // 分别获取三个摄像头的比较清晰的一帧作为H矩阵计算的依据，分别为image1,image2,image3
    VideoCapture cap1(0);
    VideoCapture cap2(1);
    VideoCapture cap3(2);
    VideoCapture cap4(3);

    Mat videoImageSrc1,videoImageSrc2,videoImageSrc3,videoImageSrc4;
    Mat image1,image2,image3,image4;

    while(1)
    {
        cap1>>videoImageSrc1;
        cap2>>videoImageSrc2;
        cap3>>videoImageSrc3;
        cap4>>videoImageSrc4;

        rotate_90n(videoImageSrc1,image1,-90);
        rotate_90n(videoImageSrc2,image2,-90);
        rotate_90n(videoImageSrc3,image3,-90);
        rotate_90n(videoImageSrc4,image4,-90);

        imshow("first image",image1);
        imshow("second image",image2);
        imshow("third image",image3);
        imshow("fourth image",image4);

        if(cvWaitKey(2)>0)
        {
            break;
        }
    }

    //计算两个H矩阵
    H12=findHMatrix(image1,image2);
    QMessageBox::about(NULL,"About","单应矩阵H12计算成功");
    H23=findHMatrix(image2,image3);
    QMessageBox::about(NULL,"About","单应矩阵H23计算成功");
    H34=findHMatrix(image3,image4);
    QMessageBox::about(NULL,"About","单应矩阵H34计算成功");

    //计算第一个重叠区域的四个角坐标之后融合
    CalcFourCorner1(image1);
    QMessageBox::about(NULL,"About","first FourCorner");
    Mat result12=imageMix1(image1,image2);
    imshow("result12",result12);

    QMessageBox::about(NULL,"About","12拼接成功");


    //根据上一次融合结果得出的拼接图片和H23矩阵计算第二个重叠区域的四个角坐标
    CalcFourCorner2(result12);
    Mat result123=imageMix2(result12,image3);

    imshow("result123",result123);

    QMessageBox::about(NULL,"About","123拼接成功");

    CalcFourCorner3(result123);
    Mat result=imageMix3(result123,image4);
    imshow("result",result);
    QMessageBox::about(NULL,"About","1234拼接成功");
}

void fourCamsVideoStitching::on_videoStitchingBtn_clicked()
{
    VideoCapture cap1(0);
    VideoCapture cap2(1);
    VideoCapture cap3(2);
    VideoCapture cap4(3);

    Mat videoImageSrc1,videoImageSrc2,videoImageSrc3,videoImageSrc4;
    Mat image1,image2,image3,image4;
    Mat result12;
    Mat result123;
    Mat result;

    if(!cap1.isOpened())  // check if we succeeded
    {
        QMessageBox::about(NULL,"About","01打开失败");
        return ;
    }
    if(!cap2.isOpened())  // check if we succeeded
    {
        QMessageBox::about(NULL,"About","02打开失败");
        return ;
    }
    if(!cap3.isOpened())  // check if we succeeded
    {
        QMessageBox::about(NULL,"About","03打开失败");
        return ;
    }
    if(!cap4.isOpened())  // check if we succeeded
    {
        QMessageBox::about(NULL,"About","04打开失败");
        return ;
    }

    cap1>>videoImageSrc1;
    cap2>>videoImageSrc2;
    cap3>>videoImageSrc3;
    cap4>>videoImageSrc4;

    rotate_90n(videoImageSrc1,image1,-90);
    rotate_90n(videoImageSrc2,image2,-90);
    rotate_90n(videoImageSrc3,image3,-90);
    rotate_90n(videoImageSrc4,image4,-90);


    //VideoWriter writer1("Cam1.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(image1.cols, image1.rows));
    //VideoWriter writer2("Cam2.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(image2.cols, image2.rows));
    //VideoWriter writer3("Cam3.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(image3.cols, image3.rows));
    VideoWriter writerResult("result.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(MIN(rightTop3.x,rightBottom3.x), image4.rows));

    while(1) //一直循环
    {

        //QMessageBox::about(NULL,"About","start");
        cap1>>videoImageSrc1;
        cap2>>videoImageSrc2;
        cap3>>videoImageSrc3;
        cap4>>videoImageSrc4;

        rotate_90n(videoImageSrc1,image1,-90);
        rotate_90n(videoImageSrc2,image2,-90);
        rotate_90n(videoImageSrc3,image3,-90);
        rotate_90n(videoImageSrc4,image4,-90);

        imshow("Camera Video 1",image1); //显示视频内容的图片
        imshow("Camera Video 2",image2); //显示视频内容的图片
        imshow("Camera Video 3",image3); //显示视频内容的图片
        imshow("Camera Video 4",image4); //显示视频内容的图片


        result12=imageMix1(image1,image2);
        result123=imageMix2(result12,image3);
        result=imageMix3(result123,image4);
        imshow("result",result);

        //writer1<<image1;
        //writer2<<image2;
        writerResult<<result;

        if(cvWaitKey(2)>0)
        {
            break; //两秒内按任意键退出
        }
    }
    QMessageBox::about(NULL,"About","success");
}
