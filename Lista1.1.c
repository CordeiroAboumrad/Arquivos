#include <stdio.h>



int main(int argc, char** argv){

  if(argc != 2){
    printf("Numero insuficiente de argumentos inserido. Insira o nome do arquivo a ser lido:\n");
    return 1;
  }

  FILE *entrada;
  int contadorLinha=1, contadorPalavra=1, c, flag=0;
  char caracter[1], previousLetter[1];

  // printf("Arquivo:\n");
  // printf(argv[1]);
  entrada = fopen(argv[1], "r");


  if(!entrada){
    printf("Arquivo não encontrado\n");
  }else
  // {
  //   printf("Arquivo encontrado\n");
  // }


  c = fread(caracter, sizeof(char), 1, entrada);
  //  c=fgetc(entrada);


  while(c > 0){
      // fread(buffer, 1, 1, entrada);
      // printf("%s", caracter);

      

      if(*caracter == ' '){

        if(flag == 0){

          ++contadorPalavra;
          printf("Palavra contada\n");
          flag = 1;

        }

      }else if(*caracter == '\n'){

        ++contadorLinha;
        ++contadorPalavra;
        flag = 0;
      }else{
        flag = 0;
      }

      c = fread(caracter, sizeof(char), 1, entrada);
    // c=fgetc(entrada);

  }

  fclose(entrada);
  printf("O numero de linhas do arquivo eh igual a %d e o numero de palavras eh igual a %d", contadorLinha, contadorPalavra);
  return 0;
}