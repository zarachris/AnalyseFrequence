#include <iostream>
#include <string>
#include <fstream>
#include <map> //Pour associer une lettre au nombre de fois où il apparait
#include <algorithm>//Pour enlever tous les espaces dans le message chiffré

using namespace std;

string LireMessage(string fileName);
void AnalyseFreq(void);//La nouvelle fonction
ofstream fichier_out;
ifstream fichier_in;

int main()
{
	AnalyseFreq();//Lance l'analyse de fréquence

}


void AnalyseFreq(void)
{
	string message = LireMessage("message.txt");//J'ouvre cette fois-ci le "message.txt" avec le msg chiffré, à mettre dans le dossier !
	message.erase(remove(message.begin(), message.end(), ' '), message.end());//Enleve les espaces pour éviter de les compter après !
	string output = "";


	unsigned int nmax = 0;//Le nombre d'occurence de la lettre qui apparait le +
	unsigned char cnmax;//La lettre qui apparait le +
	float _key;//La clé a la fin, en float pour permettre de gérer les nombres négatifs



	map < unsigned char,unsigned int> occurences;//En gros, va associer une lettre (char) à son nombre d'occurence (int)

	
	for (int i = 0; i < 256 /* Les 256 caractères existants */; i++) {
		occurences[i] = 0; // Il n'y a pour l'instant aucune occurence
	}


	for (unsigned int i = 0; i < size(message); i++)/* On va regarder chaque lettre du message */ {

		unsigned char caracterencours = tolower(message[i]);//En plus d'avoir supprimé les espaces plus haut, on met tout en minuscule

		occurences[caracterencours]++;//On ajoute 1 à chaque fois que l'on trouve la lettre correspondante dans le message


		if (occurences[caracterencours] > nmax)//Si cette lettre apparait le plus par rapport aux précédentes lettres, on la stocke
		{
			nmax = occurences[caracterencours];//On garde le nombre d'occurence de la lettre qui apparait le plus
			cnmax = caracterencours;//On garde la lettre qui apparaît le plus
		}
	}



	_key = (cnmax - 'a') - ('e' - 'a');

	//On détermine la clé en soustrayant :
	//La comparaison des nombres ASCII de la lettre qui apparait le + (cnmax) avec le début de l'alphabet 'a'
	//La comparaison des nombres ASCII de la lettre qui apparait le + en anglais ('e') avec le début de l'alphabet 'a'
	//Cette comparaison donne l'espace qu'il y a entre 'e' et la lettre qui apparait le + (cnmax)
	// Remarque : On a enlevé les espaces pour ne pas les compter, sinon cnmax serait devenu ' '. 
	//			  On a tout mis en minuscule pour pouvoir prendre en compte les lettres en majuscule.
	//C'est donc la clé que l'on cherche !


	if (_key < 0) //Au cas où la soustraction de _key est négative, ce qui peut arriver avec une grande clé
	{
		_key = 26 + _key;//Ainsi on retrouvera la bonne clé plutôt qu'un nombre négatif
	}


	cout << "La clé est " << _key <<"."<<endl;


}

string LireMessage(string fileName) {
	string message = "";
	fichier_in.open(fileName);

	if (fichier_in.fail()) {
		cout << "Erreur a l'ouverture du fichier..." << endl;
		cout << "Veuillez vérifier que le fichier existe et qu'il est placé à la racine du projet." << endl;
	}
	else {
		string line;

		while (std::getline(fichier_in, line)) {
			message.append(line + "\n"); // on ajoute chaque ligne au message + un saut de ligne
		}
	}
	fichier_in.close();
	return message;
}