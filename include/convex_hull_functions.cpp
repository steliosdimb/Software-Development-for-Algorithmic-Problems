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
        std::getline(in, line);
        i = 0;
        ccc = line.at(i);
        while (ccc != '\t')
        {
            i++;
            ccc = line.at(i);
        }
        line.erase(0, i + 1);
        temp = line;
        i = 0;
        ccc = line.at(i);
        while (ccc != '\t')
        {
            i++;
            ccc = line.at(i);
        }
        line.erase(line.begin() + i, line.end());
        n = stoi(line);
        line = temp;
        length = trunc(log10(n)) + 1;
        line.erase(0, length + 1);
        n1 = stoi(line);
        result2.push_back(Point_2(n, n1));
    }
    return result2;
}
Point_2 pointdistance1(Points interior, segments ch, dist d, int count)
{ // sunarthsh upologismou apostashs apo ena edge se ena interior point
    int i;
    Point_2 temppoint;
    d.clear();
    for (i = 0; i < interior.size(); i++)
    {
        d.push_back(CGAL::squared_distance(ch.front(), interior[i]));
    }
    std::sort(d.begin(), d.end()); // vriskw tis mikroteres apostaseis
    for (i = 0; i < interior.size(); i++)
    {
        if (CGAL::squared_distance(ch.front(), interior[i]) == d[count])
        { // vriskw kai to poio einai to point
            temppoint = interior[i];
        }
    }
    return temppoint;
}
Point_2 pointdistance(Points interior, segments ch, dist d)
{ // sunarthsh upologismou apostashs apo ena edge se ena interior point
    int i;
    Point_2 temppoint;
    d.clear();
    for (i = 0; i < interior.size(); i++)
    {
        d.push_back(CGAL::squared_distance(ch.front(), interior[i]));
    }
    std::sort(d.begin(), d.end()); // vriskw tis mikroteres apostaseis
    for (i = 0; i < interior.size(); i++)
    {
        if (CGAL::squared_distance(ch.front(), interior[i]) == d.front())
        { // vriskw kai to poio einai to point
            temppoint = interior[i];
        }
    }
    return temppoint;
}
segments findvisible(Point_2 t, segments temp, segments chain, segments visible)
{
    int c = 0;
    int flag;
    while (c < chain.size()) // gia kathe edge
    {
        temp.push_back(Segment_2(t, chain[c][0]));                  // auth einai h edge me to interior point kai thn mia korufh ths akmhs ths polugwnikhs
        temp.push_back(Segment_2(t, chain[c][1]));                  // auth einai h edge me to interior point kai thn allh korufh ths akmhs ths polugwnikhs grammhs
        flag = findintersection(temp[0], temp[1], chain, chain[c]); // kalw gia na dw an h akmh auth einai orath
        if (flag == 0)                                              // den exw interactions ara exw pithano edge
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
    int c = 0;
    int flag;
    while (c < pchain.size())
    {
        flag = 0;
        auto result = CGAL::intersection(interioredge1, pchain[c]);
        if (result)
        {
            if (const Segment_2 *s = boost::get<Segment_2>(&*result))
            {
                flag = 1;
            }
            else
            {
                Point_2 *p = boost::get<Point_2>(&*result);
                if (pchain[c] == chainedge && *p == interioredge1[1])
                {
                    flag = 0;
                }
                else
                {
                    flag = 1;
                }
            }
        }
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