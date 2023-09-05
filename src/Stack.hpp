#ifndef __STACK_HPP_
#define __STACK_HPP_

#include "Vector.hpp"
template<typename T, size_t maxStackSize = defaultMaxStackSize>
class Stack : public Container<T>{ /*A stack is a container,but not subscriptable, and not iterable*/

    /*The maximum size of the stack should be provided as a positive integer: */
    static_assert(maxStackSize != 0 , "A stack with maximum size zero is not allowed");

    public:

        /*Default Constructor: */
        Stack() = default;

        /*Initializer List Constructor: */
        Stack(const std::initializer_list<T>& list) : internalVector{list}{
            
        }

        /*Initializer List assignment operator: */
        Stack& operator=(const std::initializer_list<T>& list){
            assert(list.size() <= maxStackSize);
            this->internalVector = Vector<T,maxStackSize>(list);
            return *this;
        }

        /*Default Copy and Move Constructors and assignment operators: */
        Stack(const Stack&) = default;
        Stack& operator=(const Stack&) = default;
        Stack(Stack&&) = default;
        Stack& operator=(Stack&&) = default;

        /*Stack constructor for different sized stacks: */
        template<size_t otherStackSize>
        Stack(const Stack<T,otherStackSize>& otherStack){
            this->operator=(otherStack);
        }

        /*Stack assignment operator for different sized stacks: */
        template<size_t otherStackSize>
        Stack& operator=(Stack<T,otherStackSize> otherStack){
            
            this->internalVector.clear();

            for(size_t i = this->size()-1 ; i>=0 ; i--){
                auto toInsert =  otherStack.pop();
                cout<<"Hereeee"<<" ";
                this->internalVector.push_back(toInsert);
            }
            return *this;
        }

        /*Returns the number of elements in a stack*/
        size_t size() const override{
            return this->internalVector.size();
        } 

        /*Removes all the content of the stack*/
        void clear() override{
            this->internalVector.clear();
        }

    /*Stack specific methods: */

    /*Push Operation: */
        /*Pushes a single element to the top of the stack: */
        inline void push(const T& value){
            
            assert(this->internalVector.size() < maxStackSize);

            this->internalVector.push_back(value);

        }

        /*Pushes another stack to the top of the current stack: */
        template<size_t otherStackSize>
        inline void push(Stack<T,otherStackSize> otherStack){
            
            Stack<T,otherStackSize> reverseStack{};
            
            while(!otherStack.empty()){
                reverseStack.push(otherStack.pop());
            }

            while(!reverseStack.empty()){
                this->push(reverseStack.pop());
            }

        }

    /*Pop Operation: */
        /*Pops a single element from the stack: */
        inline T pop(){

            assert(this->size() != 0);

            return this->internalVector.pop_back();

        }

        /*Pops a number of elements from the stack and returns another stack: */
        inline Stack<T,maxStackSize> pop(size_t count){
   
            auto result = top(count);

            for(int i = 0 ; i < count ; i++){
                this->pop();
            }

            return result;
        }

        /*Returns the element on top of the stack: */
        inline T top() const{
            return this->internalVector.back();
        }

        /*Returns a sub-stack on top of the other stack: */
        inline Stack<T,maxStackSize> top(size_t count) const{

            auto iter = this->size()-count;

            Stack<T,maxStackSize> resultStack{};

            while(iter < this->size()){
                resultStack.push(this->internalVector[iter]);
                iter++;
            }

            return resultStack;

        }
    private:
        /*An internal vector instance: */
        Vector<T,maxStackSize> internalVector;

};

#endif