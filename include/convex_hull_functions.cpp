#include "convex_hull_functions.hpp"
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