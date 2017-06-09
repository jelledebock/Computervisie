#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

void opgave10(string filename){
    Mat src, dst;
    src = imread(filename);
    imshow("Origineel", src);

    //Een mooi resultaat is ksize1 = 23 en ksize2 = 30
    Mat kernel = getGaussianKernel(23,-1,CV_64F);
    cout<<kernel<<endl;
    Mat vierkant(kernel.rows,kernel.rows,CV_8UC1);
    kernel.col(0).copyTo(vierkant.col(vierkant.rows/2));

    double ksize = 1;
    while(ksize<100){
        cout<<"Kernel size = "<<ksize<<endl;
        Mat kernel2 = getGaussianKernel(ksize,-1,CV_64F);
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
        imwrite("labo5_10.png",abs_grey);
        waitKey();
        ksize+=0.5;

    }

}

void opgave11(string filename){
    Mat src, dst;
    src = imread(filename);
    imshow("Origineel", src);

    Canny( src, dst, 100, 300);
    vector<Vec2f> lines;
    HoughLines(dst,lines,1,CV_PI/180,70);

    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( src, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
    }
    imshow("Edges",src);
    imwrite("labo5_11.png",src);
    waitKey();
}

void opgave12(string filename){
    Mat src, grayscale;
    src = imread(filename);
    imshow("Origineel", src);

    cvtColor(src,grayscale, CV_BGR2GRAY);

    vector<Point2f> corners;
    int maxCorners=100;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3;
    bool useHarrisDetector = true;
    double k = 0.04;

    goodFeaturesToTrack( grayscale,
                         corners,
                         maxCorners,
                         qualityLevel,
                         minDistance,
                         Mat(),
                         blockSize,
                         useHarrisDetector,
                         k );
    cout<<"** Number of corners detected: "<<corners.size()<<endl;

    for( size_t i = 0; i < corners.size(); i++ )
    {
        cv::circle( src, corners[i], 5, cv::Scalar( 255. ), -1 );
    }

    imshow( "corners", src );
    imwrite("labo5_12.png",src);
    waitKey(0);
}

void opgave13(string filename1, string filename2){
    const float inlier_threshold = 2.5f; // Distance threshold to identify inliers
    const float nn_match_ratio = 0.8f;   // Nearest neighbor matching ratio

    Mat src1, src2;
    vector<KeyPoint> kp1,kp2;
    Mat desc1, desc2;

    src1=imread(filename1, CV_LOAD_IMAGE_GRAYSCALE);
    src2=imread(filename2, CV_LOAD_IMAGE_GRAYSCALE);

    Ptr<FeatureDetector> detector = ORB::create(48);

    detector->detect(src1, kp1 );
    detector->detect(src2, kp2);

    Ptr<DescriptorExtractor> extractor = ORB::create(48);

    extractor->compute(src1, kp1, desc1);
    extractor->compute(src2, kp2, desc2);

    vector<DMatch> matches;
    BFMatcher matcher(cv::NORM_HAMMING, true);
    matcher.match(desc1,desc2, matches, noArray());


    Mat res;
    drawMatches(src1, kp1, src2, kp2, matches, res, Scalar::all(-1), Scalar::all(-1),
                vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    imshow("Resultaat", res);
    imwrite("labo5_13.png",res);
    waitKey();
}

int main(int argc, char **argv) {
    int keuze = std::stoi(argv[1]);
    switch(keuze){
        case 13:
            opgave13(argv[2], argv[3]);
            break;
        case 12:
            opgave12(argv[2]);
            break;
        case 11:
            opgave11(argv[2]);
            break;
        case 10:
            opgave10(argv[2]);
    }
    return 0;
}

