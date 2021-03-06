#include "pch.h" 
#include <iostream>
#include <vector>
#include <algorithm>
class Graph {
public:
	Graph(size_t n);
	void add_edge(size_t from, size_t to, double weight);
	std::vector <size_t> pathfinder(size_t from, size_t to);
private:
	std::vector < std::vector < std::pair < double, size_t > >> graph;
	
};

Graph::Graph(size_t n): graph(n)
{

}

void Graph::add_edge(size_t from, size_t to, double weight) {
	graph[from].push_back(std::make_pair(weight, to));
}

std::vector<size_t> Graph::pathfinder(size_t from, size_t to) {
	for (size_t i = 0; i < graph.size(); i++) {
		std::sort(graph[i].begin(), graph[i].end());
	}

	std::vector<bool> already_visited(graph.size());
	std::vector<size_t> parent(graph.size());
	size_t from_backup = from;
	while (from != to) {
		already_visited[from] = true;
		//std::cout<<(char)(from+'a')<<" already visited"<<std::endl;
		bool go_back_required = true;
		for (size_t i = 0; i < graph[from].size() && go_back_required; i++) {

			size_t vertex = graph[from][i].second;
			if (!already_visited[vertex]) {
				parent[vertex] = from;
				from = vertex;
				go_back_required = false;
				
			}
		}
		if (go_back_required) {
			from = parent[from];
		}
	}
	std::vector<size_t> path;
	
	from = from_backup;
	while (from != to) {
		path.push_back(to);
		to = parent[to];
	}
	path.push_back(from);
	std::reverse(path.begin(), path.end());

	return path;
}

int main()
{
	char from, to;
	std::cin >> from >> to;
	Graph graph(26);
	while (!std::cin.eof()) {
		char from, to;
		double weight;
		std::cin >> from >> to >> weight;
		graph.add_edge(from - 'a', to - 'a', weight);
	}

	std::vector<size_t> path = graph.pathfinder(from - 'a', to - 'a');

	for (size_t i = 0; i < path.size(); i++) {
		std::cout << char(path[i] + 'a');
	}

	return 0;
}