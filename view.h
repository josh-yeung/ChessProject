#ifndef __VIEW_H__
#define __VIEW_H__

class View {
public:
    // virtual function that dipslays the state of the board
    virtual void notify() = 0;
    // virtual destructor
    virtual ~View();
};

#endif
