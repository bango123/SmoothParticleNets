#ifndef __gpu_kernels_h__
#define __gpu_kernels_h__
#ifdef __cplusplus
extern "C" {
#endif

int cuda_convsp(
        const float* qlocs,
        const float* locs, 
        const float* data, 
        const float* neighbors,
        const float* weight, 
        const float* bias, 
        const int batch_size, 
        const int M,
        const int N, 
        const int nchannels, 
        const int ndims, 
        const int max_neighbors,
        const int nkernels, 
        const int ncells, 
        const float radius, 
        const float* kernel_size, 
        const float* dilation, 
        const int dis_norm, 
        const int kernel_fn, 
        float* out, 
        float* dqlocs,
        float* dlocs,
        float* ddata, 
        float* dweight, 
        cudaStream_t stream, 
        const size_t nshared_device_mem);

int cuda_convsdf(
	const float* locs, 
	const int batch_size, 
	const int N, 
	const int ndims, 
	const float* idxs,
    const float* poses, 
    const float* scales, 
    const int M, 
    const int pose_len, 
    const float* sdfs, 
    const float* sdf_offsets, 
    const float* sdf_shapes, 
    const float* weight, 
    const float* bias, 
    const int nkernels, 
    const int ncells, 
    const float* kernel_size, 
    const float* dilation, 
    const float max_distance, 
    float* out, 
    float* dlocs,
    float* dweight, 
    float* dposes,
    cudaStream_t stream);

size_t GetSharedMemPerBlock(int device);

int cuda_hashgrid_order(
    float* locs,
    const float* low,
    const float* grid_dims,
    float* cellIDs,
    float* idxs,
    float* buffer,
    const int batch_size,
    const int N,
    const int ndims,
    const float cellEdge,
    cudaStream_t stream);

int cuda_compute_collisions(
    const float* qlocs,
    const float* locs,
    const float* low,
    const float* grid_dims,
    const float* cellIDs,
    float* cellStarts,
    float* cellEnds,
    float* collisions,
    const int batch_size,
    const int M,
    const int N,
    const int ndims,
    const int max_collisions,
    const int ncells,
    const float cellEdge,
    const float radius,
    const int include_self,
    cudaStream_t stream);

int cuda_reorder_data(
    float* locs,
    float* data,
    float* idxs,
    float* nlocs,
    float* ndata,
    const int batch_size,
    const int N,
    const int ndims,
    const int nchannels,
    const int reverse,
    cudaStream_t stream);

size_t get_radixsort_buffer_size(cudaStream_t stream);

int cuda_particleprojection(
        const float* locs, 
        const float camera_fl,
        const float filter_std,
        const float filter_scale,
        const float* depth_mask, 
        const int batch_size,
        const int N,
        const int width,
        const int height,
        float* out, 
        float* dlocs,
        cudaStream_t stream);

int cuda_imageprojection(
        const float* locs, 
        const float* image,
        const float camera_fl,
        const float* depth_mask, 
        const int batch_size,
        const int N,
        const int width,
        const int height,
        const int channels,
        float* out, 
        float* dlocs,
        float* dimage,
        cudaStream_t stream);

#ifdef __cplusplus
}
#endif

#endif