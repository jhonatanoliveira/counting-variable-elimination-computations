#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

int main() {

	// ### Defining variables ###

	string netType;
	int numOfVars, varCard, numOfCpts, numOfVarCpt, cptVar, numOfElimOrd, numOfVarElim, varElim;
	vector<int> vars;
	vector< set<int> > cpts;
	vector< vector<int> > elimOrds;
	vector< vector<int> > countings;

	// ### Readings ###

	// Reading variables' cardinality
	cin >> numOfVars;
	for (int i = 0; i < numOfVars; i++) {
		cin >> varCard;
		vars.push_back(varCard);
	}

	// Reading CPTs
	cin >> numOfCpts;
	for (int j = 0; j < numOfCpts; j++) {

		// Reading variables of CPT
		cin >> numOfVarCpt;
		set<int> cpt;
		for (int k = 0; k < numOfVarCpt; k++) {
			cin >> cptVar;
			cpt.insert(cptVar);
		}
		cpts.push_back(cpt);
	}

	// Reading elimination orderings
	cin >> numOfElimOrd;
	for (int l = 0; l < numOfElimOrd; l++) {

		// Reading each elimination ordering
		cin >> numOfVarElim;
		vector<int> elimOrd;
		for (int m = 0; m < numOfVarElim; m++) {
			cin >> varElim;
			elimOrd.push_back(varElim);
		}
		elimOrds.push_back(elimOrd);
	}

	// ### Computing ##

	// For each elimination ordering
	for (int n = 0; n < elimOrds.size(); n++) {
		// For each variable
		vector<int> counting;
		vector< set<int> > currentCpts;
		currentCpts = cpts;
		int multiplicationCount = 0;
		int summationCount = 0;
		for (int o = 0; o < elimOrds[n].size(); o++) {
			// Looking for CPTs with the variable
			set<int> productCpt;
			for (int p = 0; p < currentCpts.size(); p++) {
				set<int>::iterator findVarElim =  currentCpts[p].find(elimOrds[n][o]);
				if (findVarElim != currentCpts[p].end()) {
					productCpt.insert( currentCpts[p].begin(), currentCpts[p].end() );
					currentCpts.erase(currentCpts.begin() + p);
					p--; // countd down because of the erasing
				}
			}
			// Counting multiplications
			set<int>::iterator it;
			int preMultiplicationCount = 1;
			for (it = productCpt.begin(); it != productCpt.end(); ++it) {
				preMultiplicationCount *= vars[*it];
			}
			multiplicationCount += preMultiplicationCount;
			// remove variable to be eliminates from CPT
			productCpt.erase(elimOrds[n][o]);
			// Counting summations
			set<int>::iterator it2;
			int preSummationCount = 1;
			for (it2 = productCpt.begin(); it2 != productCpt.end(); ++it2) {
				preSummationCount *= vars[*it2];
			}
			summationCount += preSummationCount;
			// add product to current CPTs
			currentCpts.push_back(productCpt);
		}
		// saving countings
		counting.push_back(multiplicationCount);
		counting.push_back(summationCount);
		countings.push_back(counting);
	}

	// ### Showing ##

	for (int q = 0; q < countings.size(); q++) {
		cout << "Counting for Elimination No " << q+1 << endl;
		for (int r = 0; r < countings[q].size(); r++) {
			cout << countings[q][r] << " ";
		}
		cout << endl;
	}

	return 0;
}