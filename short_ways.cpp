// short_ways.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <ctime>
#include <chrono>

using namespace std;


void floydWarshall(int n, vector<vector<int>>& W, bool out = true) {
	vector<vector<int>> A(n, vector<int>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i != j) {
				A[i][j] = W[i][j];
			}
			else {
				A[i][j] = 0;
			}
		}
	}
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
	if (out) {
		cout << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << A[i][j] << " ";
			}
			cout << endl;
		}
	}
}

void dijkstra(int n, int start, vector<vector<int>>& w, bool out = true) {
	
	const int INF = 1000000000;
	vector<int> dist(n, INF);
	dist[start] = 0;
	vector <bool> used(n);
	int min_dist = 0;
	int min_vertex = start;
	while (min_dist < INF)
	{
		int i = min_vertex;
		used[i] = true;
		for (int j = 0; j < n; ++j)
			if (dist[i] + w[i][j] < dist[j])
				dist[j] = dist[i] + w[i][j];
			min_dist = INF;
		for (int j = 0; j < n; ++j)
			if (!used[j] && dist[j] < min_dist)
			{
				min_dist = dist[j];
				min_vertex = j;
			}
	}
	if (out) {
		cout << endl;
		for (int i = 0; i < n; i++) {
			cout << dist[i] << " ";
		}
		
		
	}
	
}

void bellmanFord(int n, int start, vector<vector<int>>& w, bool out = true) {
	
	const int INF = 1000000000;
	vector <vector<int> > F(n, vector<int>(n, INF));
	F[0][start] = 0;
	for (int k = 1; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			F[k][i] = F[k - 1][i];
			for (int j = 0; j < n; ++j)
				if (F[k - 1][j] + w[j][i] < F[k][i])
					F[k][i] = F[k - 1][j] + w[j][i];
		}
	}
	if (out) {
		cout << endl;
		for (int i = 0; i < n; i++) {
			cout << F[n - 1][i] << " ";
		}
	}
}
void fillVector(const string& file, vector<vector<int>>& w) {
	ifstream in(file);
	if (in.is_open()) {
		for (int i = 0; i < w.size(); i++) {
			for (int j = 0; j < w.size(); j++) {
				in >> w[i][j];
				//cout << w[i][j];
			}
		}
	}

	else {
		cout << file << endl;
		cout << "io ERROR!" << endl;
		return;
	}
	in.close();
}

void makeFloydWarshallTestTime(vector<double> &FloydWarshall_time, int num, bool out) {
	string file = "matrix" + to_string(num) + ".txt";
	vector<vector<int>> w(num, vector<int>(num));
	fillVector(file, w);
	auto start = std::chrono::steady_clock::now();
	floydWarshall(num, w, out);
	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start) / 1000.0;
	if (!out) {
		std::cout << "FloydWarshall time for " << num << " elements: " << elapsed.count() << " miliseconds." << std::endl;
		FloydWarshall_time.push_back(elapsed.count());
	}

}

void makeDijkstraTestTime(vector<double> &Dijkstra_time,int num, bool out) {
	string file = "matrix" + to_string(num) + ".txt";
	vector<vector<int>> w(num, vector<int>(num));
	fillVector(file, w);
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < num; i++) {
		dijkstra(num, i, w, out);
	}
	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start) / 1000.0;
	if (!out) {
		std::cout << "\nDijkstra time for " << num << " elements: " << elapsed.count() << " miliseconds." << std::endl;
		Dijkstra_time.push_back(elapsed.count());
	}
}

void makeBellmanFordTestTime(vector<double> &BellmanFord_time,int num, bool out) {
	string file = "matrix" + to_string(num) + ".txt";
	vector<vector<int>> w(num, vector<int>(num));
	fillVector(file, w);
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < num; i++) {
		bellmanFord(num, i, w, out);
	}
	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start) / 1000.0;
	if (!out) {
		std::cout << "\nBellmanFord time for " << num << " elements: " << elapsed.count() << " miliseconds." << std::endl;
		BellmanFord_time.push_back(elapsed.count());
	}
}


int main()
{
	vector<double> FloydWarshall_time, Dijkstra_time, BellmanFord_time;
	vector<int>size_m;

	makeFloydWarshallTestTime(FloydWarshall_time,5,false);
	makeDijkstraTestTime(Dijkstra_time, 5,false);
	makeBellmanFordTestTime(BellmanFord_time,5, false);
	cout << endl;
	size_m.push_back(5);

	makeFloydWarshallTestTime(FloydWarshall_time, 10, false);
	makeDijkstraTestTime(Dijkstra_time, 10, false);
	makeBellmanFordTestTime(BellmanFord_time, 10, false);
	cout << endl;
	size_m.push_back(10);

	makeFloydWarshallTestTime(FloydWarshall_time, 100, false);
	makeDijkstraTestTime(Dijkstra_time, 100, false);
	makeBellmanFordTestTime(BellmanFord_time, 100, false);
	cout << endl;
	size_m.push_back(100);

	ofstream file("Graph.txt");
	for (int j = 0; j < 3; j++) {
		file << FloydWarshall_time[j] << ' ';
	}
	file << endl;

	for (int j = 0; j < 3; j++) {
		file << Dijkstra_time[j] << ' ';
	}
	file << endl;
	for (int j = 0; j < 3; j++) {
		file << BellmanFord_time[j] << ' ';
	}
	file << endl;
	

	for (int j = 0; j < 3; j++) {
		file << size_m[j] << ' ';
	}
	file << endl;
	file.close();

	
	system("pause");
    return 0;
}

