#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/squared_distance_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/intersections.h>
#include <CGAL/draw_polygon_2.h>
#include <CGAL/Polygon_2_algorithms.h>
#include "include/convex_hull_functions.hpp"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstring>
#include <chrono>
using namespace std::chrono;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;     // antikeimeno tupou point
typedef K::Segment_2 Segment_2; // antikeimeno typou pleuras
typedef CGAL::Polygon_2<K> Polygon_2;
typedef std::istream_iterator<Point_2> point2_iterator; // iterator se points apo to input file
typedef std::vector<Point_2> Points;                    // vector me stoixeia point
typedef std::vector<Segment_2> segments;                // vector me stoixeia pleurwn
typedef std::vector<double> dist;
typedef std::vector<int> areas;
typedef std::vector<int> find;
typedef std::vector<Point_2>::iterator pveciterator; // iterator se vector me ta point

int main(int argc, char **argv)
{ 
  auto start = high_resolution_clock::now();
  std::ifstream in(argv[2]);
  std::ofstream outfile;
  outfile.open(argv[4]);
  int flagalgo;
  if (strcmp("incremental",argv[6])==0)
  {
    flagalgo=1;
  }
  else if (strcmp("convex_hull",argv[6])==0)
  {
    flagalgo=2;
  }
  int flagedge;
  if (strcmp("1",argv[8])==0)
  {
    flagedge=1;
  }
  else if (strcmp("2",argv[8])==0)
  {
    flagedge=2;
  }
  else
  {
    flagedge=3;
  }
  srand((unsigned)time(NULL));
  int j;
  int i;
  int e;
  int k;
  int random;
  int counterr;
  int numberofsegments;
  int pointcount;
  int flag;
  int flag1;
  int pos;
  int index;
  double area;
  double re;
  Points result;  // init vector me points gia to convex hull
  Points result1; // init vector me points gia to sunolo ton eswterikwn points
  Points result2; // init me ola ta poiints
  Points keep;
  segments chain;   // init polugwnikh alusida pou sh arxh einai isi me to convex hull
  segments temp;    // gia temp edges
  Polygon_2 p;      // to polugwno mou
  segments visible; // gia tis visible akmes
  dist dis;         // vector me apostaseis
  areas areas;
  find find;
  std::string line;
  std::getline(in, line);
  std::getline(in, line); // anoigw arxeio (thelei kai alles epexergasies)
  result2 = handleinput(in, result2);
  std::copy(result2.begin(), result2.end(), std::back_inserter(result1));          // kanw copy sto vector result1 ta points                                                // paw xana sthn arxh tou arxeiou
  CGAL::convex_hull_2(result2.begin(), result2.end(), std::back_inserter(result)); // vazei ta points apo to convex hull sto result (vector)
  for (j = 0; j < result.size(); j++)
  {
    result1.erase(std::remove(result1.begin(), result1.end(), result[j]), result1.end()); // vgazw ta shmeia ta exwterika
  }
  numberofsegments = result.size();
  for (i = 0; i < numberofsegments - 1; i++)
  {
    chain.push_back(Segment_2(result[i], result[i + 1]));
  }
  chain.push_back(Segment_2(result[i], result[0])); // eftiaxa thn arxikh polugwnikh alusida
  for (i = 0; i < result.size(); i++)
  {
    p.push_back(result[i]);
  } // to polugwno mou einai h polugwnikh alusida mou
  if (flagalgo==2)
  {
    pointcount = 0;
    while (result1.size() != 0)
    {            // oso to polugwno den periexei ola ta shmeia tou input kai den exw perilavei ola ta eswterika shmeia
      Point_2 t; // to kontinotero interior point
      i = 0;
      if (pointcount != 0)
      {
        t = pointdistance1(result1, chain, dis, pointcount);
      }
      else
      {
        t = pointdistance(result1, chain, dis); // h sunarthsh epistrefei gia kathe edge to shmeio me thn mikroterh apostash
      }
      if (flagedge == 1)
      {
        flag1 = 0;
        visible = findvisible(t, temp, chain, visible);
        while (visible.size() != 0)
        {
          random = rand() % visible.size();
          e = 0;
          while (e < chain.size())
          {
            if (visible[random] == chain[e])
            { /// PREPEI NA TSEKARW AFOU EINAI VISIBLE TO EDGE AN EFTIAXNA AUTO TO POLUGON THA HTAN SIMPLE KAI OTI DE THA EFEINA INTERIOR POINT STHN APEXW
              pos = e;
              break;
            }
            e++;
          }
          Segment_2 tempppp = chain[pos];
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
          if (flag1 == 1 || p.is_simple() == 0)
          { ///////SOSSSSS DEN EXW ELEGXEI KATHOLOU AN LEITOURGEI
            // se periptwsh pou den prepei na travhxw authn thn grammh
            chain.erase(chain.begin() + pos);
            chain.erase(chain.begin() + pos);
            chain.insert(chain.begin() + pos, tempppp);
            result1.push_back(t);
            visible.erase(std::find(visible.begin(), visible.end(), tempppp));
            if (visible.size() == 0)
            {
              pointcount++; // an gia auto to shmeio den vrw oratoe edge tote paw sto epomeno kontinotero shmeio
            }
          }
          else
          {
            pointcount = 0;
            break;
          }
        }
        visible.clear();
      }
      else if (flagedge==2 || flagedge==3)
      {
        flag1 = 0;
        counterr = 0;
        visible = findvisible(t, temp, chain, visible);
        while (visible.size() > counterr)
        {
          random = counterr;
          e = 0;
          while (e < chain.size())
          {
            if (visible[random] == chain[e])
            { /// PREPEI NA TSEKARW AFOU EINAI VISIBLE TO EDGE AN EFTIAXNA AUTO TO POLUGON THA HTAN SIMPLE KAI OTI DE THA EFEINA INTERIOR POINT STHN APEXW
              pos = e;
              break;
            }
            e++;
          }
          Segment_2 tempppp = chain[pos];
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
          if (flag1 == 1 || p.is_simple() == 0)
          { ///////SOSSSSS DEN EXW ELEGXEI KATHOLOU AN LEITOURGEI
            // se periptwsh pou den prepei na travhxw authn thn grammh
            chain.erase(chain.begin() + pos);
            chain.erase(chain.begin() + pos);
            chain.insert(chain.begin() + pos, tempppp);
            result1.push_back(t);
            // visible.erase(std::find(visible.begin(), visible.end(), tempppp));
            if (visible.size() == 0)
            {
              pointcount++; // an gia auto to shmeio den vrw oratoe edge tote paw sto epomeno kontinotero shmeio
            }
          }
          else
          {
            pointcount = 0;
            CGAL::area_2(p.begin(), p.end(), re, K());
            areas.push_back(re);
            find.push_back(counterr);
            chain.erase(chain.begin() + pos);
            chain.erase(chain.begin() + pos);
            chain.insert(chain.begin() + pos, tempppp);
            result1.push_back(t);
            // Auto gia ton upoligsimo emvadou
          }
          counterr++;
        }
        if (pointcount == 0)
        {
          if (flagedge == 2)
          {
            index = std::distance(std::begin(areas), std::min_element(std::begin(areas), std::end(areas)));
          }
          else if (flagedge==3)
          {
            index = std::distance(std::begin(areas), std::max_element(std::begin(areas), std::end(areas)));
          }
          random = find[index];
          e = 0;
          while (e < chain.size())
          {
            if (visible[random] == chain[e])
            { /// PREPEI NA TSEKARW AFOU EINAI VISIBLE TO EDGE AN EFTIAXNA AUTO TO POLUGON THA HTAN SIMPLE KAI OTI DE THA EFEINA INTERIOR POINT STHN APEXW
              pos = e;
              break;
            }
            e++;
          }
          Segment_2 tempppp = chain[pos];
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
        }
        find.clear();
        areas.clear();
        visible.clear();
      }
    }
    k = 0;
    outfile << "Polygonization" << std::endl;
    while(k<p.size()){
      outfile << p[k] << std::endl;
      k++;
    }
    k=0;
    while (k < chain.size())
    {
      outfile << chain[k][0] << "<----" << chain[k][1] << std::endl;
      k++;
    }
    outfile << "Algorithm: convex_hull edge selection " << flagedge << std::endl;
    CGAL::area_2(p.begin(), p.end(), area, K());
    outfile << "area: " << area << std::endl;
    outfile << "ratio: 1" << std::endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    outfile << "construction time: " << duration.count() << " ms " << std::endl;
  }
}
