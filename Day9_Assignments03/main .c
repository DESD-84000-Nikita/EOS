#include <stdio.h>
#include "circle.h"
#include "square.h"
#include "rectnagle.h"

int main() {
    float circleArea = calculateCircleArea(5);
    printf("Area of circle: %.2f\n", circleArea);

    float squareArea = calculateSquareArea(4);
    printf("Area of square: %.2f\n", squareArea);

    float rectangleArea = calculateRectangleArea(3, 6);
    printf("Area of rectangle: %.2f\n", rectangleArea);

    return 0;
}
