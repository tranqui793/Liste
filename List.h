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
        Node(Node *next = nullptr, Node *prev = nullptr) : next(next), prev(prev) {}

        virtual ~Node() = default;
    };

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
        Node* element;

    };

public:
    class Iterator :AbstractIterator{
    public:
        Iterator(Node* ele= nullptr):AbstractIterator(ele){};
        Iterator(const AbstractIterator& it):AbstractIterator(it){};
        T&operator*();
        Node*operator->();
        Iterator&operator++();
        Iterator&operator--();
        Iterator operator++(int);
        Iterator operator--(int);

    };
};

#endif //LISTE_LIST_H
