#ifndef _PROCESSO_
#define _PROCESSO_

#include <string>
#include <vector>

using namespace std;

//Classe representativa de processos
class Processo{
  private:
  	//Atributos
  	string id;
  	string nome;
  	vector<Processo*> filhos;
  	string usuario;
  	string pai;
    unsigned int memoria;

  public:

    Processo(){/*NULO*/}

    /*  Descrição : Construtor da classe
     *
     *  @param string : Id do processo 
     *  @param string : Nome do processo
     *  @param string : Id do pai do processo
     *  @param string : id do usuário
     *  @param unsigned int : Memória utilizada pelo processo
     */
  	Processo(string nId,string nNome,string nPai, string nUsuario, unsigned int nMemoria){
  		this->id = nId;
  		this->nome = nNome;
  		this->pai = nPai; 
      this->usuario = nUsuario;
  	  this->memoria = nMemoria; 
    }

    /*  Descrição : Obter o id do processo
     *
     *  @return string : Id do processo
     */
  	string getId(){
  		return this->id;	
  	}

    /*  Descrição : Obter a mémoria usada pelo processo
     *
     *  @return unisgned int : Valor em KB de memória usada no processo
     */
    unsigned int getMemoria(){
      return this->memoria;  
    }

    /*  Descrição : Obter o id do pai do processo
     *
     *  @return string : Id do pai do processo
     */
  	string getPai(){
  		return this->pai;
  	}

    /*  Descrição : Obter o nome do processo
     *
     *  @return string : Nome do processo
     */
  	string getNome(){
  		return this->nome;
  	}

    /*  Descrição : Obter os filhos do processo
     *
     *  @return vector<Processo*>* : Vetor com os endereços dos filhos do processo
     */
  	vector<Processo*>* getFilhos(){
  		return &(this->filhos);
  	}

    /*  Descrição : Obter o id do usuário do processo
     *
     *  @return string : Id do usuário do processo
     */
    string getUsuario() {
      return this->usuario;
    }


    /*  Descrição : Adicionar novo pai para o processo
     *
     *  @param string : Novo id do pai do processo
     */  
    void setPai(string nPai){
      this->pai = nPai;
    }

    /*  Descrição : Adicionar novo valor de memória para o processo
     *
     *  @param string : Nova memória do processo
     */  
    void setMemoria(unsigned int nMemoria){
      this->memoria = nMemoria;
    }

     /*  Descrição : Adicionar novo id para o processo
     *
     *  @param string : Novo id do processo
     */  
  	void setId(string nId){
  		this->id = nId;
  	}

    /*  Descrição : Adicionar novo nome para o processo
     *
     *  @param string : Novo nome do processo
     */ 
  	void setNome(string nNome){
  		this->nome = nNome;
  	}

    /*  Descrição : Adicionar novo usuário para o processo
     *
     *  @param string : Novo usuário do processo
     */ 
  	void setUsuario(string nUsuario){
  		this->usuario = nUsuario;
  	}

};	

#endif