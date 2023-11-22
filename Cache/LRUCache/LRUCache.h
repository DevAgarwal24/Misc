// https://leetcode.com/problems/lru-cache/description/

#include <iostream>
#include <unordered_map>

using namespace std;

class Node {
public:
	Node() : key{0}, value{0}, next{nullptr} {}
	Node(int x, int y) : key{x}, value{y}, next{nullptr}, prev{nullptr} {}
	Node(int x, int y, Node* next) : key{x}, value{y}, next{next}, prev{nullptr} {}
	Node(int x, int y, Node* next, Node* prev) : key{x}, value{y}, next{next}, prev{prev} {}

  int key, value;
	Node* next;
	Node* prev;
};

class LRUCache {
public:
    LRUCache(int capacity) : size{capacity}, currSize{0} {
        head = new Node();
        last = new Node();
        
        head->next = last;
        last->prev = head;
    }

    ~LRUCache() {
        Node *curr = head;
        while (curr->next) {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
        delete curr;
    }

    void addNode(Node *node) {
        head->next = node;
        node->next->prev = node;
    }
    
    void moveToHead(Node *node) {  // Add to the head
        node->prev->next = node->next;
        node->next->prev = node->prev;
        
        node->next = head->next;
        node->prev = head;
        addNode(node);
    }

    void deleteNode(Node *node) {   // Delete from the tail
        node->prev->next = node->next;
        node->next->prev = node->prev;

        m.erase(node->key);
        delete node;
    }

    int get(int key) {
        if (m.find(key) != m.end()) {
            Node *node = m[key];
            if (node->prev != head) {
                moveToHead(node);
            }
            return m[key]->value;
        } else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        if (m.find(key) != m.end()) {
            Node *node = m[key];
            node->value = value;
            moveToHead(node);
        } else {    // Node not already present, add one
            Node *newNode = new Node(key, value, head->next, head);
            addNode(newNode);
            m.insert({key, newNode});
            
            if (m.size() > size) {
                deleteNode(last->prev);
            }
        }
    }

private:
    int size, currSize;
    Node *head;
    Node *last;
    unordered_map<int, Node*> m;
};
