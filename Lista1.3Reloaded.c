#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){

  FILE *entradaA, *entradaB, *saida;
  int tamanho, tamanhoRegistro, cA, cB, posicao;
  int encontrado = 0, checkpoint;

  struct Registro{
    char id_inscricao[4];
    char curso[20];
    char cpf[15];
    char dataNascimento[11];
    char sexo[1];
    char email[40];
    char opcaoQuadro[1];
  };

  typedef struct Registro Registro;

  Registro regA, regB, regAux;

  tamanhoRegistro = sizeof(Registro);


  entradaA = fopen("candidatosA.dat", "r");
  entradaB = fopen("candidatosB.dat", "r");

  saida=fopen("candidatosFinal.dat", "w");

  // O arquivo A será a base, enquanto B será percorrido para achar o CPF que seja igual
  cA = fread(&regA, tamanhoRegistro, 1, entradaA);
  cB = fread(&regB, tamanhoRegistro, 1, entradaB);



  while (cA > 0)
  {
    printf("ID do candidatosA.dat: %s\n", regA.id_inscricao);
    printf("ID do candidatosB.dat: %s\n", regB.id_inscricao);

    if(strncmp(regA.cpf, regB.cpf, 11) == 0){
      fwrite(&regA, tamanhoRegistro, 1, saida);
      fprintf(saida, "%s", "\n");


      fseek(entradaA, 2, SEEK_CUR);
      cA = fread(&regA, tamanhoRegistro, 1, entradaA);

      fseek(entradaB, 2, SEEK_CUR);
      cB = fread(&regB, tamanhoRegistro, 1, entradaB);
    }else{


      
      // printf("ftell(entradaB): %d\n", ftell(entradaB));
      fseek(entradaB, 2, SEEK_CUR);
      cB = fread(&regB, tamanhoRegistro, 1, entradaB);


      while (cB > 0){

        printf("ID do candidatosA.dat: %s\n", regA.id_inscricao);
        printf("ID do candidatosB.dat: %s\n", regB.id_inscricao);


        if(strncmp(regA.cpf, regB.cpf, 11) != 0){
          
          // fseek(entradaB, 2, SEEK_CUR);
          // printf("ftell(entradaB): %d\n", ftell(entradaB));
          
          fseek(entradaB, 2, SEEK_CUR);
          cB = fread(&regB, tamanhoRegistro, 1, entradaB);

          printf("cB = %d\n", ftell(entradaB));

        }else{

          printf("CPF encontrado!");
          fwrite(&regA, tamanhoRegistro, 1, saida);
          fprintf(saida, "%s", "\n");

          fseek(entradaB, 2, SEEK_CUR);
          cB = fread(&regB, tamanhoRegistro, 1, entradaB);
          encontrado = 1;

          checkpoint = ftell(entradaB);
          
          goto proximoA;

        }

        
      }
      proximoA:
      // printf("ftell(entradaA): %d\n", ftell(entradaA));
      
      fseek(entradaA, 2, SEEK_CUR);
      cA = fread(&regA, tamanhoRegistro, 1, entradaA);
      printf("Proximo regA lido: \n");
      printf(regA.id_inscricao);
      printf("\n");


      if(encontrado == 0){

        // Indo para o último registro de B encontrado, caso nao encontre o registro de A

        fseek(entradaB, 0, SEEK_SET);

      }else{
        fseek(entradaB, checkpoint, SEEK_SET);
      }
    }

    
  }
  


  return 0;
}