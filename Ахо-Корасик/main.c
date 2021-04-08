#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    char value;
    struct tree * child;
}tree;

tree * create_tree_elem(char value, tree * child){
    tree * t = malloc(sizeof(tree));
    t->value = value;
    t->child = child;
    return t;
}

tree * create_tree(char * word){
    tree * head = create_tree_elem(word[0], NULL);
    tree * t = head;
    int i = 1;
    while(word[i]){
        t->child = create_tree_elem(word[i],NULL);
        t = t->child;
        i++;
    }
    return head;
}

void tree_delete(tree * t){
    if(!t->child)
        return;
    tree_delete(t->child);
    free(t);
}

tree * find_parent(tree * head, tree * t){
    if(head == t)
        return t;
    while (head){
        if(head->child == t)
            return head;
        head = head->child;
    }
}

tree * find_position(tree * head, tree * now, char value){
    if(value == now->child->value)
        return now->child;
    tree * parent = find_parent(head, now);
    while (1){
        if(parent == head)
            return head;
        if(parent->value == value)
            return parent;
        parent = find_parent(head,parent);
    }
}

int aho_kor(FILE * f, char * podstroka){
    tree * head = create_tree_elem('1', create_tree(podstroka));
    tree * t = head;
    char c;
    while (!feof(f)){
        fscanf(f,"%c",&c);
        t = find_position(head,t,c);
        if(!t->child){
            tree_delete(head);
            return 1;
        }
    }
    tree_delete(head);
    return 0;
}

int len_word(FILE * f){
    char c;
    fscanf(f,"%c",&c);
    int res = 0;
    while (c != '\n'){
        res++;
        fscanf(f,"%c",&c);
    }
    return res;
}

int main() {
    FILE * text = fopen("C:\\Users\\ylian\\CLionProjects\\Aho-Korasik\\text.TXT", "r");
    FILE * words = fopen("C:\\Users\\ylian\\CLionProjects\\Aho-Korasik\\word_list.TXT", "r");
    FILE * words2 = fopen("C:\\Users\\ylian\\CLionProjects\\Aho-Korasik\\word_list.TXT", "r");
    if((!text)||(!words)||(words2))
        return -1;

    int n;
    fscanf(words,"%d", &n);
    fscanf(words2,"%d", &n);
    char help;
    fscanf(words2,"%c", &help);
    for(int i = 0; i < n; i++){
        char s[len_word(words2)];
        fscanf(words,"%s", s);
        printf("%d\n", aho_kor(text,s));
        fclose(text);
        text = fopen("C:\\Users\\ylian\\CLionProjects\\Aho-Korasik\\text.TXT", "r");
    }

    fclose(text);
    fclose(words);
    fclose(words2);
    return 0;
}
