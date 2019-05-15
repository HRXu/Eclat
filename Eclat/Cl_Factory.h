#pragma once
#include<string>
#include<CL/cl.h>
#include<cstdio>
class CL_Factory
{
public:
	CL_Factory();
	//initialize
	void Init(cl_platform_id id);
	//complie the kernal code and create the runtime environment
	void Complie(std::string s,int elements);

	//set the params add excute the kernal
	void WriteBufferA(bool * A, int elements);
	void WriteBufferB(bool * B, int elements);
	void Run(bool * C, int elements);

	cl_platform_id* platforms = nullptr;
	cl_device_id* devices = nullptr;
	cl_uint numDevices = 0;
	cl_int status;
	~CL_Factory();

private:
	cl_context context = NULL;
	cl_program program;
	cl_kernel kernel = NULL;
	cl_command_queue cmdQueue;

	//param A
	cl_mem bufferA;
	//param B
	cl_mem bufferB;
	//result C
	cl_mem bufferC;
};

