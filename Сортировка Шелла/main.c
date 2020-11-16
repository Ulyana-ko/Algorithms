#include <stdio.h>
#include <time.h>
#include <windows.h>

int stepen(int a){
    int res = 1;
    for (int i = 0; i < a; i++)
        res = res * 2;
    return res;
}

int poisk(int n){
    int t = 0;
    int s = 1;
    while (s < n){
        if (t%2 == 0)
            s = 9*stepen(t) - 9*stepen(t/2) + 1;
        else
            s = 8*stepen(t) - 6*stepen((t+1)/2) + 1;
        t++;
    }
    return t;
}

int main(int argc, char * argv[]) {

    int n  = 0;
    FILE * f = fopen(argv[1], "r");
    FILE * size = fopen("size.txt", "a");
    if(f == NULL)
        return 1;
    int mas[1000];
    while (!(feof(f))){
        fscanf(f, "%d", &mas[n]);
        n++;
    }
    fprintf(size, "%d ", n);

    int t = poisk(n);
    int d;
    if (t%2 == 0)
        d = 9*stepen(t) - 9*stepen(t/2) + 1;
    else
        d = 8*stepen(t) - 6*stepen((t+1)/2) + 1;

    //struct timespec t1;
    //clock_gettime(CLOCK_REALTIME, &t1);
    SYSTEMTIME t1;
    GetLocalTime(&t1);

    while (d >= 1){
        int r = 0;
        for(int i = 0; i < n; i++)
            for(int j = i; j + d < n; j = j+d)
                if (mas[j] > mas[j+d]) {
                    int c = mas[j];
                    mas[j] = mas[j + d];
                    mas[j + d] = c;
                    r = 1;
                }
        t--;
        if ((t < 0) && (r == 0))
            break;
        if(t < 0)
            continue;
        if (t%2 == 0)
            d = 9*stepen(t) - 9*stepen(t/2) + 1;
        else
            d = 8*stepen(t) - 6*stepen((t+1)/2) + 1;
    }

    //struct timespec t2;
    //clock_gettime(CLOCK_REALTIME, &t2);
    SYSTEMTIME t2;
    GetLocalTime(&t2);

    FILE * f2 = fopen(argv[2], "w");
    for(int i = 0; i < n; i++)
        fprintf(f2, "%d ", mas[i]);
    FILE * time = fopen("time.txt", "a");
    fprintf(time,"%d ", ((1000*t2.wSecond+t2.wMilliseconds)-(1000*t1.wSecond+t1.wMilliseconds)));
    
    fclose(f);
    fclose(size);
    fclose(time);
    fclose(f2);
    return 0;
}