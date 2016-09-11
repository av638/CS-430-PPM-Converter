#include <stdio.h>
#include <stdlib.h>
typedef struct Pixmap // This will serve as my buffer
{
    unsigned char r, g, b;

} Pixmap;
    Pixmap *pixmapSix;

int pSixtoPThree(char* inputFile, char* outputFile)
{
    FILE *source, *destination;
    char magicNumber[3];
        unsigned char r, g, b;

    int width, height, depth;
    int i, j, counter;

    source = fopen (inputFile, "rb");
    destination = fopen("output.ppm", "w+");

    if(source == NULL)
    {
        fprintf(stderr, "File cannot be opened!");
        return -1;
    }


    fscanf(source, "%s", magicNumber);
    if (strcmp(magicNumber, "P6") != 0)
    {
        fprintf(stderr, "This is not in the correct P6 format!");
        return -1;
    }

    fscanf(src, "\n%d %d\n%d\n", &width, &height, &depth);
    //pixmapSix = malloc(sizeof(Pixmap)* width * height);


    fprintf(destination, "P3\n");
    fprintf(destination, "#P3 converted from P6\n");
    fprintf(destination, "%d %d\n%d\n", width, height, depth);

    for (i = 0; i < width*height; i++)
    {

        for (j = 0;  j < 3; j++)
        {
            fread(&r, 1, 1, source);
            fread(&g, 1, 1, source);
            fread(&b, 1, 1, source);
        }

        for (j = 0;  j < 3; j++)
            fprintf(destination, "%d %d %d ", r, g, b);

        if (counter == width)
        {
            fprintf(destination, "\n");
            counter = 1;
        }

        else
            counter++;
    }


   /* Mess with the buffer to convert the P6 to P3 format */

    fclose(source);
    fclose(destination);
    printf("\nConversion Finished");
    return 0;
}

int main(int argc, char *argv[])
{
    if (argv[1] = 6)
    {
        printf("Converting starting...");
        pSixtoPThree(argv[2], argv[3]);
    }

    //printf("\nConverting complete...\n");
    return 0;
}
