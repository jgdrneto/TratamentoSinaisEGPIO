# **README DO PROJETO DA ATIVIDADE 2**


## **Alunos:**
### Débora Emili Costa Oliveira (Email: emilli.costa@hotmail.com).
### José gameleira do Rêgo Neto (Email: jgdrneto@gmail.com).

## **Professor:**
### Edgard de Fari Correa
### Ivanovitch Medeiros Dantas Da Silva 


## **Descrição:**

1.Executar programa que em execução (processo) consuma de forma crescente um determinado recurso (CPU, memória, etc.)

2.	Usar GPIOs da BeagleBoneBoard para sinalizar, através de LEDs, o percentual de uso desse(s) recurso(s):
	
	> LED verde acende se até 25% do recurso estiver sendo usado;
	> LED amarelo acende se o uso do recurso estiver entre 25% e 50%;
	> LED vermelho acende se o uso do recurso estiver entre 50% e 75%;
	> Acima de 75% todos os LEDs ficarão piscando.

3.	Quando o recurso tiver ultrapassado os 75% um "botão do pânico"
deve ser acionado e o processo que estiver causando o aumento do
uso do recurso deverá ser terminado.

4.	Ao ser acionado o botão do pânico todos os LEDs ficarão apagados
por "X" segundos e depois segue a lógica citada.

## **Importação:**

* Para compilar use *g++ -Wall -std=c++11 Main.cpp -o princ*
* Para executar use *./princ*