    #include "head_for_reflect.h"
ReflectTest::ReflectTest(){

}

void ReflectTest::setId(int id){
    this->id = id;
}

std::string ReflectTest::getPassword(){
    return password;
}
int ReflectTest::getId(){
    return id;
}

ReflectTest::~ReflectTest(){
}