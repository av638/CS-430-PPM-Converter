#include <stdio.h>
#include <stdlib.h>

int pSixtoPThree(char* inputFile)
{
    FILE *source, *destination;
    int height, width, depth,i;
    long length;
    unsigned char red, green, blue;
    char *buffer;

    source = fopen (inputFile, "rb");

    if(source == NULL)
    {
        fprintf(stderr, "File cannot be opened!");
        return -1;
    }


    fseek( source , 0L , SEEK_END);
    length = ftell( source );
    rewind( source );

    /* allocate memory for entire content */
    buffer = calloc( 1, length+1 );
    if( !buffer )
    {
      fclose(source);
      fprintf(stderr,"memory alloc fails");
      return 1;
    }

    /* copy the image into the buffer */
    if( 1!=fread( buffer , length, 1 , source) )
    {
        fclose(source);
        free(buffer);
        fprintf(stderr,"entire read fails");
        return 1;
    }

    for( i = 0; i < 50; i++)
    {
         printf("\nbuffer[%d] == %c", i, buffer[i]);
    }
    //printf("buffer = %s\n", buffer);

    /* Mess with the buffer to convert the P6 to P3 format */

    fclose(source);
    free(buffer);
    printf("\nConversion Finished");
    return 0;
}

int main(int argc, char *argv[])
{
    if (argv[1] = 6)
    {
        printf("Converting starting...");
        pSixtoPThree(argv[2]);
    }

    //printf("\nConverting complete...\n");
    return 0;
}
