#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include"bmp.h"
//直方图处理
char* histogram_equalize(bmp_file* bmpfile,unsigned char* data)//24位图有效
{
	int width = bmpfile->infoHeader.biWidth;
	int height = bmpfile->infoHeader.biHeight;
	int imagesize = width*height;
	int sum = 0;
	//一个像素占三个字节代表BGR分量
	//因为灰度图像三个通道的值相等
	//histogram先做记录pix_val-pix_num的key-value对
	//后做记录pix_val-pix_new_val的key-value对
	int histogram[256][3] = { 0 };
	double countprobability[256][3] = { 0 };
	//内存设置为0
	memset(histogram, 0, sizeof(histogram));
	memset(countprobability, 0, sizeof(countprobability));
	//下面这些计算，要结合算法的公式来体会
	
	//统计BGR通道各个像素数量
	for (long i = 0; i < bmpfile->infoHeader.biSizeImage; i+=3)
	{
		histogram[data[i]][0]++;	
		histogram[data[i+1]][1]++;
		histogram[data[i+2]][2]++;
	}

	//计算各通道各像素的单独的概率
	for (int i = 0; i < 256; i++)
	{
		countprobability[i][0] = 1.0*histogram[i][0] / imagesize;
		countprobability[i][1] = 1.0*histogram[i][1] / imagesize;
		countprobability[i][2] = 1.0*histogram[i][2] / imagesize;
	}
	//用递推的方法，计算累计概率
	for (int i = 1; i < 256; i++)
	{
		countprobability[i][0] += countprobability[i - 1][0];
		countprobability[i][1] += countprobability[i - 1][1];
		countprobability[i][2] += countprobability[i - 1][2];
	}

	//计算新的映射，四舍五入向上取整
	for (int i = 0; i < 256; i++)
	{
		histogram[i][0] = 1.0*255 * countprobability[i][0]+0.5;
		histogram[i][1] = 1.0 * 255 * countprobability[i][1] + 0.5;
		histogram[i][2] = 1.0 * 255 * countprobability[i][2] + 0.5;
	}


	//替换均衡化后的值
	for (long i = 0; i < bmpfile->infoHeader.biSizeImage; i += 3)
	{
		 data[i] = histogram[data[i]][0];
		 data[i + 1] = histogram[data[i+1]][1];
		 data[i + 2] = histogram[data[i+2]][2];
	}
	return data;
}

char* readbmp(bmp_file* bmpfile,const char*bmppath)
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
	//分配数据大小
	unsigned char* data = (char*)malloc(bmpfile->infoHeader.biSizeImage);
	memset(data, 0, bmpfile->infoHeader.biSizeImage);
	int i = 0;
	
	while (i<bmpfile->infoHeader.biSizeImage)
	{
		fread(data + i, sizeof(char), 1, fd);
		i++;
	}

	fclose(fd);
	return data;
}

void writebmp(bmp_file* bmpfile,const char* data)
{
	FILE* fd;

	fd = fopen("result.bmp", "wb");
	fwrite((void*)bmpfile, sizeof(bmp_file), 1, fd);
	long i = 0;
	while (i < bmpfile->infoHeader.biSizeImage)
	{
		fwrite(data + i, sizeof(char), 1, fd);
		i++;
	}
	//关闭文件流和清空内存
	fclose(fd);
	free(data);
}

int main()
{
	bmp_file bmpfile = {0};
	unsigned char* data = readbmp(&bmpfile, "rgbtest.bmp");
	if (data != NULL)
	{
		printf("图像宽度：%d\n图像高度:%d\n图像位数:%d\n", 
			bmpfile.infoHeader.biWidth,
			bmpfile.infoHeader.biHeight,
			bmpfile.infoHeader.biBitCount);		
	}

	data = histogram_equalize(&bmpfile,data);
	writebmp(&bmpfile, data);

	return 0;
	
}