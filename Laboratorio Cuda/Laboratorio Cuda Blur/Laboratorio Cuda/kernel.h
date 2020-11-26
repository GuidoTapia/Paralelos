#ifndef IMAGEFILTER_GREYSCALE_CUDA_H
#define IMAGEFILTER_GREYSCALE_CUDA_H

void blur(unsigned char* R, unsigned char* G, unsigned char* B, unsigned char* Rout, unsigned char* Gout, unsigned char* Bout, int w, int h);

#endif 