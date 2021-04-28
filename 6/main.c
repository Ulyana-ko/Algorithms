#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct avltree_t {
    int key;
    int value;
    struct avltree_t * left, * right;
}avltree_t;

int max2(int a, int b){
    if(b > a)
        return b;
    return a;
}

int abs(int a){
    if(a < 0)
        return -a;
    return a;
}

void prefix_dump(avltree_t * tree,int n){
    if(!tree){
        for(int i = 0; i < n; i++)
            printf("  ");
        printf("(nil)\n");
        return;
    }
    for(int i = 0; i < n; i++)
        printf("  ");
    printf("(%d\n", tree->key);
    n++;
    prefix_dump(tree->left, n);
    prefix_dump(tree->right, n);
    n--;
    for(int i = 0; i < n; i++)
        printf("  ");
    printf(")\n");

}

avltree_t * create(int key, int value){
    avltree_t * tree = malloc(sizeof(avltree_t));
    tree->key = key;
    tree->value = value;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

avltree_t * insert(avltree_t * tree, int key, int value){
    if (key == tree->key)
        return NULL;
    if (key > tree->key)
        if(tree->right)
            return insert(tree->right, key, value);
        else{
            tree->right = create(key,value);
            return tree->right;
        }
    else
    if(tree->left)
        return insert(tree->left, key, value);
    else{
        tree->left = create(key,value);
        return tree->left;
    }
}

int find_hight(avltree_t * tree){
    if(!tree)
        return 0;
    int h = 1;
    if(tree->left)
        h = 1 + find_hight(tree->left);
    if(tree->right)
        h = max2(h, 1 + find_hight(tree->right));
    return h;
}

avltree_t * find_parent(avltree_t * tree, int key){
    if (key == tree->key)
        return NULL;
    if((tree->right)&&(tree->left))
        if((tree->right->key == key)||(tree->left->key == key))
            return tree;
    if((tree->right)&&(!tree->left))
        if(tree->right->key == key)
            return tree;
    if((!tree->right)&&(tree->left))
        if(tree->left->key == key)
            return tree;
    avltree_t * t;
    if(key > tree->key)
        if(tree->right)
            t = find_parent(tree->right, key);
        else
            return NULL;
    if(key < tree->key)
        if(tree->left)
            t = find_parent(tree->left, key);
        else
            return NULL;
    return t;
}

avltree_t * rotate_right_little(avltree_t * tree){
    avltree_t * left = tree->left;
    tree->left = tree->left->right;
    left->right = tree;
    return left;
}

avltree_t * rotate_left_little(avltree_t * tree){
    avltree_t * right = tree->right;
    tree->right = tree->right->left;
    right->left = tree;
    return right;
}

avltree_t * rotate_right_large(avltree_t * tree){
    tree->left = rotate_left_little(tree->left);
    return rotate_right_little(tree);
}

avltree_t * rotate_left_large(avltree_t * tree){
    tree->right = rotate_right_little(tree->right);
    return rotate_left_little(tree);
}

avltree_t * repair(avltree_t * tree, avltree_t * t){
    if (abs(find_hight(t->right) - find_hight(t->left)) <= 1){
        if(t == tree)
            return tree;
        tree = repair(tree, find_parent(tree,t->key));
    }
    if((find_hight(t->right) - find_hight(t->left) > 1)&&(find_hight(t->right->left) <= find_hight(t->right->right))){
        avltree_t * parent = find_parent(tree,t->key);
        avltree_t * elem = rotate_left_little(t);
        if(t == tree) {
            tree = elem;
            return tree;
        }
        if(parent->left->key == t->key)
            parent->left = elem;
        else
            parent->right = elem;
        tree = repair(tree, parent);
    }
    if((find_hight(t->right) - find_hight(t->left) > 1)&&(find_hight(t->right->left) > find_hight(t->right->right))){
        avltree_t * parent = find_parent(tree,t->key);
        avltree_t * elem = rotate_left_large(t);
        if(t == tree) {
            tree = elem;
            return tree;
        }
        if(parent->left->key == t->key)
            parent->left = elem;
        else
            parent->right = elem;
        tree = repair(tree, parent);
    }
    if((find_hight(t->left) - find_hight(t->right) > 1)&&(find_hight(t->left->right) <= find_hight(t->left->left))){
        avltree_t * parent = find_parent(tree,t->key);
        avltree_t * elem = rotate_right_little(t);
        if(t == tree) {
            tree = elem;
            return tree;
        }
        if(parent->left->key == t->key)
            parent->left = elem;
        else
            parent->right = elem;
        tree = repair(tree, parent);
    }
    if((find_hight(t->left) - find_hight(t->right) > 1)&&(find_hight(t->left->right) > find_hight(t->left->left))){
        avltree_t * parent = find_parent(tree,t->key);
        avltree_t * elem = rotate_right_large(t);
        if(t == tree){
            tree = elem;
            return tree;
        }
        if(parent->left->key == t->key)
            parent->left = elem;
        else
            parent->right = elem;
        tree = repair(tree, parent);
    }
    return tree;
}

avltree_t * append(avltree_t * tree, int key, int value){
    avltree_t * t = insert(tree,key,value);
    if(!t)
        return tree;
    tree = repair(tree,t);
    return tree;
}

void delete_tree(avltree_t * tree){
    if(!tree)
        return;
    delete_tree(tree->left);
    delete_tree(tree->right);
    free(tree);
}

avltree_t * find_elem(avltree_t * tree, int key){
    if (key == tree->key)
        return tree;
    if (key > tree->key)
        if (tree->right)
            find_elem(tree->right, key);
        else
            return NULL;
    else
    if (tree->left)
        find_elem(tree->left, key);
    else
        return NULL;
}

void fprint_tree(avltree_t * tree, FILE * f){
    if(!tree)
        return;
    fprint_tree(tree->left, f);
    fprintf(f, "%d ", tree->key);
    fprint_tree(tree->right, f);
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

    int key;
    fscanf(f,"%d", &key);
    avltree_t * tree = create(key,0);
    struct timespec t1;
    clock_gettime (CLOCK_REALTIME, &t1);
    while(!feof(f)){
        fscanf(f,"%d", &key);
        tree = append(tree,key,0);
    }
    struct timespec t2;
    clock_gettime (CLOCK_REALTIME, &t2);

    fprintf(f2,"%lld\n", ((1000000000*t2.tv_sec+t2.tv_nsec) - (1000000000*t1.tv_sec+t1.tv_nsec)));
    fprint_tree(tree,f2);
    fclose(f);
    fclose(f2);

    return 0;
}
