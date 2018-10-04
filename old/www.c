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
    char  red;
    char  green;
    char  blue;

} RGB;


void floodFill(int n, int m, char** screen, int x, int y)
{
size_t rgb = sizeof(RGB);
    if (x < 0 || x >= n || y < 0 || y >= m)
        return;
    if (screen[x][y*rgb]!= 255 && screen[x][y*rgb+1]!= 255 && screen[x][y*rgb+2]!= 255){
	screen[x][y*rgb]=0;
	screen[x][y*rgb+1]=0;
	screen[x][y*rgb+2]=255;
        return;
    }
    
    floodFill(n,m,screen, x+1, y);
    floodFill(n,m,screen, x-1, y);
    floodFill(n,m,screen, x, y+1);
    floodFill(n,m,screen, x, y-1);
}

char** ReadBmp(FILE* input, BMFileHeader* FileHeader, BMInfoHeader* InfoHeader)
{   int i = 0, j = 0, k = 0;
    fseek(input,0,SEEK_END);//set pointer to the end of the file
    int BmpSize = ftell(input);//pointer value of current position in stream. For a binary stream, ammount of bytes from the beginning of the file is returned
    fseek(input,0,SEEK_SET);//set pointer to the beginning of the file

    char* buf = (char*)malloc(sizeof(char)*BmpSize); 
    //printf("..have size..\n");
    fread(buf,sizeof(char),BmpSize,input);
    *FileHeader = *((BMFileHeader*)buf); //set FileHeader pointer to point to the beginning of the file
    buf += sizeof(BMFileHeader); //move buf pointer to the start of InfoHeader (after the end of FileHeader)
    *InfoHeader = *((BMInfoHeader*)buf); //set InfoHeader pointer to point to the beginning of BMInfoHeader structure
    buf -= sizeof(BMFileHeader); // move back to beginning of BMFileHeader structure
    buf += FileHeader -> boffset; // move buf pointer to point to the beginning of the picture raster (pixel info array)

    int len = 3*InfoHeader->width + (InfoHeader->width%4); /* 24 bits = 3 bytes + allignment 
    (the BMP format requires each row to be padded at the end such that each row is represented by multiples of 4 bytes of data)*/
    char** raster = (char**)malloc(sizeof(char*)*InfoHeader->height);

    for(i=0; i < InfoHeader->height; i++)
    {
        raster[i] = (char*)malloc(sizeof(char)*len);//fill raster with picture info, like an array of strings
        for(j=0; j < len; j++)
        raster[i][j] = buf[k++];
    }
    return raster;
}

char** whiteblue(char** raster,BMFileHeader* FileHeader, BMInfoHeader* InfoHeader)
{
    int i = 0, j = 0, k = 0, e = 0, w=0, N=1000;
    
    RGB** area = (RGB**)malloc(N); 
	
	int height = InfoHeader->height, width = InfoHeader->width;
printf("..have parameters..\n");
    for ( i = 0; i <height; i++)
    {
//printf("[%d]i=%d\n",height,i);
        area[i] = (RGB*)malloc(N);  
        memmove(area[i], raster[i], sizeof(RGB)*(width));

    }
printf("..have rgb..\n");

	/*for (i=0; i < height; i++){
		for(j=0;j < width;j++){
			if(area[i][j].red==255 && area[i][j].green==255 && area[i][j].blue==255){
			printf("here\n");
			floodFill(height,width, area, i, j);
			}
		}	
	}*/
size_t rgb=sizeof(RGB);
	for (i=0; i < height; i++){
		for(j=0;j < width;j++){
			if(raster[i][j*rgb]==255 && raster[i][j*rgb+1]==255 && raster[i][j*rgb+2]==255){
			printf("here\n");
			floodFill(height,width, raster, i, j);
			}
		}	
	}
return raster;
	printf("here\n");
    char** newraster = (char**)malloc(sizeof(RGB*)*(height)); 
    
    for ( i = 0; i <height; i++)
    {
        newraster[i] = (char*)malloc(sizeof(RGB)*(height));  
        memmove(newraster[i], (char*)area[i], sizeof(RGB)*(height));//y is a row, x is a column

    }

return newraster;
}

void NewBmp(char* input, char** raster, BMFileHeader* FileHeader, BMInfoHeader* InfoHeader)
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
        fwrite(raster[i], sizeof(char), pixel, output);
        for (j=0; j < alignment; j++) //to fill alignment junk with zeros
        fputc(0, output);
    }
    fclose(output);
}

int main()
{
    //int x0 = -1, x1 = -1, y0 = -1, y1 = -1;
    char* BmpName = (char*)malloc(sizeof(char)*100);
    printf("-Outline white with blue in BMP-\nName of the BMP file (do NOT include file extention .bmp):\n");
    fgets(BmpName,100,stdin);
//printf("..name=%s..",BmpName);
    *(strchr(BmpName,'\n')) = '\0';
//printf("..name=%s..",BmpName);
    strcat(BmpName,".bmp");
//printf("..name=%s..",BmpName);
	//printf("..name..");
    FILE* input = fopen(BmpName, "rb");
    if(input==NULL){
        printf("Error: no such file\n");
        return 0;
    }
	printf("..read bmp name complete..\n");
    BMFileHeader FileHeader;
    BMInfoHeader InfoHeader;

    char** buf = ReadBmp(input, &FileHeader, &InfoHeader);
    fclose(input);
    printf("..read bmp complete..\n");
    buf = whiteblue(buf, &FileHeader, &InfoHeader);
    printf("..whiteblue complete..\n");
    NewBmp(BmpName,buf, &FileHeader, &InfoHeader);
    
    printf("BMP file created: %s\n", BmpName);

    free(BmpName);

    for(int i=0; i < InfoHeader.height; i++){
        free(buf[i]);
    }

    free(buf);
    return 0;
}
