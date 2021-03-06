#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include "pch.h"
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <queue>
#include <functional> //std::greater-компаратор для приоритетной очереди
#include <cmath>      //std::abs

class Graph {
public:
	Graph(size_t n);
	void add_edge(size_t from, size_t to, double weight);
	std::vector <size_t> pathfinder(size_t from, size_t to);
	double cost_edge(size_t, size_t);
	size_t path_size(std::vector<size_t>& path, size_t i);
	void admissibility_and_monotonicity(std::vector<size_t>& path);
private:
	std::vector < std::vector < std::pair < double, size_t > >> graph;
};

Graph::Graph(size_t n) : graph(n)
{
}


double Graph::cost_edge(size_t a, size_t b) {
	for (auto& i : graph[a])
		if (i.second == b) return i.first;
}

void Graph::add_edge(size_t from, size_t to, double weight) {
	graph[from].push_back(std::make_pair(weight, to));
}

double heuristic(size_t a, size_t b) {		//расстояние между символами в алфавите
	return std::abs(double(a) - double(b));
}

std::vector<size_t> Graph::pathfinder(size_t from, size_t to) {
	typedef std::pair<double, size_t> qel; // queue element
	std::priority_queue<qel, std::vector<qel>, std::greater<qel>> frontier;	//элемент очереди, контейнер, компаратор чтоб вершина с наименьшим приоритетом была наверху в очереди
	frontier.push(std::make_pair(0, from));
	std::vector<bool> already_visited(graph.size());
	std::vector<size_t> parent(graph.size());
	std::vector<double> cost_to_start(graph.size()); //А* - оценка приоритета вершины: distance on a square grid return abs(a.x - b.x) + abs(a.y - b.y) (ф-я heuristic)
	parent[from] = from;
	already_visited[from] = true;
	cost_to_start[from] = 0;
	//---начало алгоритма-------
	while (!frontier.empty()) {
		
		auto current = frontier.top();	//вытащенная вершина заменяется ее потомками, а очередь сортируется
		std::cout << "\n____________\nOn top of queue: " << char(current.second + 'a') <<"\n";
		frontier.pop();	
		if (current.second == to) //"ранний выход"
			break;
		std::cout << "\nIts neighbors:\n";
		for (auto& next : graph[current.second]) {
			std::cout << "\nVertex: " << char( next.second+'a')<<"\n";
			double new_cost = cost_to_start[current.second] + next.first; //расстояние до старта для исследуемого потомка, чем оно меньше тем выгоднее нам достать вершину из очереди
			if (!already_visited[next.second] || new_cost < cost_to_start[next.second]) {
				std::cout << "\nHasn't been visited or has lower path-to-start length\n" ;
				double priority = new_cost + heuristic(next.second, to); //приоритет для очереди
				frontier.push(std::make_pair(priority, next.second));
				already_visited[next.second] = true;
				parent[next.second] = current.second;
				cost_to_start[next.second] = new_cost;
			}
		}
	}
	//----конец--------
	std::vector<size_t> path;
	while (from != to) {
		path.push_back(to);
		to = parent[to];
	}
	path.push_back(from);
	std::reverse(path.begin(), path.end());

	return path;
}

void Graph::admissibility_and_monotonicity(std::vector<size_t>& path) {
	bool monotonicity = true;
	for (size_t i = 0; i < path.size(); i++) {
		for (size_t j = i; j < path.size(); j++) {
			if (j == i)continue;
			//size_t size = Graph::path_size(path, i);
			if (heuristic(path[i], path.back()) - heuristic(path[j], path.back()) < cost_edge(path[i], path[j])) {
				monotonicity = false;
				break;
			}
		}
	}
	bool admissibility = true; 

	size_t sum_path = 0;
	for (size_t i = 0; i < path.size() - 1; i++) {
		sum_path += cost_edge(path[i], path[i + 1]);
	}
	size_t j = 0;
	if (!monotonicity) {
		for (size_t i = 0; i < path.size(); i++) {
			if (heuristic(path[i], path.back()) > sum_path) {
				admissibility = false;
				break;
			}
			if (i) {
				sum_path -= cost_edge(path[j], path[i]);
				j++;
			}

		}
	}
	if (admissibility)
		std::cout << "\nAdmissible and ";
	else
		std::cout << "\nNot admissible and ";
	if (monotonicity)
		std::cout << "monotone\n"; // разность эвристических оценок для вершины v_1 и её потомка v_2 не превышает фактического веса ребра между этими вершинами
	else
		std::cout << "not monotone\n";
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

	std::cout << "Path: ";
	for (size_t i = 0; i < path.size(); i++) {
		std::cout << char(path[i] + 'a');
	}

	graph.admissibility_and_monotonicity(path);

	return 0;
}