
#include "datatype.h"

Vertex *nm2_head;
vector<EDGE *> elist;
vector<vector<Edge *>> avail_paths;
vector<vector<Edge *>>  shortpath;
vector<vector<int>> val_of_shortpath;
vector<VERTEX *> vlist, ovlist, euler_cycle;
vector<string> ShortPath(string m, string n, Vertex *current);

void AddEdge();
int **length_matrix;
VERTEX **optimal_list;
NetworkManager *nm, *nm2;
int min_weight = INT_MAX;
void tracePath(string);
bool FindOddVertex();
void FindShortPath();
void inputdata(string );
void CalculateShortestPath();
int matching(int, int);
vector<VERTEX *> Hierholzer();
vector<string> GetShortPath(string, string, Vertex *);

int main(int argc, char *argv[])
{
	nm = new NetworkManager();
	nm->interpret(argv[1]);
	Path *path = new Path();
	path->append(nm->elist);
	inputdata(argv[1]);
	FindShortPath() ;
	if (!FindOddVertex()) {
		optimal_list = new VERTEX*[ovlist.size()];
		CalculateShortestPath();
		int a = matching(0, 0);
		AddEdge();
	}
	euler_cycle = Hierholzer();
	tracePath(argv[2]);
	
	//plot dotfile
	//Gplot *gp = new Gplot();
	//gp->gp_add(nm->elist);
	//gp->gp_dump(true);
	//gp->gp_export("plot");
	return 0;
}

void inputdata(string filein)
{
	ifstream in_file_1(filein, ios::in);
	ifstream in_file_2(filein, ios::in);
	map<string, VERTEX *> table;
	string a, c1, c2;
	int n = 0;
	while (!in_file_1.eof()) {
		in_file_1 >> c1;
		if (table[c1] == NULL) {
			VERTEX *tmp = new VERTEX;
			table[c1] = tmp;
			tmp->name = c1;
			vlist.push_back(tmp);
			in_file_1 >> c2;
			if (table[c2] == NULL) {
				VERTEX *temp2 = new VERTEX;
				table[c2] = temp2;
				temp2->name = c2;
				vlist.push_back(temp2);
				in_file_1 >> a >> a;
			}
			else
				in_file_1 >> a >> a;
		}
		else {
			in_file_1 >> c1;
			if (table[c1] == NULL) {
				VERTEX *temp3 = new VERTEX;
				table[c1] = temp3;
				temp3->name = c1;
				vlist.push_back(temp3);
				in_file_1 >> a >> a;
			}
			else
				in_file_1 >> a >> a;
		}
	}
	string b;
	string v1, v2;
	int n_edge = 1;
	while (in_file_2 >> v1 >> v2) {
		in_file_2 >> b >> b;
		EDGE *reg = new EDGE;
		for (unsigned int i = 0; i < vlist.size(); ++i) {
			if (vlist[i]->name == v1) {
				reg->v1 = vlist[i];
				vlist[i]->Connect_N.push_back(reg);
			}
			else if (vlist[i]->name == v2) {
				reg->v2 = vlist[i];
				vlist[i]->Connect_N.push_back(reg);
			}
		}
		elist.push_back(reg);
	}
}

bool FindOddVertex()
{
	int odd_index = 0;
	for (unsigned int i = 0; i < vlist.size(); ++i) {
		if (vlist[i]->Connect_N.size() % 2 != 0) {
			vlist[i]->odd_index = odd_index;
			odd_index++;
			ovlist.push_back(vlist[i]);
		}
	}
	if (odd_index == 0)
		return true;

	return false;
}

void CalculateShortestPath()
{
	length_matrix = new int*[ovlist.size()];
	for (unsigned int i = 0; i < ovlist.size(); ++i) {
		length_matrix[i] = new int[ovlist.size()];
		for (unsigned int j = 0; j < ovlist.size(); ++j)
			length_matrix[i][j] = 0;
	}
	for (unsigned int i = 0; i < ovlist.size() - 1; ++i) {
		for (unsigned int j = i + 1; j < ovlist.size(); ++j) {
			vector<string> vertex_path = GetShortPath(ovlist[i]->name, ovlist[j]->name, nm2_head);
			int shortest_path_length = vertex_path.size() - 1;
			length_matrix[i][j] = shortest_path_length;
			length_matrix[j][i] = shortest_path_length;
		}
	}
}
int matching(int w, int start)
{
	int min_w = INT_MAX;

	if (start == ovlist.size() - 2) {
		int weight = length_matrix[ovlist[start]->odd_index][ovlist[start + 1]->odd_index];
		if (w + weight < min_weight) {
			min_weight = w + weight;
			for (unsigned int i = 0; i < ovlist.size(); ++i)
				optimal_list[i] = ovlist[i];
		}
		return weight;
	}

	for (unsigned int i = start + 1; i < ovlist.size(); ++i) {
		int weight = length_matrix[ovlist[start]->odd_index][ovlist[i]->odd_index];
		VERTEX *tmp = ovlist[start + 1];
		ovlist[start + 1] = ovlist[i];
		ovlist[i] = tmp;
		weight += matching(w + weight, start + 2);
		tmp = ovlist[start + 1];
		ovlist[start + 1] = ovlist[i];
		ovlist[i] = tmp;
		if (weight < min_w)
			min_w = weight;
	}
	return min_w;
}

void FindShortPath() 
{
	
	nm2 = new NetworkManager();
	int num_v = 0;
	Vertex *ver0 = nm->get_all_nodes();
	Vertex *ver_head = ver0;

	while (ver0 != NULL) {
		nm2->add_switch(ver0->name);
		num_v++;
		ver0 = ver0->next;
	}


	Vertex *ver1 = ver_head;
	Vertex *ver2 = ver1;
	Edge *edge1 = nm->elist;
	while (edge1 != NULL) {

		if (nm2->connected(edge1->head->name, edge1->tail->name) == 1) {  
			nm2->connect_r(edge1->head->name, edge1->tail->name);
		}
		edge1 = edge1->next;
	}
	Path *path;
	path = new Path();
	path->append(nm2->elist);
	Vertex *v = nm2->get_all_nodes();
	Vertex *v2 = v;
	nm2_head = v;
	Vertex *v_tail;

	while (v2 != NULL) {
		if (v2->next == NULL)
			v_tail = v2;
		v2 = v2->next;
	}
	v2 = v;

	while (v != NULL) {
		while (v2 != NULL) {
			if (v2 == v)
				v2 = v2->next;
			if (v2 != NULL) {
				avail_paths = path->find_paths(v->name, v2->name);
				v2 = v2->next;
				int shorter = 0;

				for (int i = 0; i < avail_paths.size(); i++) {
					if (avail_paths[i].size() < avail_paths[shorter].size())
						shorter = i;
				}
				shortpath.push_back(avail_paths[shorter]);
			}

		}
		v = v->next;
		v2 = nm2_head;
	}

	vector<int> val_of_line;
	int count = 0;
	for (int i = 0; i<shortpath.size(); i++) {
		count++;
		val_of_line.push_back(shortpath[i].size());
		if (count == num_v - 1) {
			int pos = (i + 1) / count - 1;
			val_of_line.insert(val_of_line.begin() + pos, 0);

			val_of_shortpath.push_back(val_of_line);
			val_of_line.clear();
			count = 0;
		}
	}
}

vector<string> GetShortPath(string m, string n, Vertex *current) 
{
	vector<string> vertex_path;
	int order_m = 0;
	int order_n = 0;
	int count = 0;
	int num = 0;


	while (current != NULL) {
		num++;
		if (n == current->name) {
			order_n = count;
		}

		if (m == current->name) {
			order_m = count;
		}
		current = current->next;
		count++;
	}
	int order_in_path = 0;

	if (order_m > order_n)
		order_in_path = order_m*(num - 1) + order_n;

	if (order_m < order_n)
		order_in_path = order_m*(num - 1) + order_n - 1;

	vertex_path.push_back(m);
	for (int i = 0; i < shortpath[order_in_path].size(); i++) {
		vertex_path.push_back(shortpath[order_in_path][i]->tail->name);
	}

	return vertex_path;
}
void AddEdge()
{
	for (unsigned int i = 0; i < elist.size(); ++i)
		elist[i]->fake = false;

	EDGE *extra_edge;
	for(unsigned int i = 0; i < ovlist.size(); i += 2) {
		extra_edge = new EDGE(ovlist[i], ovlist[i + 1], true);
		ovlist[i]->Connect_N.push_back(extra_edge);
		ovlist[i + 1]->Connect_N.push_back(extra_edge);
		elist.push_back(extra_edge);
	}
}

vector<VERTEX *> Hierholzer()
{
	VERTEX *top;
	stack<VERTEX *> tmp_path;
	vector<VERTEX *> final_path;

	for (unsigned int i = 0; i < elist.size(); ++i)
		elist[i]->flag = false;

	if (!vlist.empty())
		tmp_path.push(vlist.front());

	while (!tmp_path.empty()) {
		top = tmp_path.top();
		unsigned int i;
		for (i = 0; i < top->Connect_N.size(); ++i) {
			if (!top->Connect_N[i]->flag) {
				top->Connect_N[i]->flag = true;
				if (top->Connect_N[i]->v1->name != top->name)
					tmp_path.push(top->Connect_N[i]->v1);
				else
					tmp_path.push(top->Connect_N[i]->v2);
				break;
			}
		}
		if (i == top->Connect_N.size()) {
			tmp_path.pop();
			final_path.push_back(top);
		}
	}

	return final_path;
}

void tracePath(string fout)
{
	ofstream outfile(fout.c_str());
	vector<string> vertex_path;
	for (unsigned int i = 0; i < euler_cycle.size() - 1; ++i) {
		for (unsigned int j = 0; j < euler_cycle[i]->Connect_N.size(); ++j) {
			if (euler_cycle[i]->Connect_N[j]->v1->name == euler_cycle[i + 1]->name ||
				euler_cycle[i]->Connect_N[j]->v2->name == euler_cycle[i + 1]->name) {
				if (!euler_cycle[i]->Connect_N[j]->fake)
					outfile << euler_cycle[i]->name << "->";
				else {
					vertex_path = GetShortPath(euler_cycle[i]->name, euler_cycle[i + 1]->name, nm2_head);
					for (unsigned int k = 0; k < vertex_path.size()-1; ++k)
						outfile << vertex_path[k] << "->";
				}
				break;
			}
		}
	}
	
	outfile << euler_cycle.back()->name << endl;
}
