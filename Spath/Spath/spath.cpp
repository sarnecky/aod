//#include <iostream>
//#include <fstream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string>
//#include<map>
//#include<list>
//#include<vector>
//#include <time.h>       /* time */
//#define MAXVALUE 2147483647
//using namespace std;
//
//template <class T> void swapElements(T& a, T& b)
//{
//	T c(a); a = b; b = c;
//}
//
//struct Point
//{
//	int Distance;
//	int Index; //index miasta
//};
//struct Path
//{
//	int startCity;
//	int targetCity;
//	int distance;
//	bool visited;
//};
//struct City {
//
//	int Distance;
//	bool Visited;
//	vector<Point> Adjacets;
//	int NumberOfAdjacet;
//	int Index; //index miasta
//};
////mapowanie indexow https://pastebin.com/kkZn123m
////kolejka priorytetowa opara o pseudokod z książki Wprowadzenie do algorytmów Cormena. Kod pochodzi także z mojego projektu na AISD
////link https://github.com/sarnecky/Algorytmy-i-struktury-danych/blob/master/SpacerPoGorach/SpacerPoGorach/Source.cpp
//struct PriorityQueue
//{
//	vector<Point> tab;
//	map<int, int> mapper; //index miasta, index w kolejce
//	int _numberOfElements;
//
//	void init(int n) 
//	{
//		_numberOfElements = n;
//		for (int i = 0; i <= n; i++)
//		{
//			Point p;
//			int indexCity = i - 1;
//			p.Index = indexCity;
//			if (i == 0)
//			{
//				tab.push_back(p);
//				continue;
//			}
//			else if (i == 1) {
//				p.Distance = 0;
//			}
//			else {
//				p.Distance = MAXVALUE; 
//			}
//			mapper.insert(pair<int, int>(indexCity, i));
//			tab.push_back(p);
//		}
//	}
//
//	void decreaseKey(int indexCity, int newDistance)
//	{
//		int indexInQueue = mapper.at(indexCity);
//		if (tab[indexInQueue].Distance < newDistance)
//			return;
//
//		tab[indexInQueue].Distance = newDistance;
//		heapyfiUp(indexInQueue);
//	}
//
//	void heapyfiUp(int i)
//	{ 
//		int P = (i+1) / 2;
//
//		while (i > 1)
//		{
//			if (tab[P].Distance > tab[i].Distance)
//			{
//				swapCity(tab[P], tab[i]);
//			}
//			i = P;
//			P = i / 2;
//		}
//	}
//
//	void heapyfy(int i)
//	{
//		int L = 2 * i;
//		int P = 2 * i + 1;
//		int min;
//
//		if (L <= _numberOfElements && tab[L].Distance  < tab[i].Distance) // jezeli lewy element jest mniejszy od rodzica to trzeba go zamienic
//		{
//			min = L; //mniejszy stoi na lewej stronie
//		}
//		else min = i;
//
//
//		if (P <= _numberOfElements && tab[P].Distance  < tab[min].Distance) // jezeli prawy element jest mniejszy od rodzica to trzeba go zamienic
//		{
//			min = P; //mniejszy stoi na prawej stronie
//		}
//
//		if (min != i)  //zamiana elementow i 
//		{
//			swapCity(tab[i], tab[min]);
//			heapyfy(min);
//		}
//	}
//
//	void buildHeap()
//	{
//		for (int i = _numberOfElements / 2; i >= 1; i = i / 2)
//		{
//			heapyfy(i);
//		}
//	}
//
//	void insertHeap(int indexOfCity, int pathTo) //trza dodac index
//	{
//		_numberOfElements++;
//		Point p;
//		p.Index = indexOfCity;
//		p.Distance = pathTo;
//		tab.push_back(p);
//		buildHeap();
//	}
//
//	void swapCity(Point& a, Point& b) 
//	{
//		int temp= mapper[a.Index];
//		mapper[a.Index] = mapper[b.Index];
//		mapper[b.Index] = temp;
//		Point c(a); a = b; b = c;
//	}
//
//	Point removeHeap()
//	{
//		Point root;
//		root.Distance = tab[1].Distance;
//		root.Index = tab[1].Index;
//		swapCity(tab[1], tab[_numberOfElements]);
//		tab[_numberOfElements] = tab[0];
//		_numberOfElements--;
//		buildHeap();
//		return root;
//	}
//};
//
//
//int main()
//{
//	PriorityQueue *p = new PriorityQueue();
//	p->init(5);
//	p->removeHeap();
//	p->decreaseKey(1, 2);
//	p->decreaseKey(2, 7);
//	p->removeHeap();
//	p->decreaseKey(2, 5);
//	p->decreaseKey(3, 10);
//	p->decreaseKey(4, 7);
//	p->removeHeap();
//	p->decreaseKey(3, 6);
//	p->removeHeap();
//	p->removeHeap();
//	return 0;
//}
