#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "headers/GLCamera.h"
#include "headers/GLMap.h"

Map::Map() { } // added for ease of expansion

void Map::loadPerlinImage(std::string path) {
    cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE);
    for (int x = 0; x < img.rows; x++)
        for (int y = 0; y < img.cols; y++)
            arrayPerlin.push_back((int)img.at<uchar>(x, y) >> 4); // (255/ 2^4) ~= 16
    
    width = (int) sqrt(arrayPerlin.size());
}

void Map::cleanPerlinArray() {
    arrayPerlin.clear();
}

void Map::addObjectPosition(float x, float y, float z) {
    objectPositions.push_back(glm::vec3(x, y, z));
}

int Map::getPerlinIndex(float camPos, int i) {
    return (abs(i + (int)(camPos / EDGE_SIZE*2)) % width);
}


