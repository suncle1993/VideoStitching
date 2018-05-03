#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "opencv2/stitching/stitcher.hpp"
#include <iostream>


using namespace std;
using namespace cv;
int main()
{
	Mat pano;
	vector<Mat> imgs;
	CvCapture* capture1=cvCreateCameraCapture(1);
	CvCapture* capture2=cvCreateCameraCapture(2);
	CvVideoWriter* video1=NULL;
	CvVideoWriter* video2=NULL;
	IplImage* frame1=NULL;
	IplImage* frame2=NULL;

	if(!capture1&&!capture2) //如果不能打开摄像头给出警告
	{
		cout<<"Can not open the camera."<<endl;
		return -1;
	}
	else
	{
		frame1=cvQueryFrame(capture1); //首先取得摄像头中的一帧
		frame2=cvQueryFrame(capture2);
		//经测试，镜头的长宽都是640*480，取其中一个就行
		int width=frame1->width;
		int height=frame1->height;
		cout<<width<<"  "<<height<<endl;
		
		if(video1&&video2) //如果能创建CvVideoWriter对象则表明成功
		{
			cout<<"VideoWriter has created."<<endl;
		}

		cvNamedWindow("Camera Video1",1); //新建一个窗口
		cvNamedWindow("Camera Video2",1); //新建一个窗口

		while(1) 
		{
			
			frame1=cvQueryFrame(capture1); //从CvCapture中获得一帧
			frame2=cvQueryFrame(capture2); //从CvCapture中获得一帧
			if(!frame1&&!frame2)
			{
				cout<<"Can not get frame from the capture."<<endl;
				break;
			}

			cvShowImage("Camera Video1",frame1); //显示视频内容的图片
			cvShowImage("Camera Video2",frame2); //显示视频内容的图片
			
			
			if(cvWaitKey(2)>0) 
				break; //两秒内按任意键退出

		}
		
		cvReleaseVideoWriter(&video1);
		cvReleaseVideoWriter(&video2);
		cvReleaseCapture(&capture1);
		cvReleaseCapture(&capture2);
		cvDestroyWindow("Camera Video1");
		cvDestroyWindow("Camera Video2");
	}
	return 0;
}