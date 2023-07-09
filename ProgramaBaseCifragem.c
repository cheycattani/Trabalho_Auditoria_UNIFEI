/********************************************************
*  Nome: Cheyenne Cattani Pereira   Matrícula: 2021001943 *
*  Para compilar gcc ProgramaBaseCifragem.c -o cifragem *
*  Para executar ./cifragem                             *
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MD5_IMPLEMENTATION

#include "md5.h"
#include "encrypt.h"

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

  // Limpar a memória
  memset(Leitura, 0, 1000);

  // Leitura do arquivo
  fread (Leitura, 1, 1000, ArquivoEntrada);

  // Função Hash
  char Hash[16] = {};
  md5String(Leitura, (uint8_t *)Hash);

  // Separando memória para colocar a mensagem com a concatenação
  char PonteiroConcatenacao[1016] = {};

  // Conteudo da mensagem + hash 
  strcpy(PonteiroConcatenacao, Leitura);
  strcat(PonteiroConcatenacao, Hash);

  FILE *MensagemComHash = fopen("ArquivoMensagemComHash.txt", "wb");
  fwrite(PonteiroConcatenacao, 1, 1016, MensagemComHash);
  fclose(MensagemComHash);

  MensagemComHash = fopen("ArquivoMensagemComHash.txt", "rb");

  if (!ArquivoSaida) {
    printf("Não foi possível abrir o arquivo de saída\n");
    return 1;
  }

  do 
  {
    count = fread(data, 1, TAM, MensagemComHash);
    if(count!=0)
    {
      Encrypt(data, key, count);
      fwrite(data, count, 1, ArquivoSaida);
    }
  } while(!feof(MensagemComHash));

    fclose(MensagemComHash);
    fclose(ArquivoSaida);
    fclose(ArquivoEntrada);
    
    return 0;
}
