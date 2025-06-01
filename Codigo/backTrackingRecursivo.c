#include <stdio.h>
#include <stdint.h>

#define MAX 100

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
return (x >= 0 && x < linhas && y >= 0 && y < colunas && (labirinto[x][y] == '0' || labirinto[x][y] == 'X'));
}

int VerificaSaida(int x, int y, Ponto inicial)
{
    return (x == 0 || y == 0 || x == linhas - 1 || y == colunas - 1) && labirinto[x][y] == '0' && !(x == inicial.x && y == inicial.y);
}

int buscar_saida(int x, int y, Ponto inicial)
{
    if (!CaminhoValido(x, y))
        return 0;
    if (VerificaSaida(x, y, inicial))
    {
        fprintf(output, "FIM@%d,%d\n", x, y);
        return 1;
    }
    // exibir labirinto para verificar
    if (labirinto[x][y] == '0' || labirinto[x][y] == 'X') labirinto[x][y] = '1'; // Só marca se for caminho livre// Marca como visitado
    // for (int j = 0; j < linhas; j++)
    // {
    //     for (int c = 0; c < colunas; c++)
    //     {
    //         printf("%c ", labirinto[j][c]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    // Movimentos: F (Frente), D (Direita), T (Trás), E (Esquerda)
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

        // Exibe o labirinto corretamente
        // printf("Labirinto %d:\n", i + 1);
        // for (int j = 0; j < linhas; j++)
        // {
        //     for (int c = 0; c < colunas; c++)
        //     {
        //         printf("%c ", labirinto[j][c]);
        //     }
        //     printf("\n");
        // }
        // printf("\n");

        if (!buscar_saida(inicial.x, inicial.y, inicial))
        {
            fprintf(output, "FIM@-,-\n");
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}