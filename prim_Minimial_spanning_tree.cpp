//This implements Prim's minimal spanning tree algorithm. runtime: O(V*logV + E*logV) = O(E*logV)
//It uses std::set (balanced red-black tree) as the priority queue
#include <iostream>
#include <set>
#include <vector>
#include <utility>

using namespace std;
int main()
{ 	int nodes, edges;
	cin>>nodes>>edges;
	vector<vector<pair<int, int> > >adj_list(nodes+1);//adj_list[i]={edge_cost, node};
	for(int i=0; i<edges; i++)
	{	int n1, n2, edge_cost;
		cin>>n1>>n2>>edge_cost;
		adj_list[n1].push_back({edge_cost, n2});
		adj_list[n2].push_back({edge_cost, n1});
	}

	vector<int> visited(nodes, 0);				//visited[i] denotes whether ith node has been visited by now.
	set<pair<int, int> > min_weight_for_vertex;	//Heap of edges sorted by their costs.
	vector<int> parent(nodes);					//parent[i] denotes parent of ith node in the MST.
	const int root=0;
	visited.at(root)=1;							//We mark the root node as visited.
	parent.at(root)= root;						//Root is parent of itself. Just a convention.
	min_weight_for_vertex.insert({0, root});	//We push root into the heap, with distance from itself as 0.
	vector<int> min_cost(nodes);				//min_cost[i] = "known least cost edge to node i."

	while(!min_weight_for_vertex.empty())		//While heap is not empty.
	{ 	auto cheapest_node = min_weight_for_vertex.begin();
		int vert = cheapest_node->second;				//find the cheapest edge.
		min_weight_for_vertex.erase(cheapest_node);		//pop it from the heap.
		count++;
		for(pair<int, int> p : adj_list.at(vert))	//for all vertices adjacent to vert.
		{	if(!visited.at(p.second))				//If we haven't processed this vertex so far.
			{	min_weight_for_vertex.insert(p);	//we push it into the heap.
				visited[p.second]=1;				//We mark it as visited. (just used in place of set.find() )
				min_cost.at(p.second)= p.first;		//minimum cost known for this vertex is W(vert, p).
				parent.at(p.second)= vert;			//node vert is the temporarily parent of node p, in proposed MST.
			}
			else if((p.first < min_cost.at(p.second)) and
			min_weight_for_vertex.find({min_cost.at(p.second), p.second}) != min_weight_for_vertex.end())	//If it's in the heap.
			{	parent.at(p.second) = vert;				//now, parent of p node is vert.
				min_weight_for_vertex.erase(min_weight_for_vertex.find({min_cost[p.second], p.second}));
				//remove old pair.
				min_cost[p.second] = p.first;			//minimum known cost of p, is W(vert, p).
				min_weight_for_vertex.insert(p);		//insert new pair.
			}
		}
	}

	long long sum_Of_MST=0;						//Sum of cost of all edges in the MST.
	vector<int> MST[nodes];						//MST as an adjacency list.
	for(int i=0; i<nodes; i++)					//We find MST cost like this, because each node has only 1 parent.
	{	if(i== root)
			continue;
		MST[parent[i]].push_back(i);
		MST[i].push_back(parent[i]);
		sum_Of_MST += min_cost[i];
		//cout<<i<<' '<<parent[i]<<' '<<min_cost[i]<<endl;	//To really print the MST.
	}
	cout<<sum_Of_MST;
return 0;
}
