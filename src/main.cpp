#include <vector>
#include <chrono>
#include <time.h>
#include <iostream>
#include "knn.cpp"


int main(){
	KNN<Int2DPoints> base_knn;
    
	for(int i=0; i< 10000; i++)
			base_knn.insert_point(rand() % 10000, rand() % 10000);
    
  auto start = chrono::high_resolution_clock::now(); 

	auto s = base_knn.get_neighbors(100, 200);

  auto stop = chrono::high_resolution_clock::now(); 

  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  cout << "Time: " << endl;
  cout << duration.count() << endl;
	for (const auto & val : s){
		//val->print();
		//cout << endl;
	}

	return 0;
}
