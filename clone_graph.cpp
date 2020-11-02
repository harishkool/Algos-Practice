#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <unordered_map>

using namespace std;


class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


std::shared_ptr<Node> clone_graph(Node* node){

    std::shared_ptr<Node> root = std::make_shared<Node>(node->val);
    std::queue<std::shared_ptr<Node>>q;
    q.push(root);
    std::shared_ptr<Node> root2 = std::make_shared<Node>(root->val);
    std::unordered_map<Node*, Node*>mp;
    mp[node] = root2.get();
    std::queue<std::shared_ptr<Node>>clone_q;
    clone_q.push(root2);
    while(!q.empty()){
        std::shared_ptr<Node> nd = q.front();
        std::shared_ptr<Node> clone_nd = clone_q.front();
        clone_q.pop();
        q.pop();
        std::vector<Node*> neighbhors = nd->neighbors;
        for(auto neighbor: neighbhors){
            q.push(std::shared_ptr<Node>(neighbor));
            std::shared_ptr<Node> neigh = std::make_shared<Node>(neighbor->val);
            if(mp.find(neighbor) == mp.end()){
                mp[neighbor] = neigh.get();
                clone_nd->neighbors.push_back(neigh.get());
            }else{
                clone_nd->neighbors.push_back(mp[neighbor]);
            }

        }

    }   

    
    return root2;

}


