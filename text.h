#ifndef __TEXT_H__
#define __TEXT_H__
#include "view.h"
#include "model.h"

class Text: public View {
    Model* m;
public:
    // Constructs Text that has a Model m
    Text(Model* m);
    // Destructor for Text that detaches itself from Model
    ~Text();
    // prints current state of the board to screen
    void notify() override;
};

#endif
