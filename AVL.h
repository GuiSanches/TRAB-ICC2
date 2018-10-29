#define true 1
#define false 0

typedef int bool;

typedef struct aux {
	int chave;
	int valor;
	struct aux *esq;
	struct aux *dir;	
	int h;	
} NO, *PONT_r;

PONT_r inicializa();
int max(int a, int b);
int altura(PONT_r r);
PONT_r direita(PONT_r r);
PONT_r esquerda(PONT_r r);
PONT_r esquerdaDireita(PONT_r r);
PONT_r direitaEsquerda(PONT_r r);
PONT_r criaNo(int ch, int valor);
PONT_r insere(PONT_r PONT_r, int ch, int valor);
PONT_r busca_arvore(PONT_r r, int ch, int*);
PONT_r delete(PONT_r raiz, int ch);
int balanceamento(PONT_r r);
PONT_r minValorNo(PONT_r r);
PONT_r remove_no(PONT_r r, int ch);
