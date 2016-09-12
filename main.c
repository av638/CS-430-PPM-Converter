#include <stdio.h>
#include <stdlib.h>
typedef struct Pixmap // This will serve as my buffer
{
    int width, height, magicNumber;

    unsigned char *image;

} Pixmap;



int ppmConverter(char *inputFile, char *outputFile, int desiredFormat)
{
    FILE *source;
    int magicNumber;
    char c;
    int width, height, maxColor;
    int i, j, size, totalItemsRead;

    //Create a buffer for the pixmap image
    Pixmap *buffer = (Pixmap *)malloc(sizeof(Pixmap));

    source = fopen (inputFile, "r");
    if(source == NULL)
    {
        fprintf(stderr, "File cannot be opened & or does not Exist!");
        exit(-1);
    }

    fscanf(source, "P%c\n", &c);
    magicNumber = c -'0';
    //printf("%c", c);
    if (c == 6 || c == 3) //if not in either p6 or p3 format then exit
    {
        fprintf(stderr, "This is not in the correct ppm format!");
        exit(-1);
    }

    c = getc(source);

    //skip the comments since they do not matter
    while(c =='#')
    {
        do
        {
            c = getc(source);
        }
        while(c!='\n'); //read to the end of the line
        c =getc(source);
    }
    // double checks to make sure if there is a digit in c
    if(!isdigit(c))
    {
        fprintf(stderr,"can't read header information from PPM format");
    }

    // get it ready to read in the width, height, max color
    ungetc(c, source);

    // read in the width, height. and max color value
    fscanf(source, "%d %d %d\n", &width, &height, &maxColor);
    //printf("%d", width);

    if(maxColor >= 65336 || maxColor <= 0){
        fprintf(stderr,"image is not true color(8byte), read failed");
        exit(-1);
    }
    // mult the size by three to account for rgb
    size = width * height * 3;
    //Pixmap *buffer = (Pixmap *)malloc(sizeof(Pixmap));

    // Put everything necessary into the buffer to be used to write it out into a different or even same format.
    // Except for the data because we just want to make sure that we allocate enough memory first.
    if(!buffer)
    {
        fprintf(stderr, "Cannot allocate memory for the ppm image.");
        exit(-1);
    }
    else{
        buffer->width = width;
        buffer->height = height;
        buffer->magicNumber = magicNumber;
        // Allocate memory for the entire image and mult by three to account for RGB
        buffer->image = (unsigned char *)malloc(width*height*3);
    }

    if(!buffer->image){
        perror("Cannot allocate memory for the ppm image.");
    }
    //printf("\nBuffer successfully created with all stuff!\n");
    // Read the image into the buffer depending on whether it is in P6 or P3 format
    // If its raw bits
    if(magicNumber == 6)
    {   // Read from the file the entire size of the image at a One Byte size into the buffer
        totalItemsRead = fread((void *) buffer->image, 1, (size_t) size, source);
        if (totalItemsRead != size)
        {
            fprintf(stderr,"cannot read image data from file \n");
            exit(-1);
        }

    }
    // If its in ascii
    else if(magicNumber == 3)
    { int pixel;
        for(i=0;i<height;i++)
        {
            for(j=0;j<width;j++)
            {

                fscanf(source, "%d ", &pixel);
                //printf("Working on p3");

                buffer->image[i*width*3+3*j] = pixel;

                fscanf(source, "%d ", &pixel);
                buffer->image[i*width*3+3*j+1] = pixel;

                fscanf(source, "%d ", &pixel);
                buffer->image[i*width*3+3*j+2] = pixel;

            }
        }
    }

    fclose(source);
    printf("\nImage has been completely read!");
    pThreeORpSixOut(buffer, outputFile, size, desiredFormat);
    free(buffer);
    printf("\nImage has been Converted!");
    return 0;
}

void pThreeORpSixOut(Pixmap *buffer, char *outputFileName, int size, int desiredFormat)
{
    int i, j, numPix;
    char comment[] = {"#This was converted by Alejandro Varela"};
    //printf("%s", comment);

    FILE *destination = fopen(outputFileName, "w");
    if (!destination)
    {
        fprintf(stderr,"\nFile already Exist!!!");
    }
    else
    {
        fprintf(destination, "P%d\n%s\n%d %d\n%d\n", desiredFormat, comment, buffer->width, buffer->height, 255);
        //p4-p7
        if(desiredFormat == 6)
        {
            numPix = fwrite((void *) buffer->image, 1, (size_t) size, destination);
        }
        else if(desiredFormat == 3)
        {   printf("doing stuff!");
            for(i=0;i<buffer->height;i++)
            {
                for(j=0;j<buffer->width;j++)
                {
                     fprintf(destination, "%d ",buffer->image[i*buffer->width*3+3*j]);
                     fprintf(destination, "%d ",buffer->image[i*buffer->width*3+3*j+1]);
                     fprintf(destination, "%d ",buffer->image[i*buffer->width*3+3*j+2]);
                }

                 fprintf(destination, "\n");
            }
        }
    fclose(destination);
    }
    return 0;
}


int main(int argc, char *argv[])
{
    int ppmFormat = atoi(argv[1]);

    printf("Converting starting...");
    ppmConverter(argv[2], argv[3], ppmFormat);

    return 0;
}
