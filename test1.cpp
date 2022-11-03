#include <ordering.h>

int main(){
  Points convex_hull;   //shmeia convex hull
  Points temp;
  Points result;  //gia to apotelesma
  Points result1;
  Points result2;
  Segments chain; //gia thn alusida
  pveciterator p1;
  pveciterator p2;
  Polygon p;


  std::string line;
  std::ifstream in("input.txt");
  std::getline(in,line);
  std::getline(in,line);                 // anoigw arxeio (thelei kai alles epexergasies)
  char ch;
  int length;
  char ccc;

  while(in.peek()!=EOF){
    std::getline(in,line);
    int i=0;
    ccc=line.at(i);
    while(ccc!='\t'){
      i++;
      ccc=line.at(i);
    }
    line.erase(0,i+1);
    std::string temp=line;
    i=0;
    ccc=line.at(i);
    while(ccc!='\t'){
      i++;
      ccc=line.at(i);
    }
    line.erase(line.begin() + i,line.end());
    int n=stoi(line);
    line=temp;
    length=trunc(log10(n)) + 1;
    line.erase(0,length+1);
    int n1=stoi(line);
    result2.push_back(Point_2(n,n1));
  }

  std::copy(result2.begin(), result2.end(), std::back_inserter(result)); // kanw copy sto vector result1 ta points                                                // paw xana sthn arxh tou arxeiou

  if(result.size()>=3){         //sxhmatizw trigvno poy sto temp
    for(int i=0; i<3; i++){      
      Point_2 t = result[i];    
      temp.push_back(t);
    }
  }

  p1=result.begin();    //diagrafw ta 3 points apo to result
  p2=result.begin()+3;
  result.erase(p1, p2);  

  int numberofsegments = temp.size();
  int i;

  for (i = 0; i < numberofsegments; i++)    //arxikopoiw to chain me ta 3 segments
  {
    if(i==numberofsegments-1){
      chain.push_back(segment(temp[numberofsegments-1],temp[0]));
      break;
    }
    chain.push_back(segment(temp[i], temp[i + 1]));
  }
  
  //incremental(result, temp, chain);
  init_2a(result2);
  CGAL::convex_hull_2(result2.begin(), result2.end(), std::back_inserter(convex_hull));
  int d = convex_hull.size();
  std::cout << d << " points on the convex hull" << std::endl;
  for(int i=0; i<convex_hull.size(); i++){
    cout<<convex_hull[i]<<" -> "; 
    p.push_back(convex_hull[i]);
  }

  // for (pveciterator iter=convex_hull.begin(); iter!=convex_hull.end(); iter++){
  //     std::cout << *iter << std::endl;
  //     p.push_back(*iter);}



  CGAL::draw(p);

  return 0;

}

