#include "FTGL.h"

template <typename FT_VECTOR_ITEM_TYPE>
class FTGL_EXPORT FTVector
{
    public:
  
        typedef FT_VECTOR_ITEM_TYPE value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef value_type* iterator;
        typedef const value_type* const_iterator;
        typedef size_t size_type;

        FTVector()
        {
            Size = NumberOfItems = 0;
            Items = 0;
        }

        virtual ~FTVector()
        {
            clear();
        }

        FTVector& operator = ( const FTVector& v)
        {
            // Warning: the vector is not cleared and resized to v capacity for
            // efficiency reasons.
            // clear();
            reserve(v.capacity());
  
            iterator ptr = begin();
            const_iterator vbegin = v.begin();
            const_iterator vend = v.end();

            while (vbegin != vend)
            {
                *ptr++ = *vbegin++;
            }
            NumberOfItems = v.size();
            return *this;
        }

        size_type size() const
        {
            return NumberOfItems; 
        }
        
        size_type capacity() const
        { 
            return Size; 
        }

        iterator begin()
        { 
            return Items; 
        }

        iterator end()
        { 
            return begin() + size(); 
        }

        const_iterator begin() const
        { 
          return Items; 
        }

        const_iterator end() const
        { 
            return begin() + size(); 
        }

        bool empty() const
        { 
            return size() == 0; 
        }

        reference operator []( size_type pos)
        { 
            return (*(begin() + pos)); 
        }

        const_reference operator []( size_type pos) const
        { 
            return (*(begin() + pos)); 
        }


        void clear()
        {
            if (Size)
            {
                delete [] Items;
                Size = NumberOfItems = 0;
                Items = 0;
            }
        }

        void reserve( size_type n)
        {
            if( capacity() < n)
            {
                expand(n);
            }
        }

        void push_back( const value_type& x)
        {
            if( size() == capacity())
            {
                expand();
            }
            
            (*this)[size()] = x;
            NumberOfItems++;
        }

        void resize( size_type, value_type)
        {
            reserve(n);
            iterator end = end();
            iterator end_capacity = begin() + capacity();
        
            while (end != end_capacity)
            {
                *end++ = x;
            }
        }


    protected:
        void expand( size_type size_hint = 0)
        {
            // Allocate new vector (size doubles)
            size_type new_size = (size() == 0) ? 256 : size() * 2;
            if( size_hint)
            {
                while( new_size < size_hint)
                {
                    new_size *= 2;
                }
            }
          
            value_type *ptr = new value_type[new_size];
        
            // Copy values to new vector
            iterator begin = this->begin();
            iterator end = this->end();
            while( begin != end)
            {
                *ptr++ = *begin++;
            }
        
            // Deallocate old vector and use new vector
            delete [] Items;
            Items = ptr;
            Size = new_size;
        }


    private:
        size_type Size;
        size_type NumberOfItems;
        value_type* Items;
};

