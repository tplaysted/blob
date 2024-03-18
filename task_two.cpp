#include "blob.h"


int main() {
    // First, generate test images
    vector<double> angles = {0.3, 0.9, 0.9, 1.2, 1.5, 1.8, 2.1
                            ,0.3, 0.9, 0.9, 1.2, 1.5, 1.8, 2.1
                            ,0.3, 0.9, 0.9, 1.2, 1.5, 1.8, 2.1
                            ,0.3, 0.9, 0.9, 1.2, 1.5, 1.8, 2.1
                            ,0.3, 0.9, 0.9, 1.2, 1.5, 1.8, 2.1};

    vector<Mat> test_images(angles.size());

    for (int i=0; i<angles.size(); i++) {
        test_images[i] = create_test_image(angles[i]);
    }

    // Display test images one at a time
    for (auto &im: test_images) {
        // Display test image and capture from external camera
        imshow("Test image", im);
        Mat capture = capture_photo();

        // Do perception 
        Mat gray = make_grayscale(capture);
        Mat bin_img = apply_otsu_thresholding(gray, 15); 
        vector<Moments> m = get_moments(bin_img);

        // Attempt to determine the reference image
        double o1 = get_orientation(m[0]);
        double o2 = get_orientation(m[1]);

        int x1 = get_centroid(m[0])[0];
        int x2 = get_centroid(m[1])[0];

        if (o2 >= o1) {
            if (x1 < x2) {
                cout << "Right\n" << endl;
            } else {
                cout << "Left\n" << endl;
            }
        } else {
            if (x1 < x2) {
                cout << "Left\n" << endl;
            } else {
                cout << "Right\n" << endl;
            }
        }
        
        // Display the image
        mark_blob(capture, m[0]);
        mark_blob(capture, m[1]);
        imshow("Capture", capture);
        waitKey(0);
    }

    cout << "See ya later, alligator" << endl;
    return 0;
}
