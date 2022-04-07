#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 10

/*
— la taille du nom de fichier, sur un octet,
— le nom du fichier, dans un emplacement de huit octets,
— la taille du fichier en octets, sur un octet,
— six indices de bloc de données, sur un octet chacun.
*/

typedef struct
{ // sur un octet chacun
    uint8_t block_1;
    uint8_t block_2;
    uint8_t block_3;
    uint8_t block_4;
    uint8_t block_5;
    uint8_t block_6;
} data_bloc_t;

typedef struct
{
    uint8_t filename_size;  // taille du fichier sur 8 bit
    char filename[8];       // nom du fichier
    uint8_t file_size;      // taille du fichier sur un octet
    data_bloc_t totalMarks; // indice de bloc de donnees
} inode_t;

void read_number_of_block(unsigned char *block_number, FILE *file)
{

    if (fread(&block_number, 1, 1, file) == 0)
    {
        printf("On n'a pas pu lire le nombre de blocs\n");
        exit(0);
    }
    printf("Read block : %s\n", block_number);
}

void read_number_of_inodes(unsigned char *inodes_number, FILE *file)
{
    if (fread(&inodes_number, 1, 1, file) == 0)
    {
        printf("On n'a pas pu lire le nombre d'inoeuds\n");
        exit(0);
    }
    printf("Read innode : %s\n", inodes_number);
}

void read_block_bitmap(unsigned char *table_block, unsigned char block_number, FILE *file)
{

    if (fread(table_block, sizeof(unsigned char), block_number / 8, file) < block_number / 8)
    {
        printf("On n'a pas pu lire le bitmap des blocs\n");
        exit(0);
    }
    printf("On a pu lire le bitmap des blocs et on affiche les valeurs entières\n");
    for (int i = 0; i < block_number / 8; i++)
    {
        printf("entre %d et %d bits : %d\n", i * 8, (i + 1) * 8 - 1, table_block[i]);
    }
    printf("On a fini d'afficher le bitmap des blocs\n\n");
}

void read_inode_bitmap(unsigned char *table_inode, unsigned char *table_block, unsigned char inodes_number, unsigned char block_number, FILE *file)
{

    if (fread(table_inode, sizeof(unsigned char), inodes_number / 8, file) < inodes_number / 8)
    {
        printf("On n'a pas pu lire le bitmap des inoeuds\n");
        exit(0);
    }

    printf("On a pu lire le bitmap des inoeuds et on affiche les valeurs entières\n");

    for (int i = 0; i < inodes_number / 8; i++)
    {
        printf("entre %d et %d bits : %d\n", i * 8, (i + 1) * 8 - 1, table_block[i]);
    }

    printf("On a fini d'afficher le bitmap des inoeuds\n\n");
}

void read_fs()
{
    char filename_to_read[13] = "correct-1.fs";
    unsigned char block_number, inodes_number; // unsigned char est codé sur 8bits.

    unsigned char *table_block;
    table_block = malloc(sizeof(unsigned char) * (block_number / 8));

    unsigned char *table_inode;
    table_inode = malloc(sizeof(unsigned char) * (inodes_number / 8));

    FILE *file;
    file = fopen(filename_to_read, "rb");

    printf("Reading file : %s\n", filename_to_read);

    read_number_of_block(&block_number, file);
    read_number_of_inodes(&inodes_number, file);
    read_block_bitmap(&table_block, inodes_number, file);
    read_inode_bitmap(&table_inode, &table_block, inodes_number, block_number, file);

    printf("Number of blocks :  %d\n", (unsigned int)block_number);
    printf("Nunber of inodes :  %d\n", (unsigned int)inodes_number);

    fclose(file);

    free(table_block);
    free(table_inode);
}

void save_fs()
{
    FILE *file;
    file = fopen("binaire", "wb"); // wb pour écriture binaire

    // TODO use struct and write on fs
    /*
    fwrite(&nb, sizeof(unsigned char), 1, file);
    fwrite(&ni, sizeof(unsigned char), 1, file);
    fwrite(tB, sizeof(unsigned char), nb / 8, file);
    fwrite(tI, sizeof(unsigned char), ni / 8, file);
     */

    fclose(file);
}

int main(int argc, char const *argv[])
{
    read_fs();
    return EXIT_SUCCESS;
}