#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include "HashMap.hpp"

int frequence_mot(){
	return 0;
}

int main () {
	using namespace std;
	using namespace std::chrono;

	vector<pair <string, size_t>> vec;

	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;
    pr::HashMap<string, int> hashmap(30000);

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		//bool trouve = false;
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		
		int* word_count = hashmap.get(word);
		if (word_count != nullptr){
			(*word_count)++;
		}
		else {
			hashmap.put(word,1);		//Ajoute l'entrée à la table de hachage (il y a une occurence actuellement)
		}
		/*
		//Fréquences des mots avec vecteur :
		for ( auto& pair : vec) {
			if (pair.first == word){
				trouve = true;
				pair.second++;
				break;
			}
		}

		if (!trouve){
				vec.emplace_back(word, 1);
				// word est maintenant "tout propre"
				if (nombre_lu % 100 == 0)
				// on affiche un mot "propre" sur 100
					cout << nombre_lu << ": "<< word << endl;
				nombre_lu++;
		}
		*/
		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
		// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;
	}
			
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";
	cout << "Amount of differents words :" << hashmap.size() << endl;
    cout << "Found a total of " << nombre_lu << " words." << endl;

    return 0;
}




