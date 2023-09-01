#ifndef __CONTAINER_HPP_
#define __CONTAINER_HPP_

#include <cstddef>

/*
 * Description: A base class for all container types.
 */
template <typename T>
class Container{

    public:        
        /*Returns the number of elements in a container*/
        virtual size_t size() const = 0; 

        /*Checks if the container is empty*/
        inline bool empty() const{
            return this->size() == 0;
        }

        /*Removes all the content of the container*/
        virtual void clear() = 0;

        class Iterator{

        public:
            /*Dereference operator: */
            virtual const T& operator*() const = 0;

            /*Increment operators: */
            virtual void operator++() = 0;

            virtual void operator++(int) = 0 ;

            /*Decrement operators: */
            virtual void operator--() = 0;

            virtual void operator--(int) = 0;
        
        };
    
        /*Destructor: */
        virtual ~Container() = default;
};


/*An interface for containers that provide read only iterators:*/
template<typename T>
struct const_iteratable{
    
    virtual const typename Container<T>::Iterator& begin() const = 0;

    virtual const typename Container<T>::Iterator& end() const = 0;

};

/*An interface for containers that provide read/write iterators:*/
template<typename T>
struct iteratable : const_iteratable<T>{
    
    virtual typename Container<T>::Iterator& begin() = 0;

    virtual typename Container<T>::Iterator& end() = 0;

};

#endif

