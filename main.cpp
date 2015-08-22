#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <map>
#include <set>
#include <queue>
#include <string>

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

typedef struct _on{
	string nome;
	int peso;
	
	bool operator<(const _on& rhs) const
	{
		return nome < rhs.nome;
	}
	
	bool operator>(const _on& rhs) const
	{
		return peso < rhs.peso;
	}

	bool operator==(const _on& rhs) const
	{
		return nome == rhs.nome;
	}
}type_edge;

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
	set<int> vertices;
	set<type_edge> edges;
    
	vector<extern_node> grafo = utils_tomem("entrada.txt");
	for(int i=0;i<(int)grafo.size();i++)
	{
                //Inserimos os vertices no conjunto de vertices
		vertices.insert(grafo.at(i).nome);
		list<intern_node> viz_aux = grafo.at(i).vizinhos;
		list<intern_node>::iterator it = viz_aux.begin();
                
                //For para andar pela lista de vizinhos do vertice que acabou de ser inserido no conjunto
		for(int j=0;j<(int)viz_aux.size();j++)
		{
			string nome;
			type_edge aux;
			
			nome.clear();
			advance(it, j);
                        
                        //nome da aresta eh sempre uma string 'MENOR,MAIOR' onde MENOR e MAIOR sao numeros (por enquanto)
			if(grafo.at(i).nome <= it->nome){
				nome.append(to_string(grafo.at(i).nome) );
				nome += ',';
				nome.append(to_string(it->nome));
			}
			else{
				nome.append(to_string(it->nome));
				nome += ',';
				nome.append(to_string(grafo.at(i).nome) );
			}
			aux.nome = nome;
			aux.peso = it->peso;
                        
                        //Inserimos a aresta no conjunto de arestas. Caso o nome da aresta ja exista, o conjunto nao insere nada
                        edges.insert(aux);
		}
	}
	//Printa conjunto de vertices
	for(set<int>::iterator iter=vertices.begin(); iter != vertices.end(); ++iter){
		cout<< *iter << endl;
	}
	cout << endl;
        //Printa conjunto de arestas com seus pesos
	for(set<type_edge>::iterator iter=edges.begin(); iter != edges.end(); ++iter){
		cout<< iter->nome << " " << iter->peso << endl;
	}

	
	
        
}
