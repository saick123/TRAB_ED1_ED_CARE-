#include <bits/stdc++.h>
using namespace std;
// Autor: Pedro Igor
// Ccomp
/*
ATENÇÃO:
	Este gerador também cria casos de teste que a Professora Patrícia não vai cobrar,
	porém optou-se por esta decisão, pois assim temos a oportunidade de trazer robustez ao trabalho.
	
OBS:
	Não garantimos que todos os casos de testes gerados são válidos, portanto não nos responsabilizamos.
	Apenas os casos de teste fornecidos pela professora Patrícia são "100%" válidos para avaliação.
	O gerador é apenas um extra.

*/
#define MAX_TEMP	40.0001	
#define MAX_LINHAS 	1000

int Rand(int a, int b){
	return a + rand() % (b - a + 1);
}

int digits(int a){
	int qtd = 0;

	if(a == 0) return 1;

	while(a){
		a /= 10;
		qtd++;		
	}
	
	return qtd;
}

int main(int argc, char* argv[]){
	
	//ios_base::sync_with_stdio(0);	

	// Passo 1: gerar velhos e criar apoio.txt	
	srand(atoi(argv[1]));
	int k = 30;
	int dados = 100;//Rand(10, MAX_LINHAS);
	int n1 = Rand(2, k); // number of old people in the program
	
	char* s = (char*)calloc(21, sizeof(char));
	
	sprintf(s, "folder%d/apoio.txt", atoi(argv[1]));	
	
	vector<string> idosos;	

	FILE* apoio = fopen(s, "w");	
	
	if(apoio == NULL) assert(0);	
	
	int d = digits(k);

	char* str = (char*)calloc(d, sizeof(char));	
	FILE* new_idoso;	
	//Passo 2, parte 1: escrever  os nomes dos velhos 
	for(int i = 1; i <= n1; i++){
		
			
		sprintf(str, "idoso%d", i);

		idosos.push_back( string(str) );
		//Passo 4: criar arquivo do idoso	
		string s = "folder" + string(argv[1]) + "/" + string(str) + ".txt";	
		
		new_idoso = fopen(s.c_str(), "w");
			
		for(int j = 1; j <= dados; j++){
			if(Rand(1, 100) != 1) { fprintf(new_idoso, 
					"%f;%d;%d;%d\n",
				       	((float)rand()/(float)(RAND_MAX)) * MAX_TEMP,
					Rand(0, INT_MAX-1),
					Rand(0, INT_MAX-1),
					Rand(0, 1));
			}
			else {
				fprintf(new_idoso, "%s\n", "falecimento");
				break;
			}
		}	

		fclose(new_idoso);


		fprintf(apoio, "%s", str);

		if( i < n1) 
			fprintf(apoio, "%c", ';');
		else if(i == n1)
			fprintf(apoio, "%c", '\n');

		memset(str, '\0', d);	
	}

	//Passo 2, parte 2: escrever as relações dos velhos
	char* str_a = (char*)calloc(d, sizeof(char));
	char* str_b = (char*)calloc(d, sizeof(char));
	
	//Rand(2, n1)
	for(int i = 0, m = n1; i < m; i++){
			
		int temp1 = Rand(2, n1);	
		
		sprintf(str_a, "idoso%d", temp1);	
		
		//garantir que não é a mesma pessoa	
		int temp2 = Rand(2, n1);
		
		if( temp2 == temp1 ){
			if(temp2 < n1) temp2++;
			else temp2--;
		}	

		sprintf(str_b, "idoso%d", temp2);

		fprintf(apoio, "%s;", str_a);
		fprintf(apoio, "%s\n", str_b);	
		
		memset(str_a, '\0', d);
		
		memset(str_b, '\0', d);
	} // obs: pode ser que ocorra um " joao;pedro" e depois um "pedro;joao"
	  // mas isso não é errado, apenas redundante. Pois a amizade
	  // é reflexiva nesse caso (trab1)
	free(str);
	free(str_a);
	free(str_b);	
	fclose(apoio);

	int n2 = Rand(2, n1); // não faz sentido ter mais cuidadores do que idosos
	
	if(apoio == NULL) assert(0);	
	
	k = 10;

	d = digits(k);

	str = (char*)calloc(d, sizeof(char));	

	s = (char*)calloc(26, sizeof(char));
	
	sprintf(s, "folder%d/cuidadores.txt", atoi(argv[1]));		
	
	FILE* cuidadores = fopen(s, "w");
	FILE* cuidador;	
	//Passo 3, parte 1: escrever os nomes dos cuidadores 
	for(int i = 1; i <= n2; i++){
				
		sprintf(str, "cuidador%d", i);
		string s = "folder" + string(argv[1]) + "/" + string(str) + ".txt";	
		cuidador = fopen(s.c_str(), "w");

		for(int j = 1; j <= dados; j++)
			fprintf(cuidador, "%d;%d\n", Rand(0, INT_MAX-1), Rand(0, INT_MAX-1));
	
		fprintf(cuidadores, "%s", str);

		if( i < n2) 
			fprintf(cuidadores, "%c", ';');
		else if(i == n2)
			fprintf(cuidadores, "%c", '\n');

		memset(str, '\0', d);	
	}
	
	//Passo 3, parte 2: escrever os idosos (na ordem) e seus respectivos cuidadores aleatórios
	set<char*> cnr; // cuidadores não repetidos
		
	for(int i = 0; i < n1; i++){
			
		fprintf(cuidadores, "%s", idosos[i].c_str());
		fprintf(cuidadores, "%s", ";");	
		
		for(int j = 1, x = Rand(1, n2); j <= x ; j++){
			
			sprintf(str, "cuidador%d", Rand(1, n2));
			
			while( j > 1 && cnr.find(str) == cnr.end() ) {
				sprintf(str, "cuidador%d", Rand(1, n2));
			}	
			
			fprintf(cuidadores, "%s", str);
				
			if(j < x) fprintf(cuidadores, "%s",";");
				
			cnr.insert(str);
			
	
		}
		fprintf(cuidadores, "%s", "\n");

	}
			

	return 0;
}
