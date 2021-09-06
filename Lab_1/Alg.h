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
    explicit Line():head(nullptr), tail(nullptr), n(0){}
    ~Line();
    void push_back(T &data);
    Node<T> *get_head() const;
    Node<T> *get_tail() const;
    int get_number() const;
    void set_number(int x);
private:
    Node<T> *head; // начало списка
    Node<T> *tail;
    int n;
};


template <class T>
void Line<T>::push_back(T &data) {
    if (head == nullptr){
        try{
            head = new Node<T>(data);
        }catch (std::bad_alloc const &a){
            std::cout << "Can`t allocate memory " << a.what() << std::endl;
            return;
        }
        tail = head;
    } else{
        Node<T> *ptr = nullptr;
        try{
            ptr = new Node<T>(data);
        }catch (std::bad_alloc const &a){
            std::cout << "Can`t allocate memory " << a.what() << std::endl;
            return;
        }
        tail->next = ptr;
        tail = ptr;
    }
    n++;
}

template <class T>
Node<T> *Line<T>::get_head() const {
    return head;
}

template <class T>
Node<T> *Line<T>::get_tail() const {
    return tail;
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

template <class T>
int Line<T>::get_number() const {
    return n;
}

template<class T>
void Line<T>::set_number(int x) {
    n = x;
}




#endif //LAB_1_ALG_H
