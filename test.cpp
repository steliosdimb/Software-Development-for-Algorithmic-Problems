

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/convex_hull_2.h>
#include <CGAL/squared_distance_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/intersections.h>
#include <CGAL/draw_polygon_2.h>
#include <CGAL/Polygon_2_algorithms.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>

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
int findintersection(Segment_2, Segment_2, segments,Segment_2);
int check_inside(Point_2, Point_2 *, Point_2 *, K);
int main()
{
  srand((unsigned)time(NULL));
  int random;
  Points result;  // init vector me points gia to convex hull
  Points result1; // init vector me points gia to sunolo ton eswterikwn points
  Points result2; // init me ola ta poiints
  Points keep;
  segments chain;                                // init polugwnikh alusida pou sh arxh einai isi me to convex hull
  segments temp;                                 // gia temp edges
  Polygon_2 p;                                   // to polugwno mou
  segments visible;                              // gia tis visible akmes
  dist dis;                                      // vector me apostaseis
  std::ifstream in("input.txt");                 // anoigw arxeio (thelei kai alles epexergasies)
  point2_iterator begin(in);                     // deixnw sto prwto point tou arxeiou
  point2_iterator end;                           // deixnei teleutaio point tou arxeiou
  copy(begin, end, std::back_inserter(result1)); // kanw copy sto vector result1 ta points
  int r = 0;
  while (r < result1.size())
  { // vazw ola ta points sto result2
    result2.push_back(result1[r]);
    r++;
  }
  in.clear();
  in.seekg(0);                                                 // paw xana sthn arxh tou arxeiou
  CGAL::convex_hull_2(begin, end, std::back_inserter(result)); // vazei ta points apo to convex hull sto result (vector)
  std::cout << result.size() << " points on the convex hull" << std::endl;
  for (pveciterator iter = result.begin(); iter != result.end(); ++iter) // trexw me to iterator to vector kai ektypwnw
    std::cout << *iter << std::endl;
  int j;
  for (j = 0; j < result.size(); j++)
  {
    result1.erase(std::remove(result1.begin(), result1.end(), result[j]), result1.end()); // vgazw ta shmeia ta exwterika
  }
  std::cout << result1.size() << " interior points" << std::endl; // ektupwnw ta eswterika shmeia
  for (pveciterator iter = result1.begin(); iter != result1.end(); ++iter)
    std::cout << *iter << std::endl;
  int numberofsegments = result.size();
  int i;
  for (i = 0; i < numberofsegments - 1; i++)
  {
    chain.push_back(Segment_2(result[i], result[i + 1]));
  }
  chain.push_back(Segment_2(result[i], result[0])); // eftiaxa thn arxikh polugwnikh alusida
  for (i = 0; i < result.size(); i++)
  {
    p.push_back(result[i]);
  } // to polugwno mou einai h polugwnikh alusida mou

  while (result2.size() != p.size() || result1.size() != 0)
  {            // oso to polugwno den periexei ola ta shmeia tou input kai den exw perilavei ola ta eswterika shmeia
    Point_2 t; // to kontinotero interior point
    i = 0;
    t = pointdistance(result1, chain, dis); // h sunarthsh epistrefei gia kathe edge to shmeio me thn mikroterh apostash
    int k;
    int flag;
    int flag1 = 0;
    int pos;
    int c=0;
    while(c < chain.size())
    {
      temp.push_back(Segment_2(t, chain[c][0]));           // auth einai h edge me to interior point kai thn mia korufh ths akmhs ths polugwnikhs
      temp.push_back(Segment_2(t, chain[c][1]));           // auth einai h edge me to interior point kai thn allh korufh ths akmhs ths polugwnikhs grammhs
      flag = findintersection(temp[0], temp[1], chain,chain[c]); // kalw gia na dw an h akmh auth einai orath
      if (flag == 0)                                       // den exw interactions ara exw pithano edge
      {
        visible.push_back(chain[c]);
      }
      temp.clear();
      c++;
    }
    while(visible.size()!=0){
      random=rand() % visible.size();
      int e=0;
      while(e<chain.size()){
        if(visible[random]==chain[e]){/// PREPEI NA TSEKARW AFOU EINAI VISIBLE TO EDGE AN EFTIAXNA AUTO TO POLUGON THA HTAN SIMPLE KAI OTI DE THA EFEINA INTERIOR POINT STHN APEXW
          pos=e;
          break;
        }
        e++;
      }
      Segment_2 tempppp=chain[pos];
      Point_2 temppp = Point_2(chain[pos][1]);
      chain.insert(chain.begin() + pos, Segment_2(chain[pos][0], t));
      chain.insert(chain.begin() + pos + 1, Segment_2(t, temppp)); // ta kanw ola auta gia na exw mia swsth seira me ta edges gia na ftiaxw eukola to polugwno
      chain.erase(chain.begin() + pos + 2);
      result1.erase(std::find(result1.begin(), result1.end(), t));
      p.clear();
      keep.clear();
      e = 0;
      p.push_back(chain[e][0]);
      keep.push_back(chain[e][0]);
      p.push_back(chain[e][1]);
      keep.push_back(chain[e][1]);
      e++;
      while (e < chain.size() - 1)
      {
        p.push_back(chain[e][1]);
        keep.push_back(chain[e][1]);
        e++;
      }
      e = 0;
      while (e < result1.size())
      {
        flag1 = check_inside(result1[e], &*keep.begin(), &*keep.end(), K()); // check an me to neo edge pou ekana exw periklisei ola ta points kai den afhsa eswteriko point apexw apo to polugwno
        e++;
      }
      if (flag1==1 || p.is_simple()==0){ ///////SOSSSSS DEN EXW ELEGXEI KATHOLOU AN LEITOURGEI
        //se periptwsh pou den prepei na travhxw authn thn grammh
        chain.erase(chain.begin()+pos);
        chain.erase(chain.begin()+pos);
        chain.insert(chain.begin()+pos,tempppp);
        result1.push_back(t);
        visible.erase(std::find(visible.begin(), visible.end(), tempppp));
      }
      else{
        break;
      }
    }
    visible.clear();
  }
  int k=0;
  while(k<chain.size()){
    std::cout << chain[k][0] << "<----" << chain[k][1] << std::endl; 
    k++; 
  }
  CGAL::draw(p);
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
int findintersection(Segment_2 interioredge1, Segment_2 interioredge2, segments pchain,Segment_2 chainedge)
{
  int c = 0;
  int flag;
  while (c < pchain.size())
  {
    flag = 0;
    auto result = CGAL::intersection(interioredge1, pchain[c]);
    if (result)
    {
      Point_2 *p = boost::get<Point_2>(&*result); // Ah intersect an den exw intersect tha epistrefei to koino point ton edges(apo ekei pou tis enwnw)
      if (pchain[c]==chainedge && *p == interioredge1[1])
      {
        flag=0;
      }
      else{
        flag =1;
      }
    }
    result = CGAL::intersection(interioredge2, pchain[c]);
    if (result)
    {
      Point_2 *p = boost::get<Point_2>(&*result); // Ah intersect an den exw intersect tha epistrefei to koino point ton edges(apo ekei pou tis enwnw)
      if (pchain[c]==chainedge && *p == interioredge2[1])
      {
        flag = 0;
      }
      else{
        flag=1;
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





/*
1.Se kapoia trww segme na kanw debugging,kai na ftiaxw functions 
2.sunexizw sta epomena erwthamata
*/