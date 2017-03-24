//Bibliotecas
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iterator>
#include <unistd.h> 

//Classe com o nome do processo
#include "Processo.cpp"

#include "json.hpp"

#define ARQUIVO_TEMP "temp.txt"       //Nome do arquivo temporário


  /*  Decrição : Obtem um vetor de string resultante de um comando
   *
   *  @param string : Nome do arquivo
   *
   *  @return vector<string> : Vetor com string de cada linha do arquivo
   */ 
  vector<string> obterStringsDoComando(string comando){

    stringstream ss;

    ss << comando << " > " << ARQUIVO_TEMP;
      
    //Executando comando
    system(ss.str().c_str());  

    //Vetor que terá as linhas do comando
    vector<string> linhas;
    string linha; 
    ifstream file;
    //Abrindo arquivo com as informações do comando executado pelo system()
    file.open(ARQUIVO_TEMP);

    if (file.is_open()){
          
      while ( getline (file,linha) ) {
        //Adicionando linha no vetor de string
        linhas.push_back(linha);
      }
     file.close();
    } 
    
    //Retornando um vetor de string onde cada string é uma linha do resultado(no terminal) do comando system();
    return linhas;

  }


  /*  Descrição: Obter o comando para ter todos os ids dos processos
   *
   *  return string : Comando que retorna o id de todos os processos
   */
  string obterComStringProcessos(){

    //String capaz de se fazer concatenação
    stringstream ss;
    //Concatenando string para gerar o comando
    ss << "ls /proc | grep \"^[0-9]\"";
    //Atribuindo o valor da concatenação em uma string
    return ss.str();
  }

  /*  Descrição: Obter o comando para ter as informações de um determinado processo
   *  
   *  @param string : Id do processo que se deseja ter as informações  
   *
   *  return string : Comando que retorna as informações de um processo
   */
  string obterComInformacaoProcesso(string processo){

    //String no qual vai está o comando
    string comando;
    //String capaz de se fazer concatenação
    stringstream ss;
    //Concatenando string para gerar o comando
    ss << "cat /proc/" << processo << "/status";

    //Atribuindo o valor da concatenação em uma string
    return ss.str();
  }


  /*  Descrição : Imprimir a árvore em pré-ordem 
   *
   *  @param Processo& : Endereço do processo raiz
   */
  void imprimirArvore(Processo& raiz){

    //Imprimindo processo atual
    cout << "Id: " << raiz.getId() << " " << "Nome: " << raiz.getNome() << " Pai: " << raiz.getPai() << " Usuário: " << raiz.getUsuario() << endl; 

    //Iterando em todos os processos filhos
    for(Processo* p : *(raiz.getFilhos())){

      //Recursão que imprime os filhos do processo
      imprimirArvore(*(p));

    }

  }

  /*  Descrição : Buscar o processo pelo id
   *
   *  @param string : Id do processo que se deseja obter 
   *  @param vector<Processo>& : Endereço de vetor de processos de todos os processos
   *
   *  @return Processo& : Processo que se deseja buscar
   */
  Processo& buscaPorId(string id,vector<Processo>& processos){

    for(unsigned int i=0;i<processos.size();i++){
        if(id==processos[i].getId()){
          return processos[i];
        } 
    }

    return *(new Processo("-1","erro", "-1", "-1"));

  }

  /*  Descrição : Construir a árvore
   *  
   *  @param vector<Processo>& : Endereço de vetor de processos de todos os processos
   */
  void construirArvore(vector<Processo>& processos){
    
    for(unsigned int pai=0;pai<processos.size();pai++){
      for(unsigned int filho=0;filho<processos.size();filho++){
        if(processos[pai].getId() == processos[filho].getPai()){

          processos[pai].getFilhos()->push_back(&(processos[filho]));

        }
      }
    }

  }
  /*  Descrição : Função que quebra string em varias string pelo caractere de " " 
   *
   *  @param const string& : String que se deseja quebrar
   *  
   *  @return vector<string> : Vetor de string resultantes da quebra
   */

  vector<string> split(const string& str) {
      stringstream ss(str);
      return {istream_iterator<string>{ss}, istream_iterator<string>{}};
  }

  /*  Descrição : Obteem os atributos relevantes das informações  
   *
   *  @param vector<string> : Vetor com as informações brutas
   *  
   *  @return vector<string> : Vetor com as informações interpretadas 
   */
  vector<string> obterAtributos(vector<string> informacoes){
    
    //Vetor com as inforamções relevantes
    vector<string> atributos;

    //Interando entre todas as linhas do vetor das informações
    for(string s : informacoes){

      //Quebrando as informações
      vector<string> lexemas = split(s);
      
      switch(lexemas[0]){
        case "Name:" :
        case "PPid:" :
        case "Uid:" :
        case "VmData:" :
          atributos.push_back(lexemas[1]);
        break;
        default:
        break;  
      }

    }

    return atributos;
  }

  /*  Descrição : Verificar integridade das informações
   *
   *  @param vector<string> : String com todos os processos
   *
   *  @return vector<string> : String que passaram no controle de integridade 
   *
   */
  vector<string> verificarIntegridade(vector<string> processos){
    
    //Vetor resultante 
    vector<string> result;
    
    //Iterando entre todos os processos  
    for(string p : processos){

      ifstream obj;
      obj.open("/proc/"+p+"/status");

      //Aceitando apenas as strings que tem o arquivo status  
      if (obj.is_open()) {
        result.push_back(p);  
      }
      obj.close();
    }

    return result;
  }

  /*  Descrição : Obter informações do processo
   *
   *  @param string : String com id do processo
   *
   *  @return vector<string> : Obter infomrações do processo
   */
  vector<string> obterinformacoesProcesso(string processo){
    vector<string> linhas;
    
    string linha; 
    ifstream file;
    
    file.open("/proc/"+processo+"/status");
    
    if (file.is_open()){
      
      while ( getline (file,linha) ) {

        linhas.push_back(linha);

      }
     file.close();
    }else{

      vector<string> s;
      return s;
    
    } 
    
    //Resultado do comando
    return linhas;
  }

  /*  Descrição : Construir os processos
   *
   *  @return vector<Processo> : Vetor com os processo presentes no sistema operacional
   */
  vector<Processo> construirProcessos(){
    
    vector<Processo> resultado;

    //Criando processo Odin(Pai de todos)
    resultado.push_back(*(new Processo("0","OS","-1","-1")));

    //Obtendo os id de todos os processos  
    vector<string> processosString = verificarIntegridade(executarComando(obterComStringProcessos()));  

    //Iterando entre todos os ids encontrados
    for(string p : processosString){
      
      //Obter inforamções do processo  
      vector<string> informacoes = obterinformacoesProcesso(p);

      //Se existir informações sobre ele adiciona-o para o vetor resultante
      if(!informacoes.empty()){

        //Obter os atributos relevantes
        vector<string> atributos = obterAtributos(informacoes);

        if(atributos.size()==4){
          //Criando o processo
          resultado.push_back(*(new Processo(p,atributos[0], atributos[1],atributos[2], (unsigned int)0)));
        }else{

          unsigned int memoria = (unsigned int)std::stoi (str_dec,nullptr,0);

          resultado.push_back(*(new Processo(p,atributos[0], atributos[1],atributos[2], memoria)));
        }
      }
    }

    return resultado;
  }

  /*  Descrição : Verifica se existe um usuario em uma lista
   *
   *  @param vector<string> : Vetor com os usuários
   *  @param string : Usuário que se quer saber se já está no vetor
   *
   *  @return bool : Verdadeiro se io usuário está no vetor, e falso caso contrário
   */
  bool contemUsuario(vector<string> usuarios,string s ){

    for(string u : usuarios){
      if(u==s){
        return true;
      }
    }

    return false;
  }

  /*  Descrição : Obter todos os usuários distintos dos processos
   *  
   *  @param vector<Processo> : Vetor com todos os processos
   *
   *  @return vector<string> : Vetor com todos os usuários distintos do processo
   */
  vector<string> obterUsuariosDistintos(vector<Processo> processos){
    vector<string> resultado;

    //Iterando entre os processos
    for(Processo p : processos){
      //Excluindo o processo Odin(Pai de todos)
      if(p.getUsuario()!="-1"){
        //Adicionando apenas usuários que ainda não existe no vetor
        if(!contem(resultado,p.getUsuario())){
          resultado.push_back(p.getUsuario());
        }
      }
    }

    return resultado;
  }

  /*  Descrição : Contar todos os processo de um determindado usuário
   *
   *  @param string : Usuário que se deseja ver a quantidade de procesos
   *  @param vector<Processo> : Todos os processos que serão analisados
   *
   *  @return int : Quantidade de processos de um usuário 
   */

  int contarProcessosDoUsuario(string usuario, vector<Processo> processos){

    int cont=0;
    //Iterando entre todos os usuários
    for(Processo p :processos){
      //Contando apenas os que tem usuário igual
      if(p.getUsuario()==usuario){
        cont++;
      }
    }

    return cont;
  }

  /*  Descrição : Salvar os processos em um arquivo JSON
   *
   *  @param vector<Processos> : Processos que serão salvos
   */
  void salvarArvore(vector<Processo> processos){
    
    nlohmann::json j;

    //Iterando entre todos os processos
    for(Processo p : processos){

      //Ecluindo o processo Odin(pai de todos)
      if(p.getId()!="0"){    
        //Salvar as informações no fim do arquivo json 
        j.push_back(nlohmann::json{{"ID", p.getId()}, {"Nome", p.getNome()}, {"Pai", p.getPai()},{"Usuário:", p.getUsuario()},{"Meḿória Utilizada:", p.getMemoria()}});
      }
    }
    
    //Escrita do objeto representante no JSON no arquivo JSON
    std::ofstream o("arvore.json");
    o << std::setw(4) << j << std::endl;
  }

  /*  Descrição : Imprimir a árvore de processos na tela
   */
  void verArvore(){

    //Construindo todos os processos
    vector<Processo> processos = construirProcessos();

    //Construindo a árvore 
    construirArvore(processos);

    //Obtendo o número de processo que se deseja ver a árvore
    string processo = numeroDoProcesso();

    //Buscando processo pelo seu id
    Processo p = buscaPorId(processo, processos);

    //Verificando se processo existe
    if(p.getId()!="-1"){
      imprimirArvore(p);
    }else{
      cout << "Processo não existe" << endl;
    }

    //Salvando os processos em um arquivo JSON
    salvarArvore(processos);

  }

  vector<Processo> ObterProcessos(){
     
     vector<Processo> processos = construirProcessos();
     construirArvore(processos);

     return processos;
  };

  /*  Descrição : Visualizar o número de processos
   */
  void verNumerosProcessos(){

    //Definindo tempo de espera entre medições
    int tempoSleep = definirSleep();

    //Vetor com os processos
    vector<Processo> processos;

    //Vetor com os usuários
    vector<string> usuarios; 
    
    //Loop infinito para medições infinitas
    while(true){

      //COsntruindo o processo
      processos = construirProcessos();

      //Construir a árvore
      construirArvore(processos);

      cout << "Quantidade de processos totais: " << processos.size() << endl; 

      //Obtendo um vetor com todos os usuários distintos
      usuarios = obterUsuariosDistintos(processos); 

       //Iterando entre todos os usuários distintos
      for(string u : usuarios){
        cout << "Usuário: " << u << "\t Quantidade de processos: " << contarProcessosDoUsuario(u,processos) << endl;
      }

      cout << "-----------------------------------------------------------------------" << endl;
      cout << "" << endl;
      cout << "-----------------------------------------------------------------------" << endl;

      //Limpando os vetores para se ter armazenar novas medições
      processos.clear();
      usuarios.clear();

      //Função para da tempo entre interações do laço
      sleep(tempoSleep);
    }
  }
  
