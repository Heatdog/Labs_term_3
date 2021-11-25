//
// Created by User on 23.11.2021.
//

#ifndef LAB4_UNORDEDNODE_H
#define LAB4_UNORDEDNODE_H

/*!
 * \file
 * \brief Заголовочный файл с описанием unordered_map (собственная реализация)
 */

#include <iostream>
#include <iterator>

namespace Lab4{
    // ------------------------- Нода ------------------------------------
    template<class Key, class Value>
    struct Node{
        typedef std::pair<const Key, Value> Pair;
        explicit Node(Pair data, Node* next_ = nullptr) : next(next_), pair(data), next_list(nullptr), prev_list(nullptr){}
        Node* next;
        Pair pair;
        Node* next_list;
        Node* prev_list;
    };

    // ----------------------- Двусвязный список для связи элементов ----------------
    template<class Key, class Value>
    struct list{
        Node<Key, Value> *head; ///< Начало списка
        Node<Key, Value> *tail; ///< Конец списка

        list() : head(nullptr), tail(nullptr){}
        void push_front(Node<Key, Value> *ptr) noexcept;
        void erase(Node<Key, Value> *ptr);
        list& operator=(list<Key, Value> const &other){
            if (this != &other){
                head = other.head;
                tail = other.tail;
            }
            return *this;
        }
    };

    // добавить в начало
    template<class Key, class Value>
    void list<Key, Value>::push_front(Node<Key, Value> *ptr) noexcept{
        if (head == nullptr && tail == nullptr){
            head = ptr;
            tail = ptr;
            ptr->next_list = ptr->prev_list = nullptr;
        } else{
            Node<Key, Value> *ptr_prev = head;
            ptr->next_list = ptr_prev;
            ptr_prev->prev_list = ptr;
            head = ptr;
        }
    }

    // ----------------- Хэш таблица ------------------------------------
    template<class Key, class Value, class Hash = std::hash<Key>, class EqualTo = std::equal_to<Key>>
    class unordered_map{
    public:
        typedef std::pair<const Key, Value> Pair;

        template<class Iter>
        struct Iterator : public std::iterator<std::bidirectional_iterator_tag, Iter>{ // итератор (двунаправленный)
        private:
            Iter *data;
        public:
            explicit Iterator(Iter* const other) : data(other){}
            bool operator != (Iterator const &other) const{return data != other.data;}
            bool operator == (Iterator const &other) const{return data == other.data;}
            const Pair &operator*() {return (data->pair);}
            const Pair *operator->() {return &(data->pair);}
            Iter *get_data() const{return data;}
            Iterator& operator++(){
                data = data->next_list;
                return *this;
            }
            Iterator& operator--(){
                data = data->prev_list;
                return *this;
            }
            Iterator operator++(int){
                Iterator temp(data);
                ++(*this);
                return temp;
            }
            Iterator operator--(int){
                Iterator temp(data);
                --(*this);
                return temp;
            }
        };

        typedef Iterator<Node<Key, Value>> iterator;
        typedef Iterator<const Node<Key, Value>> const_iterator;
    private:
        struct forward_list{ // односвязный список, для основы хэш-таблицы
            forward_list() : count(0), head(nullptr){}
            ~forward_list(){
                Node<Key, Value> *ptr_prev = nullptr;
                for (auto ptr = head; ptr != nullptr;){
                    ptr_prev = ptr;
                    ptr = ptr->next;
                    delete ptr_prev;
                }
            }
            forward_list& operator=(forward_list const &other){
                if (this != &other){
                    count = other.count;
                    for (auto ptr = head; ptr != nullptr; ptr = ptr->next){
                        push_front(ptr->pair);
                    }
                }
                return *this;
            }
            void push_front(Pair data){
                head = new Node<Key, Value>(data, head);
                count++;
            }
            iterator erase(const Key &key);
            int count;
            Node<Key, Value> *head;
        };

        // ------------ приватные поля таблицы ---------------
        forward_list* table;
        list<Key, Value> list_iterator;
        int buckets_count;
        int size_;
        double max_load_factor;
        // ----------------------------------------------------

        const_iterator find_in_bucket(Key const &key, forward_list const &list) const;
        iterator find_in_bucket(Key const &key, forward_list const &list);
    public:
        unordered_map() : buckets_count(10), size_(0), max_load_factor(0.5){
            table = new forward_list[buckets_count];
        }
        explicit unordered_map(int count) : buckets_count(count), size_(0), max_load_factor(0.5){
            table = new forward_list[buckets_count];
        }
        ~unordered_map(){
            delete[] table;
        }
        unordered_map& operator=(unordered_map &&other) noexcept{
            delete[] table;
            buckets_count = other.buckets_count;
            size_ = other.size_;
            max_load_factor = other.max_load_factor;
            table = other.table;
            list_iterator = other.list_iterator;
            other.table = nullptr;
            return *this;
        }
        unordered_map& operator=(unordered_map const &other){
            if (this != &other){
                delete[] table;
                buckets_count = other.buckets_count;
                size_ = other.size_;
                max_load_factor = other.max_load_factor;
                table = new forward_list[buckets_count];
                for (int i = 0; i < buckets_count; i++){
                    table[i] = other.table[i];
                }
                list_iterator = other.list_iterator;
            }
            return *this;
        }
        unordered_map(unordered_map const &other){
            buckets_count = other.buckets_count;
            size_ = other.size_;
            max_load_factor = other.max_load_factor;
            table = new forward_list[buckets_count];
            for (int i = 0; i < buckets_count; i++){
                table[i] = other.table[i];
            }
            list_iterator = other.list_iterator;
        }

        std::pair<iterator, bool> emplace(Pair data);
        int size() const {return size_;}
        iterator begin(){return iterator(list_iterator.head);}
        iterator end(){return iterator(nullptr);}
        const_iterator begin() const {return const_iterator(list_iterator.head);}
        const_iterator end() const {return const_iterator(nullptr);}
        const_iterator find(Key const &key) const;
        iterator find(Key const &key);
        unsigned int erase(Key const &key);
        void rehash(int count);
    };


    template<class Key, class Value, class Hash, class EqualTo>
    std::pair<typename unordered_map<Key, Value, Hash, EqualTo>::iterator, bool> unordered_map<Key, Value, Hash, EqualTo>::emplace(Pair data){
        Hash type_hash;
        unsigned int hash = type_hash(data.first) % buckets_count;
        iterator it = find_in_bucket(data.first, table[hash]);
        if (it == end()){
            if (size_ + 1 > buckets_count*max_load_factor){
                rehash(buckets_count*2);
                hash = type_hash(data.first) % buckets_count;
            }
            table[hash].push_front(data);
            list_iterator.push_front(table[hash].head);
            size_++;
            return std::make_pair(iterator(list_iterator.head), true);
        }
        return std::make_pair(it, false);
    }

    template<class Key, class Value, class Hash, class EqualTo>
    typename unordered_map<Key, Value, Hash, EqualTo>::const_iterator unordered_map<Key, Value, Hash, EqualTo>::find_in_bucket(const Key &key, forward_list const &list) const{
        for (Node<Key, Value>* ptr = list.head; ptr != nullptr; ptr = ptr->next){
            EqualTo eq;
            if (eq(ptr->pair.first, key)){
                return const_iterator(ptr);
            }
        }
        return end();
    }

    template<class Key, class Value, class Hash, class EqualTo>
    typename unordered_map<Key, Value, Hash, EqualTo>::iterator unordered_map<Key, Value, Hash, EqualTo>::find_in_bucket(const Key &key, forward_list const &list){
        for (Node<Key, Value>* ptr = list.head; ptr != nullptr; ptr = ptr->next){
            EqualTo eq;
            if (eq(ptr->pair.first, key)){
                return iterator(ptr);
            }
        }
        return end();
    }

    template<class Key, class Value, class Hash, class EqualTo>
    void unordered_map<Key, Value, Hash, EqualTo>::rehash(int count) {
        if (count < size_/max_load_factor){
            count = size_/max_load_factor;
        }
        unordered_map<Key, Value, Hash, EqualTo> new_map(count);
        for (auto i = begin(); i != end(); i++){
            new_map.emplace(*i);
        }
        *this = std::move(new_map);
    }

    template<class Key, class Value, class Hash, class EqualTo>
    typename unordered_map<Key, Value, Hash, EqualTo>::const_iterator unordered_map<Key, Value, Hash, EqualTo>::find(const Key &key) const {
        Hash type_hash;
        const unsigned int hash = type_hash(key) % buckets_count;
        return find_in_bucket(key, table[hash]);
    }

    template<class Key, class Value, class Hash, class EqualTo>
    typename unordered_map<Key, Value, Hash, EqualTo>::iterator unordered_map<Key, Value, Hash, EqualTo>::find(const Key &key){
        Hash type_hash;
        const unsigned int hash = type_hash(key) % buckets_count;
        return find_in_bucket(key, table[hash]);
    }


    template<class Key, class Value, class Hash, class EqualTo>
    unsigned int unordered_map<Key, Value, Hash, EqualTo>::erase(const Key &key) {
        Hash type_hash;
        const unsigned int hash = type_hash(key) % buckets_count;
        iterator it = table[hash].erase(key);
        if (it == end()){
            return 0;
        }
        list_iterator.erase(it.get_data());
        delete it.get_data();
        size_--;
        return 1;
    }

    template<class Key, class Value, class Hash, class EqualTo>
    typename unordered_map<Key, Value, Hash, EqualTo>::iterator unordered_map<Key, Value, Hash, EqualTo>::forward_list::erase(const Key &key) {
        if (head == nullptr){
            return iterator(nullptr);
        }
        EqualTo eq;
        Node<Key, Value>* ptr_prev = nullptr;
        for (Node<Key, Value>* ptr = head; ptr != nullptr;){
            if (eq(ptr->pair.first,key)){
                if (ptr == head){
                    head = ptr->next;
                } else{
                    ptr_prev->next = ptr->next;
                }
                count--;
                return iterator(ptr);
            }
            ptr_prev = ptr;
            ptr = ptr->next;
        }
        return iterator(nullptr);
    }

    template<class Key, class Value>
    void list<Key, Value>::erase(Node<Key, Value>* ptr) {
        if (ptr->prev_list == nullptr && ptr->next_list == nullptr){
            head = nullptr;
            tail = nullptr;
        } else if (ptr == head){
            head = ptr->next_list;
            head->prev_list = nullptr;
        } else if (ptr == tail){
            tail = ptr->prev_list;
            tail->next_list = nullptr;
        } else {
            ptr->prev_list->next_list = ptr->next_list;
            ptr->next_list->prev_list = ptr->prev_list;
        }
    }
}


#endif //LAB4_UNORDEDNODE_H
