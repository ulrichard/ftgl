#ifndef    __FTList__
#define    __FTList__

#include "FTGL.h"

template <typename FT_LIST_ITEM_TYPE>
class FTGL_EXPORT FTList
{
    public:
        typedef FT_LIST_ITEM_TYPE value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef size_t size_type;

        FTList()
        :	listSize(0),
            tail(0)
        {
            tail = NULL;
            head = new Node;
        }
        
        ~FTList()
        {
            Node* temp = head;
            
            while( temp->next)
            {
                temp = head->next;
                delete head;
            }
        }
        
        size_type size() const
        {
            return listSize;
        }

        void push_back( const value_type& item)
        {
            Node* node = new Node( item);
            
            if( head->next == NULL)
            {
                head->next = node;
            }
            
            tail = node;
            ++listSize;
        }
        
        reference front() const
        {
            return head->next->payload;
        }

        reference back() const
        {
            return tail->payload;
        }

    private:
        struct Node
        {
            Node()
            :	next(NULL)
            {}

            Node( const value_type& item)
            :	next(NULL)
            {
                payload = item;
            }
            
            Node* next;
            
            value_type payload;
        };
        
        size_type listSize;

        Node* head;
        Node* tail;
};

#endif // __FTList__

