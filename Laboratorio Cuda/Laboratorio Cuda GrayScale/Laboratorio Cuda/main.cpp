#include <iostream>
#include <cstdio>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "kernel.h"

using namespace std;
using namespace cv;



int main() {
    string image_path;
    string auxStr;
    cout << "Ingresa el nombre de la imagen\n";
    cin >> image_path;
    auxStr = "./"+image_path + "_grayscale.jpg";
    image_path.insert(0, "../");

    Mat matrix_image;
    Mat matrix_filtered;
    string result_image_path;

    matrix_image = imread(image_path, cv::IMREAD_COLOR);// CV_LOAD_IMAGE_COLOR);
    if (!(matrix_image).data) {
        cout << "Error reading image" << endl;
        return 0;
    }

    int cols = matrix_image.cols;
    int rows = matrix_image.rows;
    float* Blue = new float[cols * rows];
    float* Green = new float[cols * rows];
    float* Red = new float[cols * rows];
    float* GrayScaleMatrix = new float[cols * rows];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int pos = cols * i + j;
            Blue[pos] = (float)matrix_image.at<cv::Vec3b>(i, j)[0];
            Green[pos] = (float)matrix_image.at<cv::Vec3b>(i, j)[1];
            Red[pos] = (float)matrix_image.at<cv::Vec3b>(i, j)[2];
        }
    }
    grayscale(Red, Green, Blue, GrayScaleMatrix, cols * rows);
    Mat gray = Mat(rows, cols, CV_32FC1, GrayScaleMatrix);
    gray.convertTo(gray, CV_8UC3, 255.0);
    imwrite(auxStr, gray);

    return 0;
}