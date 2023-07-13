

/*
library include
library link
*/
#include "Common.h"
int main()
{
	//image path
	string fileDir = "../../KCCImageNet/";
	string fileName = fileDir + "find_google_area.png";


	//load image
	Mat src_color = imread(fileName, ImreadModes::IMREAD_COLOR);
	Mat src_HSV;
	cvtColor(src_color, src_HSV, COLOR_BGR2HSV);

//알고리즘
	//Detect Shape
	int low_H = 160;
	int high_H = 180;
	int low_S = 140;
	int high_S = 255;
	int low_V = 117;
	int high_V = 255;

	Scalar lower_R(low_H, low_S, low_V);
	Scalar high_R(high_H, high_S, high_V);

	Mat detect_img_R, mask_color;
	inRange(src_HSV, lower_R, high_R, detect_img_R);

	Mat reduced_R = src_color.clone();
	cvtColor(detect_img_R, mask_color, CV_GRAY2BGR);

	//google에서 O만 빼옴
	bitwise_and(src_color, mask_color, reduced_R);
	
	//이미지 필터링 과정
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(detect_img_R, detect_img_R, se);	//팽창(dilatation)
	dilate(detect_img_R, detect_img_R, se);	
	erode(detect_img_R, detect_img_R, se);	//침식(erosion)
	erode(detect_img_R, detect_img_R, se);	

	//특징값 저장
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	
	//윤곽선 출력
	findContours(detect_img_R, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	//윤곽선 그리기
	RNG rng(12345);
	//draw contours
	int maxArea_index = 0;
	double maxArea = 0;

	//영역
	double area = contourArea(contours[0]);
	

	//사각형
	cv::Rect rt = cv::boundingRect(contours[maxArea_index]); //boundingRect함수 = 테두리따서 min max 값따라서 사각형좌표 
	//rectangle(src_color, rt, Scalar(0, 0, 0), 1); //그 좌표대로 사각형 그리기

	drawContours(src_color, contours, maxArea_index, Scalar(0, 255, 255), 1, LINE_8, hierarchy, 0);

	// 바운딩박스 크기
	int width = rt.width;
	int height = rt.height;

	// 길이
	int length = 2 * (width + height);


	// 중심 위치
	int centroidX = rt.x + width / 2;
	int centroidY = rt.y + height / 2;

	// 기울어진 각도
	RotatedRect r_rt = minAreaRect(contours[0]);
	RotatedRect ellipse = fitEllipse(contours[0]);

	//draw rotated rectangle
	Point2f vertices[4];
	ellipse.points(vertices);
	for (int i = 0; i < 4; i++) {
		line(src_color, vertices[i], vertices[(i+1)% 4], Scalar(159, 255, 0), 2);
	}
	 
	//ellipse[2]
	
	
	
	
	
	
	cv::Moments mu = cv::moments(contours[maxArea_index]);
	double angle = 0.5 * atan2(2 * mu.mu11, mu.mu20 - mu.mu02) * 180 / CV_PI;
	/*
	//###########상자 각도만큼 회전#################
	Point2f center(centroidX, centroidY), pts[4];   //중심 위치서 꼭지점 4개 생성
	Size2f ssize(width, height);   //상자 사이즈
	float r_angle = angle;
	RotatedRect rot_rect(center, ssize, r_angle);
	Rect bound_rect = rot_rect.boundingRect();  //x,y좌표 ,너비,높이
	//rectangle(src_color, bound_rect, Scalar(0.255,0), 2);
	rot_rect.points(pts);

	for (int i = 0; i < 4; i++)
	{
		line(src_color, pts[i], pts[(i + 1) % 4], Scalar(0, 255, 0), 2);
	}*/


	// 평균 밝기
	cv::Mat gray;
	cv::cvtColor(src_color, gray, cv::COLOR_BGR2GRAY);
	cv::Scalar meanColor = cv::mean(gray(rt));

	// 특징값 출력
	cout << endl;
	cout << "len(길이): " << length << endl;
	cout << "area(크기): " << area << endl;
	cout << "기울어진 각도: "  << angle << endl;
	cout << "ratio(비율): " << width / (float)height  << endl;
	cout << "평균밝기: "  << meanColor[0] << endl;
	cout << "중심 위치 x: "<< centroidX << "\ty: " << centroidY << endl;

	


	// GUI에 특징값 표시
	putText(src_color, "len: " + to_string(length), Point(10, 180), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 255), 2);
	putText(src_color, "area: " + to_string(area), Point(10, 210), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 255), 2);
	putText(src_color, "min radius: " + to_string(angle), Point(10, 240), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 255), 2);
	putText(src_color, "ratio: " + to_string(width/(float)height), Point(10, 300), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 255), 2);
	string txt_center = "center (x: " + to_string(centroidX) + "		y: " + to_string(centroidY) + ")";
	putText(src_color, txt_center, Point(10, 270), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 255), 2);

	//이미지 저장
	imwrite("output.bmp", src_color);


}
