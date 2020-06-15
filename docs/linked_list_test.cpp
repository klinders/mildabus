/*
 * MIT License
 *
 * Copyright (c) 2020 klinders
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#define NULL nullptr
#include <iostream>
using namespace std;
/**
 * @brief Singly linked list node
 * 
 * @tparam _T type
 */
template<typename _T>
struct MB_List_Item {
public:
    _T value;
    MB_List_Item* next;

    bool operator==(const MB_List_Item& o2){
        // Not the same as the value is not the same
        return this == o2;
    }

    bool operator!=(const MB_List_Item& o2){
        // Not the same as the value is not the same
        return this != o2;
    }
};

/**
 * @brief Singly linked list iterator
 * 
 * @tparam _T type
 */
template<typename _T>
struct MB_List_Iterator {
public:
    MB_List_Item<_T>* node;

public:
     MB_List_Iterator(){
         node = NULL;
     }

    MB_List_Iterator(MB_List_Item<_T>* n){
        node = n;
    }

    /**
     * @brief return next node
     * 
     * @return MB_List_Item<_T> 
     */
    MB_List_Iterator<_T> next(void) const{
        node = node->next;
        return *this;
    }

    // Overload for the postincrement operator ++
    MB_List_Iterator<_T> operator++(int) {
        MB_List_Iterator<_T> temp = *this;
        node = node->next;
        return temp;
    }

    // Overload for the preincrement operator ++
    MB_List_Iterator<_T>& operator++() {
        node = node->next;
        return *this;
    }

    MB_List_Iterator<_T>& operator=(const MB_List_Iterator<_T>& other){
        if(this != &other){
            node = other.node;
        }
        return *this;
    }

    // Overload for the comparison operator !=
    bool operator!=(const MB_List_Iterator<_T>& itr) const {
        return node != itr.node;
    }

    // Overload for the comparison operator ==
    bool operator==(const MB_List_Iterator<_T>& itr) const {
        return node == itr->node;
    }

    // Overload for the dereference operator *
    _T& operator*() const {
        return node->value;
    }
    
        // Overload for the dereference operator *
    _T* operator->() const {
        return &(node->value);
    }

};

template<class _T>
class MB_List {
private:
    MB_List_Item<_T>* head;
    MB_List_Item<_T>* tail;
    int size;

public:
    /**
     * @brief Construct a new mb list object
     * 
     */
    MB_List(){
        head = NULL;
        tail = NULL;
        size = 0;
    }
    /**
     * @brief Add item to the back of the list
     * 
     * @param _value reference to the item
     */
    void push_back(_T _value){
        MB_List_Item<_T>* tmp = new MB_List_Item<_T>;
        tmp->value = _value;
        size++;
        if(head == NULL){
            tmp->next = NULL;
            head = tmp;
            tail = tmp;
        }else{
            tail->next = tmp;
            tail = tmp;
        }
    }

    /**
     * @brief Add item to the front of the list
     * 
     * @param _value reference to the item
     */
    void push_front(_T _value){
        MB_List_Item<_T>* tmp = new MB_List_Item<_T>;
        tmp->value = _value;
        size++;
        if(head == NULL){
            tmp->next = NULL;
            head = tmp;
            tail = tmp;
        }else{
            tmp->next = head;
            head = tmp;
        }
    }
    
    /**
     * @brief remove the last item
     * Beware this is an expensive task
     * 
     */
    void pop_back(void){
        if(head == NULL) return;
        if(head->next == NULL){
            delete head;
            head = NULL;
            tail = NULL;
        }else{
            MB_List_Item<_T>* tmp = head;
            MB_List_Item<_T>* prev = NULL;
        
            while(tmp->next != NULL){
                prev = tmp;
                tmp = tmp->next;
            }

            prev->next = NULL;
            delete tmp;
        }
        size--;
    }

    void pop_front(void){
        if(head == NULL) return;
        MB_List_Item<_T>* tmp = head;
        head = head->next;
        delete tmp;
        size--;
    }

    /**
     * @brief Removes all items matching the value
     * Be aware: this function only removes the item from the list.
     * if the stored item is a pointer, the memory has to be cleared by the user!!
     * 
     * @param _value a reference to the item value
     */
    void remove(_T _value){
        MB_List_Item<_T>* tmp = head;
        MB_List_Item<_T>* prev = NULL;
        while(tmp != NULL){
            if(tmp->value == _value){
                // We have a match
                if(tmp == head){
                    // Remove the head and relink
                    head = tmp->next;
                    delete tmp;
                    // Start with the new head to find more matches
                    tmp = head;
                }else if(tmp == tail){
                    // Break the link of prev
                    prev->next = NULL;
                    tail = prev;
                    delete tmp;
                    // Set tmp to null to end the loop
                    tmp = NULL;
                }else{
                    // Remove the item and relink
                    prev->next = tmp->next;
                    delete tmp;
                    // Change tmp to the new next
                    tmp = prev->next;
                }
                size--;
            }else{
                prev = tmp;
                tmp = tmp->next;
            }
        }
    }

    void for_each(void (*c)(MB_List_Item<_T>)){
        MB_List_Item<_T>* tmp = head;
        while(tmp != NULL){
            c(*tmp);
            tmp = tmp->next;
        }
    }
    /**
     * @brief Get the Size of the list
     * 
     * @return const int size
     */
    const int getSize(void) const{
        return size;
    }
    
    MB_List_Iterator<_T> begin(void){
        return MB_List_Iterator<_T>(head);
    }

    MB_List_Iterator<_T> end(void){
        return MB_List_Iterator<_T>();
    }

    /**
     * @brief Destroy the whole list
     * Be aware: this function only removes the items from the list.
     * if the stored item is a pointer, the memory has to be cleared by the user!!
     *  
     */
    void destroy(void){
        while(size){
            pop_front();
        }
    }
};

template<class _T>
void print(MB_List_Item<_T> item){
    cout << item.value << endl;
}

int main(void){
    MB_List<int> l;
    l.push_front(1);
    l.push_front(2);
    l.push_front(3);
    l.push_front(4);
    l.push_front(1);

    l.destroy();
    
    
    l.for_each(&print);
    
    MB_List_Iterator<int> it;
    
    for(int el : l){
        cout << el << endl;
    }
}