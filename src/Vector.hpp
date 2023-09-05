#ifndef __VECTOR_HPP_
#define __VECTOR_HPP_

#include "Properties.hpp"
#include "Container.hpp"
#include "Array.hpp"


template<typename T, size_t maxSize>
class Vector : public Container<T>,
               public subscriptable<T>
{

    /*The maximum size of the vector should be provided as a positive integer: */
    static_assert(maxSize != 0 , "A vector with size zero is not allowed");

    public: 
        /*Default Constructor: */
        Vector() = default;

        /*Initializer List Constructor: */
        Vector(const std::initializer_list<T>& list) : arr{list}{
            this->currentSize = list.size();
        }

        /*Initializer List assignment operator: */
        Vector& operator=(const std::initializer_list<T>& list){
            this->arr = list;
            this->currentSize = list.size();
        }


        /*Default Copy and Move Constructors and assignment operators: */
        Vector(const Vector&) = default;
        Vector& operator=(const Vector&) = default;
        Vector(Vector&&) = default;
        Vector& operator=(Vector&&) = default;

        /*Vector constructor for different sized vectors: */
        template<size_t otherSize>
        Vector(const Vector<T,otherSize>& vect){
            /*This time, the dynamic sizes of the vectors should be compared: */
            assert(this->currentSize >= vect.currentSize);

            this->operator=(vect);
        }

        /*Vector assignment operator for different sized vectors: */
        template<size_t otherSize>
        Vector operator=(const Vector<T,otherSize>& vect){
            /*This time, the dynamic sizes of the vectors should be compared: */
            assert(this->currentSize >= vect.size());

            /*Copy the array content: */
            for(size_t i = 0 ; i < vect.size() ; i++){
                this->arr[i] = vect[i];
            }
            /*Copy the size parameter: */
            this->currentSize = vect.size();
        }

        /*Returns the dynamic size of the vector: */
        size_t size() const override{
            return this->currentSize;
        } 

        /*Removes all the content of the vector: */
        void clear() override{
            this->currentSize = 0;
        }


/*Operators: */
    /*Subscript Operators: */
    inline const T& operator[](size_t index) const override{
        return this->arr[index];
    }

    inline T& operator[](size_t index) override{
        return this->arr[index];
    }

/*Vector specific methods: */

    /*Push operation: */
    void push_back(const T& element){

        assert(this->currentSize < maxSize);
        
        this->arr[currentSize] = element;
        
        currentSize++;
        
    }

    /*Pop operation: */
    T pop_back(){
    
        assert(currentSize != 0);
        
        currentSize--;
        
        return this->arr[currentSize];
    }

    inline T back() const{
        assert(currentSize != 0);
        return this->arr[currentSize-1];
    }

    inline T front() const{
        assert(currentSize!=0);
        return this->arr[0];
    }

    private:
        /*An internal array instance: */
        Array<T,maxSize> arr{};
        /*The dynamic size of the vector: */
        size_t currentSize{0};        

};

#endif