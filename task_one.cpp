#include "blob.h"

int main() {
    cout << "Testing my OpenCV compilation." << endl;

    // Mat image = capture_photo();
    Mat image = imread("DEMO_circle_fish_star_02.jpg");
    // Mat image = imread("DEMO_circle_fish_star_01.jpg");

    Mat gray = make_grayscale(image);
    Mat bin_img = apply_otsu_thresholding(gray, 15); // 35 seems to be ideal, may be smaller for 720p cam

    vector<Moments> m = get_moments(bin_img); // begin to gather stats
    vector<int> labels = get_tri_classifier_labels(m); // do classification assuming 3 categories (based on AREA)
    vector<char> l_names = {'A', 'B', 'C'};

    for (int i=0; i<m.size(); i++) {
        Moments x = m[i];
        vector<int> c = get_centroid(x);
        double o = get_orientation(x);
        char label = l_names[labels[i]];

        cout << "Blob #" << i + 1 << " (label: " << label << ")" << endl;
        cout << "(x: " << c[0] << ", y: " << c[1] << ")" << endl;
        cout << "theta = " << (180 / pi) * o << " degrees" << endl;
        cout << "area = " << x.m00 << " px\n" << endl;

        mark_blob(image, x);
        draw_label(image, c[0], c[1], label);
    }

    // Display the image
    imshow("Image", image);

    waitKey(0);
    cout << "Hasta la vista, baby" << endl;

    return 0;
}