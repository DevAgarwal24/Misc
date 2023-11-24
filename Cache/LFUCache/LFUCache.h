// https://leetcode.com/problems/lfu-cache/description/

#include <iostream>
#include <unordered_map>

using namespace std;

class Node {
public:
	Node() = delete;
	Node(int x, int y) : key{x}, value{y}, cnt{1}, next{nullptr}, prev{nullptr} {}
	Node(int x, int y, Node* next) : key{x}, value{y}, cnt{1}, next{next}, prev{nullptr} {}
	Node(int x, int y, Node* next, Node* prev) : key{x}, value{y}, cnt{1}, next{next}, prev{prev} {}

    int key, value, cnt;
	Node* next;
	Node* prev;
};

class List {
public:
    List() {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
        size = 0;
    }

    void addFront(Node *node) {
        Node *tmp = head->next;
        head->next = node;
        node->prev = head;
        node->next = tmp;
        tmp->prev = node;
        size++;
    }

    void removeNode(Node *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        size--;
    }

    ~List() {
        delete head;
        delete tail;
    }

    int size;
    Node *head;
    Node *tail;
};

class LFUCache {
public:
    LFUCache(int capacity) {
        maxSizeCache = capacity;
        minFreq = 0;
    }
    
    void updateFreqListMap(Node *node) {
        keyNode.erase(node->key);
        freqList[node->cnt]->removeNode(node);
        if (node->cnt == minFreq && freqList[node->cnt]->size == 0) {
            // The list is now empty, so freeing the space
            delete freqList[node->cnt];
            freqList.erase(node->cnt);
            minFreq++;
        }

        List *nextHigherFreq = nullptr;
        if (freqList.find(node->cnt + 1) == freqList.end()) {   // next freq list doesn't exist
            // create a new list to store the next freq
            nextHigherFreq = new List();
            freqList.insert({node->cnt + 1,nextHigherFreq});
        }

        nextHigherFreq = freqList[node->cnt + 1];
        node->cnt += 1;
        nextHigherFreq->addFront(node);
        keyNode.insert({node->key, node});
    }
    
    int get(int key) {
        if (keyNode.find(key) != keyNode.end()) {
            Node *node = keyNode[key];
            int val = node->value;
            updateFreqListMap(node);
            return val;
        }

        return -1;
    }
    
    void put(int key, int value) {
        if (keyNode.find(key) != keyNode.end()) {
            Node *node = keyNode[key];
            node->value = value;
            updateFreqListMap(node);
        } else {
            if (keyNode.size() == maxSizeCache) {
                List *list = freqList[minFreq];
                Node *node = list->tail->prev;
                keyNode.erase(node->key);
                list->removeNode(node);
                delete node;
            }
            minFreq = 1;
            List *list = nullptr;
            if (freqList.find(minFreq) == freqList.end()) {
                list = new List();
                freqList.insert({minFreq, list});
            }
            list = freqList[minFreq];
            Node *node = new Node(key, value);
            list->addFront(node);
            keyNode.insert({key, node});
        }
    }

    unordered_map<int, Node*> keyNode;
    unordered_map<int, List*> freqList;
    int maxSizeCache;
    int minFreq;
};
