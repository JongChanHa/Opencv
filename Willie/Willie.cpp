#include "Common.h"

int main()
{
	//image path
	string filePath = "./Willie/";
	//¥‰¡ˆ
	string InputName = filePath + "Willie.jpg";
	//≈€«√∏¥
	string templateName = filePath + "me.jpg";
	
	Mat input_img = cv::imread(InputName, cv::ImreadModes::IMREAD_ANYCOLOR);
	Mat template_img = cv::imread(templateName, cv::ImreadModes::IMREAD_ANYCOLOR);
	Mat result;

	//match normalize
	int match_method = cv::TM_CCOEFF_NORMED;
	matchTemplate(input_img, template_img, result, match_method);

	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	//localize the best match with minmaxLoc
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;
	
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());


	if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}
	rectangle(input_img, matchLoc, Point(matchLoc.x + template_img.cols, matchLoc.y + template_img.rows), Scalar::all(0), 2, 8, 0);
	
	imshow("image_window", input_img);
	
	waitKey(0);


 }