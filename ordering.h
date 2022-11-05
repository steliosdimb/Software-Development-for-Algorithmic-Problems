#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/intersections.h>
#include <CGAL/draw_polygon_2.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>    // std::sort
#include <time.h>

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

Points init_1a(Points p);
Points init_1b(Points p);
Points init_2a(Points p);
Points init_2b(Points p);

Segments incremental(Points result, Points curr_points, Segments segments, Segments );
bool equal_segments(segment a, segment b);
segment edge_exists(Point_2 a, Point_2 b, Segments chain);
Segments create_segments(Points p);
int find_red_segments(segment k, Points convex_hull, Segments chain);
segment error = segment(Point_2(-1,-1), Point_2(-1,-1));

Points init_1a(Points p){
    std::sort(p.begin(), p.end(), comp1a);
    return p;
}

Points init_1b(Points p){
    std::sort(p.begin(), p.end(), comp1b);
    return p;
}
Points init_2a(Points p){
    std::sort(p.begin(), p.end(), comp2a);
    return p;
}
Points init_2b(Points p){
    std::sort(p.begin(), p.end(), comp2b);
    return p;
}


Segments incremental(Points result, Points curr_points, Segments convex_seg, Segments chain_seg){
  srand((unsigned)time(NULL));

  Points convex_hull;
  Points red_points;

  Segments red_segments_convex;
  Segments red_segments_chain;
  Segments red_segments_final;
  Polygon p;
  Polygon keep;

  while (result.size() != 0)
  {
    red_points.clear();
    convex_hull.clear();
    convex_seg.clear();
    red_segments_final.clear();
    
    CGAL::convex_hull_2(curr_points.begin(), curr_points.end(), std::back_inserter(convex_hull)); // create convex hull for curr points
    
    int numberofsegments = convex_hull.size();
    int i;

    for (i = 0; i < numberofsegments; i++) // arxikopoiw to convex_seg me ta 3 segments
    {
      if (i == numberofsegments - 1)
      {
        convex_seg.push_back(segment(convex_hull[numberofsegments - 1], convex_hull[0]));
        break;
      }

      convex_seg.push_back(segment(convex_hull[i], convex_hull[i + 1]));
    }


    Point_2 k = result[0]; // brhskw to neo shmeio k
    cout<<"new point is "<<k<<endl;

    for (int i = 0; i < convex_hull.size(); i++)
    { 
      int res = find_red_segments(segment(k, convex_hull[i]), convex_hull, convex_seg);
      
      if (!res)
      { // briskw an exei kokkini akmh
        red_points.push_back(convex_hull[i]);
      }
      
    }

    if (!red_points.empty())
    { // ean exw kapoies korufes tou convex hull poy einai kokkines
      for (int i = 0; i < red_points.size(); i++)
      {
        for (int j = 1; j < red_points.size(); j++)
        {
          segment temp = edge_exists(red_points[i], red_points[j], convex_seg);
          //std::cout << temp << std::endl;
          if(edge_exists(temp[0], temp[1], chain_seg) != error){
            if(std::find(red_segments_final.begin(), red_segments_final.end(), edge_exists(temp[0], temp[1], chain_seg))==red_segments_final.end())
              red_segments_final.push_back(edge_exists(temp[0], temp[1], chain_seg));
          }
        }
      }
    }
    
    red_points.clear();
    Points tempp=curr_points;
    // if no visible edges in convex hull then search in polygon chain
    if (red_segments_final.size() == 0)
    {
      for (int i = 0; i < curr_points.size(); i++)
      { 
        //std::cout << segment(k,curr_points[i]) << std::endl;
        int res = find_red_segments(segment(k, curr_points[i]), curr_points, chain_seg);
        if (!res)
        { // briskw an exei kokkini akmh
          red_points.push_back(curr_points[i]);
        }
      } 
      if (!red_points.empty())
      { // ean exw kapoies korufes poy einai kokkines
        for (int i = 0; i < red_points.size(); i++)
        {
          for (int j = 1; j < red_points.size(); j++)
          {
            segment temp = edge_exists(red_points[i], red_points[j], chain_seg);
            //cout<<temp<<"temp is "<<endl;
            if (temp!=error)
            { // for every combination of red edges check if they match a segment in CH
              if(std::find(red_segments_final.begin(), red_segments_final.end(), temp)==red_segments_final.end())
                red_segments_final.push_back(temp);
            }
          }
        }
      }
    }

    while (red_segments_final.size() > 0)
    {
      int random = rand() % red_segments_final.size();

      int i = 0;
      int pos;
      while (i < chain_seg.size())
      {
        if (red_segments_final[random] == chain_seg[i])
        {
          pos = i;
          break;
        }
        i++;
      }
      segment tempppp = chain_seg[pos];

      Point_2 temppp = Point_2(chain_seg[pos][1]);

      curr_points.push_back(k);
      chain_seg.insert(chain_seg.begin() + pos, segment(chain_seg[pos][0], k));
 // insert in chain at the position that the visible edge was found the new edge connecting with the interior point
      chain_seg.insert(chain_seg.begin() + pos + 1, segment(k, temppp));
      chain_seg.erase(chain_seg.begin() + pos + 2);
      result.erase(result.begin());

      p.clear();
      keep.clear();
      int e = 0;
      p.push_back(chain_seg[e][0]);    // initialize the new polygon
      keep.push_back(chain_seg[e][0]); // make a copy of this polygon
      p.push_back(chain_seg[e][1]);
      keep.push_back(chain_seg[e][1]);
      e++;
      while (e < chain_seg.size() - 1)
      {
        p.push_back(chain_seg[e][1]);
        keep.push_back(chain_seg[e][1]);
        e++;
      }

      if (p.is_simple() == 0) // if with the new edges the polugon is not simple or the polugon does not surround every point i am backtracking
      {
        chain_seg.erase(chain_seg.begin() + pos);
        chain_seg.erase(chain_seg.begin() + pos);
        chain_seg.insert(chain_seg.begin() + pos, tempppp);                                                 // backtracking deleting the edges i created and bringing back the previous edge
        result.insert(result.begin(),k) ;                                  
        curr_points.pop_back();                                           // pushing back again the interior point
        red_segments_final.erase(std::find(red_segments_final.begin(), red_segments_final.end(), tempppp)); // deleting the visible edges because it doesnt meet the criteria
      }
      else
      {
        break;
      }
    }
    CGAL::draw(p);
  }

  return chain_seg;
}

int find_red_segments(segment k, Points convex_hull, Segments chain){
    int flag;
    int counter=0;

    for(int i=0; i<chain.size(); i++){
      auto result = CGAL::intersection(k, chain[i]);
      if(result)
            {
            if (const segment *s = boost::get<segment>(&*result))
            {
              flag = 1;
              counter++;
              break;
            }
            else
            {
              Point_2 *p = boost::get<Point_2>(&*result);
              if (std::find(convex_hull.begin(), convex_hull.end(), *p) != convex_hull.end())
              {
                flag = 0;
              }
              else
                {
                //cout<<" point of intersection asssssss"<<*p<<endl;
                flag = 1;
                counter++;
                break;
                }
              }
            }
    }

    return counter == 0 ? 0 : 1;
    
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


segment edge_exists(Point_2 a, Point_2 b, Segments chain){     //returns true if seg(a,b) exists in chain
  if (std::find(chain.begin(), chain.end(), segment(a, b)) != chain.end())
      return segment(a, b);
  else if (std::find(chain.begin(), chain.end(), segment(b, a)) != chain.end())
      return segment(b, a);
  else
    return error;
}

bool test(segment a, segment b){
  if(a.source() == b.source() && a.target() == b.target())
      return true;
  else 
    return false;
}

Segments create_segments(Points p){   //give ordered set of points to create vector of segments
  Segments s;
  for(int i=0; i<p.size(); i++){
    if(i!=p.size()-1) 
      s.push_back(segment(p[i],p[i+1]));
  }
  s.push_back(segment(p[p.size()-1], p[0]));

  return s;
}

