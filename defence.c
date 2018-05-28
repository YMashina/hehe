#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push, 1)

typedef struct BMFileHeader
{
    unsigned short btype;
    unsigned int bsize;
    unsigned int breserved12;
    unsigned int boffset;
}BMFileHeader;

typedef struct BMInfoHeader
{
    unsigned int size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitCount;
    unsigned int compression;
    unsigned int sizelmage;
    unsigned int xPelsPerMeter;
    unsigned int yPelsPerMeter;
    unsigned int clrUsed;
    unsigned int clrImportant;

}BMInfoHeader;

#pragma pack(pop)

typedef struct RGB
{
    unsigned char  red;
    unsigned char  green;
    unsigned char  blue;

} RGB;

void whiteblue(unsigned char** raster, size_t rgb, int height, int width){
int flag = 0, i=0, j = 0;
    for (i = 0; i < height; i++)
    {
        flag = 0;
        for (j = 0; j < width; j++)
        {
            flag = 0;
            if (j + 1 < width && j - 1 > 0 && i - 1 > 0 && i + 1 < height)
            {

                if (raster[i][j * rgb] >= 210 && raster[i][j * rgb + 1] >= 210 && raster[i][j * rgb + 2] >= 210)
                {

                    if (raster[i][(j + 1) * rgb] <= 210 && raster[i][(j + 1) * rgb + 1] <= 210 && raster[i][(j + 1) * rgb + 2] <= 210)
                        flag = 1;
                    if (raster[i][(j - 1) * rgb] <= 210 && raster[i][(j - 1) * rgb + 1] <= 210 && raster[i][(j - 1) * rgb + 2] <= 210)
                        flag = 1;
                    if (raster[i + 1][(j) * rgb] <= 210 && raster[i + 1][(j) * rgb + 1] <= 210 && raster[i + 1][(j) * rgb + 2] <= 210)
                        flag = 1;
                    if (raster[i - 1][(j) * rgb] <= 210 && raster[i - 1][(j) * rgb + 1] <= 210 && raster[i - 1][(j) * rgb + 2] <= 210)
                        flag = 1;
                }

                if (flag == 1)
                {
                    raster[i][j * rgb] = 255;
                    raster[i][j * rgb + 1] = 0;
                    raster[i][j * rgb + 2] = 0;
                }
            }
        }
    }
}

unsigned char** ReadBmp(FILE* input, BMFileHeader* FileHeader, BMInfoHeader* InfoHeader)
{   int i = 0, j = 0, k = 0;
    fseek(input,0,SEEK_END);//set pointer to the end of the file
    int BmpSize = ftell(input);//pointer value of current position in stream. For a binary stream, ammount of bytes from the beginning of the file is returned
    fseek(input,0,SEEK_SET);//set pointer to the beginning of the file

    unsigned char* buf = (char*)malloc(sizeof(unsigned char)*BmpSize); 
    //printf("..have size..\n");
    fread(buf,sizeof(unsigned char),BmpSize,input);
    *FileHeader = *((BMFileHeader*)buf); //set FileHeader pointer to point to the beginning of the file
    buf += sizeof(BMFileHeader); //move buf pointer to the start of InfoHeader (after the end of FileHeader)
    *InfoHeader = *((BMInfoHeader*)buf); //set InfoHeader pointer to point to the beginning of BMInfoHeader structure
    buf -= sizeof(BMFileHeader); // move back to beginning of BMFileHeader structure
    buf += FileHeader -> boffset; // move buf pointer to point to the beginning of the picture raster (pixel info array)

    int len = 3*InfoHeader->width + (InfoHeader->width%4); /* 24 bits = 3 bytes; + allignment 
    (the BMP format requires each row to be padded at the end such that each row is represented by multiples of 4 bytes of data)*/
    unsigned char** raster = (unsigned char**)malloc(sizeof(unsigned char*)*InfoHeader->height);

    for(i=0; i < InfoHeader->height; i++)
    {
        raster[i] = (unsigned char*)malloc(sizeof(unsigned char)*len);//fill raster with picture info, like an array of strings
        for(j=0; j < len; j++)
        raster[i][j] = buf[k++];
    }
    return raster;
}


void NewBmp(char* input, unsigned char** raster, BMFileHeader* FileHeader, BMInfoHeader* InfoHeader)
{   
    int i,j ;
    *(strchr(input, '.')) = '\0';
    strcat(input, "_1.bmp");

    FILE* output = fopen(input,"wb");
    fwrite(FileHeader,sizeof(BMFileHeader), 1, output); //set FileHeader
    fwrite(InfoHeader,sizeof(BMInfoHeader),1, output); //set InfoHeader
    int pixel = 3*InfoHeader->width; // pixel size
    int alignment = InfoHeader->width%4; //allignment size
    for(i=0; i < InfoHeader->height; i++)
    {
        fwrite(raster[i], sizeof(unsigned char), pixel, output);
        for (j=0; j < alignment; j++) //to fill alignment junk with zeros
        fputc(0, output);
    }
    fclose(output);
}

int main()
{
    char* BmpName = (char*)malloc(sizeof(unsigned char)*100);
    printf("-Outline white with blue in BMP-\nName of the BMP file (do NOT include file extention .bmp):\n");
    fgets(BmpName,100,stdin);

    *(strchr(BmpName,'\n')) = '\0';

    strcat(BmpName,".bmp");

    FILE* input = fopen(BmpName, "rb");
    if(input==NULL){
        printf("Error: no such file\n");
        return 0;
    }
	printf("..read bmp name complete..\n");
    BMFileHeader FileHeader;
    BMInfoHeader InfoHeader;

    unsigned char** raster = ReadBmp(input, &FileHeader, &InfoHeader);
    fclose(input);
    printf("..read bmp complete..\n");

    int i = 0, j = 0;
int height = InfoHeader.height, width = InfoHeader.width;
size_t rgb=sizeof(RGB);

whiteblue(raster, rgb, height, width);

    printf("..whiteblue complete..\n");
    NewBmp(BmpName,raster, &FileHeader, &InfoHeader);
    
    printf("BMP file created: %s\n", BmpName);

    free(BmpName);

    for(int i=0; i < InfoHeader.height; i++){
        free(raster[i]);
    }

    free(raster);
    return 0;
}