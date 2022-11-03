#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/intersections.h>
#include <CGAL/draw_polygon_2.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>    // std::sort


using namespace std;


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef K::Segment_2 segment;   //antikeimeno pleuras
typedef K::Point_2 Point_2;     //antikeimeno shmeiou
typedef CGAL::Polygon_2<K> Polygon_2;

typedef std::istream_iterator< Point_2 > point2_iterator;  //iterator gia input
typedef std::vector<Point_2>::iterator pveciterator;        //iterator gia vector apo points
typedef std::vector<segment>::iterator segiterator;      //iterator gia segments

typedef std::vector<segment> Segments;    //vector gia segments
typedef std::vector<Point_2> Points;   //vector gia points
typedef std::vector<double> distance;   
typedef CGAL::Polygon_2<K> Polygon;


bool comp1a(Point_2 pt1, Point_2 pt2) { return (pt1.x() < pt2.x());}
bool comp1b(Point_2 pt1, Point_2 pt2) { return (pt1.x() > pt2.x());}
bool comp2a(Point_2 pt1, Point_2 pt2) { return (pt1.y() < pt2.y());}
bool comp2b(Point_2 pt1, Point_2 pt2) { return (pt1.y() > pt2.y());}

void init_1a(Points p);
void init_1b(Points p);
void init_2a(Points p);
void init_2b(Points p);

void incremental(Points result, Points curr_points, Segments segments, Segments );
bool equal_segments(segment a, segment b);
bool edge_exists(Point_2 a, Point_2 b, Segments chain);
Segments create_segments(Points p);
int find_red_segments(segment k, Points curr_points, Points convex_hull);

void init_1a(Points p){
    std::sort(p.begin(), p.end(), comp1a);
    for (pveciterator iter=p.begin(); iter!=p.end(); iter++)
      std::cout << *iter << std::endl;
}

void init_1b(Points p){
    std::sort(p.begin(), p.end(), comp1b);
    for (pveciterator iter=p.begin(); iter!=p.end(); iter++)
      std::cout << *iter << std::endl;
}
void init_2a(Points p){
    std::sort(p.begin(), p.end(), comp2a);
    for (pveciterator iter=p.begin(); iter!=p.end(); iter++)
      std::cout << *iter << std::endl;
}
void init_2b(Points p){
    std::sort(p.begin(), p.end(), comp2b);
    for (pveciterator iter=p.begin(); iter!=p.end(); iter++)
      std::cout << *iter << std::endl;
}

void incremental(Points result, Points curr_points, Segments convex_seg, Segments chain_seg){
  Points convex_hull;   
  Points red_points;
  CGAL::convex_hull_points_2(curr_points.begin(), curr_points.end(), std::back_inserter(convex_hull));    //create convex hull for curr points
  pveciterator k = result.begin();   //brhskw to neo shmeio k

  pveciterator p = curr_points.begin()+curr_points.size()-1;   //brhskw to teleutaio shmeio apo to curr_points

  for(int i=0; i<curr_points.size(); i++){
    if(!find_red_segments(segment(*k, convex_hull[i]), convex_hull, convex_hull)){ //briskw an exei kokkini akmh
        red_points.push_back(convex_hull[i]);
    }
  }
  if(!red_points.empty()){
    Segments red_segments;
    for(int i=0; i<convex_hull.size(); i++){
      for(int j=1; j<convex_hull.size(); j++){
        if(edge_exists(red_points[i], red_points[j], convex_seg)){
          red_segments.push_back(segment(red_points[i], red_points[j]));
        }
      }
    }
  }
}

int find_red_segments(segment k, Points curr_points, Points convex_hull){
    int flag;
    for(int i = 0; i<curr_points.size(); i++){
      flag=-1;
      if(i==curr_points.size()-1){
        auto result = CGAL::intersection(k, segment(curr_points[i], curr_points[0]));
        if (const segment *s = boost::get<segment>(&*result))
        {
          flag=1;
        }
        else{  
          Point_2 *p = boost::get<Point_2>(&*result);
        if (std::find(curr_points.begin(), curr_points.end(), *p) == curr_points.end())  //an den uparxei stis korufes
          {
            flag = 0;
          }
        else
          {
            flag = 1;
          }
      }
      }
      else{
          auto result = CGAL::intersection(k, segment(curr_points[i], curr_points[i+1]));
          if(result){
            if (const segment *s = boost::get<segment>(&*result))
              {
                flag=1;
              }
            else{  
                Point_2 *p = boost::get<Point_2>(&*result);
                if (std::find(curr_points.begin(), curr_points.end(), *p) != curr_points.end())
                {
                  flag = 0;
                }
                else
                {
                  flag = 1;
                }
            }
          }
        }
    }
    return flag;
    
}

bool equal_segments(segment a, segment b){     //returns true if a has same cordinates as b
  if(a.source() == b.source() && a.target() == b.target())
      return true;
  else if(a.source() == b.target() && b.source() == a.target())
      return true;
  else if(a==b)
      return true;
  else return false;
}


bool edge_exists(Point_2 a, Point_2 b, Segments chain){     //returns true if seg(a,b) exists in chain
  int flag=0;
  for(segiterator s = chain.begin(); s!=chain.end(); s++){
    if(equal_segments(segment(a,b),*s))
      flag=1;
    else 
      flag=0;
  }
  return flag!=0 ? true : false;
}

Segments create_segments(Points p){   //give ordered set of points to create vector of segments
  Segments s;
  for(int i=0; i<p.size(); i++){
    s.push_back(segment(p[i],p[i+1]));
  }
  s.push_back(segment(p[p.size()-1], p[0]));

}