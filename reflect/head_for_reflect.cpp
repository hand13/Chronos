#include "head_for_reflect.h"
ReflectTest::ReflectTest() {
    id = 1234;
    password = "123456";
}

void ReflectTest::setId(int id) { this->id = id; }

std::string ReflectTest::getPassword() { return password; }
int ReflectTest::getId() { return id; }

ReflectTest::~ReflectTest() {}