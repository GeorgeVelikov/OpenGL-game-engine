#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "headers/GLMap.h"

void createPerlinMap(std::string path, std::vector<int> &map) {
    cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE);
    for (int x = 0; x < img.rows; x++)
        for (int y = 0; y < img.cols; y++)
            map.push_back(int(img.at<uchar>(x, y)) / 16);
}