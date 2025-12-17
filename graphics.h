#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__
#include "view.h"
#include "model.h"
#include "window.h"

class Graphics: public View {
    Model* m;
    Xwindow* dis;
public:
    // Constructs Graphics that has a Model m
    Graphics(Model* m);
    // Destructor for Graphics that detaches itself from Model and deletes Xwindow display
    ~Graphics();
    // Uses Xwindow dis to display a graphical interface of the chess board
    void notify() override;
};

#endif
