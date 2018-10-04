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

int Check(FILE* input,int x0,int y0,int x1,int y1)
{
    if (x0 < 0 || y0 < 0 || x1 < 0 || y1 < 0 || x1 - x0 < 0 || y0-y1 < 0){ /*Coordinates are to be positive, area is to be positive*/
        printf("Error: invalid coordinates\n"); 
        fclose(input);
        return 0;
    }
    if ((x1 - x0) != (y0 - y1)) //if the area isn't square
    {
        printf("The area isn't square\n");
        fclose(input);
        return 0;
    }
    return 1;
}


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

char** Cut(char** raster, int x0, int y0, int x1, int y1,BMFileHeader* FileHeader, BMInfoHeader* InfoHeader)
{
    int i = 0, j = 0, k = 0, e = 0, w=0;
    RGB* str = NULL;
    //int i = 0, j = 0, k = 0;
    RGB** area = (RGB**)malloc(sizeof(RGB*)*(y0-y1+1)); 
    
    for ( i = 0; i <=y0-y1; i++)
    {
        area[i] = (RGB*)malloc(sizeof(RGB)*(x1-x0+1));  
        memmove(area[i], raster[y1+i]+x0*sizeof(RGB), sizeof(RGB)*(x1-x0+1));//y is a row, x is a column

    }
    printf("..setting RGB..\n");
    for ( j = y1; j <= y0; j++) //restricting demanded area
    {
        str = (RGB*)raster[j];
        for( k = x0; k <=x1; k++)
        {
            str[k]=area[e][w++];      
        }
        e++;
    }
    //free(area);
    printf("..RGB set complete..\n");
    int newwidth = x1-x0+1; // width in pixels
    int newheight = y0-y1+1;
    int newlength = newwidth*3+(x1-x0+1)%4; //width + allignment
/*
    //ATTEMPT TO CREATE NEW RASTER

    char** newraster = (char**)malloc(sizeof(char*)*newheight);
    for(i=0; i < newheight; i++)
    {
        newraster[i] = (char*)malloc(sizeof(char)*newlength);//fill raster with picture info, like an array of strings
        for(j=0; j < newwidth; j++){
        newraster[i][j] = raster[y1][x0++];
        }
        for(k=0;k<newwidth%4;k++){
            newraster[i][j++] = 0;
        }
        y1++;
    }*/

//printf("%d\n", newheight*newlength);


//NEW ATTEMPT

    char** ar = (char**)malloc(sizeof(RGB*)*(y0-y1+1)); 
    
    for ( i = 0; i <=y0-y1; i++)
    {
        ar[i] = (char*)malloc(sizeof(RGB)*(x1-x0+1));  
        memmove(ar[i], (char*)area[i], sizeof(RGB)*(x1-x0+1));//y is a row, x is a column

    }

//END OF NEW ATTEMPT

    InfoHeader->sizelmage = newheight*newlength;
    InfoHeader->width = newwidth;
    InfoHeader->height = newheight;

return ar;
    //return newraster;
}

void NewBmp(char* input, char** raster, BMFileHeader* FileHeader, BMInfoHeader* InfoHeader)
{   
    int i,j ;
    *(strchr(input, '.')) = '\0';
    strcat(input, "_cut.bmp");

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
    int x0 = -1, x1 = -1, y0 = -1, y1 = -1;
    char* BmpName = (char*)malloc(sizeof(char)*100);
    printf("Name of the BMP file:\n");
    fgets(BmpName,100,stdin);
    *(strchr(BmpName,'\n')) = '\0';
    strcat(BmpName,".bmp");
    FILE* input = fopen(BmpName, "rb");
    if(input==NULL){
        printf("Error: no such file\n");
        return 0;
    }

    printf("Top left coordinates [x0 y0]:\n");
    scanf("%d %d", &x0, &y0);
    printf("Bottom right coordinates [x1 y1]:\n");
    scanf("%d %d", &x1, &y1);


    if (Check(input, x0,y0,x1,y1) == 0)
    {
        printf("The area isn't correctly defined: invalid coordinates\n");
        free(BmpName);
        return 0;
    }

    printf("..checking file complete..\n");

    BMFileHeader FileHeader;
    BMInfoHeader InfoHeader;//&&&&&&&&

    char** buf = ReadBmp(input, &FileHeader, &InfoHeader);//&&&
    printf("..BMP read complete..\n");
    fclose(input);
    if (InfoHeader.width < x1+1 || InfoHeader.height < y0+1)
    {
        printf("The area isn't correctly defined: larger than possible\n");
        free(BmpName);
        return 0;
    }
    printf("..the area is defined correctly..\n");
    buf = Cut(buf, x0, y0,x1,y1, &FileHeader, &InfoHeader);
    printf("..cut function complete..\n");
    NewBmp(BmpName,buf, &FileHeader, &InfoHeader);
    printf("..creating NewBmp complete..\n");
    printf("Created cut BMP file: %s\n", BmpName);

    free(BmpName);

    for(int i=0; i < InfoHeader.height; i++){
        free(buf[i]);
    }

    free(buf);
    return 0;
}