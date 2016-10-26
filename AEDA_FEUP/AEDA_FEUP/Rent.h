#pragma once

/*
* Aluguer.h
*
*  Created on: 22/10/2016
*      Author: angrydodo
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;


/*
A FAZER:

1 - Implementar uma classe Data com os respetivos operadores, para conseguir extrair de uma string uma data utilizabel,
lidar com uma data invalida, e ter operadores de menor e igual para compararmos datas e facilitar a averiguacao
da validade de um aluguer.

2 - No menu, tem que haver dois tipos de acessos, um de fornecedor e outro de clientes. O Fornecedor serve para adicionar
alugueres, o de clientes para pesquisar e reservar possibilidades de acordo com os alugueres disponiveis

3 - Classes que faltam do aluguer

4 - Criar uma classe mãe de Clientes, com duas derivadas. Uma para clientes registados(com pontos) outra para esporádicos.

5 - Criar uma classe de Fornecedores, que tem um vetor de alugueres, e informacao. Mais concretamente:
" Quando um fornecedor se regista no sistema, deve incluir os seus dados (nome, NIF, morada), e a lista de ofertas
que deseja disponibilizar, com as respectivas características"

6 - Criar uma classe Empresa, que possui um vetor de clientes e outro de fornecedores. Esta vai ser a que engloba tudo,
e que vai dirigir tudo.

7 - Panisguices incrivelmente bonitas!

*/

class Aluguer
{
protected:

	// Todas estas variaveis sao comuns a todos os alugueres, por isso é que as ponho aqui

	string cidade;              // Pretty obvious, I guess
	Data dataInicio, dataFim;   // Será melhor pormos a data como float ou whatevs? Acho melhor
								// assim por causa da extracao de um istream;
								// Outra cena, é dataInicio e fim porque o fornecedor tem de explicitar
								// quais sao as datas em que o aluguer esta disponivel;

	string tipoEstadia;         // Estas duas trabalham juntas, porque o fornecedor tem de dizer quanto
	int duracaoEstadia;         // tempo uma pessoa pode ter um determinado aluguer, funcionando do género
								// "A duração do aluguer será em noites, semanas, ou meses?" , extrai para o tipoEstadia
								// "Quantos noites/semanas/meses serão? " texto varia com tipoEstadia, extrai para duracaoEstadia

	int numOcupantes;           // O numero de pessoas que vai para um determinado aluguer, (quarto duplo, triplo, etc...)

public:
	Aluguer(string c, Data dataI, Data dataF, string tipo, int d, int n);

	virtual void getNome() {}        // getNome do Hotel, nao faz sentido as outras classes terem nomes
	virtual int getNumOcupantes() {}
	Data getDataInicio() { return dataInicio; }
	Data getDataFim() { return dataFim; }
	int getDuracao() { return duracaoEstadia; }

};

Aluguer::Aluguer(string c, Data dataI, Data dataF, string tipo, int d, int n)
{
	cidade = c; dataInicio = dataI; dataFim = dataF; tipoEstadia = tipo; duracaoEstadia = d; numOcupantes = n;
}

class Hotel : public Aluguer
{
	string nomeHotel;               // Podera ser utilizado para, apos fazer sort ao vetor de aluguer, fazer display bonito
	int numOcupantes;               // Definido pelo tipo de aluguer que é
	string tipo;                    // Tipo de Quarto que quer
	float preco;
public:
	Hotel() {}
	Hotel(string c, Data dataI, Data dataF, string tipo, int d, float p, string t, int n);
	string getTipo() { return tipo; }

	string getNome() { return nomeHotel; }
	float getPreco() { return preco; }
	Hotel constroiHotel(); // Pressupostamente constroi um hotel, mas ainda tenho que pensar como implementar isto
};


Hotel::Hotel(string c, Data dataI, Data dataF, string tipo, int d, float p, string t, int n) : Aluguer(c, dataI, dataF, tipo, d, n)
{
	this->tipo = t;
	preco = p;
}

/*     NAO FUNCIONA BEM, TENHO QUE PENSAR MELHOR NESTA MERDA

Hotel Hotel::constroiHotel() // Feito para fornecedores, clientes nao escolhem nada daqui
{

Hotel h();

string x;
int n;
float f;
bool isIn = true; // Este boleano é só um sistema que usei para implementar uma deteção de erro, com possibilidade de repetição
while (isIn)
{


cout << "Qual é a cidade onde pretende disponibilizar o aluguer?\n\n";
cin >> x;
this->cidade = x;
cout << "\nQual o tipo de quarto que pretende disponibilizar? As hipóteses são:" << endl;
cout << "1 - Quarto Simples\n2 - Quarto Duplo\n3 - Quarto Duplo com cama adicional\n4 - Quarto Triplo"<< endl;
// pode levar mais panisguices aqui malta

if (n == 1)
numOcupantes = 1;
else if (n == 2)
numOcupantes = 2;
else if (n == 3)
numOcupantes = 3;
else if (n == 4)
numOcupantes = 3;
else if (inputInvalido() == true)
continue;
else  // TEM QUE AQUI VOLTAR AO MENU INICIAL, PARA CONTINUAR A FAZER FUNCOES
{
isIn = false;
return h;  // retorna hotel vazio;
break;
}
}
isIn= true;

while (isIn)
{
cout << "\nQual o preço que pretende cobrar pelo quarto?\n";
cin >> f;
if (inputInvalido() == false)
continue;
else
{
this->preco = f;
isIn = false;
break;
}
}
}
*/
