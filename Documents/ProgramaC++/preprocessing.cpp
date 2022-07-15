#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

Mat cropImage(Mat img)
{
    Mat imgGray, imgBlur, edges, cropImage;
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(9, 9), 0,0,BORDER_REPLICATE);
    
    Canny(imgBlur, edges, 10, 200);

    Rect boundRect = boundingRect(edges);

    cropImage = img(boundRect);
    return cropImage;
}

Mat rotateImage(Mat imgPrep, Mat img)
{
    int largest_area = 0;
    int largest_contour_index = 0;
    RotatedRect box;

    Mat rotated, M, imgBorder;

    vector<vector<Point>> contours; // Vector for storing contours

    findContours(imgPrep, contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE); // Find the contours in the image

    for (size_t i = 0; i < contours.size(); i++) // iterate through each contour.
    {
        double area = contourArea(contours[i]); //  Find the area of contour

        if (area > largest_area)
        {
            largest_area = area;
            largest_contour_index = i;      // Store the index of largest contour
            box = minAreaRect(contours[i]); // Find the bounding rectangle for biggest contour
        }
    }

    box = minAreaRect(contours[largest_contour_index]);

    // drawContours( src, contours,largest_contour_index, Scalar( 0, 255, 0 ), 2 ); // Draw the largest contour using previously stored index.
    double angle = box.angle;

    if (angle < -45)
        angle = (90 + angle);
    // else
    // angle = -angle;

    Point2f center((imgPrep.cols - 1) / 2.0, (imgPrep.rows - 1) / 2.0);
    M = getRotationMatrix2D(center, angle, 1.0);
    // warpAffine(img,rotated,M,img.size(),INTER_CUBIC,BORDER_REPLICATE);
    warpAffine(img, rotated, M, img.size(), INTER_LINEAR, BORDER_REPLICATE);
    // Scalar value( rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255) );
    // copyMakeBorder(img, imgBorder, top, bottom, left, right, BORDER_REPLICATE, value );
    return rotated;
}

Mat prepImageRotate(Mat img)
{
    Mat imgGray, imgBlur, imgThresh;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(9, 9), 0);
    threshold(imgBlur, imgThresh, 0, 255, THRESH_BINARY_INV + THRESH_OTSU );

    return imgThresh;
}

int main(int argc, char** argv)
{

    Mat img = imread("2.jpg");
    Mat imgPrep, imgRotated, imgCropped;

    if (img.empty())
    {
        cout << "Could not open or find the image" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    imgPrep = prepImageRotate(img);

    imgRotated = rotateImage(imgPrep, img);

    imgCropped = cropImage(imgRotated);

    imwrite("saida.jpg", imgCropped);

    return 0;
}