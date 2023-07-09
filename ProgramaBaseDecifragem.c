/********************************************************
*  Nome: Cheyenne Cattani Pereira   Matrícula: 2021001943 *
*  Para compilar gcc ProgramaBaseDecifragem.c -o decifragem *
*  Para executar ./decifragem                             *
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MD5_IMPLEMENTATION

#include "md5.h"
#include "decrypt.h"

#define TAM 9

int main()
{
  unsigned char data[TAM], key[TAM];
  FILE *ArquivoEntrada,*ArquivoSaida;
  char NomeArquivoEntrada[30], NomeArquivoSaida[30], Leitura[1000];
  int  count;

  printf("Entre com o Nome do Arquivo Original = ");
  scanf("%s",NomeArquivoEntrada);
  printf("Entre com o Nome do Arquivo para Cifragem = ");
  scanf("%s",NomeArquivoSaida);
  printf("Entre com uma senha de 8 digitos = ");
  scanf("%s",key);
  
  ArquivoEntrada  = fopen(NomeArquivoEntrada,"rb");
  ArquivoSaida = fopen(NomeArquivoSaida,"wb"); 

  if (!ArquivoEntrada) {
    printf("Não foi possível abrir o arquivo de entrada\n");
    return 1;
  }

  if (!ArquivoSaida) {
    printf("Não foi possível abrir o arquivo de saída\n");
    return 1;
  }

  do 
  {
    count = fread(data, 1, TAM, ArquivoEntrada);
    if(count!=0)
    {
      Decrypt(data, key, count);
      fwrite(data, count, 1, ArquivoSaida);
    }
  } while(!feof(ArquivoEntrada));

    // Vai ler o arquivo descriptografado
    FILE *ArquivoDescriptografado = fopen(NomeArquivoSaida, "rb");
    char Hash[16] = {};

    char ConteudoArquivo[1016];
    fread(ConteudoArquivo, 1, 1016, ArquivoDescriptografado);

    // Pegar a Hash que está concatenada com a mensagem
    for(int i=999; i < 1016; i++){
      Hash[i-999] = ConteudoArquivo[i];
    }

    // Ler a mensagem descrip
    char Mensagem[1000];
    strncpy(Mensagem, ConteudoArquivo, 1000);

    // Hash da mensagem descrip para comparar com a hash que veio no inicio
    char MeuHash[16]={};
    md5String(Mensagem, MeuHash);

    printf("%d", strcmp(Hash, MeuHash));

    fclose(ArquivoSaida);
    fclose(ArquivoEntrada);
    
    return 0;
}