#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

//#include <string>

struct node
{
    int key;
    char* value;
    node* next;

    node(int key, char* value) : key(key), value(value), next(0) {}
};

/*class linked_list
{
private:
    node *head,*tail;
public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }
};*/

#endif  // NODE_H_INCLUDED
