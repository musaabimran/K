#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int search(char** arr,int size,char* str) {
    for(int i=0;i<size;i++) {
        if(strcmp(arr[i],str) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int pos(char** arr,int size,char* str) {
    for(int i=0;i<size;i++) {
        if(strcmp(arr[i],str) == 0)
        {
            return i;
        }
    }
    return -1;
}

vector<vector<int>> readcsv(int* n) {
    char *arr[1000];
    for(int i=0;i<1000;i++)
    {
        arr[i] = (char*)malloc(50);
    }
    int size = 0;

    char file1[] = "doctorwho.csv";
    FILE* inputFile = fopen(file1,"r");
    if(inputFile == NULL) {
        printf("Unable to Open File rollNo.txt");
    }

    char* buffer1,*buffer2;

    char buffer[1000];
    fgets(buffer, sizeof (buffer), inputFile);
    while (fgets(buffer, sizeof (buffer), inputFile))
    {
        char *data = strtok(buffer, ",");
        if (data !=NULL)
        {
            buffer1 = data;
            data = strtok(NULL, ",");
            buffer2 = data;
            if(search(arr,size,buffer1) == 0) {
                strcpy(arr[size],buffer1); 
                size++;
            }
            if(search(arr,size,buffer2) == 0) {
                strcpy(arr[size],buffer2); 
                size++;
            }
        }
    }
    fclose(inputFile);

    vector<vector<int>> graph;
    *n = size;
    inputFile = fopen(file1,"r");
    if(inputFile == NULL) {
        printf("Unable to Open File rollNo.txt");
    }

    int weight;
    fgets(buffer, sizeof (buffer), inputFile);
    while (fgets(buffer, sizeof (buffer), inputFile))
    {
        char *data = strtok(buffer, ",");
        if (data !=NULL)
        {
            buffer1 = data;
            data = strtok(NULL, ",");
            buffer2 = data;
            data = strtok(NULL, ",");
            weight = atoi(data);
            vector<int> data;
            data.push_back(pos(arr,size,buffer1));
            data.push_back(pos(arr,size,buffer2));
            data.push_back(weight);
            graph.push_back(data);
        }
    }
    fclose(inputFile);
    return graph;
}

vector<vector<int>> readtext(int& nodes,int index) {
    int buffer;
    vector<vector<int>> edge;
    const char* filename[2] = {"email-Enron.txt/Email-Enron.txt", "email-EuAll.txt/Email-EuAll.txt"};

    ifstream inputFile(filename[index]);
    if (!inputFile) {
        cout << "Unable to open file " << filename << endl;
    }

    inputFile >> nodes;
    //cout << "Nodes: " << nodes << endl;
    inputFile >> buffer;

    //int count = 0;
    for (int i = 0; i < buffer && !inputFile.eof(); ++i) {
        int source, destination;
        inputFile >> source >> destination;
        if (source < nodes && destination < nodes) {
            vector<int> data;
            data.push_back(source);
            data.push_back(destination);
            data.push_back(1);
            edge.push_back(data);
            //count++;
        }
    }
    //cout << "Count: " << count << endl;
    //cout << "Data Read\n";
    return edge;
}
// Function to find K shortest path lengths
void findKShortest(vector<vector<int>> edges, int n, int m, int k, int start, int end)
{
	//Initialize graph
	vector<vector<pair<int, int> > > g(n);

	for (int i = 0; i < m; i++) {
		// Storing edges
		g[edges[i][0]].push_back(
			{ edges[i][1], edges[i][2] });
	}
	// Vector to store distances
	vector<vector<int> > dis(n, vector<int>(k, 1e9));
	// Initialization of priority queue
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int>>> pq;
	pq.push({ 0, start });
	dis[start][0] = 0;
	// while pq has elements
	while (!pq.empty()) {
		// Storing the node value
		int u = pq.top().second;
		// Storing the distance value
		int d = (pq.top().first);
		pq.pop();
		if (dis[u][k - 1] < d)
			continue;
		vector<pair<int, int> > v = g[u];
		// Traversing the adjacency list
		for (int i = 0; i < v.size(); i++) {
			int dest = v[i].first;
			int cost = v[i].second;
			// Checking for the cost
			if (d + cost < dis[dest][k - 1]) {
				dis[dest][k - 1] = d + cost;
				// Sorting the distances
				sort(dis[dest].begin(), dis[dest].end());
				// Pushing elements to priority queue
				pq.push({ (d + cost), dest });
			}
		}
	}

    cout << k << " Shortest Path from " << start << " to " << end << endl;
    for (int i = 0; i < k; i++) {
        cout << "Distance of Path " << i+1 << ": " <<  ((dis[end][i] == 1e9) ? "No Path" : to_string(dis[end][i])) << endl;
    }
}

set<pair<int,int>> generateSet(int nodes) {
    int a, b;
    set<pair<int,int>> sets;
    while(sets.size() < 10) {
        a = rand()%nodes;
        b = rand()%nodes;
        sets.insert({a,b});
    }
    return sets;
}

int main()
{
    srand(time(NULL));
	int nodes;
    clock_t start, end;
    vector<vector<int>> graph;

    cout << "Enter File to Read\n\t[1]doctorwho.csv\n\t[2]Email-Euron.txt\n\t[3]Email-EuAll.txt\nEnter Choice: ";
    cin >> nodes;
    if(nodes == 1) {
        graph = readcsv(&nodes);
    }
    else if(nodes == 2) {
        graph = readtext(nodes,0);
    }
    else if(nodes == 3) {
        graph = readtext(nodes,1);
    }
    else {
        cout << "Wrong Input Program Ended" << endl;
        return 1;
    } 

    start = clock(); 
    set<pair<int,int>> sets = generateSet(nodes);
    for (auto const &x : sets) { 
        findKShortest(graph, nodes, graph.size(), 3,x.first,x.second);
    }
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(5) << " sec" << endl; 
    
	return 0;
}
