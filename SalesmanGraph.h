#pragma once
#include <fstream>
#include "Genetic.h"
#include <algorithm>
struct Solution
{
	vector<int> path;
	int pathCost = 0;
};

class SalesmanGraph
{
public:
	int **vertexArray;
	int **costArray;
	int size;
	vector<int> path;
	int primeChange[2];
	bool roulette_sel;

public:
	SalesmanGraph(int size);
	SalesmanGraph();
	~SalesmanGraph();
	bool operator==(const SalesmanGraph &object);
	SalesmanGraph& operator=(const SalesmanGraph &object);
	SalesmanGraph(const SalesmanGraph&);
	int getCost(int v, int c);
	void setCost(int v, int c, int val);
	void loadFromFile(SalesmanGraph &graph, string file_name, bool &good);
	void loadFromFile_EUC2D(SalesmanGraph &graph, string file_name, bool &good);
	int getSize();
	int getDistance(vector<int> path);

	static void simulated_annealing(SalesmanGraph &graph, vector<int> &path, int size);
	static void losuj_sciezke(vector<int> &path, int size);


	static void swap(vector<int> &path, int x, int y);
	void showOrder();
	vector<int>& getPath();

	// GENETIC ALGORITHM
	void geneticAlgorithm(Solution &solution, int it, int mutation_kind, int selection_kind, SalesmanGraph &graph);
	void createPopulation(Genetic &genetic);
	void pickParents(Genetic &genetic);
	void cross(Genetic &genetic);
	void mutate(Genetic &genetic, vector<int>& child, int size);
	void chooseNewPopulation(Genetic &genetic, SalesmanGraph &graph);

	// helpers
	void showPopulation(Genetic genetic);
	void showChildrens(Genetic genetic);
	int getMaxValue();
	unsigned int costFunc(vector<int> path, int max);
	void tryMutate(Genetic &genetic, vector<int>& path, int size);
	void tryCross(Genetic &genetic);
	void swapGeneticOne(vector<int>& path, int i, int j);
	void swapGeneticTwo(vector<int>&path, int middle);
	int getBestWay(Genetic &genetic);
	void chooseSelection(int selection_kind);
};

