#define __CL_ENABLE_EXCEPTIONS
#include<iostream>
#include<string>
#include<fstream>
#include <CL/cl.hpp>
#include"hello.hpp"


    cl::Kernel test::hello::loadkernel(std::string filename,std::string fun_name)
    {
        std::ifstream c_file(filename);
        if(!c_file.good()){
            std::cout<<"can't open opencl file:"<<filename<<std::endl;
            exit(1);
        }

        std::string cl_str(std::istreambuf_iterator<char>(c_file),(std::istreambuf_iterator<char>()));
        cl::Program::Sources source(1,std::make_pair(cl_str.c_str(),cl_str.length()+1));
        cl::Program program(context,source);
        try{
            program.build(device_);
        }catch (cl::Error e){
        // If there's a build error, print out the build log to see what
        // exactly the problem was.
        std::cerr << "Build Status:\t"
            << program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(device_[0])
            << std::endl << "Build Options:\t"
            << program.getBuildInfo<CL_PROGRAM_BUILD_OPTIONS>(device_[0])
            << std::endl << "Build Log:\t "
            << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device_[0]) << std::endl;
    }
        return cl::Kernel(program,fun_name.c_str());
        }
     

    void test::hello::getBuffer(int *vec,int length,int *out,int lengthout){
        cl_int err;
        input = cl::Buffer(context,CL_MEM_READ_ONLY  | CL_MEM_COPY_HOST_PTR,length*sizeof(int),vec,&err);
        output = cl::Buffer(context,CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,lengthout*sizeof(int),out,&err);
        if(err!=CL_SUCCESS){
            std::cerr<<"Couldn't create a buffer"<<std::endl;
        }
    }

    void test::hello::vectorAdd(){
        cl_int error;
        try{
            error = vector_add.setArg(0,input);
            if(error!= CL_SUCCESS){
                std::cout<<"set first argument fault"<<std::endl;
            }

            error|= vector_add.setArg(1,output);
            if(error!= CL_SUCCESS){
                std::cout<<"set scecond argument fault"<<std::endl;
            }


            error = queue.enqueueNDRangeKernel(vector_add,cl::NDRange(0),cl::NDRange(8),cl::NDRange(4),NULL);
            if(error!=CL_SUCCESS){
                std::cout<<"couldn't enqueueNDRangekernel"<<std::endl;
            }
        }catch(cl::Error e){
        std::cerr<<"here enqueue kernel error:"<<e.what()<<":\t"<<e.err()<<std::endl;
        exit(1); // webpage to get specific error: https://streamhpc.com/blog/2013-04-28/opencl-error-codes/
        }   

    }

    void test::hello::Output(int *outvec,int length){
        queue.enqueueReadBuffer(output,CL_TRUE,0,length*sizeof(int),outvec);
        
    }

    test::hello::hello(){
        cl_int error;
        error = cl::Platform::get(&platform_);
        if(error != CL_SUCCESS){
            std::cout<<"hello! can't get platform"<<std::endl;
        }
        error = platform_[0].getDevices(CL_DEVICE_TYPE_GPU,&device_);
        if(error != CL_SUCCESS){
            std::cout<<"hello! can't get device"<<std::endl;
        }
        try{
            context = cl::Context(device_);
            queue = cl::CommandQueue(context,device_[0]);

            vector_add = loadkernel("./kernel/vector_add.cl","vector_add");
        }catch(cl::Error e){
            std::cerr << e.what()<<":\t"<<std::endl;
        }
    }



