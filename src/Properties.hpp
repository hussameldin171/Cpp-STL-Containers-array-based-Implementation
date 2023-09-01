#ifndef __PROPERTIES_HPP__
#define __PROPERTIES_HPP__

#include <cstddef>

/*An interface for containers that will provide a read-only subscript operator.*/
template<typename T>
struct const_subscriptable{

 virtual inline const T& operator[](size_t index) const = 0;

};

/*An interface for containers that will provide read/write subscript operator.*/
template<typename T>
struct subscriptable : public const_subscriptable<T>{

    virtual inline T& operator[](size_t index) = 0 ;    

};

/*
  An interface for iterators that will provide write access. 
  Note that iterators by default will provide read access. 
*/
template<typename T>
struct write_accessible{

     virtual T& operator*() = 0;    

};
#endif // __PROPERTIES_HPP__