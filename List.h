#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
class List_Iterator;
class List
{
public:
    List();
    List(List const &);

    List(List &&) noexcept;
    List(std::initializer_list<int>);

    List & operator=(List const &)&;
    List & operator=(List &&)& noexcept;

    void push_front(int);
    void push_back(int);

    int back() const noexcept;
    int & back() noexcept;

    int front() const noexcept;
    int & front() noexcept;

    int & at(int idx);
    int const & at(int idx) const;

    int size() const noexcept;
    bool empty() const noexcept;

    void swap(List & other) noexcept;

    friend class List_Iterator;

    List_Iterator begin() const;
    List_Iterator end() const;
private:
    struct Node
    {
        Node() = default;
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        Node(int v, Node* p, std::unique_ptr<Node> n)
                : value{v}, prev{p}, next{std::move(n)} {}
        int value {};
        Node* prev{};
        std::unique_ptr<Node> next{};
    };
    std::unique_ptr<Node> head{};
    Node* tail{};
    int sz {};
};


class List_Iterator
{
public:
    List_Iterator operator ++(int);
    List_Iterator& operator ++();

    bool operator !=(List_Iterator const& rhs)const;
    List_Iterator (List_Iterator && arg);
    List_Iterator (List_Iterator const& arg);
    int& operator *();
    friend class List;
private:
    List_Iterator(List::Node & arg);
    List::Node* memb;

};



#endif //LIST_H