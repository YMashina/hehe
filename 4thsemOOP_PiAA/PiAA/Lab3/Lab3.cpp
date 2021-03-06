
#include "pch.h"
#include <iostream>
#include <algorithm>
#include <queue>

template <size_t N> 
class Network {
public:
	Network() { //Обнуление всех потоков
		for (size_t i = 0; i < N; i++)
			for (size_t j = 0; j < N; j++) {
				m_capacity[i][j] = 0;
				m_flow[i][j] = 0;

			}

	}
	void add_edge(size_t vertex1, size_t vertex2, int capacity) {
		m_capacity[vertex1][vertex2] = capacity;
	}

	int find_max_flow(size_t source, size_t sink) {
		int max_flow = 0;
		while (augmenting_path(source, sink)) {
			std::cout << " <-- " << char(sink) << " <-- ";
			size_t vertex = sink;
			int min_path_capacity = std::numeric_limits<int>::max();
			while (vertex != source) {// ищу минимальную остаточную пропускную способность на возрастающем пути
				min_path_capacity = std::min(min_path_capacity, residual_capacity(m_parent[vertex], vertex)); 
				vertex = m_parent[vertex];
				std::cout << char(vertex) << " <-- ";
			}
			std::cout <<  "maximum flow is " << min_path_capacity << std::endl;
			vertex = sink;
			while (vertex != source) {
				m_flow[m_parent[vertex]][vertex] += min_path_capacity;
				m_flow[vertex][m_parent[vertex]] -= min_path_capacity;
				vertex = m_parent[vertex];
			}
			max_flow += min_path_capacity; // обновляю максимальный поток
		}
		return max_flow;
	}

	bool augmenting_path(size_t source, size_t sink) // возрастающий путь (увеличивающий путь или увеличивающая цепь) из истока в сток с ненулевой минимальной остатточной пропускной способностью 
	{
		for (size_t i = 0; i < N; i++)
		{
			m_visited[i] = false;
		}
		std::cout << "\nSearching for an augmenting path:\nmaximum residual capacity vertex for each member of the path:\n";
		size_t vertex = source;

		while (vertex != sink)
		{
			m_visited[vertex] = true;
			std::cout << "\nvisited: "<< char(vertex)<<"\n";
			// Вершина, в которую идёт ребро с максимальной остаточной пропускной способностью (по умолчанию 0)
			size_t max_residual_capacity_vertex = 0;

			bool max_residual_capacity_vertex_found = false;
			// перебор всех потенциальный соседей
			for (size_t i = 0; i < N; ++i)
			{
				// Если вершина ещё не посещена, пропускная способность положительна
				if (!m_visited[i] && residual_capacity(vertex, i) > 0)
				{
					std::cout << "neighbor of "<<char(vertex)<< ": " << char(i) << " and ";
					// как минимум один переход есть
					max_residual_capacity_vertex_found = true;
					std::cout << "residual capacity of [" << char(vertex) << "; " << char(i) << "] = "<< residual_capacity(vertex, i);
					//std::cout << "and";
					if (residual_capacity(vertex, i) > residual_capacity(vertex, max_residual_capacity_vertex))
					{
						// нашлось ребро получше
						max_residual_capacity_vertex = i;
						
						std::cout << " is better, new best vertex is "<< char(max_residual_capacity_vertex)<<"\n";
					}
					else std::cout << " isn't better, best vertex not changed\n";
				}
			}

			if (max_residual_capacity_vertex_found)
			{
				std::cout << "maximum residual capacity neighbor vertex of '" << char(vertex) << "' is found: " << char(max_residual_capacity_vertex) << "\n\n";
				m_parent[max_residual_capacity_vertex] = vertex;
				
				vertex = max_residual_capacity_vertex;
			}
			else
			{
				std::cout << "maximum residual capacity neighbor vertex of '"<< char(vertex)<<"' not found\n\n";
				if (vertex == source)
				{
					return (false);
				}
				vertex = m_parent[vertex];
			}
		}

		return (true);
	}
	

	void print_answer()
	{
		for (size_t i = 0; i < N; ++i)
			for (size_t j = 0; j < N; ++j)
				if (m_capacity[i][j] > 0)
					std::cout << char(i) << " " << char(j) << " " << std::max(m_flow[i][j], 0) << std::endl; // вывести 0 вместо отрицательного потока
	}

	~Network() {
	}
private:
	int residual_capacity(size_t vertex1, size_t vertex2) {
		return m_capacity[vertex1][vertex2] - m_flow[vertex1][vertex2];
	}
	int m_capacity[N][N];
	int m_flow[N][N];
	size_t m_parent[N];
	bool m_visited[N];
};


int main()
{
	Network<300> graph;

	size_t N;
	char source, sink;
	std::cin >> N >> source >> sink;
	
	for (size_t i = 0; i < N; i++) {
		char v, u;
		std::cin >> v >> u;
		int capacity;
		std::cin >> capacity;
		graph.add_edge(v, u, capacity);
	}

	std::cout << graph.find_max_flow(source, sink) << std::endl;
	graph.print_answer();

	return 0;

}

