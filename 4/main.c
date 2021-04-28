#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct list_t{
    int num;
    double cos;
    struct list_t * next;
}list_t;

typedef struct list_t2{
    int x;
    int y;
    struct list_t2 * next;
}list_t2;

list_t * create_l(int num, double cos, list_t * next){
    list_t * l = malloc(sizeof(list_t));
    l->num = num;
    l->cos = cos;
    l->next = next;
    return l;
}

list_t2 * create_l2(int x, int y, list_t2 * next){
    list_t2 * l = malloc(sizeof(list_t2));
    l->x = x;
    l->y = y;
    l->next = next;
    return l;
}

void append(list_t * head, int num, double cos){
    while ((head->next)&&(head->next->cos > cos))
        head = head->next;
    if(!head->next) {
        head->next = create_l(num, cos, NULL);
        return;
    }
    head->next = create_l(num, cos, head->next);
    return;
}

list_t2 * prepend2(list_t2 * head, int x, int y){
    list_t2 * l = create_l2(x,y, head);
    return l;
}

void delete_elem2(list_t2 * before){
    list_t2 * l = before->next->next;
    free(before->next);
    before -> next = l;
}

void delete_list(list_t * head){
    if(!head)
        return;
    delete_list(head->next);
    free(head);
}

void delete_list2(list_t2 * head){
    if(!head)
        return;
    delete_list2(head->next);
    free(head);
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

    int st = 0, n = 0;
    fscanf(f,"%d", &n);
    int mas[n][2];
    int length = 0;
    while(!feof(f)){
        fscanf(f,"%d", &mas[length][0]);
        fscanf(f,"%d", &mas[length][1]);
        length ++;
    }

    for (int i = 0; i < n; i++){
        if(mas[st][1] > mas[i][1])
            st = i;
        if(mas[st][1] == mas[i][1])
            if(mas[st][0] > mas[i][0])
                st = i;
    }

    list_t * cos_l = create_l(st,1,NULL);
    double cos;
    for (int i = 0; i < n; i++){
        cos = (double)mas[i][0] / (double)(sqrt(mas[i][0]*mas[i][0] + mas[i][1]*mas[i][1]));
        append(cos_l, i, cos);
    }
    cos_l = cos_l->next;

    list_t2 * result = create_l2(mas[st][0], mas[st][1], NULL);
    for (list_t * t = cos_l->next; t; t = t->next){
        result = prepend2(result,mas[t->num][0],mas[t->num][1]);
        if(!result->next->next)
            continue;
        while((result->next->next->next)&&(((result->next->x - result->next->next->x)*(result->y - result->next->y) - (result->next->y - result->next->next->y)*(result->x - result->next->x))) < 0)
            delete_elem2(result);
    }

    for(list_t2 * t = result; t; t = t->next)
        fprintf(f2,"(%d,%d)\n", t->x, t->y);

    fclose(f);
    fclose(f2);
    delete_list(cos_l);
    delete_list2(result);
    return 0;
}
