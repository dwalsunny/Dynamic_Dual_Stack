/*****************************************
 * UW User ID:  s24dhali
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DUAL_STACK_H
#define DYNAMIC_DUAL_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include <cassert>

template <typename Type>
class Dynamic_dual_stack {
	private:
		int initial_capacity;
		int array_capacity;
		Type *array;
		int stack_size[2];

	public:
		Dynamic_dual_stack( int = 10 );
		Dynamic_dual_stack( Dynamic_dual_stack const & );
		~Dynamic_dual_stack();

		int capacity() const;
		bool empty( int ) const;
		int size( int ) const;
		Type top( int ) const;

		void swap( Dynamic_dual_stack & );
		Dynamic_dual_stack &operator=( Dynamic_dual_stack const & );
		void push( int, Type const & );
		Type pop( int );
		void clear();

	// Friends

	/*template <typename T>
	friend std::ostream &operator<<( std::ostream &, Dynamic_dual_stack<T> const & );*/
};

template <typename Type>
Dynamic_dual_stack<Type>::Dynamic_dual_stack( int n ):
initial_capacity( std::max( 1, n ) ),
array_capacity( initial_capacity ),
array( new Type[initial_capacity] ) {
	stack_size[0] = stack_size[1] = 0;
}

template <typename Type>
Dynamic_dual_stack<Type>::Dynamic_dual_stack( Dynamic_dual_stack const &stack ):
initial_capacity( stack.initial_capacity ),
array_capacity( stack.array_capacity ),
array( new Type[array_capacity] ) {
	stack_size[0] = stack.stack_size[0];
	stack_size[1] = stack.stack_size[1];

	// The above initializations copy the values of the appropriate
	// member variables and allocate memory for the data structure; 
	// however, you must still copy the stored objects.

    //Copies over the entries from the beginning of the stack into the beginning of the array
	for(int i = 0; i < stack_size[0]; ++i)
    {
        array[i] = stack.array[i];
    }
    
    // Copies over the entries at the back of stack starting from the first entry of the back (most left)
    // and moves toward the right
    for(int i = 0; i < stack_size[1]; ++i)
    {
        array[array_capacity - i -1] = stack.array[array_capacity -i -1];
    }
}

//Destructor, deletes the array
template <typename Type>
Dynamic_dual_stack<Type>::~Dynamic_dual_stack() {
	delete [] array;
}

//Returns the number of elements the array can hold.
template <typename Type>
int Dynamic_dual_stack<Type>::capacity() const {
	return array_capacity;
}

//Returns true or false depending if the stack is empty or not.
template <typename Type>
bool Dynamic_dual_stack<Type>::empty( int m ) const {
    if(m != 0 && m != 1)
    {
        throw;
    }
    
    
	return (stack_size[m] == 0);
}

// Returns the size of the stack (number of elements in that stack)
template <typename Type>
int Dynamic_dual_stack<Type>::size( int m ) const {
	if(m != 0 && m!= 1)
    {
        throw;
    }
    
    
	return stack_size[m];
}

// Returns the element at the top of the chosen stack
template <typename  Type>
Type Dynamic_dual_stack<Type>::top( int m ) const {
    if(m != 0 && m!= 1)
    {
//        throw underflow();
        throw;
    }
    
    if(empty(m))
    {
        throw;
    }
    
    if(m == 0)
    {
        //Top of stack 0
        return array[stack_size[m]-1];
    }
    else
    {
        //Top of stack 1
        return array[array_capacity - stack_size[m]];
    }
}

template <typename Type>
void Dynamic_dual_stack<Type>::swap( Dynamic_dual_stack<Type> &stack ) {
	std::swap( initial_capacity, stack.initial_capacity );
	std::swap( array_capacity, stack.array_capacity );
	std::swap( array, stack.array );
	std::swap( stack_size[0], stack.stack_size[0] );
	std::swap( stack_size[1], stack.stack_size[1] );
}

template <typename Type>
Dynamic_dual_stack<Type> &Dynamic_dual_stack<Type>::operator=( Dynamic_dual_stack<Type> const &rhs ) {
	Dynamic_dual_stack<Type> copy( rhs );

	swap( copy );
	
	return *this;
} 

template <typename  Type>
void Dynamic_dual_stack<Type>::push( int m, Type const &obj ) {
    if(m != 0 && m!= 1)
    {
        throw;
    }
    
    // Checks if the array is full, if it is it creates a new array and copies over all the elements
    // from the old array into the new one filling the elements in there appripriate locations and points
    // the array to the new array
    if((stack_size[0] + stack_size[1]) == array_capacity)
    {
        Type *tmp_array = new Type[2*array_capacity];
        for(int i = 0; i < stack_size[0]; ++i)
        {
            tmp_array[i] = array[i];
        }
        
        for(int i = stack_size[1]; i > 0; --i)
        {
            tmp_array[(2*array_capacity) - i] = array[array_capacity-i];
        }
        
        delete [] array;
        array = tmp_array;
        array_capacity *= 2;
    }
    
    // Pushing value when stack 0 is selected
    if(m == 0)
    {
        array[stack_size[m]] = obj;
        ++stack_size[m];
    }
    // Pushing value when stack 1 is selected
    else
    {
        array[array_capacity - stack_size[m] -1] = obj;
        ++stack_size[m];
    }
    
    
}

template <typename  Type>
Type Dynamic_dual_stack<Type>::pop( int m ) {
    if(m != 0 && m!= 1)
    {
        throw;
    }
    
    if(empty(m))
    {
        throw;
    }
    
    Type popped = 0;
    
    //Popping item if stack 0 is selected
    if(m == 0)
    {
        --stack_size[m];
        popped =  array[stack_size[m]];
    }
    
    //Popping item if stack 1 is selected
    else
    {
        --stack_size[m];
        popped = array[array_capacity - stack_size[m] -1];
        
    }
    
    //Checking if the array is one fourth of array capacity, if it is it creates a new array that contains half
    // the number possible entries and copies over the values in the old array appropriately into the new array and points the
    // the array to the new array.
    if((stack_size[0] + stack_size[1]) <= (array_capacity/4))
    {
        int nsize = std::max((array_capacity/2), initial_capacity);
        Type *tmp_array = new Type[nsize];
        
        for(int i = 0; i < stack_size[0]; ++i)
        {
            tmp_array[i] = array[i];
        }
        
        for(int i = stack_size[1]; i > 0; --i)
        {
            tmp_array[nsize - i] = array[array_capacity-i];
        }
        
        delete [] array;
        array = tmp_array;
        array_capacity = nsize;
        return popped;
    }
    
    else
    {
        return popped;
    }
}

// Clears entries from both stacks
template <typename  Type>
void Dynamic_dual_stack<Type>::clear() {
    stack_size[0] = 0;
    stack_size[1] = 0;
    array_capacity = initial_capacity;
}

// You can modify this function however you want:  it will not be tested

/*template <typename T>
std::ostream &operator<<( std::ostream &out, Dynamic_dual_stack<T> const &stack ) {
	for ( int i = 0; i < stack.capacity(); ++i ) {
		if ( i < stack.stack_size[0] ) {
			out << stack.array[i] << " ";
		} else if ( i >= stack.capacity() - stack.stack_size[1] ) {
			out << stack.array[i] << " ";
		} else {
			out << "- ";
		}
	}

	return out;
}
*/
// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
