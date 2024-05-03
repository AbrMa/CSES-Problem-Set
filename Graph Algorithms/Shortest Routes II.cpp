// Shortest Routes II
// https://cses.fi/problemset/task/1672/

#include <bits/stdc++.h>
using namespace std;
const long long INF = 10e17;
int main()
{

	// Read variables
	int n, m, q;
	cin >> n >> m >> q;

	// Build graph from input
	vector<vector<pair<int, long long>>> adjacency_list(n + 1);
	for (int i = 0; i < m; i++)
	{
		int source, destination;
		int weight;
		cin >> source >> destination >> weight;
		adjacency_list[source].push_back(make_pair(destination, weight));
		adjacency_list[destination].push_back(make_pair(source, weight));
	}

	// Floyd-Warshal - Initial distance
	vector<vector<long long>> distance(n + 1, vector<long long>(n + 1, INF));
	for (int source = 1; source <= n; source++)
	{
		distance[source][source] = 0;
		for (auto &[destination, weight] : adjacency_list[source])
		{
			distance[source][destination] = min(distance[source][destination], weight);
		}
	}

	// Floyd-Warshal - Find shortest distance
	for (int intermidiate = 1; intermidiate <= n; intermidiate++)
	{
		for (int source = 1; source <= n; source++)
		{
			for (int destination = 1; destination <= n; destination++)
			{
				long long direct_path_distance = distance[source][destination];
				long long alternative_path_distance = distance[source][intermidiate] + distance[intermidiate][destination];
				distance[source][destination] = min(direct_path_distance, alternative_path_distance);
			}
		}
	}

	// Process queries
	for (int query = 0; query < q; query++)
	{
		int origin, destination;
		cin >> origin >> destination;
		if (distance[origin][destination] == INF)
		{
			distance[origin][destination] = -1;
		}
		cout << distance[origin][destination] << endl;
	}

	return 0;
}
