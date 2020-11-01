#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){

  FILE *entradaA, *entradaB, *saida;
  int tamanho, tamanhoRegistro, cA, cB, posicao, linhasRegistroB, inicio, fim, inicioGlobal, finalGlobal, meio, meioTeste;
  int testeInicio, linhaAtual;

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


  inicio = 1;
  // Contando a quantidade de linhas do arquivo B
  fseek(entradaB, 0, SEEK_END);
  finalGlobal = ftell(entradaB);
  fim = finalGlobal;

  // Rebobinando
  inicioGlobal = fseek(entradaB, 0, SEEK_SET);

  printf("O final do arquivo está em %d\n", fim);

  linhasRegistroB = ((fim)/sizeof(Registro));
  fim = linhasRegistroB;
  printf("A quantidade total de linhas do arquivo B é igual a %d\n", linhasRegistroB);
  
  
  meio = (inicio + fim)/2;

    printf("O meio do arquivo está em %d\n", meio);

  






  while (cA > 0)
  {
    
    if(strncmp(regA.cpf, regB.cpf, 11) == 0){
      fwrite(&regA, tamanhoRegistro, 1, saida);
      cA = fread(&regA, tamanhoRegistro, 1, entradaA);
    }else if(strncmp(regA.cpf, regB.cpf, 11) < 0){
      cA = fread(&regA, tamanhoRegistro, 1, entradaA);
    }else{





      while (cB > 0){

        // Pula para a linha intermediária
        printf("O meio esta em %d\nO inicio esta em %d\nO fim esta em %d\n", meio, inicio, fim);

        fseek(entradaB, (meio - 1) * tamanhoRegistro + (meio - 1) + 1 , SEEK_SET);
        printf("O ftell de B está  em %d\n", ftell(entradaB));



        cB = fread(&regB, tamanhoRegistro, 1, entradaB);

        printf("ID do candidatosA.dat: %s\n", regA.id_inscricao);
        printf("ID do candidatosB.dat: %s\n", regB.id_inscricao);

        if(strncmp(regA.cpf, regB.cpf, 11) > 0){
          inicio = meio + 1;
          fim = linhasRegistroB;
          meio = (inicio + fim)/2;
          
          if(inicio == fim){
            printf("CPF nao encontrado\n");
            break;
            inicio = inicioGlobal;
            fim = linhasRegistroB;
          }

        }else if(strncmp(regA.cpf, regB.cpf, 11) < 0){
          fim = meio - 1;
          meio = (inicio + fim)/2;
          
          if(meio == 0){
            printf("CPF nao encontrado\n");

            inicio = 1;
            fim = linhasRegistroB;

            break;
          }

        }else{
          printf("CPF encontrado!");
          fwrite(&regA, tamanhoRegistro, 1, saida);

          
          goto proximoA;


        }

        
      }
      proximoA:
      fseek(entradaA, 2, SEEK_CUR);
      printf("ftell(entradaA): %d\n", ftell(entradaA));
      cA = fread(&regA, tamanhoRegistro, 1, entradaA);
      printf("Proximo regA lido: \n");
      printf(regA.id_inscricao);
      printf("\n");
    }

    
  }
  


  return 0;
}