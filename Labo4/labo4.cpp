#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int number_clicks=0;
Point2f inputQuad[4];

void maak_proportioneel(void *pVoid);

void getEdges(int event, int x, int y, int flags, void* userdata) {
    if(event == EVENT_LBUTTONDOWN){
        inputQuad[number_clicks++]=Point2f(x,y);
        if(number_clicks==4){
            maak_proportioneel(userdata);
            number_clicks=0;
        }
    }
}

void maak_proportioneel(void *pVoid) {
    Mat lambda( 2, 4, CV_32FC1 );
    Point2f outputQuad[4];
    // The 4 points where the mapping is to be done , from top-left in clockwise order
    outputQuad[0] = Point2f( 0,0 );
    outputQuad[1] = Point2f( ((Mat*)pVoid)->cols-1,0);
    outputQuad[2] = Point2f( ((Mat*)pVoid)->cols-1,((Mat*)pVoid)->rows-1);
    outputQuad[3] = Point2f( 0,((Mat*)pVoid)->rows-1  );

    lambda = Mat::zeros( ((Mat*)pVoid)->rows, ((Mat*)pVoid)->cols, ((Mat*)pVoid)->type() );

    // Get the Perspective Transform Matrix i.e. lambda
    lambda = getPerspectiveTransform( inputQuad, outputQuad );
    // Apply the Perspective Transform just found to the src image
    Mat proportie;
    warpPerspective(*((Mat*)pVoid),proportie,lambda, ((Mat*)pVoid)->size() );

    imshow("Vierkant",proportie);
    waitKey();
}

void opgave8(char * filename){
    Mat src, dst;
    src = imread(filename);
    imshow("Origineel", src);

    float m = 0.1;
    int offset = 0;
    float kdata[] = {
                        1, -m, offset,
                        0, 1, offset
                    };
    Mat filter(2,3, CV_32F, kdata);

    warpAffine(src,dst,filter,Size(src.cols,src.rows));

    imshow("WarpAffine",dst);
    waitKey();
}

void opgave9(char * filename){
    Mat src, dst;

    src = imread(filename);
    imshow("Origineel", src);

    float m = 0.1;
    int offset = 0;
    float kdata[] = {
            1, -m, offset,
            0, 1, offset
    };
    Mat filter(2,3, CV_32F, kdata);

    warpAffine(src,dst,filter,Size(src.cols,src.rows));

    namedWindow("WarpAffine", 1);
    imshow("WarpAffine",dst);
    setMouseCallback("WarpAffine", getEdges, &dst);

    waitKey();
}

int main(int argc, char **argv) {
    opgave9(argv[1]);
    return 0;
}