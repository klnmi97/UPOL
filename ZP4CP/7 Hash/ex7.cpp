// ex7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include<unordered_map>
using namespace std;

struct OvoceCena { const char *ovoce; float cena; };

struct hash_fun
{
	unsigned operator () (const char* x) const {
		return 31 * toupper(x[0]) + tolower(x[strlen(x) - 1]) + strlen(x);
	}
};

struct equal_fun
{
	bool operator () (const char* name1, const char* name2) const {
		return stricmp(name1, name2) == 0;
	}
};

//unordered_map<string, float, hash_fun, equal_fun> m;

unordered_map<const char *, float, hash_fun, equal_fun> m;



const OvoceCena ovoceCena[] =
{ { "Jablka",24.20 },{ "Blumy",63.60 },{ "CITRONY",25.00 },
{ "Blumy",63.60 },{ "grepy",19.50 },{ "mandarinky",25.10 },
{ "POMELO",32.20 },{ "Ananas",40.60 },{ "mango",18.80 },
{ "KIWI",3.60 },{ "jahody",86.40 },{ "Hrozny",55.60 } };

const char *vypsatOvoce[] =
{ "citrony","ANANAS","Jahody","broskve","Pomelo","mirabelky" };


void vypis(const char * r = "") { 
	for (int i = 0; i < m.bucket_count(); ++i) cout << m.bucket_size(i) << r; cout << endl; 
}

int main()
{
	for (auto x : ovoceCena) {
		m.emplace(x.ovoce, x.cena);
	}

	for (auto x : m) {
		cout << x.first << " - " << x.second << endl;
	}

	cout << endl << endl;

	for (auto x : vypsatOvoce) {
		auto found = m.find(x);
		if (found == m.end())
			cout << x << " = ???";
		else
			cout << found->first << " = " << found->second;
		cout << endl;
	}
	
	cout << m.bucket_count() << endl;
	vypis("");
	cout << m.load_factor() << endl;

    return 0;
}

