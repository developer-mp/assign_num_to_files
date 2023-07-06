#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void assignNumbersToFiles(const char *sourceFolder, const char *destinationFolder)
{
    // Open the source folder
    DIR *dir = opendir(sourceFolder);
    if (dir == NULL)
    {
        printf("Error opening source folder\n");
        return;
    }

    // Create the destination folder
    if (mkdir(destinationFolder) != 0)
    {
        printf("Error creating destination folder\n");
        return;
    }

    // Read files from the source folder
    struct dirent *entry;
    int fileNumber = 1;
    while ((entry = readdir(dir)) != NULL)
    {
        char sourcePath[256];
        sprintf(sourcePath, "%s/%s", sourceFolder, entry->d_name);

        struct stat fileStat;
        if (stat(sourcePath, &fileStat) == 0 && S_ISREG(fileStat.st_mode))
        {
            char destinationPath[256];
            sprintf(destinationPath, "%s/%d. %s", destinationFolder, fileNumber, entry->d_name);

            // Copy the file
            FILE *sourceFile = fopen(sourcePath, "rb");
            FILE *destinationFile = fopen(destinationPath, "wb");

            if (sourceFile != NULL && destinationFile != NULL)
            {
                int ch;
                while ((ch = fgetc(sourceFile)) != EOF)
                {
                    fputc(ch, destinationFile);
                }

                printf("File %s copied successfully\n", entry->d_name);

                fclose(sourceFile);
                fclose(destinationFile);
            }

            fileNumber++;
        }
    }

    closedir(dir);
}

int main()
{
    char sourceFolder[256];
    char destinationFolder[256];

    printf("Enter source folder path: ");
    scanf("%s", sourceFolder);

    printf("Enter destination folder path: ");
    scanf("%s", destinationFolder);

    assignNumbersToFiles(sourceFolder, destinationFolder);

    return 0;
}
