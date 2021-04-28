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
    FILE * f;
    FILE * f2;
    if (argc >= 3){
        f = fopen(argv[1], "r");
        f2 = fopen(argv[2], "w");
    }else if (argc == 2){
        f = fopen(argv[1], "r");
        f2 = fopen("output.txt", "w");
    }else{
        f = fopen("input.txt", "r");
        f2 = fopen("output.txt", "w");
    }
    if ((f == NULL)||(f2 == NULL))
        return -1;
    int s;
    fscanf(f, "%d", &s);
    int fin;
    fscanf(f, "%d", &fin);
    int num_of_tops;
    fscanf(f, "%d", &num_of_tops);
    int num_of_edge;
    fscanf(f, "%d", &num_of_edge);
    int type;
    fscanf(f, "%d", &type);
    int length = 0;
    int mas[num_of_edge*2][2];
    while (!(feof(f))) {
        fscanf(f, "%d %d", &mas[length][0], &mas[length][1]);
        length++;
    }

    int W[num_of_tops];
    for(int i = 0; i < num_of_tops; i++)
        W[i] = 0;

    int res = DFS(mas, W, s,0,length,num_of_tops);

    if (s_in_ar(W,fin,num_of_tops))
        fprintf(f2,"%d", 1);
    else
        fprintf(f2,"%d", 0);

    fclose(f);
    fclose(f2);
    return 0;
}
