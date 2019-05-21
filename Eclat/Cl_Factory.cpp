#include "CL_Factory.h"
using namespace std;
void CL_Factory::Init()
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
	cl_platform_id p_id = platforms[0];

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

void CL_Factory::Complie()
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
		printf("Error: Failed to build program executable!\n");
		size_t log_size;
		char *program_log;
		/* Find size of log and print to std output */
		clGetProgramBuildInfo(program, devices[0], CL_PROGRAM_BUILD_LOG,
			0, NULL, &log_size);
		program_log = (char*)malloc(log_size + 1);
		program_log[log_size] = '\0';
		clGetProgramBuildInfo(program, devices[0], CL_PROGRAM_BUILD_LOG,
			log_size + 1, program_log, NULL);
		printf("%s\n", program_log);
		free(program_log);
		exit(1);
	}

	printf("Build program completed\n");

	/*Create the kernel*/
	Kernel= clCreateKernel(program, "Ex", &status);

	/*Create a command queue*/
	cmdQueue = clCreateCommandQueueWithProperties(context, devices[0], 0, &status);

}

void CL_Factory::CreateBuffer(int item_count, int t_count) {
	/*Create device buffers*/
	item_datasize = sizeof(char)*item_count;
	T_datasize = sizeof(char)*t_count;
	this->Item_Count = item_count;
	this->T_Count=t_count;

	item_buf_A = clCreateBuffer(context, CL_MEM_READ_ONLY, item_datasize, NULL, &status);
	T_buf_A = clCreateBuffer(context, CL_MEM_READ_ONLY, T_datasize, NULL, &status);	

	Item_buf= clCreateBuffer(context, CL_MEM_READ_WRITE, item_datasize*WORK_SIZE , NULL, &status);
	T_buf = clCreateBuffer(context, CL_MEM_READ_WRITE, T_datasize*WORK_SIZE , NULL, &status);
	Param_buf = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int)*WORK_SIZE , NULL, &status);
}

/*Write host data to device buffers*/
void CL_Factory::WriteBufferA(char * items, char *T)
{
	status = clEnqueueWriteBuffer(cmdQueue, item_buf_A, CL_FALSE, 0, item_datasize, items, 0, NULL, NULL);
	status = clEnqueueWriteBuffer(cmdQueue, T_buf_A, CL_FALSE, 0, T_datasize, T, 0, NULL, NULL);
}
void CL_Factory::WriteBuffer(int index,
							char * items,
							char *T,
							int _param)
{
	status = clEnqueueWriteBuffer(cmdQueue, Item_buf, CL_FALSE, index*item_datasize, item_datasize, items, 0, NULL, NULL);
	status = clEnqueueWriteBuffer(cmdQueue, T_buf, CL_FALSE, index*T_datasize, T_datasize, T, 0, NULL, NULL);
	status = clEnqueueWriteBuffer(cmdQueue, Param_buf, CL_FALSE, index *sizeof(int), sizeof(int), &_param, 0, NULL, NULL);
}

void CL_Factory::SetParamAndEnqueue()
{
	/*Set the kernel arguments*/
	status = clSetKernelArg(Kernel, 0, sizeof(cl_mem), &item_buf_A);
	status = clSetKernelArg(Kernel, 1, sizeof(cl_mem), &T_buf_A);
	status = clSetKernelArg(Kernel, 2, sizeof(cl_mem), &Item_buf);
	status = clSetKernelArg(Kernel, 3, sizeof(cl_mem), &T_buf);
	status = clSetKernelArg(Kernel, 4, sizeof(cl_mem), &Param_buf);
	status = clSetKernelArg(Kernel, 5, sizeof(int), &T_Count);
	status = clSetKernelArg(Kernel, 6, sizeof(int), &Item_Count);

	size_t globalWorkSize = GLOBAL_WORK_SIZE;
	size_t localWorkSize = LOCAL_WORK_SIZE;

	status = clEnqueueNDRangeKernel(cmdQueue, Kernel, 1, NULL, &globalWorkSize, &localWorkSize, 0, NULL, NULL);
}

void CL_Factory::ReadResult(std::vector<Column>& dest,
							int threshold,
							int item_count,
							int T_count,
							int index)
{
	clFinish(cmdQueue);
	for (int i = 0; i < index; i++)
	{
		int a_param;
		clEnqueueReadBuffer(cmdQueue, Param_buf, CL_TRUE, i*sizeof(int), sizeof(int), &a_param, 0, NULL, NULL);	

		if (a_param < threshold)
			continue;
		Column *tmp = new Column();
		tmp->Item_Array = new char[item_count];
		tmp->T_Array = new char[T_count];
		clEnqueueReadBuffer(cmdQueue, Item_buf, CL_TRUE, i*item_datasize, item_datasize, tmp->Item_Array, 0, NULL, NULL);
		clEnqueueReadBuffer(cmdQueue, T_buf, CL_TRUE, i*T_datasize, T_datasize, tmp->T_Array, 0, NULL, NULL);

		dest.push_back(*tmp);
	}
}


CL_Factory::~CL_Factory()
{
	clReleaseProgram(program);
	clReleaseCommandQueue(cmdQueue);
//TODO
	clReleaseKernel(Kernel);
	clReleaseMemObject(Item_buf);
	clReleaseMemObject(T_buf);
	clReleaseMemObject(Param_buf);

	clReleaseContext(context);

	free(platforms);
	free(devices);
}
