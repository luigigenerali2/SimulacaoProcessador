struct tpReg {
	int ut, prioridade, processador;
	char nome[100], processo[100];
};

struct tpProcesso {
	tpReg registro;
	tpProcesso *prox, *ant;
};

struct tpDescProcesso {
	tpProcesso *inicio, *fim;
	int quant;
};

struct tpProcessador {
	tpProcessador *prox, *ant;
	tpDescProcesso listaProcesso;
	tpReg processando;
	int quantI, quantGDE, quantGDI, quantD, quantL;
};

struct tpDescProcessador {
	tpProcessador *inicio, *fim;
	int quant;
};


tpProcesso *novoProcesso(tpReg registro) {
	tpProcesso *processo;
	processo = new tpProcesso;
	
	processo->registro = registro;
	processo->prox = processo->ant = NULL;

	return processo;
}

void inicializarListaProcesso(tpDescProcesso &listaProcesso) {
	listaProcesso.fim = listaProcesso.inicio = NULL;
	listaProcesso.quant = 0;
}

tpProcessador *novoProcessador() {
	tpProcessador *processador;
	processador = new tpProcessador;
	
	processador->quantD = processador->quantGDE = processador->quantGDI = processador->quantI = processador->quantL = 0;
	processador->prox = processador->ant = NULL;
	processador->processando.ut = 0;
	inicializarListaProcesso(processador->listaProcesso);
	
	return processador;
}

void inicializarListaProcessador(tpDescProcessador &listaProcessador) {
	listaProcessador.fim = listaProcessador.inicio = NULL;
	listaProcessador.quant = 0;
}

tpReg retirarInicioListaProcesso(tpDescProcesso &listaProcesso) {
	tpReg removido;
	tpProcesso *aux;
	removido = listaProcesso.inicio->registro;
	
	aux = listaProcesso.inicio;
	listaProcesso.inicio = listaProcesso.inicio->prox;
	
	if(listaProcesso.inicio != NULL)
		listaProcesso.inicio->ant = NULL;
	
	delete(aux);
	listaProcesso.quant--;
	return removido;
}

tpReg elementoInicioListaProcesso(tpDescProcesso listaProcesso) {
	return listaProcesso.inicio->registro;
}

tpReg elementoFinalListaProcesso(tpDescProcesso listaProcesso) {
	return listaProcesso.fim->registro;
}

char vaziaListaProcesso(tpDescProcesso listaProcesso) {
	return listaProcesso.inicio == NULL;
}

void inserirOrdenadoProcesso(tpDescProcesso &listaProcesso, tpReg registro) {
	tpProcesso *processo, *processoAux;
	processo = novoProcesso(registro);
	
	if(listaProcesso.inicio == NULL) {
		listaProcesso.inicio = listaProcesso.fim = processo;
	}
	else {
		// Insere processo no final
		listaProcesso.fim->prox = processo;
		processo->ant = listaProcesso.fim;
		listaProcesso.fim = processo;
		
		while(processo->ant != NULL && processo->registro.prioridade < processo->ant->registro.prioridade) {
			
			// Troca final
			if(processo->prox == NULL) {
				// Troca inicio
				if(processo->ant->ant == NULL) {
					processo->ant->prox = NULL;
					processo->prox = processo->ant;
					processo->ant->ant = processo;
					processo->ant = NULL;
					listaProcesso.inicio = processo;
				}
				else {
					processo->ant->ant->prox = processo;
					processo->ant->prox = NULL;
					processoAux = processo->ant->ant;
					processo->ant->ant = processo;
					processo->prox = processo->ant;
					processo->ant = processoAux;
				}
				listaProcesso.fim = processo->prox;
			}
			// Troca apenas o inicio
			else if(processo->ant->ant == NULL) {
				processo->ant->prox = processo->prox;
				processo->prox->ant = processo->ant;
				processo->ant->ant = processo;
				processo->prox = processo->ant;
				processo->ant = NULL;
				listaProcesso.inicio = processo;
				
			}
			// Troca comum
			else {
				processo->ant->ant->prox = processo;
				processo->prox->ant = processo->ant;
				processo->ant->prox = processo->prox;
				processo->prox = processo->ant;
				processo->ant = processo->ant->ant;
				processo->prox->ant = processo;
			}
		}
	}
	listaProcesso.quant++;
}

void inserirProcessador(tpDescProcessador &listaProcessador) {
	tpProcessador *processador;
	processador = novoProcessador();

	if(listaProcessador.inicio == NULL) {
		listaProcessador.fim = listaProcessador.inicio = processador;
	}
	else {
		listaProcessador.fim->prox = processador;
		processador->ant = listaProcessador.fim;
		listaProcessador.fim = processador;
	}
	
	listaProcessador.quant++;
}

tpProcessador *retornaProcessador(tpDescProcessador &listaProcessador, int numProcessador) {
	tpProcessador *processador = listaProcessador.inicio;
	for(int i = 1; i < numProcessador; i++) {
		processador = processador->prox;
	}
	return processador;
}

void exibeLista(tpProcesso *listaProcesso,int &cont) {
	int C,L=14,i=0;
	if(cont==1)
	{
		while(listaProcesso && i < 10){
			gotoxy(9,L+i);
			printf("%s",listaProcesso->registro.nome);
			i++;
			listaProcesso=listaProcesso->prox;
		}
	}
	if(cont==2)
	{
		while(listaProcesso && i < 10){
			gotoxy(37,L+i);
			printf("%s",listaProcesso->registro.nome);
			i++;
			listaProcesso=listaProcesso->prox;
		}
	}
	if(cont==3)
	{
		while(listaProcesso && i < 10){
			gotoxy(67,L+i);
			printf("%s",listaProcesso->registro.nome);
			i++;
			listaProcesso=listaProcesso->prox;
		}
	}
	if(cont==4)
	{
		while(listaProcesso && i < 10){
			gotoxy(92,L+i);
			printf("%s",listaProcesso->registro.nome);
			i++;
			listaProcesso=listaProcesso->prox;
		}
	}
	cont++;
}

