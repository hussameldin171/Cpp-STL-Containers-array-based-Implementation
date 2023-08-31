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
            virtual T operator*() = 0;

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

#endif


/*
 * Description: A class that serves as an interface for containers that implement the subscript operator.
 */
template<typename T>
struct is_subscriptable{

    virtual T& operator[](size_t index) = 0 ;    

    virtual const T& operator[](size_t index) const = 0;
};
