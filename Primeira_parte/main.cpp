/***********************************************************************
* Pontificia Universidade Catolica de Minas Gerais
* Ciencia da Computacao
* Algoritmos em Grafos
* Prof. Max do Val Machado
************************************************************************/
/*
*Integrantes:
*Felipe Ribeiro
*João Ribeiro
*Jordan Lyon
*Rama Alvim
*
/

//=====================================================================
// BIBLIOTECAS
//=====================================================================
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <queue>
#include <stack>
#include <deque>
using namespace std;


//=====================================================================
// DEFINICAO DE CONSTANTES
//=====================================================================
#define MAX_VERTICE            500
#define MAX_INT               0x7FFFFFFF
#define NULO                  -1
#define BRANCO                  0
#define PRETO                  1


//=====================================================================
// DEFINICAO DE TIPOS
//=====================================================================
typedef short boolean;

typedef int Vertice;
typedef int Peso;

struct Aresta
{
	Vertice vi, vj;
	Peso peso;
};

struct nodeDist
{
	int node;
	int dist;
	nodeDist(int _node, int _dist) : node(_node), dist(_dist) {}
};


//=====================================================================
// CLASSE GRAFO
//=====================================================================
class Grafo
{
private:
	int numVertice, numAresta;
	int counter;

public:
	Grafo(){
		counter = 0;
		numVertice = 0;
	}

	//Metodos nao compartilhados - implementados nas classes que herdam de Grafo.
	virtual void setAresta(Vertice v1, Vertice v2, Peso p) = 0;
	virtual Peso getAresta(Vertice v1, Vertice v2) = 0;

	//--------------------------------------------------------------------
	// lerGrafo: Realiza a leitura do grafo no arquivo.
	//--------------------------------------------------------------------
	boolean lerGrafo()
	{
		boolean resp;
		int temp;

		excluirTodasArestas();

		//Ler o numero de vertices
		cin >> temp;
		setNumVertice(temp);

		resp = (numVertice > 0) ? true : false;

		for (int i = 0; i < numVertice; i++)
		{
			inserirAresta(i, i, NULO);
			for (int j = i + 1; j < numVertice; j++)
			{
				cin >> temp;
				inserirAresta(i, j, temp);
				inserirAresta(j, i, temp);
			}
		}
		return resp;
	}

	void imprimeBipartite()
	{
		if(isBipartite())
		{
			cout<<"SIM"<<endl;
		}
		else
			{cout<<"NAO"<<endl;}

	}

	void imprimeNumArestas()
	{
		int numArestas=0;
		for(int i=0;i<numVertice;i++)
		{
			numArestas=numArestas+getGrau(i);

		}
		numArestas=numArestas/2;
		cout<<numArestas<<endl;
	}

	//
	// imprime numero de vertices
	//
	void imprimeNumVertices()
	{
		cout<<numVertice<<" ";
	}

	//
	// imprimeNumVerticeAresta
	//
	void imprimeNumVerticeAresta()
	{	
		imprimeNumVertices();
		imprimeNumArestas();
		
	}

	//--------------------------------------------------------------------
	// imprimirGrauVertice: imprime grau de um vertice.
	//--------------------------------------------------------------------
	void imprimirGrauVertice(int v)
	{
		cout << getGrau(v) << endl;
	}

	//--------------------------------------------------------------------
	// imprimeInfoGrafo: Imprime uma linha indicando se o grafo  Simples, regular, nulo, completo, euleriano e unicursal.
	//--------------------------------------------------------------------
	void imprimeInfoGrafo()
	{
		//simples
		//TODO: isSimples
	cout<<"SIM"<<" ";

		//regular
		if(isRegular())
			{cout<<"SIM"<<" ";}
		else{cout<<"NAO"<<" ";}
		//nulo
		if(isGrafoNulo())
			{cout<<"SIM"<<" ";}
		else{cout<<"NAO"<<" ";}
		//completo
		if(isCompleto())
		{cout<<"SIM"<<" ";}
		else{cout<<"NAO"<<" ";}
		//euleriano
		if(isEuleriano())
			{cout<<"SIM"<<" ";}
			else{cout<<"NAO"<<" ";}
		//unicursal
				if(isUnicursal())
			{cout<<"SIM"<<endl;}
			else{cout<<"NAO"<<endl;}
	}

	//--------------------------------------------------------------------
	// imprimirIsGrafoNulo: imprime nulo se o grafo for nulo
	//--------------------------------------------------------------------
	void imprimirIsGrafoNulo()
	{
		if (isGrafoNulo() == 1)
		{
			cout << "grafo nulo" << endl;
		} else
		{ cout << "grafo nao nulo" << endl; }
	}

	//--------------------------------------------------------------------
	//  bool isPendente: retorna true se o vertice for pendente.
	//--------------------------------------------------------------------
	bool isPendente(int v)
	{
		int grau = 0;
		int i = 0;
		for (i = 0; i < numVertice; i++)
		{
			if (getAresta(i, v) != -1)
			{
				grau++;
			}
		}
		if (grau == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}//-------------------------------------------------------------------

	//--------------------------------------------------------------------
	// isAresta: Retorna true se existe a aresta.
	//--------------------------------------------------------------------
	boolean isAresta(Vertice v1, Vertice v2)
	{
		return (getAresta(v1, v2) != NULO);
	}

	//--------------------------------------------------------------------
	// excluirAresta: Exclui uma aresta.
	//--------------------------------------------------------------------
	void excluirAresta(Vertice v1, Vertice v2)
	{

		if (v1 > numVertice)
		{
			printf("ERRO! Vertice %i nao existe no grafo", v1);
			return;
		}

		if (v2 > numVertice)
		{
			printf("ERRO! Vertice %i nao existe no grafo", v2);
			return;
		}

		if (getAresta(v1, v2) != NULO)
		{
			setAresta(v1, v2, NULO);
			numAresta--;
		}
	}

	//--------------------------------------------------------------------
	// excluirTodasArestas: Exclui todas as arestas.
	//--------------------------------------------------------------------
	void excluirTodasArestas()
	{
		for (int i = 0; i < MAX_VERTICE; i++)
		{
			setAresta(i, i, NULO);
			for (int j = i + 1; j < MAX_VERTICE; j++)
			{
				setAresta(i, j, NULO);
				setAresta(j, i, NULO);
			}
		}
		numAresta = 0;
	}//-------------------------------------------------------------------

	void imprimir()
	{
		int i = 0, j = 0;

		printf("\nN = (%i)\n\t", numVertice);
		for (i = 0; i < numVertice; i++)
		{
			if (i >= 100)
			{
				printf("\t(%i) ", i);
			} else if (i >= 10)
			{
				printf("\t(0%i) ", i);
			} else
			{
				printf("\t(00%i) ", i);
			}
		}

		for (i = 0; i < numVertice; i++)
		{
			if (i >= 100)
			{
				printf("\n(%i) - ", i);
			} else if (i >= 10)
			{
				printf("\n(0%i) - ", i);
			} else
			{
				printf("\n(00%i) - ", i);
			}

			for (j = 0; j < numVertice; j++)
			{
				if (getAresta(i, j) == NULO)
				{
					printf("\t. ");
				} else
				{
					printf("\t%i ", getAresta(i, j));
				}
			}
		}

		printf("\n");
	}

	//--------------------------------------------------------------------
	//clear: limpa fila
	//--------------------------------------------------------------------
	void clearQueue( std::queue<int> &q )
	{
		std::queue<int> empty;
		std::swap( q, empty );
	}

	//--------------------------------------------------------------------
	// imprimirIsPendente: imprime se o vertice eh pendente
	//--------------------------------------------------------------------
	void imprimirIsPendente()
	{
		if (isPendente(4) == 1)
		{
			cout << "vertice pendente" << endl;
		} else
		{
			cout << "vertice nao pendente" << endl;
		}
	}

	void caixeiro()
	{
		int temp=counter;

		//vetor visitados


		//i = vertice atual
		//for --> para cada vertice atual
		for(int i=0;i<numVertice;i++)
		{
			counter = 0;
			boolean *visi=new boolean[numVertice];
			//marca todos como nao visitados
			for(int j=0;j<numVertice;j++)
			{
				visi[j]=false;
			}
			int menor=MAX_INT;
			//começar aqui a classe
			viajante(visi,menor,i);
		}
		//cout<<counter<<endl;
		counter=temp;
	}

	void viajante(boolean visi[],int menor,int vAtual)
	{
		//descubra aresta com menor peso conectada ao vertice atual
		// e a um vertice nao visitado

		if(visi[vAtual]==false)
		{
			visi[vAtual] = true;
			counter++;

		}
			//cout<<vAtual<<endl;
		int menorV=-1;
		for(int j=0;j<numVertice;j++)
		{
			//procura pelos vertices conectados aos atuais que não tenham sido visitados
			if(isAresta(vAtual,j)==true && visi[j]==false)
			{
				if(getAresta(vAtual,j)<menor)
				{
					menor = getAresta(vAtual,j);

					menorV=j;
					cout<<menorV<<endl;
					visi[menorV]=true;
					counter++;
					if(counter<=numVertice)
					{
						viajante(visi,menor,j);
					}
				}
			}
		}
	}

	//--------------------------------------------------------------------
	//buscaProfunda: inicia a busca em profundidade do grafo
	//--------------------------------------------------------------------
	void buscaProfunda()
	{
		boolean *visitado = new boolean[numVertice];
		deque <nodeDist> caminho;
		//marcar cada vertice como não visitado
		for(int i = 0; i < numVertice; i++){
			visitado[i] = false;
		}

		//para cada vertice não visitado, faça um visite(v)
		for(int i = 0; i < numVertice; i++){
			if(visitado[i] == false)
			{
				visite(i, visitado,caminho,0);
			}
		}

	}

	//--------------------------------------------------------------------
	//buscaProfunda: realiza a busca em profundidade do grafo
	//--------------------------------------------------------------------
	void visite (Vertice v1, boolean visitado[], deque<nodeDist> &cam,int dist0)
	{
		int dist=0;

		//cout<<"tamanho "<<cam.size()<<endl;
		int i;
		visitado[v1]=true;
		//cout<<v1<<endl;
		for(i = 0; i < numVertice; i++)
		{
			if(isAresta(v1, i) == true && visitado[i]==false && counter<numVertice)
			{
				cam.push_back(nodeDist(v1,getAresta(v1, i)));
				counter++;
				dist = getAresta(v1, i) + dist0;

				//	visitado[i] = true;
				visite(i, visitado, cam, dist);
			}
		}
		counter--;
		visitado[i]=false;
		cam.pop_back();
	}

	//--------------------------------------------------------------------
	//printVisitados: inicia a busca em profundidade do grafo
   //--------------------------------------------------------------------
	void printVisitados(int visitados[])
	{
		int x=0;
		for (int i = 0; i <numVertice ; ++i)
		{
			//nao-visitados = -1
			//na fila
			x=visitados[i];

			cout<< x<< " ";
		}
		cout << endl;
	}

	void printFila( queue<int> &q )
	{
		for (int i = 0; i <q.size() ; ++i)
		{
			int x = q.front();
			q.pop();

			cout <<x<< " ";
			q.push(x);
		}
		cout<<endl;
	}

	//--------------------------------------------------------------------
	//buscaLargura: inicia a busca em largura do grafo
	//--------------------------------------------------------------------
	void buscaLargura()
	{
		int *visitados = new int[numVertice];//para ser usado em busca em largura
		queue <int> fila;
		counter=-1;
		for(int i=0; i<numVertice; i++)
		{
			visitados[i] = -1;
		}

		for(int i =0; i< numVertice; i++)
		{
			if(visitados[i]==-1)
			{
				percorreLargura(0,visitados,fila);
			}
		}
	}

	//--------------------------------------------------------------------
	//percorreLargura: percorre a busca em largura
	//--------------------------------------------------------------------
	void percorreLargura(int u,int visitados[], queue<int> &fila)
	{

		fila.push(u);//vertice recebido na para o fim da fila

		while(!fila.empty())
		{
			int v= fila.front();//lê item da frente da fila
			fila.pop();//remove item da frente da fila
			cout << v << " ";
			if(visitados[v]!=-1)
			{
				continue;
			}
			else
			{
				counter++;
				visitados[v] = counter;
			}

			for (int i = 0; i < numVertice; ++i)
			{
				if (isAresta(v,i)==1)
				{
					if(visitados[i]==-1)
					{
						fila.push(i);
					}
				}
			}
		}
	}

	//--------------------------------------------------------------------
	// isGrafoNulo: Retorna true se o grafo for nulo.
	//--------------------------------------------------------------------
	bool isGrafoNulo()
	{
		bool resp = true;
		for (int i = 0; i < numVertice && resp==true; i++)
		{
			for(int j=0;j<numVertice&&resp == true; j++)
			{
				if(getAresta(i,j)!=NULO)
				{
					resp=false;
				}
			}
		}
		return resp;
	}//-------------------------------------------------------------------

	//--------------------------------------------------------------------
	// isBipartite: Retorna true se o grafo é bipartite.
	//----------------------------------------------------------------------

	bool isBipartite()
	{
		bool resp=isBipartite(0);
		return resp;

	}

	bool isBipartite(int vert)
	{
		int color[numVertice];
		bool resp =true ;
		color[vert]=0;

		for(int i=1;i<numVertice;i++)
		{
			color[i]=-1;
		}
		color[vert]=1;

		queue <int> q;

		q.push(vert);

		while(!q.empty())
		{
			int u=q.front();
			q.pop();

			for(int v=0;v<numVertice;v++)
			{
				if(isAresta(u,v) && color[v]==-1)
				{
					color[v]=1 - color[u];
					q.push(v);
				}
				else if(isAresta(u,v) && color[v] == color[u])
				{
					resp=false;
				}
			}
		}
		return resp;
	}

      boolean isRegular()
		{

			int grau, aux = 0, x = 0;
			while(x < numVertice && aux != -1)
			{
				if(x == 0)
				{
					grau = getGrau(x);
				}
				else
				{
					if(grau != getGrau(x))
					{
    				  aux = -1;
					}
				}
				x++;
			}
			if(aux == -1)
			{
				return 0;
			}
			else
			{
				return 1;
			}
      }



	//--------------------------------------------------------------------
	// isEuleriano: Retorna true se o grafo for Euleriano.
	//--------------------------------------------------------------------


	bool isCompleto() {
		// (verificar se todos os vértices distintos são adjacentes.)	
		bool resp = true;
		for (int i=0;i<numVertice;i++){
			for (int j=i+1;j<numVertice;j++){
				if (isAresta(i,j)==false){
					resp = false;
					j = numVertice;
					i = numVertice;
				}
			}
		}
		return resp;
	}


	//--------------------------------------------------------------------
	// isEuleriano: Retorna true se o grafo for Euleriano.
	//--------------------------------------------------------------------
	bool isEuleriano()
	{
		bool resp = true;
		if (isConexo() == true)
		{
			for (int i = 0; i < numVertice; i++)
			{
				if (getGrau(i) % 2 == 1)
				{
					resp = false;
				}
			}

		}
		if(isGrafoNulo())
		{resp=false;}
		return resp;

	}

	//--------------------------------------------------------------------
	// isUnicursal: Retorna true se o grafo for unicursal.
	//--------------------------------------------------------------------

	bool isUnicursal()
	{
		//Conexo e com exatamente 2 vértices de grau ímpar.
		bool resp = true;
		int cont = 0;
		for (int i = 0; i < numVertice; i++){
			if (getGrau(i) % 2 != 0)
				cont++;
		}
		if (cont != 2 || isConexo() == false)
			{resp = false;}

		return resp;
	}

	//--------------------------------------------------------------------
	// isConexo: Retorna true se o grafo for conexo.
	//--------------------------------------------------------------------
	//TODO
	bool isConexo()
	{
		bool resp = true;
		return true;
	}

	//--------------------------------------------------------------------
	// inserirAresta: Insere uma nova aresta.
	//--------------------------------------------------------------------
	void inserirAresta(Vertice v1, Vertice v2, Peso peso)
	{

		if (v1 > MAX_VERTICE)
		{
			printf("ERRO! Vertice %i nao existe no grafico", v1);
			return;
		}

		if (v2 > MAX_VERTICE)
		{
			printf("ERRO! Vertice %i nao existe no grafico", v2);
			return;
		}

		if (getAresta(v1, v2) == NULO)
		{
			setAresta(v1, v2, peso);
			numAresta++;
		}
	}//-------------------------------------------------------------------

	//--------------------------------------------------------------------
	// getGrau: Retorna o grau da aresta.
	//--------------------------------------------------------------------
	int getGrau(int v)
	{
		int grau = 0;
		int i = 0;
		for (i = 0; i < numVertice; i++)
		{
			if (getAresta(i, v) != -1)
			{
				grau++;
				// cout <<grau<<endl;
			}
		}
		return grau;
	}//-------------------------------------------------------------------

	//--------------------------------------------------------------------
	// setNumVertice: Altera a variavel numVertice.
	//--------------------------------------------------------------------
	void setNumVertice(int nVertice)
	{

		if (nVertice > MAX_VERTICE)
		{
			printf("ERRO: Numero de vertices\n");
			return;
		}

		numVertice = nVertice;
	}//-------------------------------------------------------------------

	void imprimirVerticeAresta()
	{
		cout << numVertice << " " << numAresta << "\n";
	}
};

//=====================================================================
// CLASSE GRAFO POR MATRIZ DE ARESTAS
//=====================================================================
class GrafoMat : public Grafo
{
private:	
	Peso matriz[MAX_VERTICE][MAX_VERTICE];

public:
	GrafoMat() : Grafo() {
		excluirTodasArestas();
	}

	void setAresta(Vertice v1, Vertice v2, Peso p){
		matriz[v1][v2] = p;
	}

	Peso getAresta(Vertice v1, Vertice v2){
		return (matriz[v1][v2]);
	}
};

//=====================================================================
// CLASSE GRAFO POR LISTA DE ARESTAS
//=====================================================================
class GrafoLista : public Grafo {
private:

public:
	GrafoLista() : Grafo() {
		excluirTodasArestas();
	}

	void setAresta(Vertice v1, Vertice v2, Peso p){
		;
	}

	Peso getAresta(Vertice v1, Vertice v2){
		;
	}
};


//=====================================================================
// FUNCAO PRINCIPAL
//=====================================================================
int main(int argc, char **argv)
{

	GrafoMat *g = new GrafoMat();

	while (g->lerGrafo() == true)
	{
		//g->imprimeInfoGrafo();
		g->imprimir();
		//g->imprimeNumVerticeAresta();
		//g->imprimirVerticeAresta();
		//g->imprimirPendenteAndIsolado();
		//g->imprimirGrauVertice(0);
		//g->imprimirIsGrafoNulo();
		// g->imprimirIsPendente();
		//g->caixeiro();
		//g->buscaProfunda();
		//g->buscaLargura();
		g->imprimeBipartite();
		delete g;
		g = new GrafoMat();
	}

	delete g;

	return 0;
}//--------------------------------------------------------------------
