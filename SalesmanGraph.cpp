#include "SalesmanGraph.h"
#include <random>
#include <time.h>



SalesmanGraph::SalesmanGraph(int N)
{
	vertexArray = new int*[N];
	costArray = new int*[N];
	this->size = N;
	for (int i = 0; i < N; i++)
		this->path.push_back(i);
	path.push_back(0);
	for (int i = 0; i < N; i++)
	{
		vertexArray[i] = new int[N];
		costArray[i] = new int[N];
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			costArray[i][j] = INT_MAX;
			vertexArray[i][j] = 1;
		}
	}
}

SalesmanGraph::SalesmanGraph()
{

}

bool SalesmanGraph::operator==(const SalesmanGraph &graph)
{
	std::cout << "uzyto operatora";
	if (this->size == graph.size)
		return true;
	else
		return false;
}

SalesmanGraph::SalesmanGraph(const SalesmanGraph& graph)
{
	this->costArray = graph.costArray;
	this->size = graph.size;
	this->vertexArray = graph.vertexArray;
}

SalesmanGraph& SalesmanGraph::operator=(const SalesmanGraph& graph)
{
	if (this == &graph)
		return *this;
	for (int i = 0; i < this->size; i++)
	{
		delete[] vertexArray[i];
		delete[] costArray[i];
	}
	delete[] vertexArray;
	delete[] costArray;

	this->size = graph.size;
	this->path = graph.path;
	vertexArray = new int*[size];
	costArray = new int*[size];
	for (int i = 0; i < size; i++)
	{
		vertexArray[i] = new int[size];
		costArray[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			vertexArray[i][j] = 1;
			costArray[i][j] = INT_MAX;
		}
	}

	return *this;
}

SalesmanGraph::~SalesmanGraph()
{

	for (int i = 0; i < this->size; i++) {
		delete[] costArray[i];
		delete[] vertexArray[i];
	}
	delete[] vertexArray;
	delete[] costArray;

}

int SalesmanGraph::getCost(int v, int c)
{
	return costArray[v][c];
}

void SalesmanGraph::setCost(int v, int c, int val)
{
	costArray[v][c] = val;
}

void SalesmanGraph::loadFromFile(SalesmanGraph &graph, string file_name, bool &good)
{
	std::fstream plik;
	int matrixSize, cost = 0;
	//plik.open(file_name + ".txt");
	plik.open("/testy/" + file_name + ".txt");
	if (plik.is_open())
	{
		plik >> matrixSize;
		SalesmanGraph graph2(matrixSize);
		graph = graph2;
		for (int i = 0; i < matrixSize; i++)
		{
			for (int j = 0; j < matrixSize; j++)
			{
				plik >> cost;
				graph.setCost(i, j, cost);
			}
		}
		plik.close();
		cout << "Pomyslnie wczytano graf" << endl;
		good = false;
		return;
	}
	else
	{
		cout << "Blad, nie znaleziono pliku" << endl;
	}
}

void SalesmanGraph::loadFromFile_EUC2D(SalesmanGraph &graph, string file_name, bool &good)
{

	std::fstream plik;
	int matrixSize, cost = 0;
	plik.open(file_name + ".txt");

	if (plik.is_open())
	{
		plik >> matrixSize;
		SalesmanGraph graph2(matrixSize);
		graph = graph2;

		float **temp = new float*[matrixSize];
		for (int i = 0; i < matrixSize; i++)
		{
			temp[i] = new float[2];
			plik >> temp[i][0]; // numer miasta(niepotrzebne)
			plik >> temp[i][0];
			plik >> temp[i][1];
		}

		float xd, yd;
		for (int i = 0; i < matrixSize; i++)
		{
			for (int j = 0; j < matrixSize; j++)
			{
				xd = temp[i][0] - temp[j][0];
				yd = temp[i][1] - temp[j][1];
				cost = (int)((sqrt(xd*xd + yd * yd)) + 0.5);
				graph.setCost(i, j, cost);

			}
		}

		plik.close();
		cout << "Pomyslnie wczytano graf" << endl;
		good = false;
		return;
	}
	else
	{
		cout << "File error - OPEN" << endl;
	}
}


int SalesmanGraph::getSize()
{
	return size;
}

int SalesmanGraph::getDistance(vector<int> path)
{
	int pathCost = 0;
	for (int i = 0; i < this->getSize(); i++)
	{
		pathCost += this->getCost(path[i], path[i + 1]);
	}
	return pathCost;
}


void SalesmanGraph::geneticAlgorithm(Solution &solution, int it, int mutation_kind, int selection_kind, SalesmanGraph &graph)
{
	Genetic genetic; // Obiekt zawierajacy atrybuty i metody niezbedne do obslugi algorytmu genetycznego
	genetic.chooseMutation(mutation_kind);
	this->chooseSelection(selection_kind);
	vector<int> currentOrder = this->path; // Ustawienie defaultowej sciezki
	vector<int> bestOrder = this->path; // Ustawienie najlepszej sciezki
	int bestDistance = INT_MAX; // Ustawienie max dlugosci sciezki
	genetic.init();

	this->createPopulation(genetic); // Tworzy losowe populacje wejsciowe dla algorytmu
	for (int i = 0; i < it; i++) {
		this->pickParents(genetic);
		for (int i = 0; i < genetic.getChildPairs(); i++)
		{
			this->cross(genetic);
		}

		this->chooseNewPopulation(genetic, graph);
		int tmpbest = this->getBestWay(genetic);
		if (tmpbest < bestDistance)
		{
			bestDistance = tmpbest;
			bestOrder = genetic.populations.front();
		}
	}
	solution.path = bestOrder;

}

void SalesmanGraph::createPopulation(Genetic &genetic)
{
	for (int i = 0; i < genetic.populationSize; i++)
	{
		vector<int> path(this->getSize());
		for (int i = 0; i < this->getSize(); ++i)
		{
			path[i] = i;
		}
		path.push_back(0);
		for (int i = 0; i < rand() % 200; i++)
			std::next_permutation(path.begin() + 1, path.begin() + this->getSize() / 2);
		for (int i = 0; i < rand() % 200; i++)
			std::next_permutation(path.begin() + this->getSize() / 2, path.end() - 1);

		genetic.populations.push_back(path);
	}

}

void SalesmanGraph::pickParents(Genetic &genetic) {

	//selekcja metoda ruletkowa
	if (roulette_sel)
	{
		int MAX_VALUE = this->getMaxValue()*this->getSize();
		genetic.parents.clear();
		vector <int> pathCosts(genetic.populationSize);
		unsigned long long SUM = 0;
		unsigned long long presentCost = 0;
		unsigned long long lastCost = 0;
		int j = 0;
		for (int i = 0; i < genetic.populationSize; i++)
		{
			pathCosts[i] = this->costFunc(genetic.populations[i], MAX_VALUE);
			SUM += pathCosts[i];
		}

		//sort(genetic.populations.begin(), genetic.populations.end(), [this](auto i, auto j)->bool {return this->getDistance(i) > getDistance(j); });

		unsigned long long rulette = 0;
		for (int i = 0; i < genetic.parentsPopulationSize; i++)
		{
			rulette = ((double)rand() / (double)RAND_MAX)*SUM;
			presentCost = 0;
			lastCost = 0;

			for (int i = 0; i < genetic.populationSize; i++)
			{
				presentCost += pathCosts[i];

				if (lastCost <= rulette && rulette <= presentCost)
				{
					genetic.parents.push_back(genetic.populations.at(i));
					break;
				}
				lastCost += pathCosts[i];
			}
		}
	}
	//selekcja metoda listy rankignowej	
	else
	{
		sort(genetic.populations.begin(), genetic.populations.end(), [this](auto i, auto j)->bool {return this->getDistance(i) < getDistance(j); });
		for (int i = 0; i < genetic.parentsPopulationSize; i++)
		{
			genetic.parents.push_back(genetic.populations.at(i));
		}

	}


}

void SalesmanGraph::tryCross(Genetic &genetic) {
	if ((double)rand() / (double)RAND_MAX < genetic.crossProbablity) this->cross(genetic);
}

void SalesmanGraph::cross(Genetic &genetic) {

	int size = this->getSize() - 1;
	int parentSize = genetic.parents[0].size();
	vector<int> parent1 = genetic.parents.at(rand() % genetic.parentsPopulationSize);
	vector<int> parent2 = genetic.parents.at(rand() % genetic.parentsPopulationSize);

	int number1, number2;
	int start, end;

	do {
		number1 = rand() % size;
		number2 = rand() % size;
		start = fmin(number1, number2);
		end = fmax(number1, number2);
	} while (number1 == number2);
	vector<int> child1;
	vector<int> child2;


	//usuwanie wierzcholka poczatkowego i koncowego (czyli tego samego)
	parent1.erase(parent1.begin());
	parent1.erase(parent1.end() - 1);
	parent2.erase(parent2.begin());
	parent2.erase(parent2.end() - 1);


	//dodawanie do dziei wierzcholkow od indeksu START do STOP (wycinek sciezki)
	for (int i = start; i < end; i++)
	{
		child1.push_back(parent1[i]);
		child2.push_back(parent2[i]);
	}


	//dodanie reszty wierzcholkow od drugiego rodzica 
	int geneIndex = 0;
	int geneInparent1 = 0;
	int geneInparent2 = 0;

	for (int i = 0; i < size; i++)
	{
		geneIndex = (end + i) % size;
		geneInparent1 = parent1[geneIndex];
		geneInparent2 = parent2[geneIndex];

		bool is_there = false;
		for (int i1 = 0; i1 < child1.size(); i1++)
		{
			if (child1[i1] == geneInparent2)
			{
				is_there = true;
			}
		}
		if (!is_there)
		{
			child1.push_back(geneInparent2);
		}

		bool is_there1 = false;
		for (int i1 = 0; i1 < child2.size(); i1++)
		{
			if (child2[i1] == geneInparent1)
			{
				is_there1 = true;
			}
		}
		if (!is_there1)
		{
			child2.push_back(geneInparent1);
		}
	}


	//przesuniecie tak, aby wycinek byl na odpowiednim miejscu
	std::rotate(child1.begin(), child1.begin() + child1.size() - start, child1.end());
	std::rotate(child2.begin(), child2.begin() + child2.size() - start, child2.end());

	for (int i = 0; i < size; i++)
	{
		parent1[i] = child2[i];
		parent2[i] = child1[i];
	}

	tryMutate(genetic, child1, size);
	tryMutate(genetic, child1, size);


	//dodanie pierwszego i ostatniego wierzcholka (startowego)
	vector<int>::iterator it;
	it = child1.begin();
	it = child1.insert(it, 0);
	it = child2.begin();
	it = child2.insert(it, 0);
	child1.push_back(0);
	child2.push_back(0);

	genetic.childrens.push_back(child1);
	genetic.childrens.push_back(child2);
}

void SalesmanGraph::chooseNewPopulation(Genetic &genetic, SalesmanGraph &graph)
{
	vector<vector<int>> newPopulation;
	newPopulation.reserve(genetic.getPopulationSize());

	//algorytm memetyczny (symulowane wyzarzaie dla kazdego dziecka) - MOZNA ZAKOMENTOWAC
//	for (int i = 0; i < genetic.childrens.size(); i++)
//	{
//		SalesmanGraph::simulated_annealing(graph, genetic.childrens.at(i),genetic.childrens.at(0).size());
//
//	}

	sort(genetic.populations.begin(), genetic.populations.end(), [this](auto i, auto j)->bool {return this->getDistance(i) > getDistance(j); });
	sort(genetic.childrens.begin(), genetic.childrens.end(), [this](auto i, auto j)->bool {return getDistance(i) > getDistance(j); });
	for (int i = 0; i < genetic.getPopulationSize(); i++)
	{
		// Dodawanie dzieci
		while (!genetic.childrens.empty())
		{
			newPopulation.push_back(genetic.childrens.back());
			genetic.childrens.pop_back();
		}
	}
	genetic.populations = newPopulation;


}

void SalesmanGraph::simulated_annealing(SalesmanGraph &graph, vector<int> &path, int size)
{
	int s = INT_MAX, nowe_s = INT_MAX, delta = 0;
	float x = 0;
	double T = 99.0;
	double cooling = 0.95;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, 100);

	vector<int> temp_path;

	s = graph.getDistance(path);

	while (T > 1)
	{
		temp_path = path;

		for (int i = 0; i < graph.getSize(); i++)
		{
			losuj_sciezke(temp_path, size);		// znajdowanie nowej permutacji
			nowe_s = graph.getDistance(temp_path);

			delta = nowe_s - s;
			if (delta < 0)					// zapisanie minimum
			{
				s = nowe_s;
				path = temp_path;
			}
			else
			{
				x = dist(gen) * 0.01;
				if (x < exp(-delta / T))	// sprawdzenie czy zapisac gorszy wynik
				{
					s = nowe_s;
					path = temp_path;
				}
			}
		}

		if (T > 0.05)
			T = T * cooling;
	}

}

void SalesmanGraph::losuj_sciezke(vector<int> &path, int size)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, size - 2);

	int x = 0, y = 0, tmp = 0;
	do									//losowanie dwoch ró¿nych indeksów do znaleŸienie s¹siedztwa
	{
		x = dist(gen);
		y = dist(gen);
	} while (x == y);

	swap(path, path.at(x), path.at(y));

}

// HELPERS
int SalesmanGraph::getMaxValue() {
	int best = 0;
	for (int i = 0; i < this->getSize(); i++) {
		for (int j = 0; j < this->getSize(); j++) {
			if (this->costArray[i][j] > best)
				best = this->costArray[i][j];
		}
	}
	return best;
}
unsigned int SalesmanGraph::costFunc(vector<int> path, int max)
{
	unsigned int cost = this->getDistance(path);
	unsigned int ret = (max - cost);
	return ret;
}
void SalesmanGraph::showPopulation(Genetic genetic)
{
	for (int i = 0; i < genetic.populations.size(); i++)
	{
		cout << this->getDistance(genetic.populations[i]) << endl;
	}
}
void SalesmanGraph::showChildrens(Genetic genetic)
{
	for (int i = 0; i < genetic.populations.size(); i++)
	{
		cout << this->getDistance(genetic.childrens[i]) << endl;
	}
}
void SalesmanGraph::tryMutate(Genetic &genetic, vector<int>& path, int size)
{
	if ((double)rand() / (double)RAND_MAX < genetic.getMutationProbability()) this->mutate(genetic, path, size);
}

void SalesmanGraph::mutate(Genetic &genetic, vector<int>& child, int size)
{
	for (int i = 0; i < genetic.getSwapsInMutation(); ++i)
	{
		if (genetic.swapMutation == true)
			swapGeneticOne(child, rand() % child.size(), rand() % child.size());
		else swapGeneticTwo(child, rand() % child.size());
	}
}
void SalesmanGraph::swapGeneticOne(vector<int>& path, int i, int j)
{
	int temp = path[i];
	path[i] = path[j];
	path[j] = temp;
}
void SalesmanGraph::swapGeneticTwo(vector<int>& path, int middle) {
	rotate(path.begin(), path.begin() + middle, path.end());
}
int SalesmanGraph::getBestWay(Genetic &genetic)
{
	int score = this->getDistance(genetic.populations.front());
	return score;
}
void SalesmanGraph::swap(vector<int> &path, int x, int y)
{
	int tempVertex = path.at(x);
	path.at(x) = path.at(y);
	path.at(y) = tempVertex;

}
void SalesmanGraph::showOrder()
{
	for (int i = 0; i < this->path.size(); i++)
		cout << this->path.at(i) << " - ";
	cout << endl;
}

vector<int>& SalesmanGraph::getPath()
{
	return this->path;
}
void SalesmanGraph::chooseSelection(int selection_kind)
{
	if (selection_kind == 1) this->roulette_sel = true;
	else this->roulette_sel = false;
}