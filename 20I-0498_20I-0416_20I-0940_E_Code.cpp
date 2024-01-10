#include <iostream>
#include<fstream>
#include<string>
using namespace std;



template <class T>
class vectordup
{
public:
	T* data;
	int elements;

	vectordup()
	{
		data = NULL;
		elements = 0;
	}

	void insert(T obj)
	{
		elements++;
		T* temp = new T[elements];
		for (int i = 0; i < elements - 1; i++)
		{
			temp[i] = data[i];
		}
		temp[elements - 1] = obj;
		data = temp;
	}

};

class Message
{
public:
	int ID;
	int priority;
	string src;
	string dest;
	string payload;
	string trace;

	Message()
	{
		ID = 0;
		priority = 0;
		src = "";
		dest = "";
		payload = "";
		trace = "";
	}

	Message(int i, int p, string s, string d, string pay)
	{
		ID = i;
		priority = p;
		src = s;
		dest = d;
		payload = pay;
		trace = s;
	}

	void addTrace(string app)
	{
		trace += ",";
		trace += app;
	}

};

class InQueue
{
public:
	Message* heap;
	int elements;

	InQueue()
	{
		heap = new Message[1];
		elements = 1;
	}

	void insert(Message obj)
	{
		elements++;

		Message* temp = new Message[elements];

		for (int i = 1; i < elements - 1; i++)
		{
			temp[i] = heap[i];
		}

		temp[elements - 1] = obj;

		heap = temp;

		int current, parent;

		current = elements - 1;
		parent = current / 2;

		Message swap;

		while ((heap[parent].priority < heap[current].priority) && (current != 1))
		{
			swap = heap[parent];
			heap[parent] = heap[current];
			heap[current] = swap;
			current = parent;
			parent = current / 2;
		}
	}

	Message getTop()
	{
		return heap[1];
	}

	void deleteTop()
	{
		heap[1] = heap[elements - 1];
		elements--;

		int current = 1;
		int left, right, swapindex;

		left = current * 2;
		right = left + 1;

		Message swap;
		int check = 0;

		while (heap[current].priority > min(heap[left].priority,heap[right].priority))
		{
			if (min(heap[left].priority, heap[right].priority) == left)
			{
				swapindex = left;
			}
			else
			{
				swapindex = right;
			}

			swap = heap[current];
			heap[current] = heap[swapindex];
			heap[swapindex] = swap;

			current = swapindex;

			left = current * 2;
			right = left + 1;

			if (left > elements - 1)
			{
				check++;
			}

			if (check > 0)
			{
				break;
			}
		}

	}
};

struct QueueNode
{
	Message data;
	QueueNode* next;

	QueueNode(Message D)
	{
		data = D;
		next = NULL;
	}
};

class Queue
{
public:
	QueueNode* front;
	QueueNode* tail;

	Queue()
	{
		front = NULL;
		tail = NULL;
	}

	void enqueue(Message obj)
	{
		QueueNode* newNode = new QueueNode(obj);
		if (front == NULL)
		{
			front = newNode;
			tail = newNode;
			return;
		}

		tail->next = newNode;
		tail = newNode;
	}

	QueueNode* getFront()
	{
		return front;
	}

	void dequeue()
	{
		front = front->next;
	}

	bool isEmpty()
	{
		if (front == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class RTNode
{
public:
	string dest;
	string nxtrtr;
	RTNode* next;

	RTNode()
	{
		next = NULL;
		dest = "";
		nxtrtr = "";
	}
};

class RoutingTable
{
public:
	RTNode* head;

	RoutingTable()
	{
		head = NULL;
	}

	void insert(RTNode* A)
	{
		RTNode* temp = head;
		if (head == NULL)
		{
			head = A;
		}
		else
		{
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = A;
		}

	}

	void display()
	{
		RTNode* temp;
		temp = head;

		while (temp != NULL)
		{
			cout << "Dest: " << temp->dest << "," << "Next Router: " << temp->nxtrtr << endl;
			temp = temp->next;
		}
	}

};

class Router
{
public:
	string device;
	InQueue in;
	RoutingTable RT;

	Router()
	{
		device = "";
	}

	Router(string n)
	{
		device = n;
	}

	void setName(string name)
	{
		device = name;
	}

	void addRTNode(string dest, string rtr)
	{
		RTNode* obj = new RTNode;
		obj->dest = dest;
		obj->nxtrtr = rtr;
		RT.insert(obj);
	}
};

class Machine
{
public:
	string device;
	Queue out;

	Machine()
	{
		device = "";
	}

	Machine(string n)
	{
		device = n;
	}

	void setName(string name)
	{
		device = name;
	}
};

class Node
{
public:
	Router* R;
	Machine* M;
	string name;
	bool isRouter;
	bool isMachine;
	int edge;
	int dist;
	Node* prev;
	Node* next;

	Node()
	{
		isRouter = false;
		isMachine = false;
		R = NULL;
		M = NULL;
		next = NULL;
		prev = NULL;
		dist = 0;
		edge = 0;
	}

	void insert(Router* robj, Machine* mobj, int e)
	{
		if (robj != NULL)
		{
			isRouter = true;
			R = robj;
			name = R->device;
			edge = e;
		}
		else
		{
			isMachine = true;
			M = mobj;
			name = M->device;
			edge = e;
		}
	}

	Router* getRouter()
	{
		return R;
	}

	Machine* getMachine()
	{
		return M;
	}

	void setdist(int num)
	{
		dist = num;
	}
};

class adjList
{
public:
	Node* head;

	adjList()
	{
		head = NULL;
	}

	void headInsert(Node* obj)
	{
		head = obj;
	}

	void insertadj(Node* obj)
	{
		Node* temp = head;

		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = obj;
	}

	void display()
	{
		Node* temp;
		temp = head->next;

		cout << head->name;

		while (temp != NULL)
		{
			cout << "->" << temp->name << "," << temp->edge;
			temp = temp->next;
		}
	}

	bool find(string d)
	{
		Node* temp = head;

		while (temp->next != NULL)
		{
			if (temp->name == d)
			{
				return true;
			}
			temp = temp->next;
		}

		return false;
	}

	void setAllDist(int num)
	{
		Node* temp = head;

		while (temp != NULL)
		{
			temp->setdist(num);
			temp = temp->next;
		}
	}

	void setAllPrevNull()
	{
		Node* temp = head;

		while (temp != NULL)
		{
			temp->prev = NULL;
			temp = temp->next;
		}
	}
};

class graph
{
public:
	vectordup<adjList*> list;

	void CreateVertex(Node* obj)
	{
		adjList* temp = new adjList;
		temp->headInsert(obj);
		list.insert(temp);
	}

	void insertEdge(Node* src,Node* dest)
	{
		int iter = list.elements;

		for (int i = 0; i < iter; i++)
		{
			if (list.data[i]->head == src)
			{
				list.data[i]->insertadj(dest);
			}
		}
	}

	Node* getHead(int N)
	{
		return list.data[N]->head;
	}

	void display()
	{
		int iter = list.elements;
		for (int i = 0; i < iter; i++)
		{
			list.data[i]->display();
			cout << endl;
		}
	}

	void makeAllInfinite()
	{
		int iter = list.elements;
		for (int i = 0; i < iter; i++)
		{
			list.data[i]->setAllDist(1000);
		}
	}

	void makeAllPrevNull()
	{
		int iter = list.elements;
		for (int i = 0; i < iter; i++)
		{
			list.data[i]->setAllPrevNull();
		}
	}

	/*
	void makeRoutingTables()
	{
		int iter = list.elements;

		for (int i = 0; i < iter; i++)
		{
			for (int j = 0; j < iter; j++)
			{
				if (list.data[i]->head->name != list.data[j]->head->name)
				{
					if (list.data[i]->head->name[0] == 'R')
					{
						if (list.data[j]->head->name[0] == 'M')
						{
							string dest = list.data[j]->head->name;
							string path = dijkstra(*this, list.data[i]->head, list.data[j]->head->name);

							string rtr;

							int k = 0;

							while (path[k] != ',' && path[k] != '\0')
							{
								rtr += path[k];
								k++;
							}
							list.data[i]->head->R->addRTNode(dest,rtr);
						}
					}
				}
			}
		}
	}
	*/
	friend string dijkstra(graph&, Node* , string);
};

Node* FindMachine(graph* G, string mach)
{
	int iter = G->list.elements;

	for (int i = 0; i < iter; i++)
	{
		Node* temp = G->getHead(i);

		if (temp->name[0] == 'R')
		{
			if (G->list.data[i]->find(mach))
			{
				cout << "FOUND with " << G->list.data[i]->head->name << endl;
				return G->list.data[i]->head;
			}
		}
	}
}

class DijkstraQueue
{
public:
	Node** heap;
	int elements;

	DijkstraQueue()
	{
		heap = new Node * [1];
		elements = 1;
	}

	void insert(Node* obj)
	{
		elements++;

		Node** temp = new Node*[elements];

		for (int i = 1; i < elements - 1; i++)
		{
			temp[i] = heap[i];
		}

		temp[elements - 1] = obj;

		heap = temp;

		int current, parent;

		current = elements - 1;
		parent = current / 2;

		Node* swap;

		if (current > 1)
		{
			while ((heap[parent]->dist > heap[current]->dist))
			{
				swap = heap[parent];
				heap[parent] = heap[current];
				heap[current] = swap;
				current = parent;
				parent = current / 2;

				if (current == 1)
				{
					break;
				}
			}
		}
	}

	Node* getTop()
	{
		return heap[1];
	}

	void deleteTop()
	{
		heap[1] = heap[elements - 1];
		elements--;

		int current = 1;
		int left, right, swapindex;

		left = current * 2;
		right = left + 1;

		Node* swap;
		int check = 0;

		while (heap[current]->dist > min(heap[left]->dist, heap[right]->dist))
		{
			if (min(heap[left]->dist, heap[right]->dist) == heap[left]->dist)
			{
				swapindex = left;
			}
			else
			{
				swapindex = right;
			}

			swap = heap[current];
			heap[current] = heap[swapindex];
			heap[swapindex] = swap;

			current = swapindex;

			left = current * 2;
			right = left + 1;

			if (left > elements - 1)
			{
				check++;
			}

			if (check > 0)
			{
				break;
			}
		}

	}

	bool isEmpty()
	{
		if (elements == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void ChangeDist(string obj, int n)
	{
		for (int i = 1; i < elements; i++)
		{
			if (heap[i]->name == obj)
			{
				heap[i]->dist = n;
				return;
			}
		}
	}

	void ChangePrev(string obj, Node* n)
	{
		for (int i = 1; i < elements; i++)
		{
			if (heap[i]->name == obj)
			{
				heap[i]->prev = n;
				return;
			}
		}
	}

	void display()
	{
		for (int i = 1; i < elements; i++)
		{
			cout << heap[i]->name << "," << heap[i]->dist << endl;
		}
	}
};


string dijkstra(graph &G, Node* N, string dest)
{
	G.makeAllInfinite();
	G.makeAllPrevNull();

	N->prev = NULL;
	N->dist = 0;

	string path="";

	DijkstraQueue Q;

	int iter = G.list.elements;

	for (int i = 0; i < iter; i++)
	{
		Q.insert(G.list.data[i]->head);
	}

	while (!Q.isEmpty())
	{
		Node* current = Q.getTop();

		string currentsrt = current->name;

		Node* traverseNode = current->next;
		while (traverseNode != NULL)
		{

			if (traverseNode->dist > (traverseNode->edge + current->dist))
			{
				traverseNode->dist = traverseNode->edge + current->dist;
				traverseNode->prev = current;

				Q.ChangePrev(traverseNode->name, current);
				Q.ChangeDist(traverseNode->name, traverseNode->dist);
			}


			traverseNode = traverseNode->next;
		}

		//cout << "////////////" << endl;
		//Q.display();

		

		DijkstraQueue NewQ;
		while (!Q.isEmpty())
		{
			NewQ.insert(Q.getTop());
			Q.deleteTop();
		}

		Q = NewQ;


		
		Q.deleteTop();
		if (current->name == dest)
		{
			string tempstr;
			while (current->prev != NULL)
			{
				tempstr = current->name;
				tempstr += ",";
				tempstr += path;
				path = tempstr;
				current = current->prev;
			}

			int strint = 0;
			
			while (path[strint] != '\0')
			{
				strint++;
			}

			path[strint - 1] = '\0';
			return path;

			
		}

		
	}
}

string NextRouter(graph* G, Node* current, string mach)
{
	int i = G->list.elements;

	string path = dijkstra(*G,current,mach);

	string rtr;

	int k = 0;

	while (path[k] != ',' && path[k] != '\0')
	{
		rtr += path[k];
		k++;
	}

	return rtr;
}


int main()
{
	ifstream fin;
	fin.open("network.csv");

	string network;

	getline(fin, network, '\0');

	graph G;

	string tempstr;
	int index = 0;

	while (network[index] != '\n')
	{
		index++;

		if (network[index] != ',' && network[index] != '\n')
		{
			tempstr += network[index];
		}
		else
		{
			if (tempstr[0] == 'R')
			{
				Router* R = new Router(tempstr);
				Machine* M = NULL;

				Node* newNode = new Node;
				newNode->insert(R, M, 0);

				G.CreateVertex(newNode);
			}
			else
			{
				Machine* M = new Machine(tempstr);
				Router* R = NULL;

				Node* newNode = new Node;
				newNode->insert(R, M, 0);

				G.CreateVertex(newNode);
			}

			string newstr;
			tempstr = newstr;
		}
	}

	string newstring;
	tempstr = newstring;

	int outvertex = 0;
	int invertex = 0;

	index++;

	while (network[index] != '\0')
	{
		while (network[index] != ',' && network[index] != '\0')
		{
			tempstr += network[index];
			index++;
		}

		invertex = -1;

		tempstr = "";

		while (network[index] != '\0')
		{
			if (network[index] != ',' && network[index] != '\n')
			{
				tempstr += network[index];
			}
			else
			{
				int edge;
				if (tempstr != "?" && tempstr != "")
				{
					edge = stoi(tempstr);
					Node* newNode = new Node;
					if (G.list.data[invertex]->head->isRouter == true)
					{
						Router* tempR = G.list.data[invertex]->head->getRouter();
						newNode->insert(tempR,NULL,edge);
					}
					else
					{
						Machine* tempM = G.list.data[invertex]->head->getMachine();
						newNode->insert(NULL,tempM,edge);
					}
					G.list.data[outvertex]->insertadj(newNode);
					
				}
				tempstr = "";
				invertex++;
			}
			
			if (network[index] == '\n')
			{
				break;
			}

			index++;
		}
		outvertex++;
	}

	G.display();

	Node* checkNode = FindMachine(&G,"M14");

	//cout << dijkstra(G, G.list.data[2]->head, "M11") << endl;

	//G.makeRoutingTables();

}