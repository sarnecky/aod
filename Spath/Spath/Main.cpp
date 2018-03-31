#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include<map>
#include<list>
#include<vector>
#define MAXVALUE 2147483647
using namespace std;

template <class T> void swapElements(T& a, T& b)
{
	T c(a); a = b; b = c;
}

struct Point
{
	int pathTo;
	int Index; //index miasta
//	bool visited;
};
struct Path 
{
	int startCity;
	int targetCity;
	int distance;
	bool visited;
};
struct City {

	int Distance;
	bool Visited;
	vector<Point> Adjacets;
	int NumberOfAdjacet;
	int Index; //index miasta
};
//kolejka priorytetowa opara o pseudokod z książki Wprowadzenie do algorytmów Cormena. Kod pochodzi także z mojego projektu na AISD
//link https://github.com/sarnecky/Algorytmy-i-struktury-danych/blob/master/SpacerPoGorach/SpacerPoGorach/Source.cpp
struct Queue
{
	Point *tab[9999999];
	int _numberOfElements;

	void heapyfiUp(int i)
	{ //przyspieszyc
		int P = i / 2;

		while (i > 1)
		{
			if (tab[P]->pathTo > tab[i]->pathTo)
			{
				swapElements(tab[P], tab[i]);
			}
			i = P;
			P = i / 2;
		}
	}

	void heapyfy(int i)
	{
		int L = 2 * i;
		int P = 2 * i + 1;
		int min;

		if (L <= _numberOfElements && tab[L]->pathTo < tab[i]->pathTo) // jezeli lewy element jest mniejszy od rodzica to trzeba go zamienic
		{
			min = L; //mniejszy stoi na lewej stronie
		}
		else min = i;


		if (P <= _numberOfElements && tab[P]->pathTo < tab[min]->pathTo) // jezeli prawy element jest mniejszy od rodzica to trzeba go zamienic
		{
			min = P; //mniejszy stoi na prawej stronie
		}

		if (min != i)  //zamiana elementow i 
		{
			swapElements(tab[i], tab[min]);
			heapyfy(min);
		}
	}

	void buildHeap()
	{
		for (int i = _numberOfElements / 2; i >= 1; i = i / 2)
		{
			heapyfy(i);
		}
	}

	void insertHeap(int index, int pathTo)
	{
		_numberOfElements++;
		tab[_numberOfElements] = new Point;
		tab[_numberOfElements]->Index = index;
		tab[_numberOfElements]->pathTo = pathTo;
		//tab[_numberOfElements]->visited = false;
		buildHeap();
	}

	Point removeHeap()
	{
		Point root;
		root.pathTo = tab[1]->pathTo;
		root.Index = tab[1]->Index;
		//tab[1]->visited = true;
		swapElements(tab[1], tab[_numberOfElements]);
		tab[_numberOfElements] = tab[0];
		//tab[1] = tab[_numberOfElements];
		_numberOfElements--;
		buildHeap();
		return root;
	}
	void wypisz()
	{
		int p;
		Point liczba;
		for (int i = 1; i <= _numberOfElements;)
		{
			p = tab[i]->pathTo;
			liczba = removeHeap();
			printf("%d ", p);
		}
	}

};

//algorytm dijkstry na podstawie źródła https://www.cse.ust.hk/~dekai/271/notes/L10/L10.pdf (strona 16)
void getShortestPath(Queue *Q, map<int, City> *cities, int startCity,  map<int,int> targets, vector<Path> *paths)
{
	Point u;
	int visitedCities = 0;
	while (Q->_numberOfElements>0)
	{
		u = Q->removeHeap();
		City currentCity = cities->at(u.Index);
		if (currentCity.Distance > 200000)
			break;

		if (targets.find(u.Index)!=targets.end()) //odwiedzamy jakis z docelowych indexow
		{
			int indexInPaths = targets.at(u.Index);
			paths->at(indexInPaths).distance = cities->at(u.Index).Distance;

			if(!paths->at(indexInPaths).visited)
				visitedCities++;

			paths->at(indexInPaths).visited = true;
			if (visitedCities == targets.size())
				return;
		}

		for (int v = 0; v < cities->at(u.Index).NumberOfAdjacet; v++)
		{
			Point adjacetPoint= currentCity.Adjacets[v];
			City adjacentCity = cities->at(adjacetPoint.Index);

			int distanceToV = currentCity.Distance + adjacetPoint.pathTo;//matrixOfDistances[u.Index][adjacetIndex].pathTo;

			if (distanceToV<= 200000 && !adjacentCity.Visited && distanceToV < adjacentCity.Distance)
			{
				cities->at(adjacetPoint.Index).Distance = distanceToV;
				/*if (adjacetPoint.Index == targetCity)
					return distanceToV;*/
				Q->insertHeap(adjacetPoint.Index, cities->at(adjacetPoint.Index).Distance);
			}
		}
		cities->at(u.Index).Visited = true;
	}
	//return cities[targetCity].at(targetCity).Distance;
}
void makeMagic()
{
	Queue *Q = new Queue;
	Q->_numberOfElements = 0;
	map<int, City> *cities = new map<int, City>;
	//ifstream plik, out;
	//plik.open("dane.txt");
	int testsCount = 0;
	int citiesCount = 0;
	int numberOfNeighbours = 0;

	scanf("%d", &testsCount);
	//plik >> testsCount;

	for (int test = 0; test < testsCount; test++)
	{
		scanf("%d", &citiesCount);
		//plik >> citiesCount;

		map<string, int> *mapOfCities = new map<string, int>();
		char cityName[11];
		for (int hostPosition = 0; hostPosition < citiesCount; hostPosition++)
		{
			scanf("%s", &cityName);
			//plik >> cityName;
			mapOfCities->insert(pair<string, int>(cityName, hostPosition));
			scanf("%d", &numberOfNeighbours);
			//plik >> numberOfNeighbours;
			City city;
			for (int neighbour = 0; neighbour < numberOfNeighbours; neighbour++)
			{
				int a, b;
				scanf("%d %d", &a, &b);
				//plik >> a >> b;
				//distances[hostPosition][a-1].pathTo = b;
				Point p;
				p.pathTo = b;
				p.Index = a - 1;
				city.Adjacets.push_back(p);
			}
			
			city.Distance = MAXVALUE;
			city.Index = hostPosition;
			city.Visited = false;
			city.NumberOfAdjacet = numberOfNeighbours;
			cities->insert(pair<int, City>(hostPosition, city));
		}

		int numberOfPaths = 0;
		char cityA[11], cityB[11]; string start, end;
		vector<Path> paths; //drogi do przejscia
		scanf("%d", &numberOfPaths);
		//plik >> numberOfPaths;
		for (int i = 0; i < numberOfPaths; i++)
		{
			scanf("%s %s", &cityA, &cityB);
			//plik >> cityA >> cityB;
			Path path;
			path.startCity = mapOfCities->at(cityA);
			path.targetCity = mapOfCities->at(cityB);
			path.distance = 0;
			path.visited = false;
			paths.push_back(path); 
		}
		
		int visitedPaths = 0;
		for (int city = 0; city < citiesCount; city++) 
		{
			map<int, int>targets; //index w results, index miasta
			for (int p = 0; p < paths.size(); p++) 
			{
				if (!paths[p].visited && paths[p].startCity == city)
				{
					targets.insert(pair<int, int>(paths[p].targetCity, p));
					visitedPaths++;
				}
			}

			Queue *QCopy = new Queue(*Q);
			map<int, City> *citiesCopy = new map<int, City>(*cities);
			citiesCopy->at(city).Distance = 0;
			QCopy->insertHeap(city, 0); // pierwszy wierzcholek ma najnizszy priorytet
			getShortestPath(QCopy, citiesCopy, city, targets, &paths);

			//dodatkowe sprawdzenie drogi powrotnej
			for (int p = 0; p < paths.size(); p++)
			{
				if (!paths[p].visited && paths[p].targetCity == city)
				{
					paths[p].visited = true;
					int pathsIndex = targets.at(paths[p].startCity);
					paths[p].distance = paths[pathsIndex].distance;
					visitedPaths++;
				}
			}
			if (paths.size() == visitedPaths)
				break;
			delete QCopy;
			citiesCopy->clear();
		}

		//wypisanie wyników
		for (int i = 0; i < numberOfPaths; i++)
		{
			cout << paths.at(i).distance << endl;
		}

		mapOfCities->clear();
		cities->clear();
	}
	delete Q;
}

int main()
{
	makeMagic();

	//getchar();
	//getchar();
	return 0;
}
