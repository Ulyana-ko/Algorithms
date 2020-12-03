#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int s_in_ar(int * ar, int s, int n){
    for(int i = 0; i < n+1; i++)
        if (ar[i] == s)
            return 1;
    return 0;
}

int main(int argc, char * argv[]) {
    FILE * f = fopen(argv[1], "r");
    FILE * size = fopen("size.txt", "a");
    FILE * num = fopen(argv[3], "r");
    FILE * f2 = fopen(argv[2], "w");
    if ((f == NULL)||(num == NULL)||(f2 == NULL))
        return -1;
    int r = 0;
    int mas[500*501][2];
    while (!(feof(f))){
        fscanf(f, "%d %d", &mas[r][0], &mas[r][1]);
        r++;
    }

    int Q[1000];
    int V[1000];
    int w = 0, i = 0;
    int n;
    fscanf(num,"%d", &n);
    srand(time(NULL));
    int s = 1 + rand()%n, d = 1 + rand()%n;
    Q[i] = s;
    fprintf(size, "%d ", n);
    fprintf(f2, "%d %d ", s, d);

    struct timespec t1;
    clock_gettime (CLOCK_REALTIME, &t1);

    for (int t = 0; t < i+1; t++){
        s = Q[t];
        for (int j = 0; j < n; j++)
            for(int l = 0; l < 2; l++)
                if(mas[j][l] == s){
                    if ((l == 1) && !(s_in_ar(V, mas[j][l-1],w)) && !(s_in_ar(Q, mas[j][l-1],i))){
                        i++;
                        Q[i] = mas[j][l-1];
                    }
                    else if((l==0) && !(s_in_ar(V, mas[j][l+1],w)) && !(s_in_ar(Q, mas[j][l+1],i))){
                        i++;
                        Q[i] = mas[j][l+1];
                    }
                }
        V[w] = s;
        w++;
    }

    struct timespec t2;
    clock_gettime (CLOCK_REALTIME, &t2);

    FILE * time = fopen("time.TXT", "a");
    fprintf(time,"%lld ", ((1000000000*t2.tv_sec+t2.tv_nsec) - (1000000000*t1.tv_sec+t1.tv_nsec)));
    if (s_in_ar(V, d, w))
        fprintf(f2,"%s", "True");
    else
        fprintf(f2,"%s", "False");
    
    fclose(f);
    fclose(size);
    fclose(num);
    fclose(f2);
    fclose(time);
    return 0;
}
