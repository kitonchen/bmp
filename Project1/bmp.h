#pragma once
#pragma pack(1)
#define  true 1
#define  false 0

typedef unsigned short word;
typedef unsigned long  dword;
typedef unsigned char byte;

typedef struct BitMapFileHeader
{
	word bftype:16;//文件类型
	dword bfsize; // 文件的类型，
	word bfReserved1; //保留字，必须0
	word bfReserved2; //保留字，必须0
	dword bfOffBits;
}bitmap_file_header;

typedef struct BitMapInfoHeader
{
	dword biSize; // 本结构所占用字
	long biWidth; // 位图的高度，以像
	long biHeight; // 位图的高度，以像
	word biPlanes; // 目标设备的级别，必须为 1
	word biBitCount;// 每个像素所需的位数（详细见
	dword biCompression; // 位图压缩类型，必须是
	dword biSizeImage; // 位图的大小，以字节为单位
	long biXPelsPerMeter; // 位图水平分辨率，每米像素数
	long biYPelsPerMeter; // 位图垂直分辨率，每米像
	dword biClrUsed;//位图实际使用调色板中的颜色数（见详
	dword biClrImportant;// 位图显示过程中重要的颜色数
}bimap_info_header;

typedef struct RGBquad
{
	byte rgbBlue;//蓝色亮度
	byte rgbGreen;//绿色亮度
	byte rgbRed;//红色亮度
	byte rgbReserved;//保留
}RGB_quad;


typedef struct BMPfile
{
	bitmap_file_header fileHeader;
	bimap_info_header  infoHeader;
	//RGB_quad colorsquad[1];//彩色表
}bmp_file;





