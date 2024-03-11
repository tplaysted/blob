#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

const int THRESHOLD = 127;
const int CAMERA_PORT = 0;

using namespace std;
using namespace cv;

VideoCapture open_external_cam() { // cycle through camera ID 5 to 0
    VideoCapture cap;
    for (int i=2; i>=0; i--) {
        cap.open(i);
        if (cap.isOpened()) {
            return cap;
        }
    }

    return cap;
}

Mat make_grayscale(Mat &image) {
    Mat gray_image; 
    cvtColor(image, gray_image, COLOR_BGR2GRAY);
    return gray_image;
}

Mat full_contrast(Mat &image) {
    Mat target;
    double min, max;
    minMaxLoc(image, &min, &max);  // Get the dimmest and brightest pixels for scaling
    image.convertTo(target, image.type(), 1.0, (-1.0 * min));
    target.convertTo(target, image.type(), 255 / (max - min + 1), 0); // scale image to full range

    return target;
}

Mat apply_thresholding(Mat &image) {
    Mat target;
    threshold(image, target, THRESHOLD, 255, THRESH_BINARY);  // do thresholding
    return target;
}

Mat capture_photo() { // Display camera output and await user input before capturing
    VideoCapture cap = open_external_cam(); // On my laptop "0" is the built-in camera. 
    if (!cap.isOpened()) {
        cerr << "Error opening the camera!" << endl;
    }

    Mat frame;
    
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cout << "ERROR! blank frame grabbed\n";
            break;
        }

        // show live and wait for a key with timeout long enough to show images
        imshow("Live", frame);
        if (waitKey(5) >= 0)
            break;
    }

    return frame;
}

int main() {
    cout << "Testing my OpenCV compilation." << endl;

    Mat image = capture_photo();

    Mat gray = make_grayscale(image);
    Mat bin_img = apply_thresholding(gray);

    // Display the image
    imshow("Test OpenCV Installation", bin_img);
    waitKey(0);
    cout << "Hasta la vista, baby" << endl;
    
    return 0;
}
