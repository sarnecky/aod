#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include<map>
#include<list>
#include<vector>
#include <time.h>       /* time */
#define MAXVALUE 2147483647
using namespace std;

template <class T> void swapElements(T& a, T& b)
{
	T c(a); a = b; b = c;
}

struct Point
{
	int Distance;
	int Index; //index miasta
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

//mapowanie indexow https://pastebin.com/kkZn123m
//kolejka priorytetowa opara o pseudokod z książki Wprowadzenie do algorytmów Cormena. Kod pochodzi także z mojego projektu na AISD
//link https://github.com/sarnecky/Algorytmy-i-struktury-danych/blob/master/SpacerPoGorach/SpacerPoGorach/Source.cpp
struct PriorityQueue
{
	vector<Point> tab;
	map<int, int> mapper; //index miasta, index w kolejce
	int _numberOfElements;
	void init(int n, int rootIndexCity, int rootDistance)
	{
		mapper.clear();
		tab.clear();
		_numberOfElements = n;

		Point p;
		tab.push_back(p); //root
		p.Index = rootIndexCity;
		p.Distance = rootDistance;
		tab.push_back(p);
		mapper.insert(pair<int, int>(p.Index, 1)); //startowe miasto zawsze na 1 miejscu w kolejce
		int i = 0;
		for (int i = 0; i < _numberOfElements; i++)
		{
			if (i == rootIndexCity)
				continue;
			Point p;
			p.Index = i;
			p.Distance = MAXVALUE;
			tab.push_back(p);
		}

		int idCity = 0;
		int idQueue = 1;
		for (int i = 0; i < _numberOfElements; i++)
		{
			if (i == rootIndexCity)
				continue;
			else
				idQueue++;

			mapper.insert(pair<int, int>(i, idQueue));
			idCity++;
		}
	}

	void decreaseKey(int indexCity, int newDistance)
	{
		int indexInQueue = mapper.at(indexCity);
		if (tab[indexInQueue].Distance < newDistance)
			return;

		tab[indexInQueue].Distance = newDistance;
		heapyfiUp(indexInQueue);
	}

	void heapyfiUp(int i)
	{
		int P = (i - 1) / 2;

		while (i > 0)
		{
			if (tab[P].Distance > tab[i].Distance)
			{
				swapCity(tab[P], tab[i]);
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

		if (L <= _numberOfElements && tab[L].Distance  < tab[i].Distance) // jezeli lewy element jest mniejszy od rodzica to trzeba go zamienic
		{
			min = L; //mniejszy stoi na lewej stronie
		}
		else min = i;


		if (P <= _numberOfElements && tab[P].Distance  < tab[min].Distance) // jezeli prawy element jest mniejszy od rodzica to trzeba go zamienic
		{
			min = P; //mniejszy stoi na prawej stronie
		}

		if (min != i)  //zamiana elementow i 
		{
			swapCity(tab[i], tab[min]);
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

	void insertHeap(int indexOfCity, int pathTo) //trza dodac index
	{
		_numberOfElements++;
		Point p;
		p.Index = indexOfCity;
		p.Distance = pathTo;
		tab.push_back(p);
		buildHeap();
	}

	void swapCity(Point& a, Point& b)
	{
		int temp = mapper.at(a.Index);
		mapper.at(a.Index) = mapper[b.Index];
		mapper.at(b.Index) = temp; //nowy index sie tworzy :( znalezc sposob
		Point c(a); a = b; b = c;
	}

	Point removeHeap()
	{
		Point root;
		root.Distance = tab[1].Distance;
		root.Index = tab[1].Index;
		swapCity(tab[1], tab[_numberOfElements]);
		tab[_numberOfElements] = tab[0];
		_numberOfElements--;
		buildHeap();
		return root;
	}
};


//algorytm dijkstry na podstawie źródła https://www.cse.ust.hk/~dekai/271/notes/L10/L10.pdf (strona 16)
int getShortestPath(PriorityQueue *Q, map<int, City> *cities, int startCity, int targetCity, map<int, int> targets, vector<Path> *paths)
{
	Point u;
	int visitedCities = 0;
	while (Q->_numberOfElements>0)
	{
		u = Q->removeHeap();
		City currentCity = cities->at(u.Index);
		if (u.Index == targetCity)
			return u.Distance;

		if (currentCity.Distance > 200000)
			continue;

		for (int v = 0; v < cities->at(u.Index).NumberOfAdjacet; v++)
		{
			Point adjacetPoint = currentCity.Adjacets[v];
			City adjacentCity = cities->at(adjacetPoint.Index);

			int distanceToV = currentCity.Distance + adjacetPoint.Distance;//matrixOfDistances[u.Index][adjacetIndex].pathTo;

			if (!adjacentCity.Visited && distanceToV < adjacentCity.Distance)
			{
				cities->at(adjacetPoint.Index).Distance = distanceToV;
				Q->decreaseKey(adjacetPoint.Index, distanceToV);// adjacetPoint.Index, cities->at(adjacetPoint.Index).Distance);
			}
		}
		cities->at(u.Index).Visited = true;
	}
	return cities->at(targetCity).Distance;
}
void makeMagic()
{
	PriorityQueue *Q = new PriorityQueue;
	Q->_numberOfElements = 0;
	map<int, City> *cities = new map<int, City>;
	int testsCount = 0;
	int citiesCount = 0;
	int numberOfNeighbours = 0;

	scanf("%d", &testsCount);
	for (int test = 0; test < testsCount; test++)
	{
		scanf("%d", &citiesCount);
		map<string, int> *mapOfCities = new map<string, int>();
		char cityName[11];
		for (int hostPosition = 0; hostPosition < citiesCount; hostPosition++)
		{
			scanf("%s", &cityName);
			mapOfCities->insert(pair<string, int>(cityName, hostPosition));
			scanf("%d", &numberOfNeighbours);
			City city;
			for (int neighbour = 0; neighbour < numberOfNeighbours; neighbour++)
			{
				int a, b;
				scanf("%d %d", &a, &b);
				Point p;
				p.Distance = b;
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
		int visitedPaths = 0;
		for (int city = 0; city < numberOfPaths; city++)
		{
			map<int, int>targets;
			scanf("%s %s", &cityA, &cityB);
			if (mapOfCities->find(cityA) == mapOfCities->end())
				continue;//odwiedzamy jakis z docelowych indexow
			if (mapOfCities->find(cityB) == mapOfCities->end())
				continue;//odwiedzamy jakis z docelowych indexow

			int startCityIndex = mapOfCities->at(cityA);
			int targetCityIndex = mapOfCities->at(cityB);

			PriorityQueue *QCopy = new PriorityQueue();
			map<int, City> *citiesCopy = new map<int, City>(*cities);
			citiesCopy->at(startCityIndex).Distance = 0;

			QCopy->init(citiesCount, startCityIndex, 0); // pierwszy wierzcholek ma najnizszy priorytet
			cout << getShortestPath(QCopy, citiesCopy, startCityIndex, targetCityIndex, targets, &paths) << endl;

		}
	}
	delete Q;
}

int main()
{
	//PriorityQueue *QCopy = new PriorityQueue();
	//QCopy->init(14, 0, 5); // pierwszy wierzcholek ma najnizszy priorytet
	//QCopy->decreaseKey(1, 10);
	//QCopy->decreaseKey(2, 2);
	//QCopy->decreaseKey(3, 6);
	//QCopy->decreaseKey(4, 2);
	//QCopy->decreaseKey(5, 3);
	//QCopy->decreaseKey(6, 7);
	//QCopy->decreaseKey(7, 7);
	//QCopy->decreaseKey(8, 6);
	//QCopy->decreaseKey(9, 5);
	//QCopy->decreaseKey(10, 11);
	//QCopy->decreaseKey(11, 9);
	//QCopy->decreaseKey(12, 11);
 //   Point wynik = QCopy->removeHeap();
	//wynik = QCopy->removeHeap();
	//wynik = QCopy->removeHeap();
	//wynik = QCopy->removeHeap();
	//wynik = QCopy->removeHeap();
	//wynik = QCopy->removeHeap();
	//wynik = QCopy->removeHeap();
	//wynik = QCopy->removeHeap();
	//wynik = QCopy->removeHeap();
	//wynik = QCopy->removeHeap();
	//wynik = QCopy->removeHeap();
	//wynik = QCopy->removeHeap();
	makeMagic();
	//getchar();
	//getchar();
	return 0;
}
