#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/squared_distance_2.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2; //antikeimeno tupou point
typedef K::Segment_2 Segment_2;//antikeimeno typou pleuras
typedef std::istream_iterator< Point_2 > point2_iterator; //iterator se points apo to input file
typedef std::vector<Point_2> Points; //vector me stoixeia point
typedef std::vector<Segment_2> segments;//vector me stoixeia pleurwn
typedef std::vector<Point_2>::iterator pveciterator; //iterator se vector me ta point


int main(){
  Points result;//init vector me points gia to convex hull
  Points result1;//init vector me points gia to sunolo ton points
  segments chain;//init polugwnikh alusida pou sh arxh einai isi me to convex hull
  std::ifstream in("input.txt");//anoigw arxeio (thelei kai alles epexergasies)
  point2_iterator begin(in);//deixnw sto prwto point tou arxeiou 
  point2_iterator end;//deixnei teleutaio point tou arxeiou 
  copy(begin , end , std::back_inserter(result1) ); //kanw copy sto vector result1 ta points
  in.clear();
  in.seekg(0); //paw xana sthn arxh tou arxeiou 
  CGAL::convex_hull_2( begin, end, std::back_inserter(result) );//vazei ta points apo to convex hull sto result (vector)
  std::cout << result.size() << " points on the convex hull" << std::endl;
  for (pveciterator iter=result.begin(); iter!=result.end(); ++iter) //trexw me to iterator to vector kai ektypwnw
    std::cout << *iter << std::endl;
  int j;
  for(j=0;j<result.size();j++){
    result1.erase(std::remove(result1.begin(), result1.end(), result[j]), result1.end()); //vgazw ta shmeia ta exwterika 
  }
  std::cout << result1.size() << " interior points" << std::endl; //ektupwnw ta eswterika shmeia 
  for (pveciterator iter=result1.begin(); iter!=result1.end(); ++iter)
    std::cout << *iter << std::endl;
  int numberofsegments=result.size();
  int i;
  for(i=0;i<numberofsegments-1;i++){
    chain.push_back(Segment_2(result[i],result[i+1]));
  }
  chain.push_back(Segment_2(result[i],result[0]));//eftiaxa thn arxikh polugwnikh alusida 
  for(i=0;i<result.size();i++){
    for(j=0;j<result1.size();j++)
      std::cout << "from point in convex hull " << result[i] << " to interior point " << result1[j] << " " << CGAL::squared_distance(result[i],result1[j]) << std::endl;//apostash tou kathe ena exwterikou shmeiou apo to kathe kontino //////soss//// prepei na vrw thn elaxisth apostash
  }
  //twra exw apo kathe exwteriko point apostash apo kathe eswteriko kai tha prepei na upologisw mikroterh apostash apo eswteriko point se edge tou chain
  return 0;
}
