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
#ifndef MB_LIST_H
#define MB_LIST_H

/**
 * @brief Singly linked list node
 * 
 * @tparam data_type type
 */
template<typename data_type>
struct MB_List_Item {
public:
    data_type value;
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
 * @tparam data_type type
 */
template<typename data_type>
struct MB_List_Iterator {
private:
    MB_List_Item<data_type>* _node;

public:
    MB_List_Iterator(){
        _node = NULL;
    }

    MB_List_Iterator(MB_List_Item<data_type>* n){
        _node = n;
    };

    /**
     * @brief return next node
     * 
     * @return MB_List_Item<data_type> 
     */
    MB_List_Iterator<data_type> next(void) const{
        _node = _node->next;
        return *this;
    }

    // Overload for the postincrement operator ++
    MB_List_Iterator<data_type> operator++(int) {
        MB_List_Iterator<data_type> temp = *this;
        _node = _node->next;
        return temp;
    }

    // Overload for the preincrement operator ++
    MB_List_Iterator<data_type>& operator++() {
        _node = _node->next;
        return *this;
    }

    MB_List_Iterator<data_type>& operator=(const MB_List_Iterator<data_type>& other){
        if(this != &other){
            _node = other._node;
        }
        return *this;
    }

    // Overload for the comparison operator !=
    bool operator!=(const MB_List_Iterator<data_type>& itr) const {
        return _node != itr._node;
    }

    // Overload for the comparison operator ==
    bool operator==(const MB_List_Iterator<data_type>& itr) const {
        return _node == itr._node;
    }

    // Overload for the dereference operator *
    data_type& operator*() const {
        return _node->value;
    }

    data_type* operator->() const{
        return &(_node->value);
    }
};

template<class data_type>
class MB_List {
private:
    MB_List_Item<data_type>* _head;
    MB_List_Item<data_type>* _tail;
    int _size;

public:
    /**
     * @brief Construct a new mb list object
     * 
     */
    MB_List(){
        _head = NULL;
        _tail = NULL;
        _size = 0;
    }
    /**
     * @brief Add item to the back of the list
     * 
     * @param value reference to the item
     */
    void push_back(data_type value){
        MB_List_Item<data_type>* tmp = new MB_List_Item<data_type>;
        tmp->value = value;
        _size++;
        if(_head == NULL){
            tmp->next = NULL;
            _head = tmp;
            _tail = tmp;
        }else{
            _tail->next = tmp;
            _tail = tmp;
        }
    }

    /**
     * @brief Add item to the front of the list
     * 
     * @param value reference to the item
     */
    void push_front(data_type value){
        MB_List_Item<data_type>* tmp = new MB_List_Item<data_type>;
        tmp->value = value;
        _size++;
        if(_head == NULL){
            tmp->next = NULL;
            _head = tmp;
            _tail = tmp;
        }else{
            tmp->next = _head;
            _head = tmp;
        }
    }
    /**
     * @brief remove the last item
     * Beware this is an expensive task
     * 
     */
    void pop_back(void){
        if(_head == NULL) return;
        if(_head->next == NULL){
            delete _head;
            _head = NULL;
            _tail = NULL;
        }else{
            MB_List_Item<data_type>* tmp = _head;
            MB_List_Item<data_type>* prev = NULL;
        
            while(tmp->next != NULL){
                prev = tmp;
                tmp = tmp->next;
            }

            prev->next = NULL;
            delete tmp;
        }
        _size--;
    }

    void pop_front(void){
        if(_head == NULL) return;
        MB_List_Item<data_type>* tmp = _head;
        _head = _head->next;
        delete tmp;
        _size--;
    }

    /**
     * @brief Removes all items matching the value
     * Be aware: this function only removes the item from the list.
     * if the stored item is a pointer, the memory has to be cleared by the user!!
     * 
     * @param value a reference to the item value
     */
    void remove(data_type value){
        MB_List_Item<data_type>* tmp = _head;
        MB_List_Item<data_type>* prev = NULL;
        while(tmp != NULL){
            if(tmp->value == value){
                // We have a match
                if(tmp == _head){
                    // Remove the head and relink
                    _head = tmp->next;
                    delete tmp;
                    // Start with the new head to find more matches
                    tmp = _head;
                }else if(tmp ==  _tail){
                    // Break the link of prev
                    prev->next = NULL;
                    _tail = prev;
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
                _size--;
            }else{
                prev = tmp;
                tmp = tmp->next;
            }
        }
    }

    void for_each(Callback<void(const data_type&)> c) const{
        MB_List_Item<data_type>* tmp = _head;
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
        return _size;
    }
    
    MB_List_Iterator<data_type> begin(void){
        return MB_List_Iterator<data_type>(_head);
    }

    MB_List_Iterator<data_type> end(void){
        return MB_List_Iterator<data_type>();
    }

    /**
     * @brief Destroy the whole list
     * Be aware: this function only removes the items from the list.
     * if the stored item is a pointer, the memory has to be cleared by the user!!
     *  
     */
    void empty(void){
        while(_size){
            pop_front();
        }
    }
};

#endif