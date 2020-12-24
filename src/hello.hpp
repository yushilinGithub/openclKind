#include <vector>
#include <string>
#include <CL/cl.hpp>

namespace test{
class hello{
    private:
        std::vector<cl::Platform> platform_; 
        std::vector<cl::Device> device_;
        cl::Context context;
        cl::CommandQueue queue;
        cl::Kernel vector_add;
        cl::Buffer input;
        cl::Buffer output;
    public:
        hello();
        cl::Kernel loadkernel(std::string filename,std::string funname);
        void getBuffer(int *a,int length,int *out,int lengthout);

        void vectorAdd();
        void Output(int *output,int length);
        
};
}