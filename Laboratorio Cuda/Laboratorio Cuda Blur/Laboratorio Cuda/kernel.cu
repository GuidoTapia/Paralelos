
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#define BLUR_SIZE 10
__global__
void cudaBlur(unsigned char* R, unsigned char* G, unsigned char* B, unsigned char* Rout, unsigned char* Gout, unsigned char* Bout, int w,int h) {
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    if (col < w && row < h) {
        int Rval = 0;
        int Gval = 0;
        int Bval = 0;
        int cont = 0;
        for (int blurRow = -BLUR_SIZE; blurRow < BLUR_SIZE + 1; blurRow++) {
            for (int blurCol = -BLUR_SIZE; blurCol < BLUR_SIZE + 1; blurCol++) {
                int curRow = row + blurRow;
                int curCol = col + blurCol;
                if (curRow > -1 && curRow<h && curCol>-1 && curCol < w) {
                    Rval += R[curRow * w + curCol];
                    Gval += G[curRow * w + curCol];
                    Bval += B[curRow * w + curCol];
                    ++cont;
                }
            }
        }
        Rout[row * w + col] = (cont) ? (char)(Rval / cont) : 0;
        Gout[row * w + col] = (cont) ? (char)(Gval / cont) : 0;
        Bout[row * w + col] = (cont) ? (char)(Bval / cont) : 0;
    }
}

void blur(unsigned char* R, unsigned char* G, unsigned char* B, unsigned char* Rout, unsigned char* Gout, unsigned char* Bout, int w, int h) {
    int size = w*h * sizeof(unsigned char);
    unsigned char* d_R, * d_G, * d_B, * d_Rout, * d_Gout, * d_Bout;
    cudaMalloc((void**)&d_R, size);
    cudaMemcpy(d_R, R, size, cudaMemcpyHostToDevice);
    cudaMalloc((void**)&d_G, size);
    cudaMemcpy(d_G, G, size, cudaMemcpyHostToDevice);
    cudaMalloc((void**)&d_B, size);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);
    cudaMalloc((void**)&d_Rout, size);
    cudaMalloc((void**)&d_Gout, size);
    cudaMalloc((void**)&d_Bout, size);

    cudaBlur << <dim3(w/32, h/32), dim3(32, 32) >> > (d_R, d_G, d_B, d_Rout, d_Gout, d_Bout, w,h);
    cudaMemcpy(Rout, d_Rout, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(Gout, d_Gout, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(Bout, d_Bout, size, cudaMemcpyDeviceToHost);

    cudaFree(d_R);
    cudaFree(d_G);
    cudaFree(d_B);
    cudaFree(d_Rout);
    cudaFree(d_Gout);
    cudaFree(d_Bout);
}