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

int Check(FILE* input,int x0,int y0,int x1,int y1)
{
    if (x0 < 0 || y0 < 0 || x1 < 0 || y1 < 0 || x1 - x0 < 0 || y0-y1 < 0){ /*Coordinates are to be positive, area is to be positive*/
        printf("Error: invalid coordinates\n"); 
        fclose(input);
        return 0;
    }
return 1;
}


unsigned char** ReadBmp(FILE* input, BMFileHeader* FileHeader, BMInfoHeader* InfoHeader)
{   int i = 0, j = 0, k = 0;
    fseek(input,0,SEEK_END);//set pointer to the end of the file
    int BmpSize = ftell(input);//pointer value of current position in stream. For a binary stream, ammount of bytes from the beginning of the file is returned
    fseek(input,0,SEEK_SET);//set pointer to the beginning of the file

    unsigned char* buf = (char*)malloc(sizeof(char)*BmpSize); 
    
    fread(buf,sizeof(char),BmpSize,input);
    *FileHeader = *((BMFileHeader*)buf); //set FileHeader pointer to point to the beginning of the file
    buf += sizeof(BMFileHeader); //move buf pointer to the start of InfoHeader (after the end of FileHeader)
    *InfoHeader = *((BMInfoHeader*)buf); //set InfoHeader pointer to point to the beginning of BMInfoHeader structure
    buf -= sizeof(BMFileHeader); // move back to beginning of BMFileHeader structure
    buf += FileHeader -> boffset; // mobe buf pointer to point to the beginning of the picture raster (pixel info array)

    int len = 3*InfoHeader->width + (InfoHeader->width%4); /* 24 bits = 3 bytes + allignment 
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

unsigned char** Cut(unsigned char** raster, int x0, int y0, int x1, int y1,BMFileHeader* FileHeader, BMInfoHeader* InfoHeader)
{
    int i = 0, j = 0, k = 0, e = 0, w=0, N=100000;
    RGB* str = NULL;
    RGB** area = (RGB**)malloc(N); 
    
    for ( i = 0; i <=y0-y1; i++)
    {
        area[i] = (RGB*)malloc(N);  
        memmove(area[i], raster[y1+i]+x0*sizeof(RGB), sizeof(RGB)*(x1-x0+1));//y is a row, x is a column

    }
    
    for ( j = y1; j <= y0; j++) //restricting demanded area
    {
        str = (RGB*)raster[j];
        for( k = x0; k <=x1; k++)
        {
            str[k]=area[e][w++];      
        }
        e++;
    }

    int newwidth = x1-x0+1; // width in pixels
    int newheight = y0-y1+1;
    int newlength = newwidth*3+(x1-x0+1)%4; //width + allignment

    unsigned char** newraster = (unsigned char**)malloc(sizeof(RGB*)*(y0-y1+1)); 
    
    for ( i = 0; i <=y0-y1; i++)
    {
        newraster[i] = (unsigned char*)malloc(sizeof(RGB)*(x1-x0+1));  
        memmove(newraster[i], (unsigned char*)area[i], sizeof(RGB)*(x1-x0+1));//y is a row, x is a column

    }

    InfoHeader->sizelmage = newheight*newlength;
    InfoHeader->width = newwidth;
    InfoHeader->height = newheight;

return newraster;
}


void invert(unsigned char** raster, int height, int width, size_t rgb){
	for(int i=0; i<height;i++){
for(int j=0;j<width;j++){
	raster[i][j*rgb]=~raster[i][j*rgb];
raster[i][j*rgb+1]=~raster[i][j*rgb+1];
raster[i][j*rgb+2]=~raster[i][j*rgb+2];
}
		
}	
}

void NewBmp(char* input, unsigned char** raster, BMFileHeader* FileHeader, BMInfoHeader* InfoHeader)
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
    printf("-Cut a BMP -\nName of the BMP file (do NOT include file extention .bmp):\n");
    fgets(BmpName,100,stdin);
    *(strchr(BmpName,'\n')) = '\0';
    strcat(BmpName,".bmp");
    FILE* input = fopen(BmpName, "rb");
    if(input==NULL){
        printf("Error: no such file\n");
        return 0;
    }

    printf("Mind that coordinate origin is in the bottom left of the picture!\nSquare brackets mean input mask.\nDo NOT include them.\nTop left coordinates [x0 y0]:\n");
    scanf("%d %d", &x0, &y0);
    printf("Bottom right coordinates [x1 y1]:\n");
    scanf("%d %d", &x1, &y1);


    if (Check(input, x0,y0,x1,y1) == 0)
    {
        printf("The area isn't correctly defined: invalid coordinates\n");
        free(BmpName);
        return 0;
    }

    BMFileHeader FileHeader;
    BMInfoHeader InfoHeader;

    unsigned char** buf = ReadBmp(input, &FileHeader, &InfoHeader);
    fclose(input);
    if (InfoHeader.width < x1+1 || InfoHeader.height < y0+1)
    {
        printf("The area isn't correctly defined: larger than possible\n");
        free(BmpName);
        return 0;
    }
    
    buf = Cut(buf, x0, y0,x1,y1, &FileHeader, &InfoHeader);
size_t rgb=sizeof(RGB);
invert(buf, InfoHeader.height, InfoHeader.width, rgb);
    
    NewBmp(BmpName,buf, &FileHeader, &InfoHeader);
    
    printf("Cut BMP file created: %s\n", BmpName);

    free(BmpName);

    for(int i=0; i < InfoHeader.height; i++){
        free(buf[i]);
    }

    free(buf);
    return 0;
}
