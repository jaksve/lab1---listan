#include "List.h"
#include <iterator>
#include <utility>
#include <stdexcept>

template <typename T>
List<T>::List()
        : head{ std::make_unique<Node>()} , tail{}, sz{0}
{
    head->next = std::make_unique<Node>(T{}, head.get(), nullptr);
    tail = head->next.get();
}

template <typename T>
List<T>::List(List<T> const & other)
        : List{}
{
    for (Node* tmp {other.head->next.get()}; tmp != other.tail ; )
    {
        push_back(tmp->value);
        tmp = tmp->next.get();
    }
}

template <typename T>
List<T>::List(List && tmp) noexcept
        :List{}
{
    swap(tmp);
}
template <typename T>
List<T>::List(std::initializer_list<T> lst)
        : List{}
{
    for ( auto val : lst )
    {
        push_back(val);
    }
}
template <typename T>
void List<T>::push_front(T value)
{
    Node* old_first  {head->next.get()};
    head->next = std::make_unique<Node>(value, head.get(), std::move(head->next));
    old_first->prev = head->next.get();
    ++sz;
}

template <typename T>
void List<T>::push_back(T value)
{
    Node* old_last { tail->prev };
    old_last->next = std::make_unique<Node>(value, old_last, std::move(old_last->next));
    tail->prev = old_last->next.get();
    ++sz;
}

template <typename T>
bool List<T>::empty() const noexcept
{
    return head->next.get() == tail;
}

template <typename T>
T List<T>::back() const noexcept
{
    return tail->prev->value;
}

template <typename T>
T & List<T>::back() noexcept
{
    return tail->prev->value;
}

template <typename T>
T List<T>::front() const noexcept
{
    return head->next->value;
}

template <typename T>
T & List<T>::front() noexcept
{
    return head->next->value;
}

template <typename T>
T & List<T>::at(int idx)
{
    return const_cast<T &>(static_cast<List const *>(this)->at(idx));
}

template <typename T>
T const & List<T>::at(int idx) const
{
    if (idx >= sz)
        throw std::out_of_range{"Index not found"};
    Node* tmp {head->next.get()};
    while ( idx > 0 )
    {
        tmp = tmp->next.get();
        --idx;
    }
    return tmp->value;
}

template <typename T>
int List<T>::size() const noexcept
{
    return sz;
}

template <typename T>
void List<T>::swap(List & other) noexcept
{
    using std::swap;
    swap(head, other.head);
    swap(tail, other.tail);
    swap(sz, other.sz);
}

template <typename T>
List<T> & List<T>::operator=(List const & rhs) &
{
    List{rhs}.swap(*this);
    return *this;
}

template <typename T>
List<T> & List<T>::operator=(List && rhs)& noexcept
{
    swap(rhs);
    return *this;
}

template <typename T>
auto List<T>::begin()const
{
    return List<T>::List_Iterator(*(head->next));
}

template <typename T>
auto List<T>::end()const
{
    return List_Iterator(*tail);
}

template <typename T>
List<T>::List_Iterator:: List_Iterator( List<T>::Node &arg):memb{&arg} {}

template <typename T>
List<T>::List_Iterator:: List_Iterator (List_Iterator && arg):memb{arg.memb}
{}

template <typename T>
List<T>::List_Iterator::List_Iterator(List_Iterator const& arg): memb{arg.memb}
{}

template <typename T>
auto& List<T>::List_Iterator::operator++()
{
    if( memb -> next != nullptr)
    {
        memb = &(*(memb->next) );
    }
    return *this;
}

template <typename T>
auto List<T>::List_Iterator::operator ++ (int)
{
    List_Iterator temp(*memb);
    ++*this;
    return temp;
}

template <typename T>
auto& List<T>::List_Iterator::operator -- ()
{
    if(memb->prev->prev)
    {
        memb = memb->prev;
    }
    return *this;
}

template <typename T>
auto List<T>::List_Iterator::operator - (List_Iterator const& rhs)const
{
    int temp{0};
    List<T>::List_Iterator temp_it = *this;

    while (temp_it != rhs && temp_it.memb->prev->prev != nullptr)
    {
        --temp_it;
        temp++;

    }
    if( temp_it == rhs)
    {
        return temp;
    }
    temp = 0;
    temp_it = *this;
    while(temp_it != rhs && temp_it.memb->next->next != nullptr)
    {
        ++temp_it;
        --temp;

    }
    if( temp_it == rhs)
    {
        return temp;
    }
    throw std::range_error{"oopsie doopsie"};

}

template<typename T>
T& List<T>::List_Iterator::operator*()
{
    return memb->value;
}
template <typename T>
bool List<T>::List_Iterator:: operator !=(List_Iterator const& rhs)const
{
    return memb != rhs.memb;
}

template <typename T>
bool List<T>::List_Iterator::operator == (List_Iterator const& rhs)const
{
    return (memb == rhs.memb);
}
