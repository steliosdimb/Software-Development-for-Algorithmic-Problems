#include <ordering.h>

int main(){
  Points convex_hull;   //shmeia convex hull
  Points temp;    //points pou exoyn mpei sto polugwno
  Points result;  //points pou apomenoun 
  Points result1;
  Points result2;   //ola ta points
  Segments chain; //segments ths polugwnikhs alusidas
  Segments convex_seg; //segments toy convex hull
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
  cout<<"sorting"<<endl;
  result = init_2a(result);
  for(int i=0; i<result.size(); i++){
    cout<<result[i]<<endl;
  }

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
  
  CGAL::convex_hull_2(temp.begin(), temp.end(), std::back_inserter(convex_hull));
  int d = convex_hull.size();
  for(int i=0; i<convex_hull.size(); i++){
    p.push_back(convex_hull[i]);
  }

  convex_seg = create_segments(temp);
  Segments chain1;
  //std::cout << result.size() << std::endl;
  cout<<"temp is "<<endl;
  for(int i=0; i<temp.size(); i++){
    cout<<temp[i]<<endl;
  }
  cout<<"result is"<<endl;
  for(int i=0; i<result.size(); i++){
    cout<<result[i]<<endl;
  }
  cout<<"\n\n";




  //chain1= incremental_min(result,  temp, convex_seg, chain);
  chain1= incremental_max(result,  temp, convex_seg, chain);

  //std::cout << result.size() << std::endl;

  p.clear();
  int e=0;
  p.push_back(chain1[e][0]);    // initialize the new polygon
  p.push_back(chain1[e][1]);
  e++;
  while (e < chain1.size() - 1)
  {
    p.push_back(chain1[e][1]);
    e++;
  }
  CGAL::draw(p);
  return 0;

}

