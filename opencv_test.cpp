#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <fstream>

const int THRESHOLD = 127;
const int CAMERA_PORT = 0;

using namespace std;
using namespace cv;

void writeCSV(string filename, Mat m)
{
    ofstream myfile;
    myfile.open(filename.c_str());
    myfile<< cv::format(m, cv::Formatter::FMT_CSV) << std::endl;
    myfile.close();
}

VideoCapture open_external_cam() { // cycle through camera ID 2 to 0
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

Mat full_contrast(Mat &image) { // scale pixel values to full brightness range
    Mat target;
    double min, max;
    minMaxLoc(image, &min, &max);  // Get the dimmest and brightest pixels for scaling
    image.convertTo(target, image.type(), 1.0, (-1.0 * min));
    target.convertTo(target, image.type(), 255 / (max - min + 1), 0); // scale image to full range

    return target;
}

Mat apply_thresholding(Mat &image) {
    Mat target;
    threshold(image, target, THRESHOLD, 255, THRESH_BINARY_INV);  // do thresholding
    return target;
}

vector<Moments> get_moments(Mat &image) {  // get the 0th-3rd order moments for each component
    Mat labels, stats, centroids;
    connectedComponentsWithStats(image, labels, stats, centroids);

    int num_blobs = centroids.rows - 1;
    vector<Mat> blobs(num_blobs);

    for (int i=0; i<num_blobs; i++) {
        inRange(labels, i + 1, i + 1, blobs[i]);
    }

    vector<Moments> m(num_blobs);

    for (int i=0; i<num_blobs; i++) {
        m[i] = moments(blobs[i], true);
    }

    return m;
}

vector<int> get_centroid(Moments &m) { // get the x,y coordinates given moment data
    vector<int> centroid(2);

    centroid[0] = (int) (m.m10 / m.m00);
    centroid[1] = (int) (m.m01 / m.m00);

    return centroid;
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

    // Mat image = capture_photo();
    Mat image = imread("DEMO_circle_fish_star_01.jpg");

    Mat gray = make_grayscale(image);
    Mat bin_img = apply_thresholding(gray);

    vector<Moments> m = get_moments(bin_img);

    for (auto &x: m) {
        vector<int> c = get_centroid(x);
        cout << format("(x: %i, y: %i)", c[0], c[1]) << endl;
    }

    // Display the image
    imshow("Binary image", bin_img);

    waitKey(0);
    cout << "Hasta la vista, baby" << endl;

    return 0;
}
