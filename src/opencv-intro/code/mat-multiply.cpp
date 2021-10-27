#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    double data_a[] = { 3, 2, 1, 5, 9, 1, 3, 0 };
    double data_b[] = { 2, 9, 0, 1, 3, 5, 2, 4, 7, 8, 1, 5 };

    cv::Mat a(2, 4, CV_64F, data_a);
    cv::Mat b(4, 3, CV_64F, data_b);
    std::cout << a << '\n' << b << '\n' << a * b;
}
