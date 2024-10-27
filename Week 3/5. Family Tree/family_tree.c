#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[30];
    struct Node** children;
    int child_count;
    int descendants;
    int generation;
};

struct Node* create_node(char* name) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    strcpy(node->name, name);
    node->children = NULL;
    node->descendants = 0;
    node->generation = 0;
}

void add_child(struct Node* parent, struct Node* child) {
    parent->children = (struct Node**)realloc(parent->children, (parent->child_count + 1) * sizeof(struct Node*));
    parent->children[parent->child_count] = child;
    parent->child_count++;
}

int dfs(struct Node* node, int generation) {
    node->generation = generation;
    node->descendants = 0;
    
    for (int i = 0; i < node->child_count; ++i)
        node->descendants += 1 + dfs(node->children[i], generation + 1);
        
    return node->descendants;
}

int descendantCount(struct Node** family_tree, int size, const char* name) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(family_tree[i]->name, name) == 0) 
            return family_tree[i]->descendants;
    }
    
    return 0;
}

int generationCount(struct Node** family_tree, int size, const char* name) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(family_tree[i]->name, name) == 0) {
            int max_generation = 0;
            for (int j = 0; j < family_tree[i]->child_count; ++j) {
                int child_gen = 1 + generationCount(family_tree, size, family_tree[i]->children[j]->name);
                if (max_generation < child_gen) 
                    max_generation = child_gen;
            }
            return max_generation;
        }
    }
    return 0;
}

int main() {
    struct Node* family_tree[100];
    int family_tree_size = 0;
    char child[30], parent[30];
    
    while (scanf("%s", child) && strcmp(child, "***") != 0) {
        scanf("%s", parent);
        
        struct Node* child_node = NULL;
        struct Node* parent_node = NULL;
        
        for (int i = 0; i <family_tree_size; ++i) {
            if (strcmp(family_tree[i]->name, child) == 0) 
                child_node = family_tree[i];
            if (strcmp(family_tree[i]->name, parent) == 0)
                parent_node = family_tree[i];
        }
        
        if (!child_node) {
            child_node = create_node(child);
            family_tree[family_tree_size++] = child_node;
        }
        
        if (!parent_node) {
            parent_node = create_node(parent);
            family_tree[family_tree_size++] = parent_node;
        }
        
        add_child(parent_node, child_node);
    }
    
    for (int i = 0; i < family_tree_size; ++i) {
        if (family_tree[i]->generation == 0) {
            dfs(family_tree[i], 1);
        }
    }
    
    while (scanf("%s", child) && strcmp(child, "***") != 0) {
        scanf("%s", parent);
        
        if (strcmp(child, "descendants") == 0) 
            printf("%d\n", descendantCount(family_tree, family_tree_size, parent));
        
        if (strcmp(child, "generation") == 0) 
            printf("%d\n", generationCount(family_tree, family_tree_size, parent));
    }
    
    return 0;
} 
