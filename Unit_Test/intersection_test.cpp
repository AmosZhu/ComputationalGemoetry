//
// Created by amos on 6/6/19.
//

#include "common/Line.h"
#include "common/Template/Vector.h"
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "common/Vec.h"

void test_assignement_sample()
{
    int n_seg, n_ray, n_line, n_circle;

    std::cin >> n_seg >> n_ray >> n_line >> n_circle;
    CG::Vector<CG::Line2D<double> *> lines;
    lines.Reserve(n_seg + n_ray + n_line);

    for (int k = 0; k < n_seg; ++k)
    {
        CG::Point2<double> xy, uv;
        std::cin >> xy.x >> xy.y >> uv.x >> uv.y;

        lines.Push_back(new CG::Segment2D<double>(xy, uv));
    }

    for (int k = 0; k < n_ray; ++k)
    {
        CG::Point2<double> xy, uv;
        std::cin >> xy.x >> xy.y >> uv.x >> uv.y;

        lines.Push_back(new CG::Ray2D<double>(xy, uv));
    }

    for (int k = 0; k < n_line; ++k)
    {
        CG::Point2<double> xy, uv;
        std::cin >> xy.x >> xy.y >> uv.x >> uv.y;

        lines.Push_back(new CG::Line2D<double>(xy, uv));
    }

    int n_all = n_seg + n_ray + n_line;

    // Detect intersection with each other
    CG::Vector<CG::Point2<double>> intersections;
    for (int i = 0; i < n_all; ++i)
    {
        for (int j = i + 1; j < n_all; ++j)
        {
            CG::Point2<double> int_pt;
            if (lines[i]->Intersect(*lines[j], int_pt))
                intersections.Push_back(int_pt);
        }
    }


    // Draw configuration
    int w = 850;
    int h = 850;
    int z = 3; // zoom factor
    cv::Mat img(w, h, CV_8UC3);

    // Draw segment
    for (int i = 0; i < n_seg; ++i)
    {
        CG::Segment2D<double> *seg = dynamic_cast<CG::Segment2D<double> *>(lines[i]);

        int p1_x = (seg->p.x * z + w / 2);
        int p1_y = (seg->p.y * z + h / 2);

        int p2_x = (seg->q.x * z + w / 2);
        int p2_y = (seg->q.y * z + h / 2);

        cv::line(img, cv::Point(p1_x, p1_y), cv::Point(p2_x, p2_y), cv::Scalar(255, 0, 0), 2);
    }

    for (int i = 0; i < n_ray; ++i)
    {
        CG::Ray2D<double> *ray = dynamic_cast<CG::Ray2D<double> *>(lines[i + n_seg]);

        int p1_x = (ray->p.x * z + w / 2);
        int p1_y = (ray->p.y * z + h / 2);

        CG::Vec2<double> d = ray->Dir();
        CG::Point2<double> end = ray->p + w * d;

        int p2_x = (end.x * z + w / 2);
        int p2_y = (end.y * z + h / 2);

        cv::line(img, cv::Point(p1_x, p1_y), cv::Point(p2_x, p2_y), cv::Scalar(0, 0, 255), 2);
    }

    for (int i = 0; i < n_line; ++i)
    {
        CG::Line2D<double> *line = lines[i + n_seg + n_ray];

        CG::Vec2<double> d = line->Dir();

        CG::Point2<double> begin = line->p + w * d;
        CG::Point2<double> end = line->p - w * d;


        int p1_x = (begin.x * z + w / 2);
        int p1_y = (begin.y * z + h / 2);
        int p2_x = (end.x * z + w / 2);
        int p2_y = (end.y * z + h / 2);

        cv::line(img, cv::Point(p1_x, p1_y), cv::Point(p2_x, p2_y), cv::Scalar(0, 255, 0), 2);
    }

    // Draw intersections
    for (int i = 0; i < intersections.Size(); ++i)
    {
        double x = intersections[i].x * z + w / 2;
        double y = intersections[i].y * z + h / 2;
        cv::circle(img, cv::Point(x, y), 2, cv::Scalar(255, 255, 0), 5);
    }


    cv::imshow("display", img);
    cv::waitKey();
    cv::destroyAllWindows();
}

int main()
{

    test_assignement_sample();
}

