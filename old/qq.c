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



char** ReadBmp(FILE* input, BMFileHeader* FileHeader, BMInfoHeader* InfoHeader)
{   int i = 0, j = 0, k = 0;
    fseek(input,0,SEEK_END);//set pointer to the end of the file
    int BmpSize = ftell(input);//pointer value of current position in stream. For a binary stream, ammount of bytes from the beginning of the file is returned
    fseek(input,0,SEEK_SET);//set pointer to the beginning of the file

    char* buf = (char*)malloc(sizeof(char)*BmpSize); 
    
    fread(buf,sizeof(char),BmpSize,input);
    *FileHeader = *((BMFileHeader*)buf); //set FileHeader pointer to point to the beginning of the file
    buf += sizeof(BMFileHeader); //move buf pointer to the start of InfoHeader (after the end of FileHeader)
    *InfoHeader = *((BMInfoHeader*)buf); //set InfoHeader pointer to point to the beginning of BMInfoHeader structure
    buf -= sizeof(BMFileHeader); // move back to beginning of BMFileHeader structure
    buf += FileHeader -> boffset; // mobe buf pointer to point to the beginning of the picture raster (pixel info array)

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

char*** Cut(char** raster,BMFileHeader* FileHeader, BMInfoHeader* InfoHeader)
{
    int  N=100000, i = 0, j = 0,  k = 0, e = 0, w=0, x=0;

    RGB** area = (RGB**)malloc(N); 
    
        
    int oldwidth = InfoHeader->width;
    int oldheight = InfoHeader->height;

    int newwidth = oldwidth; // width in pixels
    int newheight = oldheight/2;
    int newlength = newwidth*3+(newwidth)%4; //width + allignment
//printf("in CUT 1\n");
    for ( i = 0; i < oldheight; i++)
    {
        area[i] = (RGB*)malloc(N);  //printf("[%d] i=%d \n",oldwidth, i );
        memmove(area[i], raster[i], sizeof(RGB)*(oldwidth));//y is a row, x is a column
        //x++;

    }
//printf("in CUT 2\n");
    char** newraster1 = (char**)malloc(N); 
    for ( i = 0; i <newheight; i++)
    {
        newraster1[i] = (char*)malloc(N); 
        memmove(newraster1[i], (char*)area[i], sizeof(RGB)*(newwidth));//y is a row, x is a column

    }
//printf("in CUT 3\n");
    char** newraster2 = (char**)malloc(N); 
    
    for ( i = newheight; i <oldheight; i++)
    {
        newraster2[x] = (char*)malloc(N);  
        memmove(newraster2[x], (char*)area[i], sizeof(RGB)*(newwidth));//y is a row, x is a column
        x++;
}

    char*** newraster= (char***)malloc(sizeof(newraster1)+sizeof(newraster2));
    newraster[0]=newraster1;
    newraster[1]=newraster2;

    InfoHeader->sizelmage = newheight*newlength;
    InfoHeader->width = newwidth;
    InfoHeader->height = newheight;

return newraster;
}

void NewBmp(char* input, char*** rasters, BMFileHeader* FileHeader, BMInfoHeader* InfoHeader)
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
        fwrite(rasters[0][i], sizeof(char), pixel, output);
        for (j=0; j < alignment; j++) //to fill alignment junk with zeros
        fputc(0, output);
    }
    fclose(output);



    *(strchr(input, '_')) = '\0';
    strcat(input, "_2.bmp");
    //printf("he\n");

    output = fopen(input,"wb");
    fwrite(FileHeader,sizeof(BMFileHeader), 1, output); //set FileHeader
    fwrite(InfoHeader,sizeof(BMInfoHeader),1, output); //set InfoHeader
    //pixel = 3*InfoHeader->width; // pixel size
    //alignment = InfoHeader->width%4; //allignment size
    //printf("%s\n", rasters[1][1]);
    //printf("before cycle\n");
    for(i=0; i < InfoHeader->height; i++)
    {
        //printf("[%d] i=%d\n", InfoHeader->height, i);
        fwrite(rasters[1][i], sizeof(char), pixel, output);
        for (j=0; j < alignment; j++) //to fill alignment junk with zeros
        fputc(0, output);
    }
    fclose(output);
}

int main()
{
    
    char* BmpName = (char*)malloc(sizeof(char)*100);
    printf("-Cut a BMP -\nName of the BMP file (do NOT include file extention .bmp):\n");
    fgets(BmpName,100,stdin);
    *(strchr(BmpName,'\n')) = '\0';
    strcat(BmpName,".bmp");
    FILE* input = fopen(BmpName, "rb");
    if(input==NULL){
        printf("Error: no such file\n");
        return 0;
    }


    BMFileHeader FileHeader;
    BMInfoHeader InfoHeader;

    char** buf = ReadBmp(input, &FileHeader, &InfoHeader);
    fclose(input);
//printf("readbmp done\n");
    char*** buf2 = (char***)malloc(100000);
    //printf("qq\n");
    buf2 = Cut(buf, &FileHeader, &InfoHeader);

    NewBmp(BmpName,buf2, &FileHeader, &InfoHeader);
    
    printf("Cut BMP files created\n");

    free(BmpName);

    for(int i=0; i < InfoHeader.height; i++){
        free(buf[i]);
    }

    free(buf);
    free(buf2);
    return 0;
}