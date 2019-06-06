#include <climits>
#include "SalesmanGraph.h"
#include <chrono>
#include <string>

using namespace std;


void load(SalesmanGraph &graph, bool &loadGood);

int main()
{
	bool loadNotGood = true;
	Solution solution;
	SalesmanGraph graph;
	while (loadNotGood)
		load(graph, loadNotGood);
	int option;
	srand(time(NULL));
	while (true)
	{
		cout << endl << endl;
		cout << "1. Wczytaj graf" << endl;
		cout << "2. Algorytm genetyczny" << endl;
		cout << "Wybierz opcje: ";
		cin >> option;
		switch (option)
		{
		case 1:
		{
			loadNotGood = true;
			while (loadNotGood)
				load(graph, loadNotGood);
			break;
		}

		case 2:
		{
			int sum = 0, it = 0;
			bool swapMutation;
			int mutation_kind, selection_kind;
			cout << "Wprowadz liczbe iteracji: " << endl;
			cin >> it;
			cout << "Wybierz rodzaj mutacji: " << endl << "1. Przez zamiane elementow (swap) " << endl << "2. Przez rotacje czesci sciezki" << endl;
			cin >> mutation_kind;
			//cout << "Wybierz rodzaj selekcji: " << endl << "1. Selekcja metoda ruletki " << endl << "2. Selekcja metoda rankingowa" << endl;
			//cin >> selection_kind;
			selection_kind = 1;
			auto start = chrono::high_resolution_clock::now();
			graph.geneticAlgorithm(solution, it, mutation_kind, selection_kind, graph);
			auto end = chrono::high_resolution_clock::now() - start;
			auto t1 = chrono::duration_cast<chrono::milliseconds>(end);
			cout << "Koszt " << graph.getDistance(solution.path) << " , czas operacji = " << t1.count() << endl;
			sum += graph.getDistance(solution.path);
			// Do przegladania sciezki grafu
			for (int i = 0; i < solution.path.size(); i++)
				cout << solution.path[i] << " - ";

			break;
		}
		}
	}
	cout << endl << endl;
	system("pause");
	return 0;
}


void load(SalesmanGraph &graph, bool &good)
{
	string filename;
	cout << "Podaj nazwe pliku bez rozszerzenia: ";
	cin >> filename;
	//graph.loadFromFile_EUC2D(graph, filename, good);
	graph.loadFromFile(graph, filename, good);

}