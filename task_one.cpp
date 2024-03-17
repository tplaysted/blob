#include "blob.h"

int main() {
    cout << "Testing my OpenCV compilation." << endl;

    // Mat image = capture_photo();
    // Mat image = imread("DEMO_circle_fish_star_02.jpg");
    Mat image = imread("DEMO_circle_fish_star_01.jpg");

    Mat gray = make_grayscale(image);
    Mat bin_img = apply_otsu_thresholding(gray, 1); // 35 seems to be ideal, may be smaller for 720p cam

    // vector<Mat> blobs(10);  // code for testing different blur radii

    // for (int i=0; i<10; i++) {
    //     blobs[i] = apply_otsu_thresholding(gray, 21 + 2 * i);
    //     imshow(format("Radius = %i", 21 + 2 * i), blobs[i]);
    // }

    vector<Moments> m = get_moments(bin_img); // begin to gather stats
    vector<int> labels = get_tri_classifier_labels(m); // do classification
    vector<char> l_names = {'A', 'B', 'C', 'D', 'E'};

    for (int i=0; i<m.size(); i++) {
        Moments x = m[i];
        vector<int> c = get_centroid(x);
        double o = get_orientation(x);

        cout << "Blob #" << i << endl;
        cout << "(x: " << c[0] << ", y: " << c[1] << ")" << endl;
        cout << "theta = " << (180 / pi) * o << " degrees" << endl;
        cout << "area = " << x.m00 << " px" << endl;
        cout << "label = " << l_names[labels[i]] << "\n" << endl;

        mark_blob(image, x);
    }

    // Display the image
    imshow("Image", image);

    waitKey(0);
    cout << "Hasta la vista, baby" << endl;

    return 0;
}