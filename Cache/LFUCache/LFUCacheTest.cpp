#include<iostream>
#include "LFUCache.h"

using namespace std;

int main()
{
    LFUCache *ch = new LFUCache(2);
    ch->put(1, 1);
    ch->put(2, 2);
    cout << ch->get(1) << endl;  // 1
    ch->put(3, 3);
    cout << ch->get(2) << endl;  // -1
    cout << ch->get(3) << endl;  // 3
    ch->put(4, 4);
    cout << ch->get(1) << endl;  // -1
    cout << ch->get(3) << endl;  // 3
    cout << ch->get(4) << endl;  // 4
    
    delete ch;
    
    return 0;
}
