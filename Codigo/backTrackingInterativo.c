#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX 100

int visitado[MAX][MAX] = {0};
char labirinto[MAX][MAX];

int numeroDeLabirintos, linhas, colunas;

FILE *input;
FILE *output;

typedef struct
{
  int x, y;
} Ponto;

int CaminhoValido(int x, int y)
{
  return (x >= 0 && x < linhas && y >= 0 && y < colunas &&
          (labirinto[x][y] == '0' || labirinto[x][y] == 'X'));
}

int VerificaSaida(int x, int y, Ponto inicial)
{
  return (x == 0 || y == 0 || x == linhas - 1 || y == colunas - 1) &&
         labirinto[x][y] == '0' && !(x == inicial.x && y == inicial.y);
}

int buscar_saida(int x, int y, Ponto inicial)
{
  Ponto pilha[MAX * MAX];
  Ponto atual = inicial;
  int topoPilha = -1;
  int saidaEncontrada = 0;

  // Empilha o ponto inicial
  pilha[++topoPilha] = atual;
  visitado[atual.x][atual.y] = 1;

  // Movimentos: DIREITA, CIMA, ESQUERDA, BAIXO
  int dx[] = {0, -1, 0, 1};
  int dy[] = {1, 0, -1, 0};
  char movimentos[] = {'D', 'F', 'E', 'T'};

  while (topoPilha >= 0)
  {
    atual = pilha[topoPilha];

    if (VerificaSaida(atual.x, atual.y, inicial))
    {
      fprintf(output, "FIM@%d,%d\n", atual.x, atual.y);
      return 1;
    }

    // Verifica próximo movimento possível
    int movimentoFeito = 0;

    for (int i = 0; i < 4; i++)
    {
      int novoX = atual.x + dx[i];
      int novoY = atual.y + dy[i];

      if (CaminhoValido(novoX, novoY) && !visitado[novoX][novoY])
      {
        fprintf(output, "%c->%d,%d|", movimentos[i], novoX,
                novoY); // Registra o movimento
        visitado[novoX][novoY] = 1;
        pilha[++topoPilha] = (Ponto){novoX, novoY};
        movimentoFeito = 1;
        break;
      }
    }
    if (!movimentoFeito)
    {
      // Backtracking: volta para posição anterior
      if (topoPilha > 0)
      {
        Ponto anterior = pilha[topoPilha-1];
        fprintf(output, "BT@%d,%d->%d,%d|", atual.x, atual.y, anterior.x, anterior.y);
      }
      topoPilha--;
    }
  }

  return 0;
}

int main(int argc, char *argv[])
{
  input = fopen(argv[1], "r");
  output = fopen(argv[2], "w");

  if (input == NULL || output == NULL)
  {
    printf("Erro ao abrir os arquivos.\n");
    return 1;
  }

  Ponto inicial;

  fscanf(input, "%d", &numeroDeLabirintos);

  for (int i = 0; i < numeroDeLabirintos; i++)
  {
    memset(visitado, 0, sizeof(visitado));
    memset(labirinto, 0, sizeof(labirinto));
    fscanf(input, "%d %d", &colunas, &linhas);

    for (int x = 0; x < linhas; x++)
    {
      for (int y = 0; y < colunas; y++)
      {
        fscanf(input, " %c", &labirinto[x][y]);
        if (labirinto[x][y] == 'X')
        {
          inicial.x = x;
          inicial.y = y;
        }
      }
    }

    fprintf(output, "L%d:INI@%d,%d|", i, inicial.x, inicial.y);
    // printf("L%d %d colunas %d linhas\n",i,colunas,linhas);
    if (!buscar_saida(inicial.x, inicial.y, inicial))
    {
      fprintf(output, "FIM@-,-\n");
    }
  }

  fclose(input);
  fclose(output);
  return 0;
}
