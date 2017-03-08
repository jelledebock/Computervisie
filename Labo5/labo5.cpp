#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void opgave10(string);
void opgave11(string);

int main(int argc, char **argv) {
    opgave11(argv[1]);
    return 0;
}

void opgave10(string filename){
    Mat src, dst;
    src = imread(filename);
    imshow("Origineel", src);

    Mat kernel = getGaussianKernel(15,4,CV_64F);
    cout<<kernel<<endl;
    Mat vierkant(kernel.rows,kernel.rows,CV_8UC1);
    kernel.col(0).copyTo(vierkant.col(vierkant.rows/2));

    Mat kernel2 = getGaussianKernel(src.rows,3,CV_64F);
    kernel2.t();

    Mat gefilterd_vierkant;
    filter2D(vierkant, gefilterd_vierkant, -1, kernel2 );

    Mat dog;
    Sobel(gefilterd_vierkant, dog, CV_32F, 1, 0);

    Mat rotatie_matrix;
    rotatie_matrix = getRotationMatrix2D(Point(0,0),75,1);

    Mat warped;
    warpAffine(dog, warped, rotatie_matrix, dog.size());

    Mat grey;
    cvtColor(src, grey, CV_RGB2GRAY);

    Mat grey_filtered;
    filter2D(grey, grey_filtered, -1, warped );

    Mat abs_grey = abs(grey_filtered);

    imshow("Filtered",abs_grey);
    waitKey();

}

void opgave11(string filename){
    Mat src, dst;
    src = imread(filename);
    imshow("Origineel", src);

    Canny( src, dst, 100, 300);

    imshow("Edges",dst);
    waitKey();
}