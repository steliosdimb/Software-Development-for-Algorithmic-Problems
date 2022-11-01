#include <cstdlib>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;     // antikeimeno tupou point
typedef K::Segment_2 Segment_2; // antikeimeno typou pleuras
typedef CGAL::Polygon_2<K> Polygon_2;
typedef std::istream_iterator<Point_2> point2_iterator; // iterator se points apo to input file
typedef std::vector<Point_2> Points;                    // vector me stoixeia point
typedef std::vector<Segment_2> segments;                // vector me stoixeia pleurwn
typedef std::vector<double> dist;
typedef std::vector<Point_2>::iterator pveciterator; // iterator se vector me ta point


Point_2 pointdistance(Points, segments, dist);
Point_2 pointdistance1(Points , segments , dist ,int );
int findintersection(Segment_2, Segment_2, segments,Segment_2);
int check_inside(Point_2, Point_2 *, Point_2 *, K);
Points handleinput(std::ifstream&,Points);
segments findvisible(Point_2,segments,segments,segments);