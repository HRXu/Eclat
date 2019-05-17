#pragma once
#include<string>
#include<CL/cl.h>
#include<cstdio>
#include<fstream>
#include<vector>
#include "Column.h"
#define GLOBAL_WORK_SIZE 4
#define LOCAL_WORK_SIZE 1
//#define WORK_SIZE GLOBAL_WORK_SIZE*LOCAL_WORK_SIZE
#define WORK_SIZE 48

class CL_Factory
{
public:
	CL_Factory();
	//initialize
	void Init(cl_platform_id id);
	//complie the kernal code and create the runtime environment
	void Load(const char *path);
	void Complie();

	void CreateBuffer(int item_count, int T_count);

	//set the params add excute the kernal
	void WriteBufferA(char * items, char * T);

	void WriteBuffer(int index, char * items, char * T, int * _param);
	void SetParamAndEnqueue(int index);
	void ReadResult(std::vector<Column>& dest, int threshold, int item_count, int T_count,int c);


	cl_platform_id* platforms = nullptr;
	cl_device_id* devices = nullptr;
	cl_uint numDevices = 0;
	cl_int status;
	~CL_Factory();

private:
	cl_context context = NULL;
	cl_program program;
	cl_command_queue cmdQueue;


	std::string source;

	int item_datasize;
	int T_datasize;

	int Item_Count;
	int T_Count;

	cl_mem item_buf_A;
	cl_mem T_buf_A;

	cl_mem item_buf[WORK_SIZE];
	cl_mem T_buf[WORK_SIZE];
	cl_mem param[WORK_SIZE];
	
	cl_kernel kernels[WORK_SIZE];
};



