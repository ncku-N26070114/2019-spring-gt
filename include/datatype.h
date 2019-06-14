#ifndef _DTATTYPE_H
#define _DTATTYPE_H

#include <iostream>
#include<fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <cstdlib>
#include <map>
#include <time.h> 
#include <math.h> 
#include <iostream>
#include <stack>
#include <limits.h>
#include <unistd.h>
#include "network_manager.h"
#include "path.h"
#include "vertex.h"
#include "edge.h"
#include"gplot.h"


using namespace std;


class EDGE;
class VERTEX {
	public:
	string name;
	vector<EDGE *> Connect_N;
	int odd_index;
};

class EDGE {
	public:
	EDGE(){};
	EDGE(VERTEX *a, VERTEX *b, bool f) {
		v1 = a;
		v2 = b;
		fake = f;
		flag = false;
	};
	VERTEX *v1, *v2;
	bool flag, fake;
};



#endif
