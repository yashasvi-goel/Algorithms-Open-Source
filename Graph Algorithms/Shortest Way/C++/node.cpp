#ifndef _NODE_CPP
#define _NODE_CPP

typedef struct node
{
    unsigned int f = 0, g = 0, h = 0;
    enum class mode { UNREACHED, OPENED, CLOSED } state = mode::UNREACHED;
    bool traversable;
    int parent_row, parent_col;
    node(bool _traverse)
        : traversable(_traverse)
    {}
} node;

#endif // define _NODE_CPP
