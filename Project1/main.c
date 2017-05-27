#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include"bmp.h"

void histogram_equalize(bmp_file* bmpfile, word bitcount)//24位图有效
{
	int totalSize = 0;
	//计算位图实际宽度
	if (bitcount == 24)
	{
		int width = bmpfile->infoHeader.biWidth;
		int height = bmpfile->infoHeader.biHeight;
		totalSize = (((width*bitcount >> 3) + 3) >> 4)*height;
	}

	unsigned char* data = (char*)malloc(totalSize);

	
}

FILE* readbmp(bmp_file* bmpfile,const char*bmppath)
{
	
	FILE* fd = fopen(bmppath, "rb");

	if (fd == NULL)
	{
		printf("打开文件%s错误\n", bmppath);
		return NULL;
	}

	fread((void*)bmpfile, sizeof(bmp_file), 1, fd);//读取

	if (bmpfile->fileHeader.bftype != 0x4d42)//判断是不是BMP
	{
		printf("不是bmp文件\n");
		fclose(fd);
		return NULL;
	}

	return fd;
}

int main()
{
	bmp_file bmpfile = {0};
	FILE* fd=NULL;
	if ((fd = readbmp(&bmpfile, "test.bmp")) != NULL)
	{
		printf("图像宽度：%d\n图像高度:%d\n图像位数:%d\n", 
			bmpfile.infoHeader.biWidth,
			bmpfile.infoHeader.biHeight,
			bmpfile.infoHeader.biBitCount);
		
	}

	fclose(fd);
	return 0;
	
}