#include <iostream>
#include <sstream>
#include <vector>
#include "Node.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::ostringstream;

// Tree:
//                  A
//                /   \
//              B      C 
//           /  |       \
//          F   E       D

void traverse(Node* root, Node* end);
ostringstream backtrace(Node* root, Node* end);
ostringstream drawTree();

int main(void){

     Node a("A");
    Node b("B");
    Node c("C");
    Node d("D");
    Node e("E");
    Node f("F");

    a.addNeighbour(&b);
    a.addNeighbour(&c);
    b.addNeighbour(&f);
    b.addNeighbour(&e);
    c.addNeighbour(&d);

    char rootNode,endNode;
    cout <<drawTree().str() << endl;
    cout << "Choose a start node: ";
    cin >> rootNode;
    cout << "Choose an end node: ";
    cin >> endNode;
    cout << endl;

    Node* root;
    Node* end;
    switch(rootNode){
        case 'a':
        case 'A':
            root = &a;
            break;
        case 'b':
        case 'B':
            root = &b;
            break;
        case 'c':
        case 'C':
            root = &c;
            break;
        case 'd':
        case 'D':
            root = &d;
            break;
        case 'e':
        case 'E':
            root = &e;
            break;
        case 'f':
        case 'F':
            root = &f;
            break;
    }
    switch(endNode){
        case 'a':
        case 'A':
            end = &a;
            break;
        case 'b':
        case 'B':
            end = &b;
            break;
        case 'c':
        case 'C':
            end = &c;
            break;
        case 'd':
        case 'D':
            end = &d;
            break;
        case 'e':
        case 'E':
            end = &e;
            break;
        case 'f':
        case 'F':
            end = &f;
            break;
    }

    traverse(root,end);
    cout << backtrace(root,end).str();

    return 0;
}

void traverse(Node* root, Node* end){
    Node* currentNode = root;
    vector<Node*> queue;
    currentNode->setVisited();
    queue.push_back(currentNode);
    
    // cout << "Current Node: " << currentNode -> getName() << endl;
    while(currentNode != end){
        
        currentNode->setVisited();
        bool finish = false;
        for(Node* node: currentNode->getNeighbours()){
            if(!finish){
                queue.push_back(node);
                // cout << "Pushing " << node->getName() << " to queue." << endl;
                finish = true;
            }
        }

        for(Node* node: currentNode->getNeighbours()){
            node->setParent(currentNode);
            queue.push_back(node);
        }

        queue.erase(queue.begin());
        if(!(currentNode->hasNeighbours())){
            // cout << "Parent of " << currentNode->getName() << ": " << currentNode->getParent()->getName() << endl;
            currentNode = currentNode->getParent();
        } else {
            currentNode = queue.at(0);
        }
        // cout << "Current Node: " << currentNode -> getName() << endl;
        // cout << "Parent of " << currentNode->getName() << ": " << currentNode->getParent()->getName() << endl<< endl;

    }

}

ostringstream backtrace(Node* root, Node* end){
    Node* currentNode = end;
    ostringstream oSS;
    vector<string> reverseSequence;

    oSS << "Path from " << root -> getName() << " to " << end -> getName() << ": " << endl;
    
    reverseSequence.push_back(currentNode->getName());
    while(currentNode->getParent() != nullptr){
        currentNode = currentNode->getParent();
        reverseSequence.push_back(currentNode->getName());
    }

    for(int i=reverseSequence.size()-1; i>=0; i--){
        oSS << reverseSequence.at(i);
        if(i != 0){
            oSS << " -> ";
        }
    }

    oSS << endl;

    return oSS;

}
ostringstream drawTree(){
    ostringstream treeSS;
    treeSS << "Current Tree" << endl;
    treeSS << "                  A"         << endl;
    treeSS << "                /   \\"      << endl;
    treeSS << "              B      C"      << endl;
    treeSS << "            / |       \\"    << endl;
    treeSS << "          F   E        D"    << endl;
    return treeSS;
}