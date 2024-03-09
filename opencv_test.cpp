#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

const int THRESHOLD = 127;
const int CAMERA_PORT = 0;

cv::Mat make_grayscale(cv::Mat &image) {
    cv::Mat gray_image; 
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    return gray_image;
}

cv::Mat apply_thresholding(cv::Mat &image) {
    cv::Mat target;
    cv::threshold(image, target, THRESHOLD, 255, cv::THRESH_BINARY);
    return target;
}

cv::Mat capture_photo() {
    cv::VideoCapture cap(2); // On my laptop "0" is the built-in camera. 
    if (!cap.isOpened()) {
        std::cerr << "Error opening the camera!" << std::endl;
    }

    cv::Mat frame;
    
    cap.read(frame);
    if (frame.empty()) {
        std::cerr << "No frame captured?" << std::endl;
    }

        for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            std::cout << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", frame);
        if (cv::waitKey(5) >= 0)
            break;
    }
    
    return frame;
}

int main() {
    std::cout << "Testing my OpenCV compilation." << std::endl;

    // Read an image file
    // cv::Mat image = cv::imread("mona_lisa.jpg");
    
    // // Check if the image is successfully loaded
    // if (image.empty()) {
    //     std::cerr << "Error: Could not open or find the image!" << std::endl;
    //     return -1;
    // }

    cv::Mat image = capture_photo();

    cv::Mat gray = make_grayscale(image);
    cv::Mat bin_img = apply_thresholding(gray);

    // Display the image
    cv::imshow("Test OpenCV Installation", bin_img);
    cv::waitKey(0);
    std::cout << "Hasta la vista, baby" << std::endl;
    
    return 0;
}
