#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    string name;
    vector<Node*> children;
    int descendants;
    int generation;

    Node(string name) : name(name), descendants(0), generation(0) {}
};

unordered_map<string, Node*> build_family_tree(const vector<pair<string, string>>& input) {
    unordered_map<string, Node*> family_tree;

    for (const auto& pair : input) {
        string child = pair.first;
        string parent = pair.second;

        if (!family_tree[child])
            family_tree[child] = new Node(child);

        if (!family_tree[parent])
            family_tree[parent] = new Node(parent);

        family_tree[parent]->children.push_back(family_tree[child]);
    }

    return family_tree;
}

int dfs(Node* node, int generation) {
    node->generation = generation;
    node->descendants = 0;  

    for (Node* child : node->children) 
        node->descendants += 1 + dfs(child, generation + 1);  

    return node->descendants;
}

int descendantCount(unordered_map<string, Node*>& node, const string& name) {
    if (node.count(name)) 
        return node[name]->descendants;
    return 0;
}

int generationCount(unordered_map<string, Node*>& node, const string& name) {
    if (node.count(name)) {
        int max_generation = 0;
        for (Node* child : node[name]->children) 
            max_generation = max(max_generation, 1 + generationCount(node, child->name));
        return max_generation;
    }
    return 0;
}

int main() {
    vector<pair<string, string>> input;
    string child, parent;
    
    while (cin >> child && child != "***") {
        cin >> parent;
        input.push_back({child, parent});
    }

    unordered_map<string, Node*> family_tree = build_family_tree(input);

    for (auto& [name, node] : family_tree) {
        if (node->generation == 0) {
            dfs(node, 1); 
        }
    }

    while (cin >> child && child != "***") {
        cin >> parent;
        if (child == "descendants")
            cout << descendantCount(family_tree, parent) << endl;
        else if (child == "generation")
            cout << generationCount(family_tree, parent) << endl;  
    }

    return 0;
}
