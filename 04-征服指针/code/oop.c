#include<stdio.h>
#include<stdlib.h>

typedef int(*fptrGet)(void *);
typedef void (*fptrSet)(void *, int);
typedef void (*fptrDisplay)();

typedef struct _functions{
    fptrSet setX;
    fptrGet getX;
    fptrSet setY;
    fptrGet getY;
    fptrDisplay display;
} vFunctions;

typedef struct _shape{
    vFunctions functions;
    int x;
    int y;
} Shape;

void shapeDisplay(Shape *shape){
    printf("Shape! Coordinate(%d,%d)!\n", shape->x, shape->y);
}

void shapeSetX(Shape *shape, int x){
    shape->x = x;
}

void shapeSetY(Shape *shape, int y){
    shape->y = y;
}

int shapeGetX(Shape *shape){
    return shape->x;
}

int shapeGetY(Shape *shape){
    return shape->y;
}

Shape* getShapeInstance(){
    Shape *shape = (Shape *)malloc(sizeof(Shape));
    shape->x = 0;
    shape->y = 0;
    shape->functions.display = shapeDisplay;
    shape->functions.setX = shapeSetX;
    shape->functions.getX = shapeGetX;
    shape->functions.setY = shapeSetY;
    shape->functions.getY = shapeGetY;
    return shape;
}

typedef struct _rectangle{
    Shape base;
    int width;
    int height;
} Rectangle;


void rectangleDisplay(Rectangle *rectangle){
    printf("Rectangle! Coordinate(%d,%d)! Width = %d, Height = %d!\n",
           rectangle->base.x, rectangle->base.y,
           rectangle->width, rectangle->height);
}

void rectangleSetX(Rectangle *rectangle, int x){
    rectangle->base.x = x;
}

void rectangleSetY(Rectangle *rectangle, int y){
    rectangle->base.y = y;
}

int rectangleGetX(Rectangle *rectangle){
    return rectangle->base.x;
}

int rectangleGetY(Rectangle *rectangle){
    return rectangle->base.y;
}

Rectangle* getRectangleInstance(){
    Rectangle *rectangle = (Rectangle *)malloc(sizeof(Rectangle));
    rectangle->base.functions.display = rectangleDisplay;
    rectangle->base.functions.setX = rectangleSetX;
    rectangle->base.functions.getX = rectangleGetX;
    rectangle->base.functions.setY = rectangleSetY;
    rectangle->base.functions.getY = rectangleGetY;
    rectangle->base.x = 0;
    rectangle->base.y = 0;
    rectangle->width = 100;
    rectangle->height = 100;
    return rectangle;
}


int main(){
    // 基类
    Shape *sptr = getShapeInstance();
    sptr->functions.display(sptr);
    sptr->functions.setX(sptr, 35);
    sptr->functions.setY(sptr, 35);
    sptr->functions.display(sptr);

    // 子类
    Rectangle *rptr = getRectangleInstance();
    rptr->base.functions.display(rptr);
    rptr->base.functions.setX(rptr, 25);
    rptr->base.functions.setY(rptr, 25);
    rptr->base.functions.display(rptr);

    return 0;
}