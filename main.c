#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>

void menu(PONT_r);

int main() {
	PONT_r AVL;
	AVL = inicializa();
	menu(AVL);	
	return 0;
}

void menu(PONT_r AVL) {
	int op, ch, valor;
	int nivel;
	while(1) {
		printf("Digite uma opcao: <1>Incluir um elemento na arvore(1). <2>Remover um elemento(2)\n"
				"<3>Buscar um elemento(3). <4>Sair do programa(4)\n"
				"Opcao: ");
		scanf(" %d", &op);

		switch(op) {
			case 1:
				printf("Para inserir um elemento digite sua chave e valor\n"
						"Chave: ");
				scanf(" %d", &ch);
				printf("Valor: ");
				scanf(" %d", &valor);
				AVL = insere(AVL, ch, valor);			
		break;
			case 2:
				printf("Para remover um elemento digite sua chave\n"
						"Chave: ");
				scanf(" %d", &ch);
				AVL = remove_no(AVL, ch);
		break;
			case 3:				
				printf("Para buscar um elemento digite sua chave\n"
						"Chave: ");
				scanf(" %d", &ch);
				PONT_r aux = busca_arvore(AVL, ch, &nivel);				
				if(aux != NULL){					
					printf("Valor(%d) Nivel(%d)\n", aux->valor, nivel);
				}
		break;
			case 4:
				exit(1);
		break;
			default:
			printf("Opcao Invalida");
		break;
		}
	/*Descomente estas linhas para limpar a tela no final de cada operacao*/
	//system("pause");
	//system("cls");	
	}	
}