#include "CL_Factory.h"
using namespace std;
CL_Factory::CL_Factory()
{
	cl_uint numPlatforms = 0;

	status = clGetPlatformIDs(0, NULL, &numPlatforms);  //retrieve number of platforms
	printf("# of platform:%d\n", numPlatforms);
	platforms = (cl_platform_id*)malloc(numPlatforms * sizeof(cl_platform_id)); // malloct memery for platform 
	status = clGetPlatformIDs(numPlatforms, platforms, NULL); // initialize platforms

	/*print  platform informations*/
	for (int i = 0; i < numPlatforms; i++)
	{
		size_t size = 0;

		//name
		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 0, NULL, &size);
		char* name = (char*)malloc(size);
		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, size, name, NULL);
		printf("CL_PLATFORM_NAME:%s\n", name);

		//vendor
		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, 0, NULL, &size);
		char *vendor = (char *)malloc(size);
		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, size, vendor, NULL);
		printf("CL_PLATFORM_VENDOR:%s\n", vendor);

		//version
		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, 0, NULL, &size);
		char *version = (char *)malloc(size);
		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, size, version, NULL);
		printf("CL_PLATFORM_VERSION:%s\n", version);

		// profile
		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, 0, NULL, &size);
		char *profile = (char *)malloc(size);
		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, size, profile, NULL);
		printf("CL_PLATFORM_PROFILE:%s\n", profile);

		// extensions
		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, 0, NULL, &size);
		char *extensions = (char *)malloc(size);
		status = clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, size, extensions, NULL);
		printf("CL_PLATFORM_EXTENSIONS:%s\n", extensions);

		// release 
		printf("\n");
		free(name);
		free(vendor);
		free(version);
		free(profile);
		free(extensions);
	}

}
void CL_Factory::Init(cl_platform_id p_id)
{
	status = clGetDeviceIDs(p_id, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);  // retrieve Device number

	printf("# of device:%d\n", numDevices);
	devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id)); // malloct memery for device

	status = clGetDeviceIDs(p_id, CL_DEVICE_TYPE_GPU, numDevices, devices, NULL); // fill in device 

	/*print device informations*/
	for (int i = 0; i < numDevices; i++)
	{
		size_t value_size = 0;
		//name
		status = clGetDeviceInfo(devices[i], CL_DEVICE_NAME, 0, NULL, &value_size);
		char* name_list = (char*)malloc(value_size);
		status = clGetDeviceInfo(devices[i], CL_DEVICE_NAME, value_size, name_list, NULL);
		printf("CL_DEVICE_NAME:%s\n", name_list);

		//PARALLEL COMPUTE UNITS(CU)
		cl_uint     maxComputeUnits = 0;
		status = clGetDeviceInfo(devices[i], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(maxComputeUnits), &maxComputeUnits, NULL);
		printf("CL_DEVICE_MAX_COMPUTE_UNITS:%u\n", maxComputeUnits);
		//maxWorkItemPerGroup
		size_t maxWorkItemPerGroup = 0;
		status = clGetDeviceInfo(devices[0], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(maxWorkItemPerGroup), &maxWorkItemPerGroup, NULL);
		printf("CL_DEVICE_MAX_WORK_GROUP_SIZE: %d\n", maxWorkItemPerGroup);
		//maxGlobalMemSize
		cl_ulong    maxGlobalMemSize = 0;
		status = clGetDeviceInfo(devices[0], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(maxGlobalMemSize), &maxGlobalMemSize, NULL);
		printf("CL_DEVICE_GLOBAL_MEM_SIZE: %lu(MB)\n", maxGlobalMemSize / 1024 / 1024);
		//maxConstantBufferSize     
		cl_ulong maxConstantBufferSize = 0;
		clGetDeviceInfo(devices[0], CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(maxConstantBufferSize), &maxConstantBufferSize, NULL);
		printf("CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE: %lu(KB)\n", maxConstantBufferSize / 1024);
		//maxLocalMemSize
		cl_ulong maxLocalMemSize = 0;
		status = clGetDeviceInfo(devices[0], CL_DEVICE_LOCAL_MEM_SIZE, sizeof(maxLocalMemSize), &maxLocalMemSize, NULL);
		printf("CL_DEVICE_LOCAL_MEM_SIZE: %lu(KB)\n", maxLocalMemSize / 1024);

		printf("\n");
	}
}

void CL_Factory::Load(const char * path)
{
	ifstream fs;
	fs.open(path, ios::in | ios::binary);
	char tmp;
	while (1) {
		tmp=fs.get();
		if (tmp == -1)
			break;
		source += tmp;
	}
	fs.close();
}

void CL_Factory::Complie(int item_count,int T_count)
{
	/*Creat a context*/
	context = clCreateContext(NULL, numDevices, devices, NULL, NULL, &status);
	size_t  device_num;
	clGetContextInfo(context, CL_CONTEXT_NUM_DEVICES, 0, NULL, &device_num);
	printf("Size of cl_device_id:%d\n", sizeof(cl_device_id));
	printf("Num of device in Context:%d\n", device_num);

	/*Create and compile the program*/
	const char *ps = source.c_str();
	program = clCreateProgramWithSource(context, 1, (const char **)&ps, NULL, &status);
	status = clBuildProgram(program, numDevices, devices, NULL, NULL, NULL);

	if (status != CL_SUCCESS)
	{
		size_t len;
		printf("Error: Failed to build program executable!\n");
		exit(1);
	}
	printf("Build program completed\n");

	/*Create the kernel*/
	kernel_intersect = clCreateKernel(program, "ve_intersect", &status);
	kernel_union = clCreateKernel(program, "ve_union", &status);

	/*Create a command queue*/
	cmdQueue = clCreateCommandQueueWithProperties(context, devices[0], 0, &status);

	/*Create device buffers*/
	const int datasize = sizeof(bool)*T_count;
	bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY, datasize, NULL, &status);
	bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY, datasize, NULL, &status);
	bufferC = clCreateBuffer(context, CL_MEM_WRITE_ONLY, datasize, NULL, &status);

	const int item_datasize = sizeof(bool)*item_count;
	bufferE = clCreateBuffer(context, CL_MEM_READ_ONLY, item_datasize, NULL, &status);
	bufferF = clCreateBuffer(context, CL_MEM_READ_ONLY, item_datasize, NULL, &status);
	bufferG = clCreateBuffer(context, CL_MEM_WRITE_ONLY, item_datasize, NULL, &status);
}
/*Write host data to device buffers*/
void CL_Factory::WriteBufferA(bool * A, int elements)
{
	status = clEnqueueWriteBuffer(cmdQueue, bufferA, CL_FALSE, 0, sizeof(bool)*elements, A, 0, NULL, NULL);
}
void CL_Factory::WriteBufferB(bool * B, int elements)
{
	status = clEnqueueWriteBuffer(cmdQueue, bufferB, CL_FALSE, 0, sizeof(bool)*elements, B, 0, NULL, NULL);
}
void CL_Factory::WriteBufferE(bool * B, int elements)
{
	status = clEnqueueWriteBuffer(cmdQueue, bufferE, CL_FALSE, 0, sizeof(bool)*elements, B, 0, NULL, NULL);
}
void CL_Factory::WriteBufferF(bool * B, int elements)
{
	status = clEnqueueWriteBuffer(cmdQueue, bufferF, CL_FALSE, 0, sizeof(bool)*elements, B, 0, NULL, NULL);
}

void CL_Factory::Run_Intersect(bool * C, int elements)
{
	/*Set the kernel arguments*/
	status = clSetKernelArg(kernel_intersect, 0, sizeof(cl_mem), &bufferA);
	status = clSetKernelArg(kernel_intersect, 1, sizeof(cl_mem), &bufferB);
	status = clSetKernelArg(kernel_intersect, 2, sizeof(cl_mem), &bufferC);

	/*CONFIGURE THE WORK-ITEM STRUCTURE*/
	size_t globalWorkSize[1];
	globalWorkSize[0] = elements;
	//  size_t globalSize[1] = { elements }, localSize[1] = { 256 };

	/*Enqueue the kernel for execution*/
	status = clEnqueueNDRangeKernel(cmdQueue, kernel_intersect, 1, NULL, globalWorkSize, NULL, 0, NULL, NULL);
	/*Read the buffer output back to host*/
	clFinish(cmdQueue);
	clEnqueueReadBuffer(cmdQueue, bufferC, CL_TRUE, 0, sizeof(bool)*elements, C, 0, NULL, NULL);
}

void CL_Factory::Run_Union(bool * G, int elements)
{
	/*Set the kernel arguments*/
	status = clSetKernelArg(kernel_union, 0, sizeof(cl_mem), &bufferE);
	status = clSetKernelArg(kernel_union, 1, sizeof(cl_mem), &bufferF);
	status = clSetKernelArg(kernel_union, 2, sizeof(cl_mem), &bufferG);

	/*CONFIGURE THE WORK-ITEM STRUCTURE*/
	size_t globalWorkSize[1];
	globalWorkSize[0] = elements;
	//  size_t globalSize[1] = { elements }, localSize[1] = { 256 };

	/*Enqueue the kernel for execution*/
	status = clEnqueueNDRangeKernel(cmdQueue, kernel_union, 1, NULL, globalWorkSize, NULL, 0, NULL, NULL);
	/*Read the buffer output back to host*/
	clFinish(cmdQueue);
	clEnqueueReadBuffer(cmdQueue, bufferC, CL_TRUE, 0, sizeof(bool)*elements, G, 0, NULL, NULL);
}

void CL_Factory::Run(bool * G, int item_count,bool * C, int t_count)
{
	/*Set the kernel arguments*/
	status = clSetKernelArg(kernel_intersect, 0, sizeof(cl_mem), &bufferA);
	status = clSetKernelArg(kernel_intersect, 1, sizeof(cl_mem), &bufferB);
	status = clSetKernelArg(kernel_intersect, 2, sizeof(cl_mem), &bufferC);

	status = clSetKernelArg(kernel_union, 0, sizeof(cl_mem), &bufferE);
	status = clSetKernelArg(kernel_union, 1, sizeof(cl_mem), &bufferF);
	status = clSetKernelArg(kernel_union, 2, sizeof(cl_mem), &bufferG);

	/*CONFIGURE THE WORK-ITEM STRUCTURE*/
	size_t globalWorkSize1 = t_count;
	size_t globalWorkSize2 = item_count;
	//  size_t globalSize[1] = { elements }, localSize[1] = { 256 };

	/*Enqueue the kernel for execution*/
	status = clEnqueueNDRangeKernel(cmdQueue, kernel_intersect, 1, NULL, &globalWorkSize1, NULL, 0, NULL, NULL);
	status = clEnqueueNDRangeKernel(cmdQueue, kernel_union, 1, NULL, &globalWorkSize2, NULL, 0, NULL, NULL);

	/*Read the buffer output back to host*/
	clFinish(cmdQueue);
	clEnqueueReadBuffer(cmdQueue, bufferC, CL_TRUE, 0, sizeof(bool)*t_count, C, 0, NULL, NULL);
	clEnqueueReadBuffer(cmdQueue, bufferG, CL_TRUE, 0, sizeof(bool)*item_count, G, 0, NULL, NULL);
}

CL_Factory::~CL_Factory()
{
	clReleaseKernel(kernel_intersect);
	clReleaseKernel(kernel_union);
	clReleaseProgram(program);
	clReleaseCommandQueue(cmdQueue);
	clReleaseMemObject(bufferA);
	clReleaseMemObject(bufferB);
	clReleaseMemObject(bufferC);
	clReleaseContext(context);

	free(platforms);
	free(devices);
}
