#include <stdio.h>
#include <stdlib.h>

typedef struct list_t{
    int num;
    int len;
    int feel;
    struct list_t * next;
}list_t;

int s_in_ar(int * ar, int s, int n){
    for(int i = 0; i < n+1; i++)
        if (ar[i] == s)
            return 1;
    return 0;
}

list_t * create_l(int num, int len, int  feel){
    list_t * l = malloc(sizeof(list_t));
    l->num = num;
    l->len = len;
    l->feel = feel;
    l->next = NULL;
    return l;
}

void append_l(list_t* head,int num,int len,int feel){
    list_t * l = create_l(num,len,feel);
    while ((head->next)&&(head->next->len < l->len))
        head = head->next;
    l->next = head->next;
    head->next = l;
}

int in_list(list_t * head, int num){
    for (list_t * i = head; i->next; i = i->next){
        if (i->num == num)
            return 1;
    }
    return 0;
}

void delete_elem(list_t * head, int num){
    for (list_t * i = head; i->next->next; i = i->next){
        if (i->next->num == num) {
            i->next = i->next->next;
            free(i->next);
            return;
        }
    }
}

void change_len(list_t * head, int len2, int num){
    for(list_t * i = head; i->next; i = i->next){
        if(i->num == num){
            if(i->len > len2) {
                i->len = len2;
                while ((head->next)&&(head->next->len < i->len))
                    head = head->next;
                list_t * l = i;
                delete_elem(head,i->num);
                l->next = head->next;
                head->next = l;
                return;
            }
        }
    }
}

int return_feel(list_t * head, int num ){
    for(list_t * i = head; i->next; i = i->next){
        if(i->num == num)
          return i->feel;
    }
    return 0;
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
    int type;
    fscanf(f, "%d", &type);
    int num_of_tops;
    fscanf(f, "%d", &num_of_tops);
    int num_of_edge;
    fscanf(f, "%d", &num_of_edge);
    int s;
    fscanf(f, "%d", &s);
    int fin;
    fscanf(f, "%d", &fin);
    fprintf(f2, "%d %d ", s, fin);
    int length = 0;

    if((type == 1)||(type == 3)) {

        int mas[num_of_edge*2][3];
        while (!(feof(f))) {
            fscanf(f, "%d %d %d", &mas[length][0], &mas[length][1], &mas[length][2]);
            length++;
        }

        list_t *h = create_l(s, 0, 1);
        list_t *n = h;
        while (n) {
            for (int i = 0; i < length; i++) {
                if (mas[i][0] == n->num) {
                    if ((in_list(h, mas[i][1])) && (return_feel(h, mas[i][1]))) {
                        change_len(h, n->len + mas[i][2], mas[i][1]);
                    };
                    if (!in_list(h, mas[i][1])) {
                        append_l(h, mas[i][1], n->len + mas[i][2], 1);
                    }
                }
            }
            n->feel = 0;
            n = n->next;
        }
        for (list_t *i = h; i->next; i = i->next) {
            if (i->num == fin)
                fprintf(f2,"%d", i->len);
        }
        delete_list(h);
    }

    if((type == 0)||(type == 2)) {
        int mas[num_of_edge*2][3];
        while (!(feof(f))) {
            fscanf(f, "%d %d", &mas[length][0], &mas[length][1]);
            length++;
        }

        int Q[num_of_tops];
        int V[num_of_tops];
        int w = 0, i = 0;
        for (int t = 0; t < i + 1; t++) {
            s = Q[t];
            for (int j = 0; j < length; j++)
                if (mas[j][0] == s) {
                    if (!(s_in_ar(V, mas[j][1], w)) && !(s_in_ar(Q, mas[j][1], i))) {
                        i++;
                        Q[i] = mas[j][1];
                    }
                }
            V[w] = s;
            w++;
        }

        if (s_in_ar(V, fin, w))
            fprintf(f2,"%s", "True");
        else
            fprintf(f2,"%s", "False");
    }

    fclose(f);
    fclose(f2);
    return 0;
}
