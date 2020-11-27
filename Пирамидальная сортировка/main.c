#include <stdio.h>
#include <time.h>

void rec_pros(int * mas, int r){
    int c = mas[0];
    mas[0] = mas[r];
    mas[r] = c;
    r--;
    if (r == 0)
        return;
    int j = 0;
    while(1==1){
        if (2*j + 1 > r)
            break;
        if (2*j + 1 == r){
            if (mas[j] > mas[2*j + 1]){
                int c = mas[j];
                mas[j] = mas[2*j + 1];
                mas[2*j + 1] = c;
                j = 2*j + 1;
            }
            else
                break;
        }
        if (2*j + 1 < r){
            if (mas[j] > mas[2*j + 1]){
                if (mas[2*j + 1] < mas[2*j + 2]){
                    int c = mas[j];
                    mas[j] = mas[2*j + 1];
                    mas[2*j + 1] = c;
                    j = 2*j + 1;
                }
                else{
                    int c = mas[j];
                    mas[j] = mas[2*j + 2];
                    mas[2*j + 2] = c;
                    j = 2*j + 2;
                }
            }
            else{
                if (mas[j] > mas[2*j + 2]){
                    int c = mas[j];
                    mas[j] = mas[2*j + 2];
                    mas[2*j + 2] = c;
                    j = 2*j + 2;
                }
                else
                    break;
            }
        }
    }
    rec_pros(mas, r);
}

void c_sorttree(int * mas, int j, int n){
    if (2*j + 1 > n)
        return;
    if (2*j + 1 == n){
        if (mas[j] > mas[2*j + 1]){
            int c = mas[j];
            mas[j] = mas[2*j + 1];
            mas[2*j + 1] = c;
            c_sorttree(mas, 2*j+1, n);
        }
        return;
    }
    if (2*j + 1 < n){
        c_sorttree(mas, 2*j + 1, n);
        c_sorttree(mas, 2*j + 2, n);
        if (mas[j] > mas[2*j + 1]){
            int c = mas[j];
            mas[j] = mas[2*j + 1];
            mas[2*j + 1] = c;
            c_sorttree(mas, 2*j+1, n);
        }
        if (mas[j] > mas[2*j + 2]){
            int c = mas[j];
            mas[j] = mas[2*j + 2];
            mas[2*j + 2] = c;
            c_sorttree(mas, 2*j+2, n);
        }
    }
}

int main(int argc, char * argv[]) {
    int n  = 0;
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

    struct timespec t1;
    clock_gettime (CLOCK_REALTIME, &t1);

    c_sorttree(mas, 0, n-1);
    rec_pros(mas, n-1);

    struct timespec t2;
    clock_gettime (CLOCK_REALTIME, &t2);

    FILE * f2 = fopen(argv[2], "w");
    if(f2 == NULL)
        return 1;
    for(int i = 0; i < n; i++)
        fprintf(f2, "%d ", mas[i]);
    FILE * time = fopen("time.TXT", "a");
    fprintf(time,"%lld ", ((1000000000*t2.tv_sec+t2.tv_nsec) - (1000000000*t1.tv_sec+t1.tv_nsec)));
    //printf("%d %d", (1000000000*t2.tv_sec+t2.tv_nsec),(1000000000*t1.tv_sec+t1.tv_nsec));

    fclose(f);
    fclose(size);
    fclose(time);
    fclose(f2);
    return 0;
}
