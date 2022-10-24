#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2; //antikeimeno tupou point
typedef std::istream_iterator< Point_2 > point2_iterator; //iterator se point
typedef std::vector<Point_2> Points; //vector me stoixeia point
typedef std::vector<Point_2>::iterator pveciterator; //iterator se vector


int main(){
  //int numLines=0;
  Points result;//init vector me points gia to convex hull
  Points result1;//init vector me points gia to sunolo ton points
  Points result2;//init vector me points ths polugwnikhs alusidas
  std::ifstream in("input.txt");//anoigw arxeio (thelei kai alles epexergasies)
  point2_iterator begin(in);//deixnw sto prwto point
  point2_iterator end;//deixnei teleutaio
  /*std::string line;
  int number_of_lines=0;
  in.clear();
  in.seekg(0);
  while(std::getline(in,line)){
    std::cout << line << std::endl;
    strtok(line,"/t");                          ////////////////////////////////THELW NA KRATAW TA POINTS POU EXW 
    result1.push_back(Point_2(0,3));
  }                                           ///////////////////EPISHS THELW NA KRATAW TO POLUGON LINE
  in.clear();
  in.seekg(0);*/
  CGAL::convex_hull_2( begin, end, std::back_inserter(result) );//vazei ta points apo to convex hull sto result (vector)
  std::cout << result.size() << " points on the convex hull" << std::endl;
  for (pveciterator iter=result.begin(); iter!=result.end(); ++iter) //trexw me to iterator to vector kai ektypwnw
    std::cout << *iter << std::endl;
  return 0;
}
