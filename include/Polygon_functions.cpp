#include "Polygon_functions.hpp"


Segment_2 error = Segment_2(Point_2(-1,-1), Point_2(-1,-1));



Points handleinput(std::ifstream &in, Points result2)
{
    std::string line;
    std::string temp;
    char ccc;
    int i;
    int n;
    int n1;
    int length;
    while (in.peek() != EOF)
    {
        //get each line 
        std::getline(in, line);
        i = 0;
        ccc = line.at(i);
        while (ccc != '\t')
        {
            i++;
            ccc = line.at(i);
        }
        line.erase(0, i + 1); //finding the first characters that i dont want 0,1,2,3,4,5 etc and erase them
        temp = line;
        i = 0;
        ccc = line.at(i);
        while (ccc != '\t')
        {
            i++;
            ccc = line.at(i);
        }
        line.erase(line.begin() + i, line.end());   //finding the first point of the line
        n = stoi(line); //converting it to int
        line = temp;
        length = trunc(log10(n)) + 1;
        line.erase(0, length + 1);  //finding the second point of the line
        n1 = stoi(line);    //converting it to int
        result2.push_back(Point_2(n, n1));  //pushing each point to the vector
    }
    return result2;
}
Point_2 pointdistance1(Points interior, segments ch, dist d, int count)
{ 
    //finding the count closest interior point from an edge
    int i;
    Point_2 temppoint;
    d.clear();
    for (i = 0; i < interior.size(); i++)
    {
        d.push_back(CGAL::squared_distance(ch.front(), interior[i]));   //for every point find the distance from an edge
    }
    std::sort(d.begin(), d.end());  //sort the distances
    for (i = 0; i < interior.size(); i++)
    {
        if (CGAL::squared_distance(ch.front(), interior[i]) == d[count])    //finding the point i want
        { 
            temppoint = interior[i];
        }
    }
    return temppoint;
}
Point_2 pointdistance(Points interior, segments ch, dist d)
{   //same as pointdistance 1 but finds the closest point from an edge
    int i;
    Point_2 temppoint;
    d.clear();
    for (i = 0; i < interior.size(); i++)
    {
        d.push_back(CGAL::squared_distance(ch.front(), interior[i]));
    }
    std::sort(d.begin(), d.end()); 
    for (i = 0; i < interior.size(); i++)
    {
        if (CGAL::squared_distance(ch.front(), interior[i]) == d.front())
        { 
            temppoint = interior[i];
        }
    }
    return temppoint;
}
segments findvisible(Point_2 t, segments temp, segments chain, segments visible)
{
    //takes one edge and two edges that conect 1 interior point with this edge and test for every edge if they intersect with any other edge
    int c = 0;
    int flag;
    while (c < chain.size()) 
    {
        temp.push_back(Segment_2(t, chain[c][0]));                  //this is an edge from interior point to a peak of a polygons edge
        temp.push_back(Segment_2(t, chain[c][1]));                  //this is an edge from interior point to the other peak of a polygons edge
        flag = findintersection(temp[0], temp[1], chain, chain[c]); //check if its visible
        if (flag == 0)                                              //no intersections so its a visible edge
        {
            visible.push_back(chain[c]);
        }
        temp.clear();
        c++;
    }
    return visible;
}
int findintersection(Segment_2 interioredge1, Segment_2 interioredge2, segments pchain, Segment_2 chainedge)
{
    //finds if two edges intersect to a point or to an edge
    int c = 0;
    int flag;
    while (c < pchain.size())
    {
        flag = 0;
        auto result = CGAL::intersection(interioredge1, pchain[c]); //giving one edge from a point to a peak of a polygons edge
        if (result)
        {
            if (const Segment_2 *s = boost::get<Segment_2>(&*result))   //if they intersect to a segment then we have an intersection
            {
                flag = 1;
            }
            else
            {
                Point_2 *p = boost::get<Point_2>(&*result); //if they intersect to a point and the point is the peak of the edge then we dont have an intersection
                if (pchain[c] == chainedge && *p == interioredge1[1])
                {
                    flag = 0;
                }
                else    //if its any other point we have an intersect
                {
                    flag = 1;
                }
            }
        }
        //same process for the edge from interior point to the other peak of the edge
        result = CGAL::intersection(interioredge2, pchain[c]);
        if (result)
        {
            if (Segment_2 *s = boost::get<Segment_2>(&*result))
            {
                flag = 1;
            }
            else
            {
                Point_2 *p = boost::get<Point_2>(&*result);
                if (pchain[c] == chainedge && *p == interioredge2[1])
                {
                    flag = 0;
                }
                else
                {
                    flag = 1;
                }
            }
        }
        c++;
    }
    return flag;
}
int check_inside(Point_2 pt, Point_2 *pgn_begin, Point_2 *pgn_end, K traits)
{
    //checks if the polygon surrounds every point or not 
    int flag = 0;
    switch (CGAL::bounded_side_2(pgn_begin, pgn_end, pt, traits))
    {
    case CGAL::ON_BOUNDED_SIDE:
        break;
    case CGAL::ON_BOUNDARY:
        break;
    case CGAL::ON_UNBOUNDED_SIDE:
        flag = 1;
        break;
    }
    return flag;
}


bool comp1a(Point_2 pt1, Point_2 pt2) { 
    if(pt1.x()==pt2.x()){
        return pt1.y()<pt2.y();
    }
    else
        return (pt1.x() < pt2.x());}
bool comp1b(Point_2 pt1, Point_2 pt2) {
    if(pt1.x()==pt2.x()){
        return pt1.y()>pt2.y();
    }
    else 
        return (pt1.x() > pt2.x());}
bool comp2a(Point_2 pt1, Point_2 pt2) { 
    if(pt1.y()==pt2.y()){
        return pt1.x()<pt2.x();
    }
    else
    return (pt1.y() < pt2.y());}
bool comp2b(Point_2 pt1, Point_2 pt2) {
    if(pt1.y()==pt2.y()){
        return pt1.x()>pt2.x();
    }
    else 
        return (pt1.y() > pt2.y());}


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


segments incremental_min(Points result, Points curr_points, segments convex_seg, segments chain_seg){    
  Points convex_hull;
  Points red_points;
  segments red_segments_final;
  Polygon_2 p;
  Polygon_2 keep;
  Areas areas;
  Areas find;

  while (result.size() != 0)
  {
    red_points.clear();
    convex_hull.clear();
    convex_seg.clear();
    red_segments_final.clear();
    
    CGAL::convex_hull_2(curr_points.begin(), curr_points.end(), std::back_inserter(convex_hull)); // create convex hull for curr points
    
    int numberofsegments = convex_hull.size();
    int i;

    for (i = 0; i < numberofsegments; i++) // initialise triangle
    {
      if (i == numberofsegments - 1)
      {
        convex_seg.push_back(Segment_2(convex_hull[numberofsegments - 1], convex_hull[0]));
        break;
      }

      convex_seg.push_back(Segment_2(convex_hull[i], convex_hull[i + 1]));
    }
    Point_2 k = result[0]; //find new point k 

    for (int i = 0; i < convex_hull.size(); i++)
    { 
      int res = find_red_segments(Segment_2(k, convex_hull[i]), convex_hull, convex_seg,0);   //find red segments 
      if (!res)
      { 
        red_points.push_back(convex_hull[i]);
      }
      
    }


    if (!red_points.empty())    //if some edges of the convex hull are red try to find if the match any side of the polygon
    { 
      for (int i = 0; i < red_points.size(); i++)
      {
        for (int j = 1; j < red_points.size(); j++)
        {
          Segment_2 temp = edge_exists(red_points[i], red_points[j], convex_seg);
          if(edge_exists(temp[0], temp[1], chain_seg) != error){
            if(std::find(red_segments_final.begin(), red_segments_final.end(), edge_exists(temp[0], temp[1], chain_seg))==red_segments_final.end()){  //check if segment of 2 red points exists in polygon
              int res = find_red_segments(Segment_2(k, midpoint(edge_exists(temp[0], temp[1], chain_seg))), convex_hull, convex_seg,1);   //check if middle of the red segment is visible
              if(!res){   
                red_segments_final.push_back(edge_exists(temp[0], temp[1], chain_seg));
              }  
            }
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
        int res = find_red_segments(Segment_2(k, curr_points[i]), curr_points, chain_seg,0);
        if (!res)
        {                                                   
          red_points.push_back(curr_points[i]);       //find red edges 
        }
      } 
      if (!red_points.empty())      //for every combination of these red edges find if they match a segment of the polygon chain 
      { 
        for (int i = 0; i < red_points.size(); i++)
        {
          for (int j = 1; j < red_points.size(); j++)
          {
            Segment_2 temp = edge_exists(red_points[i], red_points[j], chain_seg);
            if (temp!=error)
            { 
              if(std::find(red_segments_final.begin(), red_segments_final.end(), temp)==red_segments_final.end())
              {
                int res = find_red_segments(Segment_2(k, midpoint(edge_exists(temp[0], temp[1], chain_seg))), curr_points, chain_seg,1);  //check if middle of the segment is visible to the new point
                if(!res){
                  red_segments_final.push_back(temp);
                }
              }
            }
          }
        }
      }
    }

    int min=0;
    int pos;
    int min_index=0;
    while (min<red_segments_final.size())
    {

      int i = 0;
      while (i < chain_seg.size())
      {
        if (red_segments_final[min] == chain_seg[i])
        {
          pos = i;
          break;
        }
        i++;
      }
      Segment_2 tempppp = chain_seg[pos];
      Point_2 temppp = Point_2(chain_seg[pos][1]);
      curr_points.push_back(k);
      chain_seg.insert(chain_seg.begin() + pos, Segment_2(chain_seg[pos][0], k));
      // insert in chain at the position that the visible edge was found the new edge connecting with the interior point
      chain_seg.insert(chain_seg.begin() + pos + 1, Segment_2(k, temppp));
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
      }
      else
      {
        double re;
        CGAL::area_2(p.begin(),p.end(),re,K());
        areas.push_back(re);
        find.push_back(min);     //save the indexes of the red segments 
        chain_seg.erase(chain_seg.begin() + pos);
        chain_seg.erase(chain_seg.begin() + pos);
        chain_seg.insert(chain_seg.begin() + pos, tempppp);                                                 // backtracking deleting the edges i created and bringing back the previous edge
        result.insert(result.begin(),k) ;                                  
        curr_points.pop_back(); 
      }
      min++;
    }

    i = 0;
    int index=std::distance(std::begin(areas), std::min_element(std::begin(areas), std::end(areas)));   //find the of the segment which creates the minimum area
    min_index=find[index];
    while (i < chain_seg.size())
    {
      if (red_segments_final[min_index] == chain_seg[i])
      {
        pos = i;
        break;
      }
      i++;
    }
    Segment_2 tempppp = chain_seg[pos];

    Point_2 temppp = Point_2(chain_seg[pos][1]);

    curr_points.push_back(k);
    chain_seg.insert(chain_seg.begin() + pos, Segment_2(chain_seg[pos][0], k));
    // insert in chain at the position that the visible edge was found the new edge connecting with the interior point
    chain_seg.insert(chain_seg.begin() + pos + 1, Segment_2(k, temppp));
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
    find.clear();
    areas.clear();
  }
  return chain_seg;
}


segments incremental_max(Points result, Points curr_points, segments convex_seg, segments chain_seg){   //same exact function as the above but creates the polygon with the max area
  Points convex_hull;
  Points red_points;
  segments red_segments_final;
  Polygon_2 p;
  Polygon_2 keep;

  Areas areas;
  Areas find;

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
        convex_seg.push_back(Segment_2(convex_hull[numberofsegments - 1], convex_hull[0]));
        break;
      }

      convex_seg.push_back(Segment_2(convex_hull[i], convex_hull[i + 1]));
    }


    Point_2 k = result[0]; // brhskw to neo shmeio k
    for (int i = 0; i < convex_hull.size(); i++)
    { 
      int res = find_red_segments(Segment_2(k, convex_hull[i]), convex_hull, convex_seg,0);
      
      if (!res)
      {
        red_points.push_back(convex_hull[i]);
      }
      
    }

    if (!red_points.empty())
    {
      for (int i = 0; i < red_points.size(); i++)
      {
        for (int j = 1; j < red_points.size(); j++)
        {
          Segment_2 temp = edge_exists(red_points[i], red_points[j], convex_seg);
          if(edge_exists(temp[0], temp[1], chain_seg) != error){
            if(std::find(red_segments_final.begin(), red_segments_final.end(), edge_exists(temp[0], temp[1], chain_seg))==red_segments_final.end()){
              int res = find_red_segments(Segment_2(k, midpoint(edge_exists(temp[0], temp[1], chain_seg))), convex_hull, convex_seg,1);
              if(!res){
                red_segments_final.push_back(edge_exists(temp[0], temp[1], chain_seg));
              }  
            }
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
        int res = find_red_segments(Segment_2(k, curr_points[i]), curr_points, chain_seg,0);
        if (!res)
        { 
          red_points.push_back(curr_points[i]);
        }
      } 
      if (!red_points.empty())
      { 
        for (int i = 0; i < red_points.size(); i++)
        {
          for (int j = 1; j < red_points.size(); j++)
          {
            Segment_2 temp = edge_exists(red_points[i], red_points[j], chain_seg);
            if (temp!=error)
            { // for every combination of red edges check if they match a segment in polygon chain
              if(std::find(red_segments_final.begin(), red_segments_final.end(), temp)==red_segments_final.end())
              {
                int res = find_red_segments(Segment_2(k, midpoint(edge_exists(temp[0], temp[1], chain_seg))), curr_points, chain_seg,1);
                if(!res){
                  red_segments_final.push_back(temp);
                }
              }
            }
          }
        }
      }
    }
    int max=0;
    int pos;
    int max_index=0;

    while (max<red_segments_final.size())
    {
      int i = 0;
      while (i < chain_seg.size())
      {
        if (red_segments_final[max] == chain_seg[i])
        {
          pos = i;
          break;
        }
        i++;
      }
      Segment_2 tempppp = chain_seg[pos];
      Point_2 temppp = Point_2(chain_seg[pos][1]);
      curr_points.push_back(k);
      chain_seg.insert(chain_seg.begin() + pos, Segment_2(chain_seg[pos][0], k));
 // insert in chain at the position that the visible edge was found the new edge connecting with the interior point
      chain_seg.insert(chain_seg.begin() + pos + 1, Segment_2(k, temppp));
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
      }
      else
      {
        double re;
        CGAL::area_2(p.begin(),p.end(),re,K());
        areas.push_back(re);
        find.push_back(max);
        chain_seg.erase(chain_seg.begin() + pos);
        chain_seg.erase(chain_seg.begin() + pos);
        chain_seg.insert(chain_seg.begin() + pos, tempppp);                                                 // backtracking deleting the edges i created and bringing back the previous edge
        result.insert(result.begin(),k) ;                                  
        curr_points.pop_back(); 
      }
      max++;
    }
    int index = std::distance(std::begin(areas), std::max_element(std::begin(areas), std::end(areas)));
    max_index = find[index];
    i = 0;
    while (i < chain_seg.size())
    {
      if (red_segments_final[max_index] == chain_seg[i])
      {
        pos = i;
        break;
      }
      i++;
    }
    Segment_2 tempppp = chain_seg[pos];
    Point_2 temppp = Point_2(chain_seg[pos][1]);

    curr_points.push_back(k);
    chain_seg.insert(chain_seg.begin() + pos, Segment_2(chain_seg[pos][0], k));
    // insert in chain at the position that the visible edge was found the new edge connecting with the interior point
    chain_seg.insert(chain_seg.begin() + pos + 1, Segment_2(k, temppp));
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
    find.clear();
    areas.clear();
  }


  return chain_seg;
}


segments incremental(Points result, Points curr_points, segments convex_seg, segments chain_seg){   //random icremental 
  srand((unsigned)time(NULL));

  Points convex_hull;
  Points red_points;

  segments red_segments_convex;
  segments red_segments_chain;
  segments red_segments_final;
  Polygon_2 p;
  Polygon_2 keep;

  while (result.size() != 0)
  {
    red_points.clear();
    convex_hull.clear();
    convex_seg.clear();
    red_segments_final.clear();
    
    CGAL::convex_hull_2(curr_points.begin(), curr_points.end(), std::back_inserter(convex_hull)); // create convex hull for curr points
    
    int numberofsegments = convex_hull.size();
    int i;

    for (i = 0; i < numberofsegments; i++) //initialise triangle
    {
      if (i == numberofsegments - 1)
      {
        convex_seg.push_back(Segment_2(convex_hull[numberofsegments - 1], convex_hull[0]));
        break;
      }

      convex_seg.push_back(Segment_2(convex_hull[i], convex_hull[i + 1]));
    }


    Point_2 k = result[0]; //new point k
    for (int i = 0; i < convex_hull.size(); i++)
    { 
      int res = find_red_segments(Segment_2(k, convex_hull[i]), convex_hull, convex_seg,0);
      
      if (!res)
      { 
        red_points.push_back(convex_hull[i]);
      }
      
    }

    if (!red_points.empty())
    {
      for (int i = 0; i < red_points.size(); i++)
      {
        for (int j = 1; j < red_points.size(); j++)
        {
          Segment_2 temp = edge_exists(red_points[i], red_points[j], convex_seg);
          if(edge_exists(temp[0], temp[1], chain_seg) != error){
            if(std::find(red_segments_final.begin(), red_segments_final.end(), edge_exists(temp[0], temp[1], chain_seg))==red_segments_final.end()){
              int res = find_red_segments(Segment_2(k, midpoint(edge_exists(temp[0], temp[1], chain_seg))), convex_hull, convex_seg,1);
              if(!res){
                red_segments_final.push_back(edge_exists(temp[0], temp[1], chain_seg));
              }  
            }
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
        int res = find_red_segments(Segment_2(k, curr_points[i]), curr_points, chain_seg,0);
        if (!res)
        { 
          red_points.push_back(curr_points[i]);
        }
      } 
      if (!red_points.empty())
      { 
        for (int i = 0; i < red_points.size(); i++)
        {
          for (int j = 1; j < red_points.size(); j++)
          {
            Segment_2 temp = edge_exists(red_points[i], red_points[j], chain_seg);
            if (temp!=error)
            { // for every combination of red edges check if they match a segment in CH
              if(std::find(red_segments_final.begin(), red_segments_final.end(), temp)==red_segments_final.end())
              {
                int res = find_red_segments(Segment_2(k, midpoint(edge_exists(temp[0], temp[1], chain_seg))), curr_points, chain_seg,1);
                if(!res){
                  red_segments_final.push_back(temp);
                }
              }
            }
          }
        }
      }
    }
    while (red_segments_final.size() > 0)
    {
      int random = rand() % red_segments_final.size();   //find a random segment

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
      Segment_2 tempppp = chain_seg[pos];
      Point_2 temppp = Point_2(chain_seg[pos][1]);
      curr_points.push_back(k);
      chain_seg.insert(chain_seg.begin() + pos, Segment_2(chain_seg[pos][0], k));
 // insert in chain at the position that the visible edge was found the new edge connecting with the interior point
      chain_seg.insert(chain_seg.begin() + pos + 1, Segment_2(k, temppp));
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
  }

  return chain_seg;
}

int find_red_segments(Segment_2 k, Points convex_hull, segments chain, int mid){   //returns 0 if there is no intersection of k with any of the segments of the chain
    int flag;
    int counter=0;

    for(int i=0; i<chain.size(); i++){
      auto result = CGAL::intersection(k, chain[i]);
      if(result)
            {
            if (const Segment_2 *s = boost::get<Segment_2>(&*result))
            {
              flag = 1;
              counter++;
              break;
            }
            else
            {
              Point_2 *p = boost::get<Point_2>(&*result);
              if (std::find(convex_hull.begin(), convex_hull.end(), *p) != convex_hull.end() && mid==0) //check if p is an edge of the chain
              {
                flag = 0;
              }
              else if(mid == 1 && *p == k[1]){   //if we check the middle point of a segment the only point of intersection between that and the new point should be only itself
                flag=0;
              }
              else
                {
                flag = 1;
                counter++;
                break;
                }
              }
            }

    }

    return counter == 0 ? 0 : 1;
    
}


Segment_2 edge_exists(Point_2 a, Point_2 b, segments chain){     //returns segment if seg(a,b) exists in chain else returns error segment
  if (std::find(chain.begin(), chain.end(), Segment_2(a, b)) != chain.end())
      return Segment_2(a, b);
  else if (std::find(chain.begin(), chain.end(), Segment_2(b, a)) != chain.end())
      return Segment_2(b, a);
  else
    return error;
}


segments create_segments(Points p){   //give ordered set of points to create vector of segments
  segments s;
  for(int i=0; i<p.size(); i++){
    if(i!=p.size()-1) 
      s.push_back(Segment_2(p[i],p[i+1]));
  }
  s.push_back(Segment_2(p[p.size()-1], p[0]));

  return s;
}

