//Definições da classe
#ifndef _PORT_
#define _PORT_

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

#include "Constants.cpp"

#define TEMP "TEMP.txt"

//Classe representando as portas
class Port{
	private:
		PORTNAME name;
		std::string physicalAddress;
		VALUE value;
		DIRECTION direction;
		
		std::string PATH_GPIO = "/home/neto/gpio/";

		//FUNCTIONS

		std::string getGPIOPortNumber(std::string nAddress){
			
			std::string result;

			for(unsigned int i=4;i<nAddress.size();i++){
				
				//std::cout << "Caractere: " << nAddress[i] << std::endl;	

				result+=nAddress[i];
			}

			return result;
		}

		bool existDir(std::string nAddress){
			std::ifstream file;

			file.open(PATH_GPIO + nAddress + "/direction");

			return file.is_open();
		}

		std::vector<std::string> stringsOfFile(std::string nameFile){
			std::vector<std::string> linhas;
	  		std::string linha; 
	  		std::ifstream file;

	  		file.open(nameFile);

	  		if (file.is_open()){
	        
	    		while ( getline (file,linha) ) {
	      			
	      			linhas.push_back(linha);
	    		}
	   			file.close();
	  		}	 
	  
	  		return linhas;
		}

		void writeInFile(std::string nameFile, std::string value){
			std::vector<std::string> linhas;
	  		std::string linha; 
	  		std::ofstream file;

	  		file.open(nameFile);

	  		if (file.is_open()){
	        
	        	file << value;
	    		
	   			file.close();
	  		}	 
	  
		}		

		std::vector<std::string> executeCommand(std::string comando){

	  		system(comando.c_str());  

	  		std::vector<std::string> linhas;
	  		std::string linha; 
	  		std::ifstream file;

	  		file.open(TEMP);

	  		if (file.is_open()){
	        
	    		while ( getline (file,linha) ) {
	      			
	      			linhas.push_back(linha);
	    		}
	   			file.close();
	  		}	 
	  
	  		return linhas;
		}

	public:

		Port(){/*NULL*/};

		Port(PORTNAME nName, std::string nAddress){
			this->name = nName;
			this->physicalAddress = nAddress;
			this->value = VALUE::NVDEF;
			this->direction = DIRECTION::NDDEF;
			
			if(!existDir(nAddress) && nAddress!=NOT_PSY_ADD){
				executeCommand("echo " + getGPIOPortNumber(nAddress) + " > " + PATH_GPIO +"export");
			}

		}

		PORTNAME getPortName(){
			return this->name;
		}

		std::string getPhysicalAddress(){
			return this->physicalAddress;
		} 

		DIRECTION getDirection(){

			std::vector<std::string> v =  stringsOfFile(PATH_GPIO + this->physicalAddress + "/direction");

			if(!v.empty()){

				if(v[0]=="in"){
					this->direction = DIRECTION::IN;
				}else{
					this->direction = DIRECTION::OUT;
				}
			}

			return this->direction;
		}

		VALUE getValue(){

			std::vector<std::string> v =  stringsOfFile(PATH_GPIO + this->physicalAddress + "/value");

			if(!v.empty()){

				if(v[0]=="0"){
					this->value = VALUE::LOW;
				}else{
					this->value = VALUE::HIGH;
				}
			}

			return this->value;
		}

		void setDirection(DIRECTION nDirection){

			std::string v;
			
			if(nDirection==DIRECTION::IN){
				v="in";
			}else{
				v="out";

			}
			
			this->direction = nDirection;

			writeInFile(PATH_GPIO + this->physicalAddress + "/direction", v);

			this->direction = nDirection;
		}

		void setValue(VALUE nValue){

			std::string v;
			
			if(nValue==VALUE::LOW){
				v="0";
			}else{
				v="1";

			}

			this->value = nValue;

			writeInFile(PATH_GPIO + this->physicalAddress + "/value", v);

		}
};

#endif