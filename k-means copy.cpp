#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <algorithm> 
#include <math.h>

#define OBJECT_NUM 9
#define KVALUE 3

struct OBJECT {
    double arr[2];
};
int test = 0;
void printCluster(std::vector<std::vector<OBJECT> > cluster) {
	std::cout <<"******************" << std::endl;
	int out_i = 0;
	int index = 0;
	for(out_i = 0; out_i < KVALUE; ++out_i) {
		std::cout << "Cluster " << out_i << ":"<< std::endl;
		for(index = 0; index < cluster[out_i].size(); index++)
			std::cout << "(" << (cluster[out_i]).at(index).arr[0] << " " << 
				(cluster[out_i]).at(index).arr[1] << ") ";
		std::cout << std::endl;
	}
}

double distance(OBJECT ob, OBJECT tar) {
    double diffY = ob.arr[0] - tar.arr[0];
    double diffX = ob.arr[1] - tar.arr[1];
	return sqrt((diffY * diffY) + (diffX * diffX));
}

OBJECT centroids(std::vector<OBJECT> cluster) {
	int i = 0;
	double x_sum = 0;
	double y_sum = 0;
	OBJECT new_cen;
	for(i = 0; i<cluster.size(); i++) {
		x_sum = x_sum + cluster.at(i).arr[0];
		y_sum = y_sum + cluster.at(i).arr[1];
	}
	new_cen.arr[0] = (double)x_sum/(cluster.size());
	new_cen.arr[1] = (double)y_sum/(cluster.size());
	return new_cen;
} 

bool hasChanged(std::vector<std::vector<OBJECT> > cluster, 
	std::vector<std::vector<OBJECT> > tem_cluster) {
	bool mark = false;
	int i = 0;
	int a = 0;
	if(cluster.size() == tem_cluster.size()) {
		for(i = 0; i < KVALUE; ++i) {
			if(cluster[i].size() == tem_cluster[i].size()) {
				for(a = 0; a < cluster[i].size(); ++a) {
					if(cluster[i].at(a).arr[0] == tem_cluster[i].at(a).arr[0] &&
						cluster[i].at(a).arr[1] == tem_cluster[i].at(a).arr[1])
						continue;
					else 
						return true;
				}
			}
			else 
				return true;
		}
	}
	else 
		return true;
	return mark;
}

int main() {
	/* initial progress */
	double x[OBJECT_NUM] = {3,4,9,3,8,6,2,5,6};
	double y[OBJECT_NUM] = {10,6,5,8,5,6,2,7,8};
	std::vector<std::vector<OBJECT> > cluster(KVALUE);
	std::vector<std::vector<OBJECT> > tem_cluster(KVALUE);
	std::vector<OBJECT> Data(OBJECT_NUM);
	std::vector<OBJECT> seeds(KVALUE);
	int index = 0;
	for(index = 0; index < OBJECT_NUM ; index++) {
		Data.at(index).arr[0] = x[index];
		Data.at(index).arr[1] = y[index];
	}
	for(index = 0; index < OBJECT_NUM ; index++) {
		std::cout << Data.at(index).arr[0] << " " << Data.at(index).arr[1] << std::endl;
	}

	/* initiate seeds */
	for(index = 0; index < KVALUE ; index++) {
		seeds.at(index).arr[0] = x[index];
		seeds.at(index).arr[1] = y[index];
	}
	seeds.at(0).arr[0] = x[0];
	seeds.at(0).arr[1] = y[0];
	seeds.at(1).arr[0] = x[3];
	seeds.at(1).arr[1] = y[3];
	seeds.at(2).arr[0] = x[6];
	seeds.at(2).arr[1] = y[6];
	/*for(index = 0; index < KVALUE ; index++) {
		seeds.at(index).arr[0] = x[index];
		seeds.at(index).arr[1] = y[index];
	}*/
	/* k-value algorithm Step 1 */
	int out_i = 0;
	bool first = true;
	double c_distance = 0;
	int mark = 0;

	for(out_i = 0; out_i < OBJECT_NUM; out_i++) {
		for(index = 0; index < KVALUE; index++) {
			if (first) {
				c_distance = distance(Data.at(out_i), seeds.at(index));
				first = false;
				mark = 0;
				continue;
			}
			else {
				if ( c_distance > distance(Data.at(out_i), seeds.at(index))) {
					mark = index;
					c_distance = distance(Data.at(out_i), seeds.at(index));
				}
			}
		}
		/* insert current object into correspond tem_cluster */
		tem_cluster.at(mark).push_back(Data.at(out_i)); 
		/* reset marks */
		first = true;
		c_distance = 0;
		mark = 0;
	}
	printCluster(tem_cluster);
	/* repeat steps */
	while(hasChanged(cluster, tem_cluster)) {
		
		cluster = tem_cluster;
		tem_cluster.clear(); 

		/* rebuild tem_cluster */
		for(index = 0; index < KVALUE; index++) {
			std::vector<OBJECT> refresh;
			tem_cluster.push_back(refresh);
		}
		/* rebuild seeds */
		for(index = 0; index < KVALUE; index++) {
			seeds[index].arr[0] = centroids(cluster[index]).arr[0];
			seeds[index].arr[1] = centroids(cluster[index]).arr[1];
			//std::cout << "centroids: " << seeds[index].arr[0] << " "<< seeds[index].arr[1] << std::endl; 
		}
		/* re-initial marks */
		first = true;
		c_distance = 0;
		mark = 0;

		for(out_i = 0; out_i < OBJECT_NUM; out_i++) {
			for(index = 0; index < KVALUE; index++) {
				if (first) {
					c_distance = distance(Data.at(out_i), seeds.at(index));
					first = false;
					mark = 0;
					continue;
				}
				else {
					if ( c_distance > distance(Data.at(out_i), seeds.at(index))) {
						mark = index;
						c_distance = distance(Data.at(out_i), seeds.at(index));
					}
				}
			}
			/* insert current object into correspond tem_cluster */
			tem_cluster.at(mark).push_back(Data.at(out_i)); 
			/* reset marks */
			first = true;
			c_distance = 0;
			mark = 0;
		}
		printCluster(tem_cluster);
	}
	/* print the final cluster */

	return 0;
} 