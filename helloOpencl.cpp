#include<iostream>
#include<fstream>
#include "CL/cl.hpp"
#include "hello.hpp"
#define sizeOfVec 64

int main(int argc,char **argv){
    test::hello Hello = test::hello();
    int vec[sizeOfVec];
    int out[2];
    for(int i=0;i<sizeOfVec;i++){
        vec[i] = i;
    }

    Hello.getBuffer(vec,sizeOfVec,out,2);

    Hello.vectorAdd();
    std::cout<<"compute finished"<<std::endl;
    Hello.Output(out,2);

    std::cout<<"out0:"<<out[0]<<"out1:"<<out[1]<<std::endl;;
    std::cout<<"hello runtime"<<std::endl;
}
