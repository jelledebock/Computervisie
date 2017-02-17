#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

Mat src; Mat grey_dst; Mat tres_dst;
char window_name1[] = "Unprocessed Image";
char window_name2[] = "Greyed";
char window_name3[] = "Modified Treshold";

int main( int argc, char** argv )
{
    /// Load the source image
    src = imread( argv[1], 1 );

    namedWindow( window_name1, WINDOW_AUTOSIZE );
    imshow("Unprocessed Image",src);

    grey_dst = src.clone();
    cvtColor(src, grey_dst, CV_RGB2GRAY);

    namedWindow( window_name2, WINDOW_AUTOSIZE );
    imshow("Greyed",grey_dst);

    tres_dst = src.clone();
    threshold(src, tres_dst, 0.50, 255, THRESH_BINARY_INV);

    namedWindow( window_name3, WINDOW_AUTOSIZE );
    imshow("Modified Treshold" ,tres_dst);

    imwrite("greyed.png",grey_dst);
    imwrite("threshold.png",tres_dst);

    waitKey();
    return 0;
}
