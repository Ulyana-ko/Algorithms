#include <stdio.h>

int s_in_ar(int * ar, int s, int n){
    for(int i = 0; i < n; i++)
        if (ar[i] == s)
            return 1;
    return 0;
}

int DFS(int (*mas)[2], int * W, int i, int res, int n, int l){
    W[i-1] = i;
    for (int j = 0; j < n; j++){
        if(mas[j][0] == i){
            if(!s_in_ar(W,mas[j][1],l)){
                res++;
                res = DFS(mas,W,mas[j][1],res,n,l);
            }

        }
    }
    return res;
}

int main(int argc, char * argv[]) {
    FILE * f = fopen(argv[1], "r");
    FILE * f2 = fopen(argv[2], "w");
    if (f == NULL)
        return -1;
    int num_of_tops;
    fscanf(f, "%d", &num_of_tops);
    int num_of_edge;
    fscanf(f, "%d", &num_of_edge);
    int length = 0;
    int mas[num_of_edge*2][2];
    while (!(feof(f))) {
        fscanf(f, "%d %d", &mas[length][0], &mas[length][1]);
        length++;
    }

    int W[num_of_tops];
    for(int i = 0; i < num_of_tops; i++)
        W[i] = 0;

    int res = DFS(mas, W, 1,0,length,num_of_tops);

    for(int i = 0; i < num_of_tops; i++)
        if(W[i] == 0)
            res = -1;
    fprintf(f2,"%d", res);

    fclose(f);
    fclose(f2);
    return 0;
}
