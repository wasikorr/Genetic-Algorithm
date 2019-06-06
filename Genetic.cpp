#include "Genetic.h"

Genetic::Genetic()
{
	this->iterations = 10;
	this->populationSize = 10;
	this->parentsPopulationSize = 10;
	this->childPairs = 10;
	this->mutationProbability = 0.05;
	double crossProbablity = 1.0;
}


Genetic::~Genetic()
{
}

void Genetic::init()
{
	populations.reserve(populationSize);
	parents.reserve(parentsPopulationSize);
	childrens.reserve(childPairs * 2);

}

vector<vector<int>> Genetic::getPopulations()
{
	return populations;
}
vector<vector<int>> Genetic::getParents()
{
	return parents;
}
vector<vector<int>> Genetic::getChildrens()
{
	return childrens;
}
int Genetic::getIterations()
{
	return iterations;
}
int Genetic::getChildPairs() {
	return childPairs;
}

int Genetic::getPopulationSize() {
	return populationSize;
}
int Genetic::getParentsPopulationSize() {
	return parentsPopulationSize;
}
double Genetic::getMutationProbability() {
	return mutationProbability;
}
int Genetic::getSwapsInMutation() {
	return swapsInMutation;
}
void Genetic::chooseMutation(int mutation_kind) {
	if (mutation_kind == 1) swapMutation = true;
	else swapMutation = false;

}