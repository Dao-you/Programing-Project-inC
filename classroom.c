#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "classroom.h"

void raad_classroom_by_row(struct _Classroom *classroom, int row) {
	// open file by route
	FILE* fp = fopen("./Classroom_data/classroom_filtted_data.csv", "r");
	
	// check if file be opened successfully
	if (!fp)    printf("Can't open file\n");
	else
	{
		// to save a line of the file
		char buffer[1024];

		// to save the pointer status
		int now = 0;
		int column = 0;

		// to find such the row
		while (now < row+1)
		{
			now++;
			fgets(buffer, 1024, fp);
		}

		// splitting the data
		char* value = strtok(buffer, ",");
		
		// read data column by column
		while (value)
		{
			
			switch (column) {

				case 0:
					classroom -> id = atoi(value);
					break;
				
				case 1:
					strcpy(classroom -> nickname, value);
					break;
				
				case 2:
					classroom -> type = atoi(value);
					break;

				case 3:
					strcpy(classroom -> wholename, value);
					break;
				
				case 4:
					classroom -> capacity = atoi(value);
					break;

				default:
					classroom -> usage[(column-5)/13][(column-5)%13] = atoi(value);
					break;

			}

			value = strtok(NULL, ",");
			column++;
		}
	}
	
	fclose(fp);
	return;	
}

// int main() {	
// 	int i, j, k;
// 	struct _Classroom classroom;
// 	struct _Classroom classroom_table[10];
// 	// set the console to UTF-8 codec
// 	system("chcp 65001");
	
// 	raad_classroom_by_row(&classroom, 0+40);
// 	printf("%d\t", classroom.id);
// 	printf("%d\t", classroom.type);
// 	printf("%s\t", classroom.wholename);
// 	printf("\n");
// 	for (j = 0; j < 7; j++)
// 	{
// 		for (k = 0; k < 13; k++)
// 		{
// 			// if(classroom.usage[j][k]) printf("1 ");
// 			// else                      printf("0 ");
// 			printf("%d ", classroom.usage[j][k]);
// 		}
// 	}

// 	printf("\n----------------------\n");

// 	for (i = 0; i < 10; i++){

// 		raad_classroom_by_row(classroom_table+i, i+40);
// 		printf("%d\t", classroom_table[i].id);
// 		printf("%d\t", classroom_table[i].type);
// 		printf("%s\t", classroom_table[i].wholename);
// 		printf("\n");
// 		for (j = 0; j < 7; j++)
// 		{
// 			for (k = 0; k < 13; k++)
// 			{
// 				printf("%d ", classroom_table[i].usage[j][k]);
// 			}
// 		}
		
// 		printf("\n");

// 	}

// }
