#include "twocamsvideostitching.h"
#include "ui_twocamsvideostitching.h"

twoCamsVideoStitching::twoCamsVideoStitching(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::twoCamsVideoStitching)
{
    ui->setupUi(this);
}

twoCamsVideoStitching::~twoCamsVideoStitching()
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

//计算图1的四个角经矩阵H变换后的坐标
void twoCamsVideoStitching::CalcFourCorner()
{
    Mat Htmp;
    H.copyTo(Htmp);
    CvMat cvH=Htmp;


    //计算图1的四个角经矩阵H变换后的坐标
    double v2[]={0,0,1};//左上角
    double v1[3];//变换后的坐标值
    CvMat V2 = cvMat(3,1,CV_64FC1,v2);
    CvMat V1 = cvMat(3,1,CV_64FC1,v1);

    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    leftTop.x = cvRound(v1[0]/v1[2]);
    leftTop.y = cvRound(v1[1]/v1[2]);
    cout<<leftTop.x<<" "<<leftTop.y<<endl;


    //将v2中数据设为左下角坐标
    v2[0] = 0;
    v2[1] = image1.rows;
    V2 = cvMat(3,1,CV_64FC1,v2);
    V1 = cvMat(3,1,CV_64FC1,v1);
    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    leftBottom.x = cvRound(v1[0]/v1[2]);
    leftBottom.y = cvRound(v1[1]/v1[2]);
    cout<<leftBottom.x<<" "<<leftBottom.y<<endl;

    //将v2中数据设为右上角坐标
    v2[0] = image1.cols;
    v2[1] = 0;
    V2 = cvMat(3,1,CV_64FC1,v2);
    V1 = cvMat(3,1,CV_64FC1,v1);
    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    rightTop.x = cvRound(v1[0]/v1[2]);
    rightTop.y = cvRound(v1[1]/v1[2]);
    cout<<rightTop.x<<" "<<rightTop.y<<endl;

    //将v2中数据设为右下角坐标
    v2[0] = image1.cols;
    v2[1] = image1.rows;
    V2 = cvMat(3,1,CV_64FC1,v2);
    V1 = cvMat(3,1,CV_64FC1,v1);
    cvGEMM(&cvH,&V2,1,0,1,&V1);//矩阵乘法
    rightBottom.x = cvRound(v1[0]/v1[2]);
    rightBottom.y = cvRound(v1[1]/v1[2]);
    cout<<rightBottom.x<<" "<<rightBottom.y<<endl;

}

void twoCamsVideoStitching::on_HMatrixCalcBtn_clicked()
{
    // capture the images from cams
    VideoCapture cap1(0);
    VideoCapture cap2(1);

    while(1)
    {
        cap1>>videoImageSrc1;
        cap2>>videoImageSrc2;

        rotate_90n(videoImageSrc1,image1,-90);
        rotate_90n(videoImageSrc2,image2,-90);
        imshow("first image",image1);
        imshow("second image",image2);
        if(cvWaitKey(2)>0)
        {
            break; //两秒内按任意键退出
        }
    }

    //rotate the images
    //rotate_90n(videoImageSrc1,image1,-90);
    //rotate_90n(videoImageSrc2,image2,-90);

    //QMessageBox::about(NULL,"About","<font color='red'>success</font>");

    if(!image1.data||!image2.data)
    {
        QMessageBox::about(NULL,"About","图片加载<font color='red'>失败</font>");
        return ;
    }
    imshow("first image",image1);
    imshow("second image",image2);



    //图片预处理
    cvtColor(image1,gray_image1,CV_RGB2GRAY);
    cvtColor(image2,gray_image2,CV_RGB2GRAY);
    if(!gray_image1.data||!gray_image2.data)
    {
        QMessageBox::about(NULL,"About","图片加载<font color='red'>失败</font>");
    }
    imshow("first grey image",gray_image1);
    imshow("second grey image",gray_image2);



    int minHessian = 400;
    SurfFeatureDetector detector(minHessian);
    detector.detect(gray_image1,keypoints_object);
    detector.detect(gray_image2,keypoints_scene);
    //-- Draw keypoints
    //Mat img_keypoints_1; Mat img_keypoints_2;
    //drawKeypoints(image1,keypoints_object,img_keypoints_1,Scalar::all(-1),DrawMatchesFlags::DEFAULT);
    //drawKeypoints(image2,keypoints_scene,img_keypoints_2,Scalar::all(-1),DrawMatchesFlags::DEFAULT);
    //-- Show detected (drawn) keypoints
    //imshow("Keypoints 1", img_keypoints_1 );
    //imshow("Keypoints 2", img_keypoints_2 );




    SurfDescriptorExtractor extractor;
    extractor.compute( gray_image1, keypoints_object, descriptors_object );
    extractor.compute( gray_image2, keypoints_scene, descriptors_scene );
    //QMessageBox::about(NULL,"About","特征向量计算成功");



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
    //QMessageBox::about(NULL,"About","特征向量配准成功");



    H = findHomography( obj, scene, CV_RANSAC );
    QMessageBox::about(NULL,"About","单应矩阵计算成功");

    //计算四个角的坐标
    CalcFourCorner();

    cap1.release();
    cap2.release();
}

void twoCamsVideoStitching::on_videoStitchingBtn_clicked()
{
    VideoCapture cap1(0);
    VideoCapture cap2(1);

    VideoWriter writer1("Cam1.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(image1.cols, image1.rows));
    VideoWriter writer2("Cam2.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(image2.cols, image2.rows));
    VideoWriter writerResult("result.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(MIN(rightTop.x,rightBottom.x), image1.rows));

    if(!cap1.isOpened())  // check if we succeeded
    {
        QMessageBox::about(NULL,"About","01打开失败请检查摄像头连接情况");
        return ;
    }
    if(!cap2.isOpened())  // check if we succeeded
    {
        QMessageBox::about(NULL,"About","02打开失败请检查摄像头连接情况");
        return ;
    }

    Mat result;
    int start = MIN(leftTop.x,leftBottom.x) ;//开始位置，即重叠区域的左边界
    double alpha = 1;//img2中像素的权重

    while(1) //一直循环
    {

        //QMessageBox::about(NULL,"About","start");
        cap1>>videoImageSrc1;
        cap2>>videoImageSrc2;

        rotate_90n(videoImageSrc1,image1,-90);
        rotate_90n(videoImageSrc2,image2,-90);

        imshow("Camera Video 1",image1); //显示视频内容的图片
        imshow("Camera Video 2",image2); //显示视频内容的图片


        warpPerspective(image1,result,H,cv::Size(MIN(rightTop.x,rightBottom.x),image1.rows));

        //加权平均
        Mat image2Roi(image2,cv::Rect(0,0,MIN(leftTop.x,leftBottom.x),image2.rows));
        Mat resultRoi(result,cv::Rect(0,0,MIN(leftTop.x,leftBottom.x),result.rows));
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
        imshow("result",result);

        writer1<<image1;
        writer2<<image2;
        writerResult<<result;

        if(cvWaitKey(2)>0)
        {
            break; //两秒内按任意键退出
        }
    }
    QMessageBox::about(NULL,"About","success");
    cap1.release();
    cap2.release();
}
