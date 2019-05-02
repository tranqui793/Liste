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

        //! Pointeur vers le prochain element.
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
         * @param it
         * @return
         */

        bool operator== (const AbstractIterator &it) const;

        /*!
         *
         * @param it
         * @return
         */

        bool operator!= (const AbstractIterator &it) const;
        
        /*!
         *
         * @return
         */
        T& operator* () const;
        
        /*!
         *
         * @return
         */
        Node* operator->() const;

        void operator++();

        void operator--();
        
        bool hasNext () const;
        
        bool hasPrev () const;
        

    protected:
        Node* element;

    };

public:
    class Iterator : public AbstractIterator {
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

    class ConstIterator : public AbstractIterator {
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
        const T& operator*() const;

        /*!
         *
         * @return
         */
        const Node* operator->() const;

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
        ConstIterator operator++(int);

        /*!
         *
         * @return
         */
        ConstIterator operator--(int);
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
    Iterator begin() const;

    /*!
     *
     * @return
     */
    Iterator end() const;

    /*!
     *
     * @return
     */
    ConstIterator constBegin() const;

    /*!
     *
     * @return
     */
    ConstIterator constEnd() const;

    ~List();
    
    // surcharge de l'opérateur de flux
    friend std::ostream& operator<<(std::ostream& os, const List<T>& list)  {
        typename List<T>::Iterator it = list.begin();
        do
            os << *it << " ";
        while( it++ != list.end() );
        return os;
    }
   

private:
    /*!
     * pour factoriser le code
     */
    /*!
     * crée une liste vide
     */
    void initList();

    T &getElem(size_t index) const;

    /*!
     *
     * @param it Iterator sur l'element a supprimer
     */
    void deleteElement(Iterator &it) {


        Node * elt = it.operator->();
        if ( elt != nullptr) {
            
            if (elt->next) {
                // pas le dernier element
                it->next->prev = it->prev;
            }
            else {
                _tail = elt->prev;
            }
            if (elt->prev) {
                // pas le premier element
                it->prev->next = it->next;
            }
            else {
                _head = elt->next;
            }
            
            delete it.operator->();
        }
    }

    /*!
     * creer une liste depuis une autre liste
     * @param otherList
     */
    void createNewListFromOtherList(const List<T> &otherList) {
        initList();
        for (auto it = otherList.constBegin(); it != otherList.constEnd(); ++it) {
            append(it->data);
        }
    }

    /*!
     * creer une liste depuis une liste initializer
     * @param args
     */
    void createNewListFromInitilizer(const std::initializer_list<T> &args) {
        initList();
        for (auto el : args) {
            append(el);
        }
    }

    /*!
     * supprime tous les elements de la liste
     */
    void clearList() {
        
        if (_size != 0) {
            
            List<T>::Node* tmp = _head;
            for (List<T>::Iterator it = begin(); it != end(); ) {
                ++it;
                delete tmp;
                tmp = it.operator->();
            }
            _head = _tail = nullptr;
            _size = 0;
        }
    }
};



/*****       LIST DEFINITION       *****/


template<typename T>
List<T>::List() {
    initList();
}

template<typename T>
void List<T>::initList() {
    
    _head = nullptr;
    _tail = nullptr;
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
    Node *newEl = new Node {ele, _tail, nullptr};
    if (_size != 0) {
        _tail->next = newEl;
    } else {
        _head = newEl;
    }
    _tail = newEl;
    _size++;
}

template<typename T>
void List<T>::insert(const T &ele) {
    Node *newEl = new Node {ele, nullptr, _head};
    if (_size != 0) {
        _head->prev = newEl;
    } else {
        _tail = newEl;
    }
    _head = newEl;
    _size++;
}

template<typename T>
List<T>::~List() {
    clearList();
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
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(_head);
}

template<typename T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator(_tail);
}

template<typename T>
typename List<T>::ConstIterator List<T>::constBegin() const {
    return ConstIterator(_head->next);
}

template<typename T>
typename List<T>::ConstIterator List<T>::constEnd() const {
    return ConstIterator(_tail);
}

template<typename T>
List<T> &List<T>::operator=(const std::initializer_list<T> &args) {
    clearList();
    createNewListFromInitilizer(args);
    return *this;
}

template<typename T>
List<T> &List<T>::operator=(const List<T> &otherList) {
    clearList();
    createNewListFromOtherList(otherList);
    return *this;
}

template<typename T>
T List<T>::operator[](const size_t index) const {
    return getElem(index);
}

template<typename T>
T &List<T>::operator[](const size_t index) {
    return getElem(index);
}

template<typename T>
T &List<T>::getElem(size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("out of bounds");
    }

    Iterator it = constBegin();

    for (size_t i = 0; i < index; ++i) {
        ++it;
    }

    return *it;
}






/*****      ITERATORS DEFINITION     *****/


template<typename T>
typename List<T>::Node* List<T>::AbstractIterator::operator->() const {
    return element;
}

template<typename T>
T& List<T>::AbstractIterator::operator*() const {
    return element->data;
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    AbstractIterator::operator++();
    return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator temp(*this);
    operator++();
    return temp;
}

template<typename T>
typename List<T>::Iterator &List<T>::Iterator::operator--() {
    AbstractIterator::operator--();
    return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {
    Iterator temp(*this);
    operator--();
    return temp;
}

template<typename T>
const T& List<T>::ConstIterator::operator*() const {
    return AbstractIterator::element->data;
}

template<typename T>
const typename List<T>::Node* List<T>::ConstIterator::operator->() const {
    return AbstractIterator::element;
}

template<typename T>
typename List<T>::ConstIterator &List<T>::ConstIterator::operator++() {
    AbstractIterator::operator++();
    return *this;
}

template<typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int) {
    ConstIterator temp(*this);
    operator++();
    return temp;
}

template<typename T>
typename List<T>::ConstIterator &List<T>::ConstIterator::operator--() {
    AbstractIterator::operator--();
    return *this;
}

template<typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int) {
    ConstIterator temp(*this);
    operator--();
    return temp;
}

template<typename T>
List<T>::AbstractIterator::AbstractIterator(Node *element) : element(element) {}

template<typename T>
List<T>::AbstractIterator::AbstractIterator(const AbstractIterator &it) : element(it.element) {}


template<typename T>
typename List<T>::AbstractIterator &List<T>::AbstractIterator::operator=(const AbstractIterator &it) {
    if (&it != this) {
        this->element = it.element;
    }
    return *this;
}

template<typename T>
bool List<T>::AbstractIterator::operator==(const AbstractIterator &it) const {
    return it.element == element;
}

template<typename T>
bool List<T>::AbstractIterator::operator!=(const AbstractIterator &it) const {
    return element != it.element;
}

template<typename T>
bool List<T>::AbstractIterator::hasNext () const {
    return element->next != nullptr;
}

template<typename T>
bool List<T>::AbstractIterator::hasPrev () const {
    return element->prev != nullptr;
}



template<typename T>
void List<T>::AbstractIterator::operator++() {
    if (element != nullptr) {
        element = element->next;
    } else {
        throw std::out_of_range("out of range");
    }
}

template<typename T>
void List<T>::AbstractIterator::operator--() {
    if (AbstractIterator::element != nullptr) {
        AbstractIterator::element = AbstractIterator::element->prev;
    } else {
        throw std::out_of_range("out of range");
    }
}


#endif //LISTE_LIST_H
