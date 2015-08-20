#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;
typedef struct _in
{
	int nome; 
	int peso;
	_in(int _nome, int _peso): nome(_nome), peso(_peso){}
	_in(){}
}intern_node;
typedef struct _en
{
	int nome;
	list<intern_node> vizinhos;
	friend ostream& operator<<(ostream& os,const _en& it)
	{
		os << it.nome << " ";
		for(list<intern_node>::const_iterator i=it.vizinhos.begin();i!=it.vizinhos.end();i++)
		{
			os << i->nome << "[" << i->peso << "] ";
		}
		return os;

	}
}extern_node;
vector<extern_node> utils_tomem(string nome_arq);
vector<extern_node> utils_tomem(string nome_arq)
{
	fstream sc;
	vector<extern_node> grafo;
	sc.open(nome_arq.c_str());
	char *pch;
	string s;
	while(getline(sc,s))
	{
		vector<int> lista;
		extern_node n;
		if(s!="")
		{
			pch = strtok((char*)s.c_str(),"\t ");
			while(pch!=NULL)
			{
				lista.push_back(atoi(pch));
				pch = strtok(NULL,"\t []");
			}
		}
		n.nome = lista.at(0);
		for(int i=1;i<(int)lista.size();i+=2)
		{
			n.vizinhos.push_back(intern_node(lista.at(i),lista.at(i+1)));
		}
		grafo.push_back(n);
	}
	return grafo;
}
int main()
{
	vector<extern_node> grafo = utils_tomem("entrada.txt");
	for(int i=0;i<(int)grafo.size();i++)
	{
		cout << grafo.at(i) << endl;
	}
	return 0;
}
