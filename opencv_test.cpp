#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

const int THRESHOLD = 127;
const int CAMERA_PORT = 2;

cv::Mat make_grayscale(cv::Mat &image) {
    cv::Mat gray_image; 
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    return gray_image;
}

cv::Mat apply_thresholding(cv::Mat &image) {
    cv::Mat target;
    double min, max;
    cv::minMaxLoc(image, &min, &max);  // Get the dimmest and brightest pixels for scaling
    image.convertTo(target, image.type(), 1.0, (-1.0 * min));
    target.convertTo(target, image.type(), 255 / (max - min + 1), 0); // scale image to full range
    cv::threshold(target, target, THRESHOLD, 255, cv::THRESH_BINARY);  // do thresholding
    return target;
}

cv::Mat capture_photo() { // Display camera output and await user input before capturing
    cv::VideoCapture cap(CAMERA_PORT); // On my laptop "0" is the built-in camera. 
    if (!cap.isOpened()) {
        std::cerr << "Error opening the camera!" << std::endl;
    }

    cv::Mat frame;
    
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
        cv::imshow("Live", frame);
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
