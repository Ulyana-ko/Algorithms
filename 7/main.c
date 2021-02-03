#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct list_t{
    int number;
    int length;
    struct list_t * next;
}list_t;

list_t * create_l(int num, int len){
    list_t * l = malloc(sizeof(list_t));
    l->number = num;
    l->length = len;
    l->next = NULL;
    return l;
}

list_t * in_list(list_t * head, int num){
    for(list_t * it = head; it; it = it->next)
        if(it->number == num)
            return it;
    return NULL;
}

void append_l(list_t * head,int num,int len){
    list_t * l = create_l(num,len);
    while ((head->next)&&(head->next->length < l->length))
        head = head->next;
    l->next = head->next;
    head->next = l;
}

list_t * delete_head(list_t * head){
    list_t h = *head;
    free(head);
    return h.next;
}

void delete_list(list_t * head){
    for(list_t * i = head; i; i = i->next)
        free(i);
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
    int s;
    fscanf(f, "%d", &s);
    int length = 0;

    int mas[num_of_edge*2][3];
    while (!(feof(f))) {
        fscanf(f, "%d %d %d", &mas[length][0], &mas[length][1], &mas[length][2]);
        length++;
    }
    list_t * W = create_l(s,0);
    int L[num_of_tops][2];
    L[0][0] = 1;
    L[0][1] = 0;
    for(int i = 1; i < num_of_tops; i++){
        L[i][0] = i+1;
        L[i][1] = (int)INFINITY;
    }

    int change = 1;
    while (change){
        change = 0;
        for (int i = 0; i < length; i++){
            if(mas[i][0] == W->number){
                int len;
                int j;
                for(j = 0; j < num_of_tops; j++)
                    if(L[j][0] == mas[i][1]) {
                        len = L[j][1];
                        break;
                    }
                if(W->length + mas[i][2] < len){
                    L[j][1] = W->length + mas[i][2];
                    change = 1;
                    list_t * elem = in_list(W, mas[i][1]);
                    if(elem)
                        elem->length = W->length + mas[i][2];
                    else
                        append_l(W,mas[i][1],W->length + mas[i][2]);
                }
            }
        }
        W = delete_head(W);

    }
    delete_list(W);
    for (int i = 0; i < num_of_tops; i++)
        fprintf(f2,"%d %d\n", L[i][0],L[i][1]);

    fclose(f);
    fclose(f2);
    return 0;
}
