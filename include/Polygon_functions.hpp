#include <cstdlib>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;     // antikeimeno tupou point
typedef K::Segment_2 Segment_2; // antikeimeno typou pleuras 
typedef CGAL::Polygon_2<K> Polygon_2;
typedef std::vector<Point_2> Points;                    // vector me stoixeia point
typedef std::vector<Segment_2> segments;                // vector me stoixeia pleurwn
typedef std::vector<double> dist;
typedef std::vector<Point_2>::iterator pveciterator; // iterator se vector me ta point

typedef std::vector<int> Areas;
typedef std::vector<Point_2>::iterator pveciterator;        //iterator gia vector apo points
typedef std::vector<Segment_2>::iterator segiterator;      //iterator gia segments
typedef std::vector<double> distance;   


Point_2 pointdistance(Points, segments, dist);
Point_2 pointdistance1(Points , segments , dist ,int );
int findintersection(Segment_2, Segment_2, segments,Segment_2);
int check_inside(Point_2, Point_2 *, Point_2 *, K);
Points handleinput(std::ifstream&,Points);
segments findvisible(Point_2,segments,segments,segments);


bool comp1a(Point_2 pt1, Point_2 pt2);
bool comp1b(Point_2 pt1, Point_2 pt2);
bool comp2a(Point_2 pt1, Point_2 pt2);
bool comp2b(Point_2 pt1, Point_2 pt2);


Points init_1a(Points p);
Points init_1b(Points p);
Points init_2a(Points p);
Points init_2b(Points p);

segments incremental_min(Points , Points , segments , segments );
segments incremental_max(Points , Points , segments , segments);
segments incremental(Points , Points , segments, segments ); 
Segment_2 edge_exists(Point_2 , Point_2 , segments );
segments create_segments(Points );
int find_red_segments(Segment_2 , Points , segments , int );

