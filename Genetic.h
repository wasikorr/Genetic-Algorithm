#pragma once
#include <vector>
#include <iostream>
using namespace std;
class Genetic
{
public:
	vector<vector<int>> populations;
	int populationSize;
	vector<vector<int>> parents;
	int parentsPopulationSize;
	vector<vector<int>> childrens;
	int childPairs;
	bool swapMutation;


	int iterations;
	double mutationProbability;
	double crossProbablity;
	int swapsInMutation;


	double getMutationProbability();
	int getSwapsInMutation();
	vector<vector<int>> getPopulations();
	int getPopulationSize();
	vector<vector<int>> getParents();
	int getParentsPopulationSize();
	vector<vector<int>> getChildrens();
	int getIterations();
	int getChildPairs();
	void init();
	void chooseMutation(int mutation_kind);

	Genetic();
	~Genetic();
};

#pragma once
