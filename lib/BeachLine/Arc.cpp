

#include "headers/Arc.hpp"


Arc::Arc(double x, double y) {
    this->x = x;
    this->y = y;
}

Arc::Arc() {
    this->x = 0;
    this->y = 0;
}

double Arc::getX() {
    return this->x;
}

double Arc::getY() {
    return this->y;
}


void Arc::setX(double x) {
    this->x = x;
}

void Arc::setY(double y) {
    this->y = y;
}

void Arc::set(double x, double y) {
    this->x = x;
    this->y = y;
}

Arc& Arc::operator=(const Arc &a) {
    this->x = a.x;
    this->y = a.y;
    return *this;
}

Arc::Arc(const Arc &a) {
    this->x = a.x;
    this->y = a.y;
}