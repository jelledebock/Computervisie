#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

void opgave2(string filename){
    Mat src,dst;
    char windowname1[] = "Voor";

    src = imread(filename,1);

    namedWindow( windowname1, WINDOW_AUTOSIZE );
    imshow("Voor", src);


    for(int i=1; i<51; i=i+2) {
        cout<<"Blur i="<<i<<endl;
        GaussianBlur(src, dst, Size(i,i), 0);
        String window_title = "Gaussian blur";

        namedWindow( window_title , WINDOW_AUTOSIZE );
        imshow(window_title,dst);

        waitKey();
    }

    Mat img;
    GaussianBlur(src, img, Size(11,11),0);
    imwrite("labo2_2.png",img);
    cout<<"Opgave2 done"<<endl<<endl;

}

void opgave3(string filename){
    Mat src, blurred, dst;

    src = imread(filename,1);

    namedWindow( "origineel" , WINDOW_AUTOSIZE );
    imshow("origineel",src);

    namedWindow( "origineel" , WINDOW_AUTOSIZE );
    imshow("origineel",src);

    GaussianBlur(src, blurred, Size(9,9),10.0);
    Mat difference = abs(src-blurred);

    dst = src + difference;

    namedWindow( "resultaat" , WINDOW_AUTOSIZE );
    imshow("resultaat",dst);
    imwrite("labo2_3.png",dst);
    waitKey();

    cout<<"Opgave3 done"<<endl<<endl;
}

void opgave4(string filename){
    Mat src, dst;

    src = imread(filename,1);

    namedWindow( "origineel" , WINDOW_AUTOSIZE );
    imshow("origineel",src);

    medianBlur(src,dst,3);

    namedWindow( "Salt and pepper removed" , WINDOW_AUTOSIZE );
    imwrite("labo2_4.png",dst);
    imshow("Salt and pepper removed",dst);
    waitKey();

    cout<<"Opgave4 done"<<endl<<endl;
}

void opgave5(string filename){
    Mat src, gray, grad_x, abs_x;

    src = imread(filename,1);

    namedWindow( "origineel" , WINDOW_AUTOSIZE );
    imshow("origineel",src);

    cvtColor(src,gray,COLOR_RGB2GRAY);
    Sobel( gray, grad_x, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT );

    convertScaleAbs(grad_x, abs_x);

    namedWindow( "Sobel filter" , WINDOW_AUTOSIZE );
    imshow("Sobel filter",abs_x);
    imwrite("labo2_5.png",abs_x);

    waitKey();

    cout<<"Opgave5 done"<<endl<<endl;
}

void opgave6(string filename){
    Mat src, filtered;

    src = imread(filename,1);

    namedWindow( "origineel" , WINDOW_AUTOSIZE );
    imshow("origineel",src);

    float kdata[] = {
            (1.0/7),0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0, (1.0/7),0,0,0,0,0,0,0,0,0,0,0,0,0,
            0, 0, (1.0/7),0,0,0,0,0,0,0,0,0,0,0,0,
            0, 0, 0, (1.0/7),0,0,0,0,0,0,0,0,0,0,0,
            0, 0, 0, 0, (1.0/7),0,0,0,0,0,0,0,0,0,0,
            0, 0, 0, 0, 0, (1.0/7),0,0,0,0,0,0,0,0,0,
            0, 0, 0, 0, 0, 0, (1.0/7),0,0,0,0,0,0,0,0,
            0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,
            0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,
            0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,
            0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,
            0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,
            0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,
            0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0
    };

    Mat filter(14,14,CV_32F, kdata);

    filter2D(src, filtered, -1, filter, Point(13,13));

    namedWindow( "filter2D" , WINDOW_AUTOSIZE );
    imshow("filter2D",filtered);
    imwrite("labo2_6.png",filtered);
    waitKey();

    cout<<"Opgave6 done"<<endl<<endl;
}


int main(int argc, char ** argv) {
    //string filename2 = "whitenoise.png";
    //opgave2(filename2);

    string filename3 = "unsharp.png";
    opgave3(filename3);

    string filename4 = "saltandpeppernoise.png";
    opgave4(filename4);

    string filename5 = "building.png";
    opgave5(filename5);

    string filename6 = "blots.png";
    opgave6(filename6);
}