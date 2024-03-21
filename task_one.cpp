#include "blob.h"

int main() {
    cout << "Testing my OpenCV compilation." << endl;

    Mat image = capture_photo();
    // Mat image = imread("DEMO_circle_fish_star_02.jpg");
    // Mat image = imread("DEMO_circle_fish_star_01.jpg");
    // Mat image = imread("DEMO_components_02.png");

    int blur_radius = (int)sqrt(image.size().width * image.size().height) / 75;  // dynamically compute blur radius
    Mat gray = make_grayscale(image);
    Mat bin_img = apply_otsu_thresholding(gray, blur_radius); 

    vector<Moments> m = get_moments(bin_img); // begin to gather stats
    vector<int> labels = get_tri_classifier_labels(m); // do classification assuming 3 categories (based on AREA)
    vector<char> l_names = {'A', 'B', 'C'};

    int num_A=0;
    int num_B=0;
    int num_C=0;

    for (int i=0; i<m.size(); i++) {
        Moments x = m[i];
        vector<int> c = get_centroid(x);
        double o = get_orientation(x);
        char label = l_names[labels[i]];
        int id = i+1;

        cout << "Blob #" << id << " (label: " << label << ")" << endl;
        cout << "(x: " << c[0] << ", y: " << c[1] << ")" << endl;
        cout << "theta = " << (180 / pi) * o << " degrees" << endl;
        cout << "area = " << x.m00 << " px\n" << endl;

        switch (label) { // count categories
            case 'A': 
                num_A++; break;
            case 'B': 
                num_B++; break;
            case 'C': 
                num_C++; break;
        }

        mark_blob(image, x);
        draw_label(image, c[0], c[1], label, id);
    }

    // Display the image
    imshow("Image", image);
    cout << "Found instances of objects:" << endl;
    cout << "A: " << num_A << endl;
    cout << "B: " << num_B << endl;
    cout << "C: " << num_C << '\n' << endl;

    waitKey(0);
    cout << "Hasta la vista, baby" << endl;

    return 0;
}