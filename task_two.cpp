#include "blob.h"


int main() {
    Mat image = create_test_image(1);

    Mat gray = make_grayscale(image);
    Mat bin_img = apply_otsu_thresholding(gray, 7); // 35 seems to be ideal, may be smaller for 720p cam

    vector<Moments> m = get_moments(bin_img); // begin to gather stats

    for (int i=0; i<m.size(); i++) {
        Moments x = m[i];
        vector<int> c = get_centroid(x);
        double o = get_orientation(x);

        cout << "Blob #" << i << endl;
        cout << "(x: " << c[0] << ", y: " << c[1] << ")" << endl;
        cout << "theta = " << (180 / pi) * o << " degrees" << endl;
        cout << "area = " << x.m00 << " px\n" << endl;

        mark_blob(image, x);
    }

    // Display the image
    imshow("Image", image);

    waitKey(0);
    cout << "See ya later, alligator" << endl;
    return 0;
}
