#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#define tam 5

int dist(int x,int y){
    int distancia = abs(x-3)+abs(y-4);
    return distancia;
}

int main()

{
    
    int v[2]={0,0},v_ant[2]={0,0};
    char movimento;
    char linha1[tam][tam]={{'.','.','.','#','.'},
                        {'.','#','.','#','.'},
                        {'.','#','.','.','.'},
                        {'.','.','.','#','G'},
                        {'.','#','.','.','.'}
        
    };
    
    
    while (1){
        
        for(int i = 0; i<tam; i++){
            for(int j=0;j<tam;j++){
            if(i==v[0]&&j==v[1])
                printf("S ");
                
            else
                printf("%c ", linha1[i][j]);
            }
            printf("\n");
        }
        if(linha1[v[0]][v[1]]=='G')
        {
            printf("\nchegou");
            break;
        }

    scanf("\n %c", &movimento);
    printf("===============================\n");
    v_ant[0]=v[0];
    v_ant[1]=v[1];

        switch(movimento){
            case 'w':
                v[0]--;
                break;
            case 's':
                v[0]++;
                break;
            case 'a':
                v[1]--;
                break;
            case 'd':
                v[1]++;
                break;
            case 'q':
                printf("programa terminado");
                exit(1);
            
        }
            if(linha1[v[0]][v[1]]=='#'||v[0]<0||v[1]<0||v[0]>=5||v[1]>=5){
            v[0]=v_ant[0];
            v[1]=v_ant[1];
            printf("movimento invalido\n");
            }
    printf("a distancia eh: %d\n",dist(v[0],v[1]));


    }

    return 0;

}
