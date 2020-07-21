#include "ContainerQueue.h"
ContainerQueue::~ContainerQueue() {
    delete[] ctr;
}

void ContainerQueue::init(int max) {
    this->head = 0;
    this->tail = 0;
    this->max_val = max;
    this->ctr = new Container[max];
}

void ContainerQueue::push(Container& cont_val) {
    this->ctr[head++] = cont_val;
}

Container ContainerQueue::pop() {
    return this->ctr[tail++];
}

ContainerQueue::ContainerQueue() {
}
