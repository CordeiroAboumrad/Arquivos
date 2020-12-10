// Aluno: Jean Pierre Cordeiro Aboumrad
#include<stdio.h>
#include<string.h>

int main(int argc, char** argv){
  FILE *entrada;
  int caract, posicao, tamanhoArquivo, qtdeRegistros, meio, fim;
  int flagEncontrado=0;
  int inicio=0;

  int numRua=73-1, numBairro=145-73, numCidade=217-145, numEstado=289-217, numSigla=291-289, numCEP=299-291, numLixo=301-299;

  typedef struct _Endereco{
    char rua[numRua];
    char bairro[numBairro];
    char cidade[numCidade];
    char estado[numEstado];
    char sigla[numSigla];
    char cep[numCEP];
    char lixo[numLixo];
  } Endereco;

  if(argc!=1){
    "Informe o CEP desejado (digite somente os números):\n";
  }

  Endereco e;
  printf("argv[1]: %s\n", argv[1]);

  entrada = fopen("cep_ordenado.dat","r");
  if(!entrada){
    printf("Arquivo não encontrado.");
    return 1;
  }

  fseek(entrada,0,SEEK_END);
  tamanhoArquivo=ftell(entrada);
  rewind(entrada);

  qtdeRegistros=tamanhoArquivo/sizeof(Endereco);

  fim=qtdeRegistros - 1;

  printf("Número de registros: %d\n", qtdeRegistros);
  printf("inicio: %d\nfim:%d\n", inicio, fim);


  while(inicio <= fim && flagEncontrado == 0){
    meio=(inicio + fim)/2;

    posicao = meio*sizeof(Endereco);
    printf("inicio:%d\nmeio: %d\nfim:%d\n", inicio, meio, fim);

    fseek(entrada,posicao,SEEK_SET);
    //printf("Posicao atual: %d\n", ftell(entrada));
    fread(&e, 1, sizeof(Endereco), entrada);
    //printf("e.cep: %d\ninicio: %d\nmeio: %d\nfim: %d", e.cep, inicio, meio, fim);
    printf("e.cep: %s\n", e.cep);

    if(strncmp(e.cep, argv[1], 8) == 0){
      printf("Endereco encontrado!\nRua: %.72s\nBairro: %.72s\nCidade: %.72s\nEstado: %.72s\nSigla: %.2s\nCEP: %.8s\n",e.rua, e.bairro, e.cidade, e.estado, e.sigla, e.cep);
      flagEncontrado = 1;
    }else if(strncmp(e.cep, argv[1], 8) > 0){
      fim = meio - 1;
    }else{
      inicio = meio + 1;
    }
    

  }

  if(flagEncontrado != 1){
    printf("Endereço não encontrado.");
  }

  fclose(entrada);


  return 0;
}