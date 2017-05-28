#pragma once
#pragma pack(1)
#define  true 1
#define  false 0

typedef unsigned short word;
typedef unsigned long  dword;
typedef unsigned char byte;

typedef struct BitMapFileHeader
{
	word bftype:16;//�ļ�����
	dword bfsize; // �ļ������ͣ�
	word bfReserved1; //�����֣�����0
	word bfReserved2; //�����֣�����0
	dword bfOffBits;
}bitmap_file_header;

typedef struct BitMapInfoHeader
{
	dword biSize; // ���ṹ��ռ����
	long biWidth; // λͼ�ĸ߶ȣ�����
	long biHeight; // λͼ�ĸ߶ȣ�����
	word biPlanes; // Ŀ���豸�ļ��𣬱���Ϊ 1
	word biBitCount;// ÿ�����������λ������ϸ��
	dword biCompression; // λͼѹ�����ͣ�������
	dword biSizeImage; // λͼ�Ĵ�С�����ֽ�Ϊ��λ
	long biXPelsPerMeter; // λͼˮƽ�ֱ��ʣ�ÿ��������
	long biYPelsPerMeter; // λͼ��ֱ�ֱ��ʣ�ÿ����
	dword biClrUsed;//λͼʵ��ʹ�õ�ɫ���е���ɫ��������
	dword biClrImportant;// λͼ��ʾ��������Ҫ����ɫ��
}bimap_info_header;

typedef struct RGBquad
{
	byte rgbBlue;//��ɫ����
	byte rgbGreen;//��ɫ����
	byte rgbRed;//��ɫ����
	byte rgbReserved;//����
}RGB_quad;


typedef struct BMPfile
{
	bitmap_file_header fileHeader;
	bimap_info_header  infoHeader;
	//RGB_quad colorsquad[1];//��ɫ��
}bmp_file;





