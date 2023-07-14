#include "Common.h"



int main()
{
	//image path
	string fileName = "D:/PlatformCPP/KCCImageNet/solar_cell/solar_cell_03.png";

	std::cout << fileName << std::endl;
	Mat input_img = cv::imread(fileName, cv::ImreadModes::IMREAD_ANYCOLOR);

	//to do 
	int width = input_img.cols;
	int height = input_img.rows;
	int channel = input_img.channels();

	//get roi
	cout << "img width: " << width << endl;
	cout << "img height: " << height << endl;
	

	//cvt change to grey
	Mat grey_img;
	cvtColor(input_img, grey_img, ColorConversionCodes::COLOR_BGR2GRAY);



	//Mat img_1 = input_img(Rect(0, 0, width, height));
 	//Mat hole_img = ~input_img;

	Mat bin_hole_img;
	double thres_min = 150;
	double thres_max = 255;
	threshold(grey_img, bin_hole_img, thres_min, thres_max, ThresholdTypes::THRESH_BINARY);
	//bin_hole_img = ~bin_hole_img;
	
	//노이즈 제거
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat noise_remove_img;
	//dilate(bin_hole_img, noise_remove_img, se);	//팽창(dilatation)

	erode(bin_hole_img, noise_remove_img, se);	//침식(erosion)

	

	// 윤곽선 검출을 위한 변수 초기화
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	// 윤곽선 검출
	cv::findContours(noise_remove_img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	// 윤곽선 그리기
	cv::Mat contourImage = cv::Mat::zeros(noise_remove_img.size(), CV_8UC3);
	cv::drawContours(contourImage, contours, -1, cv::Scalar(0, 0, 255), 2);

	//관심영역
	int x_roi = 13, y_roi = 26;
	cv::Rect roi(x_roi, y_roi, 238, 18);
	cv::rectangle(contourImage, roi, Scalar(255, 100, 0), 3);
	cv::rectangle(bin_hole_img, roi, Scalar(255, 100, 0), 1);
	
	//이미지에 관심영역 roi(rect)를 영역 0으로 만들기
	Mat test_img;
	input_img.copyTo(test_img);
	test_img(roi) = 0;

	//이미지 합치기
	
	Rect roi2_r(18, 26, 200, 200);
	Mat roi2 = test_img(roi2_r);
	roi2.copyTo(test_img(Rect(18, 426, 200, 200)));
	//rectangle(test_img, roi2_r, cv::Scalar(0, 255, 0), 2);

	//test_img = roi2 & test_img;






}
