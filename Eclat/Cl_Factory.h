#pragma once
#include<string>
#include<CL/cl.h>
#include<cstdio>
#include<fstream>
class CL_Factory
{
public:
	CL_Factory();
	//initialize
	void Init(cl_platform_id id);
	//complie the kernal code and create the runtime environment
	void Load(const char *path);
	void Complie(int elements,int T_count);

	//set the params add excute the kernal
	void WriteBufferA(bool * A, int elements);
	void WriteBufferB(bool * B, int elements);
	void WriteBufferE(bool * B, int elements);
	void WriteBufferF(bool * B, int elements);
	void Run_Intersect(bool * C, int elements);
	void Run_Union(bool * C, int elements);

	void Run(bool * C, int item_count, bool * G, int t_count);

	cl_platform_id* platforms = nullptr;
	cl_device_id* devices = nullptr;
	cl_uint numDevices = 0;
	cl_int status;
	~CL_Factory();

private:
	cl_context context = NULL;
	cl_program program;
	cl_kernel kernel_intersect = NULL;
	cl_kernel kernel_union = NULL;
	cl_command_queue cmdQueue;

	//param A
	cl_mem bufferA;
	//param B
	cl_mem bufferB;
	//result C
	cl_mem bufferC;

	//param E
	cl_mem bufferE;
	//param F
	cl_mem bufferF;
	//result G
	cl_mem bufferG;

	std::string source;
};

