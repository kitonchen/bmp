#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include"bmp.h"
//ֱ��ͼ����
char* histogram_equalize(bmp_file* bmpfile,unsigned char* data)//24λͼ��Ч
{
	int width = bmpfile->infoHeader.biWidth;
	int height = bmpfile->infoHeader.biHeight;
	int imagesize = width*height;
	int sum = 0;
	//һ������ռ�����ֽڴ���BGR����
	//��Ϊ�Ҷ�ͼ������ͨ����ֵ���
	//histogram������¼pix_val-pix_num��key-value��
	//������¼pix_val-pix_new_val��key-value��
	int histogram[256][3] = { 0 };
	double countprobability[256][3] = { 0 };
	//�ڴ�����Ϊ0
	memset(histogram, 0, sizeof(histogram));
	memset(countprobability, 0, sizeof(countprobability));
	//������Щ���㣬Ҫ����㷨�Ĺ�ʽ�����
	
	//ͳ��BGRͨ��������������
	for (long i = 0; i < bmpfile->infoHeader.biSizeImage; i+=3)
	{
		histogram[data[i]][0]++;	
		histogram[data[i+1]][1]++;
		histogram[data[i+2]][2]++;
	}

	//�����ͨ�������صĵ����ĸ���
	for (int i = 0; i < 256; i++)
	{
		countprobability[i][0] = 1.0*histogram[i][0] / imagesize;
		countprobability[i][1] = 1.0*histogram[i][1] / imagesize;
		countprobability[i][2] = 1.0*histogram[i][2] / imagesize;
	}
	//�õ��Ƶķ����������ۼƸ���
	for (int i = 1; i < 256; i++)
	{
		countprobability[i][0] += countprobability[i - 1][0];
		countprobability[i][1] += countprobability[i - 1][1];
		countprobability[i][2] += countprobability[i - 1][2];
	}

	//�����µ�ӳ�䣬������������ȡ��
	for (int i = 0; i < 256; i++)
	{
		histogram[i][0] = 1.0*255 * countprobability[i][0]+0.5;
		histogram[i][1] = 1.0 * 255 * countprobability[i][1] + 0.5;
		histogram[i][2] = 1.0 * 255 * countprobability[i][2] + 0.5;
	}


	//�滻���⻯���ֵ
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
	//�������ݴ�С
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
	//�ر��ļ���������ڴ�
	fclose(fd);
	free(data);
}

int main()
{
	bmp_file bmpfile = {0};
	unsigned char* data = readbmp(&bmpfile, "rgbtest.bmp");
	if (data != NULL)
	{
		printf("ͼ���ȣ�%d\nͼ��߶�:%d\nͼ��λ��:%d\n", 
			bmpfile.infoHeader.biWidth,
			bmpfile.infoHeader.biHeight,
			bmpfile.infoHeader.biBitCount);		
	}

	data = histogram_equalize(&bmpfile,data);
	writebmp(&bmpfile, data);

	return 0;
	
}