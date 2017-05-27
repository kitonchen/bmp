#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include"bmp.h"

void histogram_equalize(bmp_file* bmpfile, word bitcount)//24λͼ��Ч
{
	int totalSize = 0;
	//����λͼʵ�ʿ��
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
		printf("���ļ�%s����\n", bmppath);
		return NULL;
	}

	fread((void*)bmpfile, sizeof(bmp_file), 1, fd);//��ȡ

	if (bmpfile->fileHeader.bftype != 0x4d42)//�ж��ǲ���BMP
	{
		printf("����bmp�ļ�\n");
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
		printf("ͼ���ȣ�%d\nͼ��߶�:%d\nͼ��λ��:%d\n", 
			bmpfile.infoHeader.biWidth,
			bmpfile.infoHeader.biHeight,
			bmpfile.infoHeader.biBitCount);
		
	}

	fclose(fd);
	return 0;
	
}