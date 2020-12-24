/*
__kernel void vector_add(__global int4 *in,
                            __global int *out){


        __local int intermediate[4];
        int ind = get_global_id(0);
        int4 a,b,addfour;
        int sum;
        a = in[2*ind];
        b = in[2*ind+1];
        addfour = a+b;

        int local_ind = get_local_id(0);
        intermediate[local_ind] = addfour.s0+addfour.s1+addfour.s2+addfour.s3;

        barrier(CLK_LOCAL_MEM_FENCE);
        int local_size = get_local_size(0);
        if(get_local_id(0) == 0){
            for(int i = 0;i<local_size;i++){
                sum += intermediate[i];
            }
            int group_id = get_group_id(0);
            out[group_id] = sum;
        }
}*/
__kernel void vector_add(__global int4* data, 
       __global int* group_result) {


   __local int local_result[4];
   int sum;
   int4 input1, input2, sum_vector; // array of 4 floats which support vectorization
   uint global_addr, local_addr;

   global_addr = get_global_id(0) * 2;
   input1 = data[global_addr];
   input2 = data[global_addr+1];
   sum_vector = input1 + input2; // perform four floating-point additions simultaneously

   local_addr = get_local_id(0);
   local_result[local_addr] = sum_vector.s0 + sum_vector.s1 + 
                              sum_vector.s2 + sum_vector.s3; 
   barrier(CLK_LOCAL_MEM_FENCE);

   if(get_local_id(0) == 0) {
      sum = 0.0f;
      for(int i=0; i<get_local_size(0); i++) {
         sum += local_result[i];
      }
      group_result[get_group_id(0)] = sum;
   }
}
