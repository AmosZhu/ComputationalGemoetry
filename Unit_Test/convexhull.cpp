#include "../common/ConvexHull2D.h"
#include "../common/Point.h"
#include <string.h>
#include <sstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void Intersection_Test()
{
    int w = 850;
    int h = 850;
    int z = 40;
    cv::Mat img(w, h, CV_8UC3);
    int n = 13;

//    CG::Point2<int> pts[n];
//
//    CG::Vector<CG::Point2<int>> test_vec(n);
//    srand(time(0));
//    for (int i = 0; i < n; ++i)
//    {
//        pts[i].x = (rand() % w - w / 2) + 1;
//        pts[i].y = (rand() % h - h / 2) + 1;
//        test_vec[i] = pts[i];
//    }


    CG::Point2<double> pts[n];
    pts[0] = CG::Point2<double>(-4, -2);
    pts[1] = CG::Point2<double>(-6, -4);
    pts[2] = CG::Point2<double>(-3, -10);
    pts[3] = CG::Point2<double>(1, -4);
    pts[4] = CG::Point2<double>(-3, 4);
    pts[5] = CG::Point2<double>(6, -4);
    pts[6] = CG::Point2<double>(-1,-1);
    pts[7] = CG::Point2<double>(6, 6);
    pts[8] = CG::Point2<double>(-6, 10);
    pts[9] = CG::Point2<double>(0, 8);
    pts[10] = CG::Point2<double>(0, 8);
    pts[11] = CG::Point2<double>(10, 8);
    pts[12] = CG::Point2<double>(6, 8);


    for (int i = 0; i < n; ++i)
    {
        double x = (pts[i].x * z + w / 2);
        double y = h - (pts[i].y * z + h / 2);

        std::stringstream ss;
        ss << "(" << pts[i].x << "," << pts[i].y << ")";
        cv::putText(img, ss.str(), cv::Point(x + 10, y + 10), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 143, 143), 1);
        cv::circle(img, cv::Point(x, y), 2, cv::Scalar(255, 255, 0), 1);
    }

    // Compare the result from Jarvis and Graham scan
    CG::ConvexHull2D<double> CH;
    int64 n1 = 6;
    CH.BuildFrom(pts, n1, CG::JARVIS);
    std::cout << CH << std::endl;

    std::cout << CH.ext_index << std::endl;

    long long res = CH.ext_index.Size();
    for (int i = 0; i < CH.ext_index.Size(); ++i)
    {
        res *= (CH.ext_index[i] + 1);
        res %= n1 + 1;
    }
    res = res % (n1 + 1);

    std::cout << res << std::endl;

    // Draw the convex hull boundary
    for (int i = 0; i < CH.m_extpts.Size(); ++i)
    {
        int j = (i + 1) % CH.m_extpts.Size();
        double p1_x = (CH.m_extpts[i].x * z + w / 2);
        double p1_y = h - (CH.m_extpts[i].y * z + h / 2);

        double p2_x = (CH.m_extpts[j].x * z + w / 2);
        double p2_y = h - (CH.m_extpts[j].y * z + h / 2);

        cv::arrowedLine(img, cv::Point(p1_x, p1_y), cv::Point(p2_x, p2_y), cv::Scalar(255, 0, 0), 2);
    }

    //------------------------- second convex hull -----------------------------


    CG::ConvexHull2D<double> CH_G;
    int64 n2 = n - n1;
    CH_G.BuildFrom(pts + n1, n2, CG::GRAHAMSCAN);
    std::cout << CH_G << std::endl;

    std::cout << CH_G.ext_index << std::endl;

    res = CH_G.ext_index.Size();
    for (int i = 0; i < CH_G.ext_index.Size(); ++i)
    {
        res *= (CH_G.ext_index[i] + 1);
        res %= n2 + 1;
    }
    res = res % (n2 + 1);

    std::cout << res << std::endl;

    // Draw the convex hull boundary
    for (int i = 0; i < CH_G.m_extpts.Size(); ++i)
    {
        int j = (i + 1) % CH_G.m_extpts.Size();
        double p1_x = (CH_G.m_extpts[i].x * z + w / 2);
        double p1_y = h - (CH_G.m_extpts[i].y * z + h / 2);

        double p2_x = (CH_G.m_extpts[j].x * z + w / 2);
        double p2_y = h - (CH_G.m_extpts[j].y * z + h / 2);

        cv::arrowedLine(img, cv::Point(p1_x, p1_y), cv::Point(p2_x, p2_y), cv::Scalar(0, 0, 255), 2);
    }


    cv::imshow("display", img);
    cv::waitKey();


    bool flag = CH.Intersect(CH_G);

    if (flag)
    {
        std::cout << "Intersection detected" << std::endl;
    }
    else
    {
        std::cout << "No detection" << std::endl;
    }

    cv::destroyAllWindows();

}

void ConvexHull_Construct()
{
    int w = 850;
    int h = 850;
    int z = 1;
    cv::Mat img(w, h, CV_8UC3);
    int n = 50;

//    CG::Point2<int> pts[n];
//    pts[0] = CG::Point2<int>(-4, -4);
//    pts[1] = CG::Point2<int>(-6, -4);
//    pts[2] = CG::Point2<int>(-3, -4);
//    pts[3] = CG::Point2<int>(1, -4);
//    pts[4] = CG::Point2<int>(-3, 9);
//    pts[5] = CG::Point2<int>(6, -4);
//    pts[6] = CG::Point2<int>(7, 5);
//    pts[7] = CG::Point2<int>(6, 6);
//    pts[8] = CG::Point2<int>(-6, 10);
//    pts[9] = CG::Point2<int>(0, 8);
//    pts[10] = CG::Point2<int>(0, 8);
//    pts[11] = CG::Point2<int>(10, 8);
//    pts[12] = CG::Point2<int>(6, 8);


    CG::Point2<int> pts[n];

    CG::Vector<CG::Point2<int>> test_vec(n);
    srand(time(0));
    for (int i = 0; i < n; ++i)
    {
        pts[i].x = (rand() % w - w / 2) + 1;
        pts[i].y = (rand() % h - h / 2) + 1;
        test_vec[i] = pts[i];
    }

    for (int i = 0; i < n; ++i)
    {
        int x = (pts[i].x * z + w / 2);
        int y = h - (pts[i].y * z + h / 2);

        std::stringstream ss;
        ss << "(" << pts[i].x << "," << pts[i].y << ")";
//        cv::putText(img, ss.str(), cv::Point(x + 10, y + 10), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 143, 143), 2);
        cv::circle(img, cv::Point(x, y), 2, cv::Scalar(255, 255, 0), 1);
    }

    // Compare the result from Jarvis and Graham scan
    CG::ConvexHull2D<int> CH;
    CH.BuildFrom(pts, n, CG::GRAHAMSCAN);
    std::cout << CH << std::endl;

    std::cout << CH.ext_index << std::endl;

    long long res = CH.ext_index.Size();
    for (int i = 0; i < CH.ext_index.Size(); ++i)
    {
        res *= (CH.ext_index[i] + 1);
        res %= n + 1;
    }
    res = res % (n + 1);

    std::cout << res << std::endl;

    CG::ConvexHull2D<int> CH_G;
    CH_G.BuildFrom(pts, n, CG::GRAHAMSCAN);
    std::cout << CH_G << std::endl;

    std::cout << CH_G.ext_index << std::endl;

    res = CH_G.ext_index.Size();
    for (int i = 0; i < CH_G.ext_index.Size(); ++i)
    {
        res *= (CH_G.ext_index[i] + 1);
        res %= n + 1;
    }
    res = res % (n + 1);

    std::cout << res << std::endl;

    // Draw the convex hull boundary
    for (int i = 0; i < CH.m_extpts.Size(); ++i)
    {
        int j = (i + 1) % CH.m_extpts.Size();
        int p1_x = (CH.m_extpts[i].x * z + w / 2);
        int p1_y = h - (CH.m_extpts[i].y * z + h / 2);

        int p2_x = (CH.m_extpts[j].x * z + w / 2);
        int p2_y = h - (CH.m_extpts[j].y * z + h / 2);

        cv::line(img, cv::Point(p1_x, p1_y), cv::Point(p2_x, p2_y), cv::Scalar(255, 0, 0), 2);
    }

    cv::imshow("display", img);
    cv::waitKey();
    cv::destroyAllWindows();
}

int main()
{
    Intersection_Test();
}
