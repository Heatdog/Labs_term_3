//
// Created by User on 06.09.2021.
//

#ifndef LAB_1_ALG_H
#define LAB_1_ALG_H

template <class T>
struct Node{
    explicit Node(T data = T(), Node *next = nullptr):data(data), next(next){} // конструктор для ноды
    T data;
    Node* next; // следующий элемент
};

template <class T>
class Line{
public:
    explicit Line():head(nullptr), tail(nullptr){}
    ~Line();
    void push_back(T &data);
    Node<T> *get_head() const;
private:
    Node<T> *head; // начало списка
    Node<T> *tail;
};


template <class T>
void Line<T>::push_back(T &data) {
    if (head == nullptr){
        head = new Node<T>(data);
        tail = head;
    } else{
        Node<T> *ptr = new Node<T>(data);
        tail->next = ptr;
        tail = ptr;
    }
}

template <class T>
Node<T> *Line<T>::get_head() const {
    return head;
}

template <class T>
Line<T>::~Line<T>() {
    Node<T> *ptr = head, *ptr_prev = nullptr;
    while (ptr != nullptr){
        ptr_prev = ptr;
        ptr = ptr->next;
        delete ptr_prev;
    }
}


#endif //LAB_1_ALG_H
