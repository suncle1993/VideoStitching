#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include <iostream>

using namespace std;
int main()
{
	CvCapture* capture1=cvCreateCameraCapture(1);
	CvVideoWriter* video1=NULL;
	IplImage* frame1=NULL;
	int n1;

	if(!capture1) //如果不能打开摄像头给出警告
	{
		cout<<"Can not open the camera."<<endl;
		return -1;
	}
	else
	{
		frame1=cvQueryFrame(capture1); //首先取得摄像头中的一帧
		int width=frame1->width;
		int height=frame1->height;
		video1=cvCreateVideoWriter("camera1.avi", CV_FOURCC('X', 'V', 'I', 'D'), 25,cvSize(width,height)); //创建CvVideoWriter对象并分配空间
		//保存的文件名为camera.avi，编码要在运行程序时选择，大小就是摄像头视频的大小，帧频率是32
		if(video1) //如果能创建CvVideoWriter对象则表明成功
		{
			cout<<"VideoWriter has created."<<endl;
		}

		cvNamedWindow("Camera Video1",1); //新建一个窗口

		while(1) // 让它循环1000次自动停止录取
		{
			frame1=cvQueryFrame(capture1); //从CvCapture中获得一帧
			
			if(!frame1)
			{
				cout<<"Can not get frame from the capture."<<endl;
				break;
			}
			n1=cvWriteFrame(video1,frame1); //判断是否写入成功，如果返回的是1，表示写入成功
			
			cout<<n1<<" "<<endl;
			cvShowImage("Camera Video1",frame1); //显示视频内容的图片
			
			
			if(cvWaitKey(2)>0) 
				break; //两秒内按任意键退出
		}
		
		cvReleaseVideoWriter(&video1);
		
		cvReleaseCapture(&capture1);
		
		cvDestroyWindow("Camera Video1");
		
	}
	return 0;
}