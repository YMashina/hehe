// edmundskarp.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <queue>

template <size_t N> //чтобы не надо было выделять память
class Network {
public:
	Network() { //Обнуляем все потоки
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
			size_t vertex = sink;
			int min_path_capacity = std::numeric_limits<int>::max();
			while (vertex != source) {// ищу минимальную остаточную пропускную способность на возрастающем пути
				min_path_capacity = std::min(min_path_capacity, residual_capacity(m_parent[vertex], vertex)); 
				vertex = m_parent[vertex];
			}
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

	bool augmenting_path(size_t source, size_t sink) // возрастающий путь (увеличивающий путь или увеличивающая цепь) из истока в сток 
	{
		for (size_t i = 0; i < N; i++) {
			m_visited[i] = false;
		}
		std::queue<size_t> queue_of_vertices;
		queue_of_vertices.push(source);
		while (!queue_of_vertices.empty()) {
			size_t vertex = queue_of_vertices.front();
			
			queue_of_vertices.pop();
			for (size_t i = 0; i < N; i++) {
				if (residual_capacity(vertex, i) > 0 && !m_visited[i]) { // используем ребра по которым еще можно пустить поток
					queue_of_vertices.push(i);
					m_parent[i] = vertex;
					m_visited[vertex] = true;
					if (i == sink)
						return true;
				}
			}
		}
		return false;
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

