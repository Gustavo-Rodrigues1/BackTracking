# BackTracking
Resolvedor de labirintos por meio de BackTracking, com duas lógicas diferentes, uma recursiva e outra interativa
O projeto lê arquivos no seguinte formato:

*quantidade de labirintos a serem resolvidos*
*largura do labirinto* *Altura do labirinto*
*labirinto*
 
#Exemplo
2
4 3
1 1 0 1
1 X 0 1
1 1 1 1
5 6
1 1 1 1 1
1 0 0 0 0
1 1 1 0 1
1 0 0 0 1
1 X 1 0 1
1 1 1 1 1

O 1 representa uma parede, o 0 representa um caminho válido, um 0 na borda do labirinto é uma saída e o X representa o local de ínicio onde o rato começa.
O código irá imprimir todos os movimentos que o rato irá fazer até achar a saída e caso o labirinto não possua uma saída ele imprime que não possui saida.
Na impressão dos movimentos ele mostra quais movimentos são de determinado labirinto L e suas codernadas. 

#Formato de saída
INI@i,j é o ínicio X na posição i,j 
F->i,j é movimento de Frente 
D->i,j movimento para direita 
E->i,j movimento da Esquerda 
T->i,j movimento para Trás 
BT@i,j->z,y significa BackTracking, ou seja, ele encontrou um beco sem saída e tentará procurar outro caminho, ele está na posição i,j e voltou para uma posição anterior z,y
FIM@i,j significa que ele achou uma saída, caso ele não ache ele irá imprimir FIM@-,-
