#ifndef    __FTList__
#define    __FTList__

#include "FTGL.h"

template <typename FT_LIST_ITEM_TYPE>
class FTGL_EXPORT FTList
{
    public:
        FTList()
        : listSize(0)
        {
            head = NULL;
            tail = NULL;
            head->next = tail;
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
        
        size_t size()
        {
            return listSize;
        }

        void push_back( const FT_LIST_ITEM_TYPE& item)
        {
            Node* node = new Node( item);
            if( tail)
            {
                tail->next = node;
            }
            
            tail = node;
            ++listSize;
        }
        
        FT_LIST_ITEM_TYPE& back()
        {
            return tail->payload;
        }

    private:
        struct Node
        {
            Node( const FT_LIST_ITEM_TYPE& item)
            :	next(NULL)
            {
                payload = item;
            }
            
            Node* next;
            
            FT_LIST_ITEM_TYPE payload;
        };
        
        size_t listSize;

        Node* head;
        Node* tail;
};

#endif // __FTList__

