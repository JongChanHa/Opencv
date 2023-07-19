#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <memory>
#include <fstream> // ofstream header
#include <format>
using namespace std;

//add lib

#define OPENCV_470

#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#ifdef OPENCV_470
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/types_c.h>
#endif // OPENCV_470

#ifdef _DEBUG
#pragma comment(lib, "opencv_world470d.lib")
#else	//RELEASE
#pragma comment(lib, "opencv_world470.lib")
#endif
using namespace std;
using namespace cv;