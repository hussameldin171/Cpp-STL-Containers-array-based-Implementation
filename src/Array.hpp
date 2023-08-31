
#ifndef __ARRAY_HPP_
#define __ARRAY_HPP_

#include "Container.hpp"
#include <initializer_list>
#include <cassert>

template<typename T , size_t arraySize>
class Array : public Container<T>, is_subscriptable<T> {

/*The size of the array should be provided as a positive integer: */
static_assert(arraySize != 0);

public:
    /*Default Constructor: */
    Array() = default;

    /*Initializer List Constructor: */
    Array(const std::initializer_list<T>& list){
        this->operator=(list);
    }

    /*Initializer List Assignment Operator: */
    Array& operator=(const std::initializer_list<T>& list){
        assert(arraySize >= list.size());

        int i = 0 ;
        for(const auto& element : list){
            this->arr[i++] = element; 
        }

        return *this;
    }


    /*Default Copy and Move Constructors and assignment operators: */
    Array(const Array&) = default;
    Array& operator=(const Array&) = default;
    Array(Array&&) = default;
    Array& operator=(Array&&) = default;

    /*Returns the number of elements in a array*/
    size_t size() const override{
        return arraySize;
    } 

    /*Returns a pointer to the first element of the C array: */
    T* get(){
        return this->arr;
    }

    /*Removes all the content of the container*/
    void clear() override{
        for(auto& element: this->arr){
            element = T{};
        }
    }

/*Operators: */
    /*Subscript Operator: */
    T& operator[](size_t index) override{
        assert(index < arraySize);
        return this->arr[index];
    }

    const T& operator[](size_t index) const override{
        assert(index < arraySize);
        return this->arr[index];
    }

    /*Address of Operator: */
    T* operator&(){
        return this->arr;
    }

    class Iterator : public Container<T>::Iterator{

        friend class Array<T,arraySize>;

        public:
            /*Dereference operator: */
            T operator*() override{
                return Arr[this->CurrentIndex];
            }

            /*Increment operators: */
            void operator++() override{
                this->CurrentIndex++;
            }

            void operator++(int) override{
                this->CurrentIndex++;
            }

            /*Decrement operators: */
            void operator--() override{
                this->CurrentIndex--;
            }

            void operator--(int) override{
                this->CurrentIndex--;
            }

            /*Comparison Operators: */

            bool operator==(const Array<T,arraySize>::Iterator& it) const {
                return this->CurrentIndex == it.CurrentIndex;
            }
        
            bool operator!=(const Array<T,arraySize>::Iterator& it) const{
                return this->CurrentIndex != it.CurrentIndex;
            }

            private:
                /*A reference to the array to iterate on: */
                const T (&Arr)[arraySize];
                /*An index to point at a particular position in the referenced array*/
                size_t CurrentIndex{};

                /*Private Constructor to be used by the array class: */
                Iterator(const T (&arr)[arraySize] , size_t index) : Arr{arr} , CurrentIndex{index}{
                }
        };


        /*Returns an iterator to the first place in the container*/
        Array<T,arraySize>::Iterator begin(){
            return Array<T,arraySize>::Iterator{arr,0};
        }

        /*Returns an iterator to following the last place in the container*/
        Array<T,arraySize>::Iterator end(){
            return Array<T,arraySize>::Iterator{arr,arraySize};
        }

private:
    /*The actual C type array: */
    T arr[arraySize]{};
};

#endif