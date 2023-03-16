
#include "gramschmidt_utils.h"

///////////////////////////////////////
/////// AUTOMATICALLY ANNOTATED ///////
///////////////////////////////////////
#include "kernel_invoker.h"
///////////////////////////////////////
///////////////////////////////////////
const int kernel_info_size_param_idx_gramschmidt_kernel1 __attribute__((used))  = 4;
const int kernel_info_dim_gramschmidt_kernel1 __attribute__((used))  = 2;
const int kernel_info_size_param_idx_gramschmidt_kernel2 __attribute__((used))  = 4;
const int kernel_info_dim_gramschmidt_kernel2 __attribute__((used))  = 2;
const int kernel_info_size_param_idx_gramschmidt_kernel3 __attribute__((used))  = 4;
const int kernel_info_dim_gramschmidt_kernel3 __attribute__((used))  = 2;
void
gramschmidt (DATA_TYPE* A, DATA_TYPE* R, DATA_TYPE* Q)
{
  int i, j, k;
  DATA_TYPE nrm;
  for (k = 0; k < N; k++)
    {
      nrm = 0;
      for (i = 0; i < M; i++)
 {
   nrm += A[i * N + k] * A[i * N + k];
 }
      R[k * N + k] = sqrt (nrm);
      for (i = 0; i < M; i++)
 {
   Q[i * N + k] = A[i * N + k] / R[k * N + k];
 }
      for (j = k + 1; j < N; j++)
 {
   R[k * N + j] = 0;
   for (i = 0; i < M; i++)
     {
       R[k * N + j] += Q[i * N + k] * A[i * N + j];
     }
   for (i = 0; i < M; i++)
     {
       A[i * N + j] = A[i * N + j] - Q[i * N + k] * R[k * N + j];
     }
 }
    }
}
void
init_array (DATA_TYPE* A)
{
  int i, j;
  for (i = 0; i < M; i++)
    {
      for (j = 0; j < N; j++)
 {
   A[i * N + j] = ((DATA_TYPE) (i + 1) * (j + 1)) / (M + 1);
 }
    }
}
int
compareResults (DATA_TYPE* A, DATA_TYPE* A_outputFromGpu)
{
  int i, j, fail;
  fail = 0;
  for (i = 0; i < M; i++)
    {
      for (j = 0; j < N; j++)
 {
   if (percentDiff (
       A[i * N + j],       A_outputFromGpu[i * N + j]) > PERCENT_DIFF_ERROR_THRESHOLD)
     {
       fail++;
       printf ("i: %d j: %d \n1: %f\n 2: %f\n", i, j, A[i * N + j],        A_outputFromGpu[i * N + j]);
       return (EXIT_FAILURE);
     }
 }
    }
  return (EXIT_SUCCESS);
  
}
void
GPU_argv_init ()
{
  cudaDeviceProp deviceProp;
  cudaGetDeviceProperties (&deviceProp, GPU_DEVICE);
  printf ("[running on device %d: %s]\n", GPU_DEVICE, deviceProp.name);
  cudaSetDevice ( GPU_DEVICE);
  return;
}
//__global__ void
//gramschmidt_kernel1 (DATA_TYPE *a, DATA_TYPE *r, DATA_TYPE *q, int k, int M,       int N)
//{
//  int tid = blockIdx.x * blockDim.x + threadIdx.x;
//  if (tid == 0)
//    {
//      DATA_TYPE nrm = 0.0;
//      int i;
//      for (i = 0; i < M; i++)
// {
//   nrm += a[i * N + k] * a[i * N + k];
// }
//      r[k * N + k] = sqrt (nrm);
//    }
//}
//__global__ void
//gramschmidt_kernel2 (DATA_TYPE *a, DATA_TYPE *r, DATA_TYPE *q, int k, int M,       int N)
//{
//  int i = blockIdx.x * blockDim.x + threadIdx.x;
//  if (i < M)
//    {
//      q[i * N + k] = a[i * N + k] / r[k * N + k];
//    }
//}
//__global__ void
//gramschmidt_kernel3 (DATA_TYPE *a, DATA_TYPE *r, DATA_TYPE *q, int k, int M,       int N)
//{
//  int j = blockIdx.x * blockDim.x + threadIdx.x;
//  if ((j > k) && (j < N))
//    {
//      r[k * N + j] = 0.0;
//      int i;
//      for (i = 0; i < M; i++)
// {
//   r[k * N + j] += q[i * N + k] * a[i * N + j];
// }
//      for (i = 0; i < M; i++)
// {
//   a[i * N + j] -= q[i * N + k] * r[k * N + j];
// }
//    }
//}
void
gramschmidtCuda (DATA_TYPE* A, DATA_TYPE* R, DATA_TYPE* Q,   DATA_TYPE* A_outputFromGpu)
{
  double t_start, t_end;
  dim3 block (DIM_THREAD_BLOCK_X, DIM_THREAD_BLOCK_Y);
  dim3 gridKernel1 (1, 1);
  dim3 gridKernel2 ((size_t) ceil (((float) N) / ((float) DIM_THREAD_BLOCK_X)),      1);
  dim3 gridKernel3 ((size_t) ceil (((float) N) / ((float) DIM_THREAD_BLOCK_X)),      1);
  DATA_TYPE *A_gpu;
  DATA_TYPE *R_gpu;
  DATA_TYPE *Q_gpu;
  cudaMalloc ((void **) &A_gpu, sizeof(DATA_TYPE) * M * N);
  cudaMalloc ((void **) &R_gpu, sizeof(DATA_TYPE) * M * N);
  cudaMalloc ((void **) &Q_gpu, sizeof(DATA_TYPE) * M * N);
  cudaMemcpy (A_gpu, A, sizeof(DATA_TYPE) * M * N, cudaMemcpyHostToDevice);
  cuda_timer * t1, *t2, *t3;
  t1 = (cuda_timer*) malloc (N * sizeof(cuda_timer));
  t2 = (cuda_timer*) malloc (N * sizeof(cuda_timer));
  t3 = (cuda_timer*) malloc (N * sizeof(cuda_timer));
  int k;
  for (k = 0; k < N; k++)
    {
      cuda_timer_init (t1[k]);
      cuda_timer_init (t2[k]);
      cuda_timer_init (t3[k]);
    }
  for (k = 0; k < N; k++)
    {
      cuda_timer_record_start (t1[k]);
      	
 ////////////////////////////////////////////////////////////////////////
 ////////// WARNING: AUTOMATICALLY ANNOTATED REGION BEGINS HERE /////////
 ////////////////////////////////////////////////////////////////////////
	
 

 char kernel_gramschmidt_kernel1_0_name[] = "kernel_gramschmidt_kernel1_sm_75";
 
 //launch_params: 3 for grid_dim, 3 for block_dim, 1 for dynamic_shared_mem_bytes;
 int kernel_gramschmidt_kernel1_sm_75_0_launch_params[6];
 set_kernel_launch_params(kernel_gramschmidt_kernel1_sm_75_0_launch_params, gridKernel1, block);
 
 void * kernel_gramschmidt_kernel1_sm_75_0_kernel_params[]={&A_gpu , &R_gpu , &Q_gpu , &k , &M , &N};
 
 kernel_invoker(kernel_gramschmidt_kernel1_0_name, kernel_gramschmidt_kernel1_sm_75_0_launch_params, kernel_gramschmidt_kernel1_sm_75_0_kernel_params);
 
 ////////////////////////////////////////////////////////////////////////
 ////////// WARNING: AUTOMATICALLY ANNOTATED REGION ENDS HERE ///////////
 ////////////////////////////////////////////////////////////////////////
	
      cudaCheckKernel()
      ;
      cuda_timer_record_stop (t1[k]);
      cudaThreadSynchronize ();
      cuda_timer_record_start (t2[k]);
      	
 ////////////////////////////////////////////////////////////////////////
 ////////// WARNING: AUTOMATICALLY ANNOTATED REGION BEGINS HERE /////////
 ////////////////////////////////////////////////////////////////////////
	
 

 char kernel_gramschmidt_kernel2_0_name[] = "kernel_gramschmidt_kernel2_sm_75";
 
 //launch_params: 3 for grid_dim, 3 for block_dim, 1 for dynamic_shared_mem_bytes;
 int kernel_gramschmidt_kernel2_sm_75_0_launch_params[6];
 set_kernel_launch_params(kernel_gramschmidt_kernel2_sm_75_0_launch_params, gridKernel2, block);
 
 void * kernel_gramschmidt_kernel2_sm_75_0_kernel_params[]={&A_gpu , &R_gpu , &Q_gpu , &k , &M , &N};
 
 kernel_invoker(kernel_gramschmidt_kernel2_0_name, kernel_gramschmidt_kernel2_sm_75_0_launch_params, kernel_gramschmidt_kernel2_sm_75_0_kernel_params);
 
 ////////////////////////////////////////////////////////////////////////
 ////////// WARNING: AUTOMATICALLY ANNOTATED REGION ENDS HERE ///////////
 ////////////////////////////////////////////////////////////////////////
	
      cudaCheckKernel()
      ;
      cuda_timer_record_stop (t2[k]);
      cudaThreadSynchronize ();
      cuda_timer_record_start (t3[k]);
      	
 ////////////////////////////////////////////////////////////////////////
 ////////// WARNING: AUTOMATICALLY ANNOTATED REGION BEGINS HERE /////////
 ////////////////////////////////////////////////////////////////////////
	
 

 char kernel_gramschmidt_kernel3_0_name[] = "kernel_gramschmidt_kernel3_sm_75";
 
 //launch_params: 3 for grid_dim, 3 for block_dim, 1 for dynamic_shared_mem_bytes;
 int kernel_gramschmidt_kernel3_sm_75_0_launch_params[6];
 set_kernel_launch_params(kernel_gramschmidt_kernel3_sm_75_0_launch_params, gridKernel3, block);
 
 void * kernel_gramschmidt_kernel3_sm_75_0_kernel_params[]={&A_gpu , &R_gpu , &Q_gpu , &k , &M , &N};
 
 kernel_invoker(kernel_gramschmidt_kernel3_0_name, kernel_gramschmidt_kernel3_sm_75_0_launch_params, kernel_gramschmidt_kernel3_sm_75_0_kernel_params);
 
 ////////////////////////////////////////////////////////////////////////
 ////////// WARNING: AUTOMATICALLY ANNOTATED REGION ENDS HERE ///////////
 ////////////////////////////////////////////////////////////////////////
	
      cudaCheckKernel()
      ;
      cuda_timer_record_stop (t3[k]);
      cudaThreadSynchronize ();
    }
  float t1_total = 0, t2_total = 0, t3_total = 0;
  for (k = 0; k < N; k++)
    {
      cuda_timer_record_get_elapsed_time (t1[k]);
      cuda_timer_record_get_elapsed_time (t2[k]);
      cuda_timer_record_get_elapsed_time (t3[k]);
      t1_total += t1[k].elapsed_time;
      t2_total += t2[k].elapsed_time;
      t3_total += t3[k].elapsed_time;
    }
  cudaMemcpy (A_outputFromGpu, A_gpu, sizeof(DATA_TYPE) * M * N,       cudaMemcpyDeviceToHost);
  printf (
      "[trace: n=%d, bx=%d, by=%d, elapsed_gramschmidt_kernel1=%0.4f (ms),\n"
      " elapsed_gramschmidt_kernel2=%0.4f (ms), elapsed_gramschmidt_kernel3=%0.4f (ms)] ... ",      N, DIM_THREAD_BLOCK_X, DIM_THREAD_BLOCK_Y, t1_total, t2_total, t3_total);
  cudaFree (A_gpu);
  cudaFree (R_gpu);
  cudaFree (Q_gpu);
  for (k = 0; k < N; k++)
    {
      cuda_timer_destroy (t1[k]);
      cuda_timer_destroy (t2[k]);
      cuda_timer_destroy (t3[k]);
    }
  free (t1);
  free (t2);
  free (t3);
}
int
main (int argc, char *argv[])
{
 int n = 256, bx = 32, by = 8;
  if (argc > 1)
    n = atoi (argv[1]);
  if (argc > 2)
    bx = atoi (argv[2]);
  if (argc > 3)
    by = atoi (argv[3]);
  M=N= n;
  DIM_THREAD_BLOCK_X = bx;
  DIM_THREAD_BLOCK_Y = by;
  double t_start, t_end;
  DATA_TYPE* A;
  DATA_TYPE* A_outputFromGpu;
  DATA_TYPE* R;
  DATA_TYPE* Q;
  A = (DATA_TYPE*) malloc (M * N * sizeof(DATA_TYPE));
  A_outputFromGpu = (DATA_TYPE*) malloc (M * N * sizeof(DATA_TYPE));
  R = (DATA_TYPE*) malloc (M * N * sizeof(DATA_TYPE));
  Q = (DATA_TYPE*) malloc (M * N * sizeof(DATA_TYPE));
  init_array (A);
  GPU_argv_init ();
#pragma START_TRACING
  gramschmidtCuda (A, R, Q, A_outputFromGpu);
#pragma STOP_TRACING
  gramschmidt (A, R, Q);
  int s = compareResults (A, A_outputFromGpu);
  if (s == EXIT_SUCCESS)
    printf ("PASS\n");
  else
    printf ("FAIL\n");
  free (A);
  free (A_outputFromGpu);
  free (R);
  free (Q);
  return 0;
}