#include <stdio.h>
#include <string.h>

int main(){

  FILE *entrada, *saida;

  int c, caux, linhac = 1;

  struct _Registro{
    char id_inscricao[4];
    char curso[20];
    char cpf[15];
    char dataNascimento[11];
    char sexo;
    char email[40];
    char opcaoQuadro[1];
  };

  typedef struct _Registro Registro;

  Registro r, raux;

  // char buffer[sizeof(Registro)];

  entrada = fopen("candidatos.dat", "r");
  saida = fopen("candidatos2.dat", "w");

  c = fread(&r, 1, sizeof(Registro), entrada);

  raux = r;

  //Auxiliar percorre a próxima linha, para fazer comparações com o leitor auxiliar
  fseek(entrada, 2, SEEK_CUR);
  c = fread(&r, 1, sizeof(Registro), entrada);


  while(c > 0){

    //Se for o último ou único registro do(a) candidato(a), copiar para o registro para o arquivo candidatos2.dat

    printf("\n");
    printf("CPF:\n");
    printf(raux.cpf);
    printf("\n");
    printf(r.cpf);

    if(strncmp(raux.cpf, r.cpf, 11) == 0){

      if(raux.id_inscricao > r.id_inscricao){
        fseek(entrada, 2, SEEK_CUR);
        c = fread(&r, 1, sizeof(Registro), entrada);
      }else{
        raux = r;
        fseek(entrada, 2, SEEK_CUR);
        c = fread(&r, 1, sizeof(Registro), entrada);
      }

    }else{
      fwrite(&raux, 1, sizeof(Registro), saida);
      fprintf(saida, "%s", "\n");
      raux = r;
      fseek(entrada, 2, SEEK_CUR);
      c = fread(&r, 1, sizeof(Registro), entrada);
    }

  }

  fwrite(&raux, 1, sizeof(Registro), saida);
  fprintf(saida, "%s", "\n");


}