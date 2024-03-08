#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

cv::Mat make_grayscale(cv::Mat &image) {
    cv::Mat gray_image; 
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    return gray_image;
}

// void display_histogram(cv::Mat &image) {
//     cv::Mat hist;
//     float range[] = {0, 256};
//     cv::calcHist(image, 1, cv::Mat(), hist, 256, range, true, false);
// }


int main() {
    std::cout << "Testing my OpenCV compilation." << std::endl;

    // Read an image file
    cv::Mat image = cv::imread("mona_lisa.jpg");
    
    // Check if the image is successfully loaded
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    cv::Mat gray = make_grayscale(image);

    // Display the image
    cv::imshow("Test OpenCV Installation", gray);
    cv::waitKey(0);
    std::cout << "Hasta la vista, baby" << std::endl;
    
    return 0;
}
