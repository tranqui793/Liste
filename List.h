/*!
 * @file List.h
 * @authors Lagha Oussama  & Max Caduff
 * @details list generic avec const et const iterators
 */
#ifndef LISTE_LIST_H
#define LISTE_LIST_H

#include <iostream>

template<typename T>
class List {

private:
    struct Node {
        //! valeur de l'element
        T data;

        //! Pointeur vers l'element d'avant.
        Node *prev;

        //! Pointeur vers le provhain element.
        Node *next;

    };
    size_t _size;
    Node *_head;
    Node *_tail;


    class AbstractIterator {
    public:
        /*!
         *
         * @param element
         */
        AbstractIterator(Node *element = nullptr);

        /*!
         *
         * @param it
         */
        AbstractIterator(const AbstractIterator &it);

        /*!
         *
         * @param it
         * @return
         */
        AbstractIterator &operator=(const AbstractIterator &it);

        /*!
         *
         */
        virtual ~AbstractIterator() = 0;

        /*!
         *
         * @param it
         * @return
         */

        bool operator==(const AbstractIterator &it) const;

        /*!
         *
         * @param it
         * @return
         */

        bool operator!=(const AbstractIterator &it) const;

    protected:
        Node *element;

    };

public:
    class Iterator : AbstractIterator {
    public:
        /*!
         *
         * @param ele
         */
        Iterator(Node *ele = nullptr) : AbstractIterator(ele) {};

        /*!
         *
         * @param it
         */
        Iterator(const AbstractIterator &it) : AbstractIterator(it) {};

        /*!
         *
         * @return
         */
        T &operator*();

        /*!
         *
         * @return
         */
        Node *operator->();

        /*!
         *
         * @return
         */
        Iterator &operator++();

        /*!
         *
         * @return
         */
        Iterator &operator--();

        /*!
         *
         * @return
         */
        Iterator operator++(int);

        /*!
         *
         * @return
         */
        Iterator operator--(int);

    };

    class ConstIterator : AbstractIterator {
    public:
        /*!
         *
         * @param ele
         */
        ConstIterator(Node *ele = nullptr) : AbstractIterator(ele) {};

        /*!
         *
         * @param it
         */
        ConstIterator(const AbstractIterator &it) : AbstractIterator(it) {};

        /*!
         *
         * @return
         */
        const T &operator*();

        /*!
         *
         * @return
         */
        const Node *operator->();

        /*!
         *
         * @return
         */
        ConstIterator &operator++();

        /*!
         *
         * @return
         */
        ConstIterator &operator--();

        /*!
         *
         * @return
         */
        const ConstIterator operator++(int);

        /*!
         *
         * @return
         */
        const ConstIterator operator--(int);
    };

    /*!
     *
     */
    List();

    /*!
     *
     * @param args
     */
    List(const std::initializer_list<T> &args);

    /*!
     *
     * @param otherList
     */
    List(const List<T> &otherList);

    /*!
     *
     * @return
     */
    size_t size() const;

    /*!
     *
     * @param ele
     */
    void insert(const T &ele);

    /*!
     *
     * @param ele
     */
    void append(const T &ele);

    /*!
     *
     * @param ele
     */
    void remove(const T &ele);

    /*!
     *
     * @param pos
     */
    void removeAt(const size_t pos);

    /*!
     *
     * @param ele
     * @return
     */
    int find(const T &ele);

    /*!
     *
     * @param otherList
     * @return
     */
    List &operator=(const List<T> &otherList);

    /*!
     *
     * @param args
     * @return
     */
    List &operator=(const std::initializer_list<T> &args);

    /*!
     *
     * @param pos
     * @return
     */
    T operator[](const size_t pos) const;

    /*!
     *
     * @param pos
     * @return
     */
    T &operator[](const size_t pos);

    /*!
     *
     * @return
     */
    Iterator begin();

    /*!
     *
     * @return
     */
    Iterator end();

    /*!
     *
     * @return
     */
    ConstIterator constBegin();

    /*!
     *
     * @return
     */
    ConstIterator constEnd();

private:
    /*!
     * pour factoriser le code
     */
    /*!
     * creer une liste vide
     */
    void initList();
    /*!
     *
     * @param it Iterator de l'element a supprimer
     */
    void deleteElement(Iterator &it) {

        it->prev->next = it->next;
        it->next->prev = it->prev;
        delete it.operator->();
    }
    /*!
     * creer une liste depuis une autre liste
     * @param otherList
     */
    void createNewListFromOtherList(const List<T> &otherList) {
        initList();
        for (auto it = otherList.constBegin(); it != otherList.constEnd(); ++it) {
            append(*it);
        }
    }
    /*!
     * creer une liste depuis une liste initializer
     * @param args
     */
    void createNewListFromInitilizer(const std::initializer_list<T> &args){
        initList();
        for (auto it = args.begin(); it != args.end(); ++it) {
            append(*it);
        }
    }
    /*!
     * supprime tt les elements de la liste
     */
    void clearList() {
        for (List<T>::Iterator it = begin(); it != end(); ++it) {
            delete it.operator->();
        }

        delete _head;
        delete _tail;

        _size = 0;
    }
};

template<typename T>
List<T>::List() {
    initList();
}

template<typename T>
void List<T>::initList() {
    _head = new Node;
    _tail = new Node;
    _head->next = _tail;
    _tail->prev = _head;
    _size = 0;
}

template<typename T>
List<T>::List(const std::initializer_list<T> &args) {
    createNewListFromInitilizer(args);
}

template<typename T>
List<T>::List(const List<T> &otherList) {
    createNewListFromOtherList(otherList);
}

template<typename T>
void List<T>::append(const T &ele) {
    Node *aux = new Node;
    aux->data = ele;
    if (_size != 0) {
        Node *t = _tail->prev;
        _tail->prev = aux;
        aux->next = _tail;
        t->next = aux;
        aux->prev = t;

    } else {
        _head->next = aux;
        aux->prev = _head;
        _tail->prev = aux;
        aux->next = _tail;
    }
    _size++;
}

template<typename T>
void List<T>::insert(const T &ele) {
    //le meme code que append donc on peut faire appel a append pour factoriser
    append(ele);
}

template<typename T>
size_t List<T>::size() const { return _size; }

template<typename T>
void List<T>::remove(const T &ele) {
    for (Iterator it = begin(); it != end(); ++it) {
        if (*it == ele) {
            deleteElement(it);
            return;
        }
    }
}

template<typename T>
void List<T>::removeAt(const size_t pos) {
    if (pos >= _size) {
        throw std::out_of_range("out of bounds");
    }
    Iterator it = begin();
    for (size_t i = 0; i < pos; ++i) {
        ++it;
    }
    deleteElement(it);
}

template<typename T>
int List<T>::find(const T &ele) {
    int index = 0;

    for (ConstIterator it = constBegin(); it != constEnd(); ++it) {
        if (*it == ele) {
            return index;
        }

        ++index;
    }

    return -1;
}

template<typename T>
typename List<T>::Iterator List<T>::begin() {
    return Iterator(_head->next);
}

template<typename T>
typename List<T>::Iterator List<T>::end() {
    return Iterator(_tail);
}

template<typename T>
typename List<T>::ConstIterator List<T>::constBegin() {
    return ConstIterator(_head->next);
}

template<typename T>
typename List<T>::ConstIterator List<T>::constEnd() {
    return ConstIterator(_tail);
}
template <typename T>
List<T>& List<T>::operator=(const std::initializer_list<T> &args) {
    clearList();
    createNewListFromInitilizer(args);
    return *this;
}
template <typename T>
List<T>& List<T>::operator=(const List<T>& otherList) {
    clearList();
    createNewListFromOtherList(otherList);
    return *this;
}
#endif //LISTE_LIST_H
