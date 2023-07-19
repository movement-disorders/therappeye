#include "circle.h"

Circle::Circle(int x, int y, int radius) {
    this->x = x;
    this->y = y;
    this->radius = radius;
}

void Circle::draw() {
    // Set color to green
    setColor(0, 255, 0);

    // Draw circle
    drawCircle(x, y, radius);
}

void Circle::update() {
    // Rotate circle
    x = x * cos(ROTATION_ANGLE) - y * sin(ROTATION_ANGLE);
    y = x * sin(ROTATION_ANGLE) + y * cos(ROTATION_ANGLE);
}