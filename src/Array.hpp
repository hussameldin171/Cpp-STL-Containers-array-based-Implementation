
#ifndef __ARRAY_HPP_
#define __ARRAY_HPP_

#include "Properties.hpp"
#include "Container.hpp"
#include <initializer_list>
#include <cassert>

template<typename T , size_t arraySize>
class Array : public Container<T>, 
              public subscriptable<T>
              
{

/*The size of the array should be provided as a positive integer: */
static_assert(arraySize != 0 , "Array with size zero is not allowed");

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

    /*Array constructor for different sized arrays*/
    template<size_t otherSize>
    Array(const Array<T,otherSize>& otherArr){
        this->operator=(otherArr);
    }

    /*Array assignment operator for different sized arrays*/
    template<size_t otherSize>
    Array& operator=(const Array<T,otherSize>& otherArr){
        
        static_assert(arraySize >= otherSize , "Cannot initialize a smaller array with a larger one.");
        
        for(size_t i = 0 ; i < otherSize ; i++){
            this->arr[i] =otherArr[i];
        }

        return *this;
    }



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
            element = T{}; //TODO: Find a way for this to work with classes that don't have a default constructor.
        }
    }

/*Operators: */
    /*Subscript Operators: */
    inline T& operator[](size_t index) override{
        assert(index < arraySize);
        return this->arr[index];
    }

    inline const T& operator[](size_t index) const override{
        assert(index < arraySize);
        return this->arr[index];
    }

    /*Address of Operator: */
    T* operator&(){
        return this->arr;
    }

    class Iterator : public Container<T>::Iterator , 
                     public write_accessible<T>
    {

        friend class Array<T,arraySize>;

        public:
            /*Dereference operators: */
            T& operator*() override{
                return this->Arr[this->CurrentIndex];
            }

            const T& operator*() const override{
                return this->Arr[this->CurrentIndex];
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
                T (&Arr)[arraySize];
                /*An index to point at a particular position in the referenced array*/
                size_t CurrentIndex{};

                /*Private Constructor to be used by the array class: */
                Iterator(T (&arr)[arraySize] , size_t index) : Arr{arr} , CurrentIndex{index}{
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

        /*Returns an iterator to the first place in the container*/
        const Array<T,arraySize>::Iterator& begin() const{
            return Array<T,arraySize>::Iterator{arr,0};
        }

        /*Returns an iterator to following the last place in the container*/
        const Array<T,arraySize>::Iterator& end() const{ 
            return Array<T,arraySize>::Iterator{arr,arraySize};
        }

private:
    /*The actual C type array: */
    T arr[arraySize]{};
};

#endif