#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

int main() {
    std::cout << "Testing my OpenCV compilation." << std::endl;

    // Read an image file
    cv::Mat image = cv::imread("mona_lisa.jpg");

    // Check if the image is successfully loaded
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    // Display the image
    cv::imshow("Test OpenCV Installation", image);
    cv::waitKey(0);
    std::cout << "Hasta la vista, baby." << std::endl;
    
    return 0;
}
