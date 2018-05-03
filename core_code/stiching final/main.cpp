#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/stitcher.hpp"
#include<Windows.h>

using namespace std;
using namespace cv;

bool try_use_gpu = false;
vector<Mat> imgs;
string result_name = "result.jpg";

int main()
{
	Mat img1=imread("1.jpg");
	Mat img2=imread("2.jpg");
	Mat img3=imread("3.jpg");
	Mat img4=imread("4.jpg");
	imgs.push_back(img1);
	imgs.push_back(img2);
	imgs.push_back(img3);
	imgs.push_back(img4);
	
	
	imshow("1.jpg",img1);
	imshow("2.jpg",img2);
	imshow("3.jpg",img3);
	imshow("4.jpg",img4);
	
	Mat pano;
	Stitcher stitcher = Stitcher::createDefault(try_use_gpu);
	Stitcher::Status status = stitcher.stitch(imgs, pano);
	
	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images, error code = " << status << endl;
		return -1;
	}
	namedWindow(result_name);
	imshow(result_name,pano);
	imwrite(result_name,pano);
	waitKey();
	return 0;
}