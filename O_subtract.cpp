

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

//�˰���
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

	//google���� O�� ����
	bitwise_and(src_color, mask_color, reduced_R);
	
	//�̹��� ���͸� ����
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(detect_img_R, detect_img_R, se);	//��â(dilatation)
	dilate(detect_img_R, detect_img_R, se);	
	erode(detect_img_R, detect_img_R, se);	//ħ��(erosion)
	erode(detect_img_R, detect_img_R, se);	

	//Ư¡�� ����
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	
	//������ ���
	findContours(detect_img_R, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	//������ �׸���
	RNG rng(12345);
	//draw contours
	int maxArea_index = 0;
	double maxArea = 0;

	//����
	double area = contourArea(contours[0]);
	

	//�簢��
	cv::Rect rt = cv::boundingRect(contours[maxArea_index]); //boundingRect�Լ� = �׵θ����� min max ������ �簢����ǥ 
	//rectangle(src_color, rt, Scalar(0, 0, 0), 1); //�� ��ǥ��� �簢�� �׸���

	drawContours(src_color, contours, maxArea_index, Scalar(0, 255, 255), 1, LINE_8, hierarchy, 0);

	// �ٿ���ڽ� ũ��
	int width = rt.width;
	int height = rt.height;

	// ����
	int length = 2 * (width + height);


	// �߽� ��ġ
	int centroidX = rt.x + width / 2;
	int centroidY = rt.y + height / 2;

	// ������ ����
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
	//###########���� ������ŭ ȸ��#################
	Point2f center(centroidX, centroidY), pts[4];   //�߽� ��ġ�� ������ 4�� ����
	Size2f ssize(width, height);   //���� ������
	float r_angle = angle;
	RotatedRect rot_rect(center, ssize, r_angle);
	Rect bound_rect = rot_rect.boundingRect();  //x,y��ǥ ,�ʺ�,����
	//rectangle(src_color, bound_rect, Scalar(0.255,0), 2);
	rot_rect.points(pts);

	for (int i = 0; i < 4; i++)
	{
		line(src_color, pts[i], pts[(i + 1) % 4], Scalar(0, 255, 0), 2);
	}*/


	// ��� ���
	cv::Mat gray;
	cv::cvtColor(src_color, gray, cv::COLOR_BGR2GRAY);
	cv::Scalar meanColor = cv::mean(gray(rt));

	// Ư¡�� ���
	cout << endl;
	cout << "len(����): " << length << endl;
	cout << "area(ũ��): " << area << endl;
	cout << "������ ����: "  << angle << endl;
	cout << "ratio(����): " << width / (float)height  << endl;
	cout << "��չ��: "  << meanColor[0] << endl;
	cout << "�߽� ��ġ x: "<< centroidX << "\ty: " << centroidY << endl;

	


	// GUI�� Ư¡�� ǥ��
	putText(src_color, "len: " + to_string(length), Point(10, 180), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 255), 2);
	putText(src_color, "area: " + to_string(area), Point(10, 210), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 255), 2);
	putText(src_color, "min radius: " + to_string(angle), Point(10, 240), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 255), 2);
	putText(src_color, "ratio: " + to_string(width/(float)height), Point(10, 300), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 255), 2);
	string txt_center = "center (x: " + to_string(centroidX) + "		y: " + to_string(centroidY) + ")";
	putText(src_color, txt_center, Point(10, 270), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 255), 2);

	//�̹��� ����
	imwrite("output.bmp", src_color);


}
