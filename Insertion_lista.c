/*LISTA DUPLAMENTE ENCADEADA, com funcao INSERTION SORT */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _produto{
	int codigo;
	char prod[20];
	float preco;
	int qtde;
}TpProduto;
typedef struct _nodo{
	TpProduto info;
	struct _nodo *next;
	struct _nodo *prev;
}TpNodo;
typedef struct _lista{
	int nItens;
	TpNodo *first;
	TpNodo *last;
}TpLista;
int insere(TpLista *lista, TpNodo *nodo);//Insere sem ordenar
int insere(TpLista *lista, TpNodo *nodo){
	TpNodo *atual;
	if(lista->first==NULL){//if para 1° elemento da lista,
		lista->first=nodo;
		lista->last=nodo;
		nodo->next=NULL;
		nodo->prev=NULL;
		return 1;
	}
	
	if(lista->first!=NULL){
		atual=lista->last;
		atual->next=nodo;
		lista->last=nodo;
		nodo->next=NULL;
		nodo->prev=atual;
			return 1;
	} 
	return 0;
}
void Insertion (TpLista *lista);//funcao INSERTION SORT.
void Insertion (TpLista *lista) {
	TpNodo *perc, *aux;
	int acod,apreco,aqtde;
	char nome[30];
	for (perc=lista->first->next; perc!=NULL; perc=perc->next) {//perc apronta sempre um a frente do aux;
		aux=perc->prev;
		acod=perc->info.codigo;
		apreco=perc->info.preco;
		aqtde=perc->info.qtde;
		strcpy(nome,perc->info.prod);
		while(aux!=NULL &&  acod < aux->info.codigo){
			aux->next->info.codigo = aux->info.codigo;
			aux->next->info.preco = aux->info.preco;
			aux->next->info.qtde = aux->info.qtde;
			strcpy(aux->next->info.prod,aux->info.prod);
			aux=aux->prev;
		}
		if(aux==NULL){//se for null, eh porque eh o primeiro da lista, e aux eh redirecionado para ele. 
			aux=lista->first;
			aux->info.codigo = acod;
			aux->info.preco = apreco;
			aux->info.qtde = aqtde;
			strcpy(aux->info.prod,nome);
		} else {//se nao for, nao precisa redirecionar
			aux->next->info.codigo = acod;
			aux->next->info.preco = apreco;
			aux->next->info.qtde = aqtde;
			strcpy(aux->next->info.prod,nome);
		}	
	}		
}

void exclui(TpLista *lista, int index);
void exclui(TpLista *lista, int index){
	TpNodo *anterior, *atual;
	for(atual=lista->first;atual->info.codigo<index && atual->next!=NULL;atual=atual->next){
			anterior=atual;
	
	}
	if(atual->info.codigo==index){
			if(lista->first==atual){
				lista->first=atual->next;
			} else {
				anterior->next=atual->next;
			}
			free(atual);
			lista->nItens--;
			printf("\n### PRODUTO EXCLUIDO COM SUCESSO ###\n");
	} else {
		
			printf("\n### PRODUTO NAO EXCLUIDO, CODIGO NAO EXISTE ###\n");
	}
		
}
void imprime(TpLista *lista, TpNodo *nodo);
void imprime(TpLista *lista, TpNodo *nodo){
	TpNodo *aux;
	printf("\n*** PRODUTOS INCLUIDOS NA LISTA (Total de %d) ***\n",lista->nItens);
	for(aux=lista->first;aux!=NULL;aux=aux->next){
		printf("\nCodigo: %d",aux->info.codigo);
		printf("\nProduto: %s",aux->info.prod);
		printf("Quantidade: %d",aux->info.qtde);
		printf("\nPreco: R$ %.2f\n",aux->info.preco);
	}	
}
int main() {
	TpLista *lista;
	TpNodo *nodo;
	int opc,opc2,exc;
	lista=(TpLista*)malloc(sizeof(TpLista));
	nodo=(TpNodo *)malloc(sizeof(TpNodo));
	lista->first=lista->last=NULL;
	lista->nItens=0;
	do {
		printf("\nEscolha a opcao:\n1-Inserir\n2-Excluir\n3-Listar\n4- Insertion");
		scanf("%d",&opc);
		switch(opc){
			case 1:
				lista->nItens++;
				nodo=(TpNodo *)malloc(sizeof(TpNodo));
				nodo->next=NULL;
				printf("\nDigite os dados do produto:\n");
				printf("\nCodigo: ");
				scanf("%d",&nodo->info.codigo);
				getchar();
				printf("\nNome: ");
				fgets(nodo->info.prod,20,stdin);
				printf("\nQuantidade: ");
				scanf("%d",&nodo->info.qtde);
				printf("\nPreco: ");
				scanf("%f",&nodo->info.preco);
				if(insere(lista,nodo)){
					printf("\n*** Produto inserido com sucesso ***\n");
				} else {
					printf("\n### Produto nao inserido, verifique ###\n");
				}
				break;
			case 2:
				printf("\nDigite o codigo do produto que deseja excluir: \n");
				scanf("%d",&exc);
				exclui(lista,exc);
				break;
			case 3:
				imprime(lista,nodo);
				break;
			case 4:
				Insertion(lista);
				imprime(lista,nodo);
				break;
			default:
				printf("\nOpcao Invalida : VERIFIQUE\n");
		}
		printf("\nDeseja continuar : 1-SIM ou 2-NAO\n");
		scanf("%d",&opc2);
	}while(opc2!=2);
	return 0;
}
