#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

void opgave7(char *);

int main(int argc, char **argv){
    opgave7(argv[1]);
    return 0;
}

void opgave7(char * filename){
    Mat src, erosie_stap, dilate_stap1, dilate_stap2;
    src=imread(filename,1);
    imshow("Voor",src);
    int erosion_size = 7;
    Mat element = getStructuringElement(MORPH_CROSS,
                                         Size( erosion_size, erosion_size ));
    erode(src, erosie_stap, element);
    imshow("Na erosie stap",erosie_stap);

    Mat dilatie = getStructuringElement(MORPH_RECT, Size( 1,src.rows/16));

    dilate(erosie_stap, dilate_stap1, dilatie);
    imshow("Na dilate stap" ,dilate_stap1);
    imwrite("labo3.png",dilate_stap1);

    waitKey();
}