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
    string result_image_path;
    cout << "Ingresa el nombre de la imagen\n";
    cin >> image_path;
    result_image_path = "./"+image_path + "_blur.jpg";
    image_path.insert(0, "../");

    Mat matrix_image;

    matrix_image = imread(image_path, cv::IMREAD_COLOR);// CV_LOAD_IMAGE_COLOR);
    if (!(matrix_image).data) {
        cout << "Error reading image" << endl;
        return 0;
    }

    int cols = matrix_image.cols;
    int rows = matrix_image.rows;

    unsigned char* Blue = new unsigned char[cols * rows];
    unsigned char* Green = new unsigned char[cols * rows];
    unsigned char* Red = new unsigned char[cols * rows];
    unsigned char* BlueBlur = new unsigned char[cols * rows];
    unsigned char* GreenBlur = new unsigned char[cols * rows];
    unsigned char* RedBlur = new unsigned char[cols * rows];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int pos = cols * i + j;
            Blue[pos] = matrix_image.at<cv::Vec3b>(i, j)[0];
            Green[pos] = matrix_image.at<cv::Vec3b>(i, j)[1];
            Red[pos] = matrix_image.at<cv::Vec3b>(i, j)[2];
        }
    }
    blur(Red, Green, Blue, RedBlur, GreenBlur, BlueBlur, cols, rows);
    Mat channelR(rows, cols, CV_8UC1, RedBlur);
    Mat channelG(rows, cols, CV_8UC1, GreenBlur);
    Mat channelB(rows, cols, CV_8UC1, BlueBlur);
    Mat matrix_filtered;
    std::vector<Mat> channels{ channelB, channelG, channelR };

    merge(channels, matrix_filtered);

    imwrite(result_image_path, matrix_filtered);

    return 0;
}