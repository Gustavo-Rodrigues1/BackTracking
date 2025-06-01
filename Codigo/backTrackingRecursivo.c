#include <stdio.h>
#include <stdint.h>

//Seguindo a proposta da atividade estipulada pelo professor o tamanho máximo do labirinto é de 100 por 100
#define MAX 100

char labirinto[MAX][MAX];
int numeroDeLabirintos, linhas, colunas;
FILE *input;
FILE *output;

//Struct para simplificar a posição no labirinto
typedef struct
{
    int x, y;
} Ponto;

//função para verificar se o caminho é valido ou se é uma parede
int CaminhoValido(int x, int y)
{
return (x >= 0 && x < linhas && y >= 0 && y < colunas && (labirinto[x][y] == '0' || labirinto[x][y] == 'X'));
}

//função para verificar se está em uma saída, 0 na borda de um labirinto
int VerificaSaida(int x, int y, Ponto inicial)
{
    return (x == 0 || y == 0 || x == linhas - 1 || y == colunas - 1) && labirinto[x][y] == '0' && !(x == inicial.x && y == inicial.y);
}

//função que contém a lógica do backtracking
int buscar_saida(int x, int y, Ponto inicial)
{
    if (!CaminhoValido(x, y))
        return 0;
    if (VerificaSaida(x, y, inicial))
    {
        fprintf(output, "FIM@%d,%d\n", x, y);
        return 1;
    }
    if (labirinto[x][y] == '0' || labirinto[x][y] == 'X') labirinto[x][y] = '1'; // Só marca se for caminho livre// Marca como visitado
   // Movimentos: DIREITA, FRENTE, ESQUERDA, TRAS
  int dx[] = {0, -1, 0, 1};
  int dy[] = {1, 0, -1, 0};
  char movimentos[] = {'D', 'F', 'E', 'T'};

    for (int i = 0; i < 4; i++) {
        int novoX = x + dx[i];
        int novoY = y + dy[i];

        if (CaminhoValido(novoX, novoY)) {
            fprintf(output, "%c->%d,%d|", movimentos[i], novoX, novoY); // Registra o movimento

            if (buscar_saida(novoX, novoY, inicial)) {
                return 1; // Se encontrou saída, retorna sucesso
            } else {
                fprintf(output, "BT@%d,%d->%d,%d|", novoX, novoY, x, y); // Backtracking
            }
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    if (input == NULL || output == NULL)
    {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    Ponto inicial;
  // leitura dos labirintos
    fscanf(input, "%d", &numeroDeLabirintos);

    for (int i = 0; i < numeroDeLabirintos; i++)
    {
        
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
                    fprintf(output, "L%d:INI@%d,%d|", i, inicial.x, inicial.y);
                }
            }
        }

        if (!buscar_saida(inicial.x, inicial.y, inicial))
        {
            fprintf(output, "FIM@-,-\n");
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}
