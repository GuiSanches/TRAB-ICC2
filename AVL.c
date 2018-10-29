#include "AVL.h"
#include <stdlib.h>
#include <stdio.h>
//cria uma arvore
PONT_r inicializa() {
	return NULL;
}
//retorna maior inteiro, usado pra calculo do maior caminho possivel de um no.
int max(int a, int b) {
	return a > b ? a:b;
}
//Altura de uma subarvore
int altura(PONT_r r) {
	if(!r) return(-1);
	return(r->h);
}
//Rotacao a direita: Feita se um no, causador do desbalanceamento, foi inserido na subarvore esquerda do filho a esquerda
PONT_r direita(PONT_r r) {
	PONT_r aux;
	aux = r->esq;
	//filho a esquerda de r passara a ser o filho a direita de seu filho a esquerda.
	r->esq = aux->dir;
	aux->dir = r;
	//Atualiza alturas
	r->h = max(altura(r->dir),
				  altura(r->esq)) +1;
   	aux->h = max(altura(aux->esq),
   						     r->h) +1;
   	//r passa a ser aux(filho a esquerda do r inicial)
   	return(aux);
   	//Com imagens fica muito claro essa rotacao. Para maior entendimento desenhe as estruturas
}
//Rotacao a esquerda: Feita se um no, causador do desbalanceamento, foi inserido na subarovre direita do filho a direita.
PONT_r esquerda(PONT_r r) {
	PONT_r aux;
	aux = r->dir;
	//filho a direita do r sera o filho a esquerda de seu filho a direita
	r->dir = aux->esq;
	aux->esq = r;
	//Atualiza as alturas
	r->h = max(altura(r->dir),
					altura(r->esq)) +1;
	aux->h = max(altura(aux->dir),
							r->h) +1;
	//r passara a ser aux(filho a direita do r inicial)
	return(aux);
	//Com imagens fica muito claro essa rotacao. Para maior entendimento desenhe as estruturas
}
//Rotacao esquerda-direita: Feita se um no, causador do desbalanceamento, foi inserido na subarvore direita do filho a esquerda.
PONT_r esquerdaDireita(PONT_r r) {
	//rotacao a esquerda
	r->esq = esquerda(r->esq);
	//rotacao a direita
	return(direita(r));
}
//Rotacao direita-esquerda: Feita se um no, causador do desbalanceamento, foi inserido na subarvore esquerda do filho a direita
PONT_r direitaEsquerda(PONT_r r) {
	//rotacao a direita
	r->dir = direita(r->dir);
	//rotacao a esquerda
	return(esquerda(r));
}
//Cria novo No
PONT_r criaNo(int ch, int valor) {
	PONT_r novoNo = (PONT_r)malloc(sizeof(NO));

	novoNo->esq = NULL;
	novoNo->dir = NULL;
	novoNo->chave = ch;
	novoNo->valor = valor;
	novoNo->h = 0;	
	return novoNo;
	}

/*Se a insercao que acarreta o desbalanceamento ocorrer na subarvore esquerda do filho a esquerda sera feita uma rotacao simples(direita)
Da mesma forma ocorre uma rotacao simples(esquerda) se o desbalanceamento ocorre na subarvore a direita do filho a direita. Percebe-se que rotacoes
simples ocorrem para insercoes na parte mais externa da arvore ja insercoes na parte mais interna na arvore geram rotacoes duplas(direita-esquerda, esquerda-direita).*/
PONT_r insere(PONT_r r, int ch, int valor) {
	int NOP = -1;
		
	PONT_r aux = busca_arvore(r, ch, &NOP);	
	if(!aux){		
		//Se a raiz for nula, nao ha arvore, cria-se no que sera arvore
		if(!r) return(criaNo(ch, valor));
		//Se valor a ser inserido for menor que o da raiz, sera inserido na subarvore da esquerda
		if(ch < r->chave) {
			r->esq = insere(r->esq, ch, valor);
			//Verifica se houve quebra de balanceamento
			if((altura(r->esq) -
					altura(r->dir)) == 2)
				//verifica se o desbalanceamento ocorreu nas laterais ou no centro. Lateral ocorre na insercao na subarvore da esquerda do no desbalanceado
				if(ch < r->esq->chave)
					//rotacao simples a direita
					r = direita(r);
				else
					//rotacao dupla. Esquerda direita
					r = esquerdaDireita(r);
		}else//Exatamente a mesma logica do trecho de codigo acima
			if(ch > r->chave) {
				r->dir =
						insere(r->dir, ch, valor);
				if((altura(r->dir) -
						altura(r->esq)) == 2)
					if(ch > r->dir->chave)
						r = esquerda(r);
					else
						r = direitaEsquerda(r);				
			}
		//atualiza altura da arvore
		r->h = max(altura(r->esq),
						altura(r->dir)) +1;
	}else
		aux->valor = valor;		
	return(r);
}
//Busca no na arvore e o retorna se houver
PONT_r busca_arvore(PONT_r r, int ch, int *nivel) {
	PONT_r ptrAtual = r;
	PONT_r aux = NULL;	
	int flag = 1;
	int cont = 0;	
	if(r != NULL) {
			while(flag) {										
					while( (ptrAtual->esq != NULL) && (ch < ptrAtual->chave) ) {
						ptrAtual = ptrAtual->esq;
						cont++;						
					}					
					flag = 0;			
					while( (ptrAtual->dir != NULL) && (ch > ptrAtual->chave) ) {
						ptrAtual = ptrAtual->dir;
						flag = 1;
						cont++;										
					}				
			}
			aux = ptrAtual->chave == ch ? ptrAtual:NULL;			
		}
		*nivel = cont;			
		return aux;
}
//retorna balanceamento do no. Precisa estar entre -1 e 1 para ser AVL. Cada insercao pode deixar o balanceamento em 2(necessitando de uma rotacao simples ou dupla para concertar)
int balanceamento(PONT_r r) {
	if(!r)
		return 0;
	else return altura(r->esq) - altura(r->dir);
}
//Retorna menor no(ultimo no a esquerda)
PONT_r minValorNo(PONT_r r) {
	PONT_r atual = r;

	while(atual->esq)
		atual = atual->esq;
	return atual;
}
//Remove um no dada sua chave e rebalanceia a arvore.
PONT_r remove_no(PONT_r r, int ch) {
	if(!r)
		return r;

	if(ch < r->chave)
		r->esq = remove_no(r->esq, ch);
	else if(ch > r->chave)
		r->dir = remove_no(r->dir, ch);
	else {
		if((!r->esq) || (!r->dir)) {
			PONT_r temp = r->esq ? r->esq :
								   r->dir;
			if(!temp) {
				temp = r;
				r = NULL;
			}else
				*r = *temp;
			free(temp);
		}else {
			PONT_r temp = minValorNo(r->dir);
			r->chave = temp->chave;
			r->dir = remove_no(r->dir, temp->chave);
		}
	}
	if(!r)
		return r;
	r->h = 1 + max(altura(r->esq),
					altura(r->dir));

	int balance = balanceamento(r);

	if(balance > 1 && balanceamento(r->esq) >= 0)
		return direita(r);
	if(balance > 1 && balanceamento(r->esq) < 0) {
		r->esq = esquerda(r->esq);
		return direita(r);
	}
	if(balance < -1 && balanceamento(r->dir) <= 0)
		return esquerda(r);
	if(balance < -1 && balanceamento(r->dir) > 0){
		r->dir = direita(r->dir);
		return esquerda(r);
	}
	return r;
}
