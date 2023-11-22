#include<iostream>
#include "LRUCache.h"

using namespace std;

int main()
{
    LRUCache *ch = new LRUCache(2);
    ch->put(1, 1);
    ch->put(3, 3);
    ch->put(2, 2);
    cout << ch->get(3) << endl;  // 3
    cout << ch->get(1) << endl;  // -1
    ch->put(1, 11);
    ch->put(4, 4);
    cout << ch->get(2) << endl;  // -1
    cout << ch->get(1) << endl;  // 11
    cout << ch->get(3) << endl;  // -1
    cout << ch->get(4) << endl;  // 4
    ch->put(4, 44);
    cout << ch->get(4) << endl;  // 44
    ch->put(2, 22);
    cout << ch->get(1) << endl;  // -1
    ch->put(3, 33);
    cout << ch->get(4) << endl;  // -1
    cout << ch->get(2) << endl;  // 22
    
    delete ch;
    
    return 0;
}
