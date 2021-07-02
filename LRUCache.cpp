#include<iostream>
#include<list>
#include<unordered_map>

using namespace std;

//Node to store the data (Linked List)
class Node{

public:
    string key;
    int value;
    Node(string key, int value){
        this->key = key;
        this->value = value;
    }
};

//LRU Cache Data Structure
class LRUCache{

public:
    int maxSize;
    list<Node> l;
    unordered_map<string, list<Node>::iterator > m;

    LRUCache(int maxSize){
        this->maxSize = maxSize > 1 ? maxSize : 1;
    }

    void insertKeyValue(string key, int value){
        //Case 1
        if(m.count(key) != 0){
            //Replace the old value & update the new value
            auto it = m[key];
            it->value = value;
        }
        else{
            //Check if Cache is full or not
            //Remove the LRU item from cache
            if(l.size() == maxSize){
                Node last = l.back();
                m.erase(last.key); //Removes from Hashmap
                l.pop_back(); //Removes from LinkedList
            }

            Node n(key, value);
            l.push_front(n);
            m[key] = l.begin();
        }
    }

    int* getValue(string key){
        if(m.count(key) != 0){ //The value can be returned only when key is present
            auto it = m[key];

            int value = it->value;
            l.push_front(*it); //Updated as the most recently accessed entity in LL
            l.erase(it);    //Erased the original value from the LL
            m[key] = l.begin();
            return &l.begin()->value;
        }

        return NULL;
    }

    string mostRecentKey(){
        return l.front().key;
    }
};

int main(){
	LRUCache lru(3);
	lru.insertKeyValue("mango",10);
	lru.insertKeyValue("apple",20);
	lru.insertKeyValue("guava",30);
	cout << lru.mostRecentKey() <<endl;

	lru.insertKeyValue("mango",40);
	cout << lru.mostRecentKey() <<endl;

	int *orders = lru.getValue("mango");
	if(orders!=NULL){
		cout<<"Order of Mango "<<*orders <<endl;
	}


	lru.insertKeyValue("banana",20);

	if(lru.getValue("apple")==NULL){
		cout<<"apple doesn't exist";
	}

	if(lru.getValue("guava")==NULL){
		cout<<"guava doesn't exist";
	}

	if(lru.getValue("banana")==NULL){
		cout<<"banana doesn't exist";
	}
	if(lru.getValue("mango")==NULL){
		cout<<"mango doesn't exist";
	}

	

	return 0;
}	
