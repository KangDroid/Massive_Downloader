#include "Container.h"

using namespace std;

class ContainerQueue {
public:
    Container* ctr;
    int max_val;
    int head;
    int tail;
    ContainerQueue();
    ~ContainerQueue();
    void init(int max);

    void push(Container& cont_val);

    Container pop();
};