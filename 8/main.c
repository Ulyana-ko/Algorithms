#include <stdio.h>
#include <math.h>

int in_tops(int * tops, int len, int top){
    for(int i = 0; i < len; i++){
        if(tops[i] == top)
            return 0;
    }
    return 1;
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
    if (f == NULL)
        return -1;
    int num_of_tops;
    fscanf(f, "%d", &num_of_tops);
    int num_of_edge;
    fscanf(f, "%d", &num_of_edge);
    int type;
    fscanf(f, "%d", &type);
    int length = 0;
    int grav[num_of_edge*2][3];
    while (!(feof(f))) {
        fscanf(f, "%d %d %d", &grav[length][0], &grav[length][1], &grav[length][2]);
        length++;
    }
    int n = length;
    int t = num_of_tops;
    int tops[t];
    for (int i = 0; i < t; i++)
        tops[i] = 0;
    int res[n][3];
    for (int i = 0; i < n; i++){
        res[i][0] = 0;
        res[i][1] = 0;
        res[i][2] = 0;
    }
    int num_top = 0;
    tops[num_top] = grav[0][0];

    int min = grav[0][2];
    int min_top = grav[0][1];
    int with_min_top = grav[0][0];
    while (!tops[t-1]){
        for (int i = 0; i < num_top + 1; i++){
            for (int j = 0; j < n; j++){
                if(grav[j][0] == tops[i]){
                    if((grav[j][2] < min)&&(in_tops(tops,num_top + 1, grav[j][1]))){
                        min = grav[j][2];
                        min_top = grav[j][1];
                        with_min_top = grav[j][0];
                    }
                }
            }
        }
        res[num_top][0] = with_min_top;
        res[num_top][1] = min_top;
        res[num_top][2] = min;
        num_top++;
        tops[num_top] = min_top;
        min = (int)INFINITY;
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (res[i][0] == 0)
            break;
        sum += res[i][2];
    }
    fprintf(f2, "%d\n%d\n%d\n%d\n", sum,num_of_tops,num_of_edge,type);
    for (int j = 0; j < length; j++)
        fprintf(f2,"%d %d %d\n", grav[j][0], grav[j][1], grav[j][2]);

    fclose(f);
    fclose(f2);
    return 0;
}
