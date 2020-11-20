#include <stdio.h>
#include <windows.h>

void my_qsort(int * mas, int l, int r){
    if(l >= r)
        return;
    int op = (mas[l] + mas[r])/2;
    int n = r;
    int m = l;
    while(l < r) {
        while ((mas[l] <= op)&&(l<=n-1))
            l++;
        while ((mas[r] > op)&&(r>=m+1))
            r--;
        if(l <= r) {
            int c = mas[l];
            mas[l] = mas[r];
            mas[r] = c;
        }
    }
    if(r<l){
        r++;
        l--;
    }
    if(l == r){
        if(l-1<m)
            r++;
        else
            l--;
    }
    my_qsort(mas,m,l);
    my_qsort(mas,r,n);
}

int main(int argc, char * argv[]) {
    int n  = 0;
    //("%s", argv[1]);
    FILE * f = fopen(argv[1], "r");
    FILE * size = fopen("size.txt", "a");
    if(f == NULL)
        return 1;
    int mas[10000];
    while (!(feof(f))){
        fscanf(f, "%d", &mas[n]);
        n++;
    }
    fprintf(size, "%d ", n);

    SYSTEMTIME t1;
    GetLocalTime(&t1);

    my_qsort(mas,0,n-1);

    SYSTEMTIME t2;
    GetLocalTime(&t2);

    FILE * f2 = fopen(argv[2], "w");
    if(f2 == NULL)
        return 1;
    for(int i = 0; i < n; i++)
        fprintf(f2, "%d ", mas[i]);
    FILE * time = fopen("time.TXT", "a");
    fprintf(time,"%d ", ((60000*t2.wMinute+1000*t2.wSecond+t2.wMilliseconds) - (60000*t1.wMinute+1000*t1.wSecond+t1.wMilliseconds)));

    fclose(f);
    fclose(size);
    fclose(time);
    fclose(f2);
    return 0;
}
