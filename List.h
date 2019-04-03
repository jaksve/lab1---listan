#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include <iterator>

namespace listerator {
    template<typename T>
    class List {
    public:
        using value_type = T;

        List();

        List(List const &);

        List(List &&) noexcept;

        List(std::initializer_list<value_type>);

        List &operator=(List const &) &;

        List &operator=(List &&) & noexcept;

        void push_front(value_type);

        void push_back(value_type);

        value_type back() const noexcept;

        value_type &back() noexcept;

        value_type front() const noexcept;

        value_type &front() noexcept;

        value_type &at(int idx);

        value_type const &at(int idx) const;

        int size() const noexcept;

        bool empty() const noexcept;

        void swap(List &other) noexcept;

        friend class List_Iterator;

    private:
        struct Node;
    public:
        class List_Iterator {
        public:
            using value_type = T;
            using iterator_category = std::bidirectional_iterator_tag;
            using difference_type = int;
            using pointer = List<T>::Node *;
            using reference = T &;

            auto operator++(int);

            auto &operator++();

            auto &operator--();

            auto operator-(List_Iterator const &rhs) const;

            bool operator!=(List_Iterator const &rhs) const;

            bool operator==(List_Iterator const &rhs) const;

            List_Iterator(List_Iterator &&arg);

            List_Iterator(List_Iterator const &arg);

            value_type &operator*();

            friend class List;

            List_Iterator(List<T>::Node &arg);

        private:
            pointer memb;

        };

        auto begin() const;

        auto end() const;

    private:
        struct Node {
            using value_type = T;

            Node() = default;

            Node(const Node &) = delete;

            Node &operator=(const Node &) = delete;

            Node(value_type v, Node *p, std::unique_ptr<Node> n)
                    : value{v}, prev{p}, next{std::move(n)} {}

            value_type value{};
            Node *prev{};
            std::unique_ptr<Node> next{};
        };

        std::unique_ptr<Node> head{};
        Node *tail{};
        int sz{};
    };

/*
class List<T>::List_Iterator
{
public:
    using value_type = T;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = int;
    using pointer = Node*;
    using reference = T&;

    List_Iterator operator ++(int);
    List_Iterator& operator ++();
    List_Iterator& operator --();

    difference_type operator - (List_Iterator const& rhs)const;

    bool operator != (List_Iterator const& rhs)const;
    bool operator == (List_Iterator const& rhs)const;

    List_Iterator (List_Iterator && arg);
    List_Iterator (List_Iterator const& arg);
    value_type & operator *();
    friend class List;
    List_Iterator(List::Node & arg);

private:
    pointer memb;

};
*/

#include "List.cc"

}

#endif //LIST_H