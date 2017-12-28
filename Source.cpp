#include<iostream>
#include<list>
#include<queue>
#include<fstream>
#include<sstream>
using namespace std;

class Node                          // defining properties of node
{
public:
	string data;
	vector< Node* > adjList;
	string color;
	int discover;
	int finish;
	int d;
	Node* parent;
	Node(string d = 0)
	{
		data = d;
	}
};

class Graphs
{
private:
	int time;
public:
	queue<string> tree;
	queue<string> back;
	queue<string> forward;
	queue<string> cross;
	list<string> order;

	void bfs(vector <Node*> G,Node* n)
	{
		Node* u = new Node(" ");
		for (int k = 1; k < G.size(); k++)
		{
			G.at(k)->color="white";
			G.at(k)->d = numeric_limits<int>::max();
			G.at(k)->parent = NULL;
		}
		G.at(0)->color="gray";
		G.at(0)->d = 0;
		G.at(0)->parent = NULL;
		queue< Node* > Q;
		Q.push(G.at(0));
		int index = 0;
		while (!Q.empty())
		{
			u = Q.front();
			Q.pop();
			for (int v = 0; v < u->adjList.size();v++)
			{
				if (u->adjList.at(v)->color=="white")
				{ 
					u->adjList.at(v)->color ="gray";
					u->adjList.at(v)->d = u->d + 1;
					u->adjList.at(v)->parent = u;
					Q.push(u->adjList.at(v));
				}
			}
			u->color ="black";
		}
	}

	void printPath(vector<Node*> G,Node* n)         //printing path from root to other nodes
	{
		if (n == G.at(0))
			cout << n->data << " ";
		else if (n->parent == NULL)
		{
			cout << "no path from " << G.at(0)->data << " to " << n->data;
		}
		else
		{
			printPath(G, n->parent);
			cout << n->data<<" ";
		}

	}	

	void dfs(vector <Node*> G)
	{
		for (int k = 0; k < G.size(); k++)
		{
			G.at(k)->color = "white";
			G.at(k)->parent = NULL;
		}
		time = 0;

		for (int k = 0; k < G.size(); k++)
		{
			if(G.at(k)->color == "white")
			DFS_VISIT(G, G.at(k));
		}
		
	}

	void DFS_VISIT(vector <Node*> G, Node* u)
	{
		time = time + 1;
		u->discover = time;
		u->color = "gray";
		
		for (int v = 0; v < u->adjList.size();v++)
		{
			if (u->adjList.at(v)->color == "white")
			{
				tree.push(u->data);
				tree.push(u->adjList.at(v)->data);
				u->adjList.at(v)->parent = u;
				DFS_VISIT(G, u->adjList.at(v));
			}
			else if (u->adjList.at(v)->color == "gray")
			{
				back.push(u->data);
				back.push(u->adjList.at(v)->data);
			}
			else if (u->adjList.at(v)->color == "black")
			{
				if (u->discover < u->adjList.at(v)->discover)
				{
					forward.push(u->data);
					forward.push(u->adjList.at(v)->data);
				}
				else if (u->discover > u->adjList.at(v)->discover)
				{
					cross.push(u->data);
					cross.push(u->adjList.at(v)->data);
				}
			}
		}
		u->color = "black";
		time = time + 1;
		u->finish = time;
		order.push_front(u->data);
	}
};
int main()
{
	Graphs g;
	int x;
	ifstream inFile;
	string str;
	vector <Node*> nodes;
	Node* nn;
	int count = 0;
	for (x = 0; x < 10; x++)                         // creating 10 nodes
	{
		nn = new Node(to_string(x+1));
		nodes.push_back(nn);
	}
	inFile.open("D:\\CSCI 174\\input.txt");                   // opening input file
	while (getline(inFile, str))                             // readiing file
	{
		vector <string> edge;
		istringstream buf(str);
		for (string word1; buf >> word1; )
		edge.push_back(word1);
		Node* n1 = new Node(edge.at(1));
		Node* n0 = new Node(edge.at(0));

		for (int w = 0; w < nodes.size();w++)                 
		{
			if (nodes.at(w)->data == n0->data)
			{
				for (x = 0; x < nodes.size(); x++) {
					if (nodes.at(x)->data == n1->data)
					{
						nodes.at(w)->adjList.push_back(nodes.at(x));     // creating adjacency list by reading input file
					}
				}
			}
		}
	}

	cout << "********BFS AlGORITHM*********" << endl << endl;
	cout << "Vertex: Distance[Path]" << endl;
	g.bfs(nodes, nodes.at(0));
	for (x = 0; x<10; x++)
	{
		cout << endl;
		cout << x + 1 << "  : ";
		 {
			if (nodes.at(x)->d > 100)
				cout << "infinity";
			else
				cout << nodes.at(x)->d;
			cout << "[";
			g.printPath(nodes, nodes.at(x));
			cout << "]";
		}

	}
	cout << endl << endl;
	cout << "********DFS AlGORITHM*********" << endl << endl;
	g.dfs(nodes);

	for (x = 0; x < nodes.size();x++)
	{
		cout << "Discover / Finish: " << nodes.at(x)->data << " : " << nodes.at(x)->discover << " " << nodes.at(x)->finish << endl;
	}
	cout << "Tree:  [";
	while(g.tree.size()!= 0)               // displaying tree edges
	{
		cout << "(" << g.tree.front();
		g.tree.pop();
		cout << " , " << g.tree.front();
		g.tree.pop();
		if (g.tree.size() == 0)
		{
			cout << ")";
			break;
		}
			
		else
		cout<< "), ";
	}
	cout << "]";
	cout << endl;
	cout << "Back:  [";
	while(g.back.size() != 0)              // displaying back edges
	{
		cout << "(" << g.back.front();
		g.back.pop();
		cout << " , " << g.back.front();
		g.back.pop();
		if (g.back.size() == 0)
		{
			cout << ")";
			break;
		}

		else
			cout << "), ";
	}
	cout << "]";
	cout << endl;
	cout << "Forward:  [";
	while (g.forward.size() != 0)                 //displaying forward edges
	{
		cout << "(" << g.forward.front();
		g.forward.pop();
		cout << " , " << g.forward.front();
		g.forward.pop();
		if (g.forward.size() == 0)
		{
			cout << ")";
			break;
		}

		else
			cout << "), ";
	}
	cout << "]";
	cout << endl;
	cout << "Cross:  [";
	while (g.cross.size() != 0)                 //displaying cross edges
	{
		cout << "(" << g.cross.front();
		g.cross.pop();
		cout << " , " << g.cross.front();
		g.cross.pop();
		if (g.cross.size() == 0)
		{
			cout << ")";
			break;
		}

		else
			cout << "), ";
	}
	cout << "]";
	cout << endl;
	cout << "Topological Order:  [";
	while (g.order.size() != 0)                // displaying topological order
	{
		cout << g.order.front();
		g.order.pop_front();
		if (g.order.size() == 0)
		{
			break;
		}

		else
			cout << " , ";
	}
	cout << "]";
	cout << endl;
	system("pause");

}	