#ifndef MB_LIST_H
#define MB_LIST_H

template<typename _T>
struct MB_List_Item {
    _T value;
    MB_List_Item* next;
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
    }
    /**
     * @brief Add item to the back of the list
     * 
     * @param i the item
     */
    void push_back(_T _value){
        MB_List_Item<_T>* tmp = new MB_List_Item<_T>;
        tmp->value = _value;
        tmp->next = NULL;
        tail->next = tmp;
        tail = tmp;
        size++;
    }

    /**
     * @brief Add item to the front of the list
     * 
     * @param i the item
     */
    void push_front(_T _value){
        MB_List_Item<_T>* tmp = new MB_List_Item<_T>;
        tmp->value = _value;
        tmp->next = head;
        head = tmp;
        size++;
    }

    /**
     * @brief Removes the item from the list
     * Be aware: this function only removes the item from the list.
     * if the stored item is a pointer, the memory has to be cleared by the user!!
     * 
     * @param i a pointer to the item to remove
     */
    void remove(_T _value){
        size--;
    }

    /**
     * @brief Destroy the whole list
     * Be aware: this function only removes the items from the list.
     * if the stored item is a pointer, the memory has to be cleared by the user!!
     *  
     */
    void destroy(void);
};

#endif