#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "classroom.h"

// return if the data find successfully
bool read_classroom_by_row(struct _Classroom *classroom, int row) {
	// open file by route
	FILE* fp = fopen("./Classroom_data/classroom_filtted_data.csv", "r");
	
	// check if file be opened successfully
	if (!fp)    printf("Can't open the classroom file\n");
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
			if( fgets(buffer, 1024, fp) == NULL ) return false;
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
		fclose(fp);
		return true;
	}
	return false;
}

// return if the data find successfully
bool read_classroom_by_id(struct _Classroom *classroom, int id) {
	// open file by route
	FILE* fp = fopen("./Classroom_data/classroom_filtted_data.csv", "r");
	
	// check if file be opened successfully
	if (!fp)   printf("Can't open the classroom file\n");
	else
	{
		// to save a line of the file
		char buffer[1024];

		// to save a column returned by function
		char* value;

		// to save the pointer status
		int column = 0;

		// to check if data find successfully
		bool flag = false;

		// to find such the row
		while ( fgets(buffer, 1024, fp) != NULL )
		{
			value = strtok(buffer, ",");
			if( atoi(value) == id ){
				// printf("Find the data %d!\n", id);
				flag = true;
				classroom -> id = atoi(value);
				break;
			}
		}

		// do nothing if the data wasn't find
		if(!flag){
			printf("Cannot find the data %d!\n", id);
			fclose(fp);
			return false;
		}
		
		// read data column by column
		while (value)
		{
			
			switch (column) {

				case 0:
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
	
		fclose(fp);
		return true;	
	}
	return false;
}

// input a unmalloc pointer of _Classroom array to save data
// and input the expected capacity and type of classroom
// the last is the usage array[7*13] that tags time wanna use "true" or 1
// return the number of avaliable classrooms
int search_classroom(struct _Classroom **classroom_list,int type, int capacity, bool *usage){
    // save reading data temporary
	struct _Classroom classroom_buffer;
	// the number of the avaliable classrooms
    int avaliable_number = 0;
	// flag for the loop break once when unavaliable
    bool flag;
	// for for loop
    int i, j, k;

	// turn it as an array
    *classroom_list = malloc(sizeof(struct _Classroom) * CLASSROOM_MAX_NUMBER);

	// serch every line
    i = 1;
    while (read_classroom_by_row(&classroom_buffer, i) == true){
        flag = true;
		
		// check classroom type and capacity
		if (classroom_buffer.type != type ) flag = false;
		if (classroom_buffer.capacity >= capacity ) flag = false;

		// check the classroom usage
		if(flag){
			for (j = 0; j < 7; j++){
				for (k = 0; k < 13; k++){
					if (usage[j*7+k] == true){
						if (classroom_buffer.usage[j][k] == true){
							// if this classroom unavaliable then
							flag = false;
							break;
						}
					}
				}
				if(!flag) break;
			}
		}

		// flag = true means classroom avaliable
		// store it in the list and update the number indicator
        if (flag){
            (*classroom_list)[avaliable_number] = classroom_buffer;
            avaliable_number++;
        }
        i++;
    }

	// update the array size to save memory
    *classroom_list = realloc(*classroom_list, sizeof(struct _Classroom) * avaliable_number);
	return avaliable_number;
}

// return if the modify success
bool update_classroom_usage(struct _Classroom *classroom){
	int i, j; // for for loop

	// open file by route
	FILE* fp = fopen("./Classroom_data/classroom_filtted_data.csv", "r+");
	
	// check if file be opened successfully
	if (!fp)   printf("Can't open the classroom file\n");
	else
	{	
		// to save a line of the file
		char buffer[1024];

		// to save a column returned by function
		char* value;

		// to save the pointer status
		int column = 0;

		// to check if data find successfully
		bool flag = false;

		// to save the line where data in
		long long line_pos = -1;

		// to save length for the line to modifying
		size_t line_length;

		// to save length of new data for line length cut off
		int data_length;

		// to find such the row
		while ( fgets(buffer, 1024, fp) != NULL )
		{
			// record the line length included the '\n'
			line_length = strlen(buffer) + 1;
			value = strtok(buffer, ",");
			if( atoi(value) == classroom -> id ){
				// printf("Find the data %d!\n", atoi(value) );
				flag = true;
				line_pos = ftell(fp);

				// move the file pointer to the head of the current line
				// because fgets() will move the pointer to the last
				fseek(fp, line_pos - line_length, SEEK_SET);

				// put static data in the file
				// and calculate data_length at the same time
				data_length = fprintf(fp, "%06d,%s,%d,%s,%d",
									  classroom -> id,
									  classroom -> nickname,
									  classroom -> type,
									  classroom -> wholename,
									  classroom -> capacity     );
				
				// put the usage data via loop
				// calculate the data_length, too
				for (i = 0; i < 7; i++){
					for (j = 0; j < 13; j++){
						data_length += fprintf(fp, ",%d", 
						                       classroom -> usage[i][j]);
					}
				}
				data_length += fprintf(fp, "\n");

				// if the updating data sorter than orginal one:
				// fill the line with spaces to match the original line length
                for (int i = data_length; i < strlen(buffer); i++) {
                    fputc(' ', fp);
                }
				
				// move the pointer back to the last
				fseek(fp, line_pos, SEEK_SET);

				fclose(fp);
				return true;
			}
		}
	}

	fclose(fp);
	return false;
}

/*
int main() {	
	int i, j, k;
	struct _Classroom classroom;
	struct _Classroom classroom_table[10];
	// set the console to UTF-8 codec
	system("chcp 65001");
	
	read_classroom_by_row(&classroom, 120);
	printf("%d\t", classroom.id);
	printf("%d\t", classroom.type);
	printf("%s\t", classroom.wholename);
	printf("\n");
	for (j = 0; j < 7; j++)
	{
		for (k = 0; k < 13; k++)
		{
			// if(classroom.usage[j][k]) printf("1 ");
			// else                      printf("0 ");
			printf("%d ", classroom.usage[j][k]);
		}
	}

	printf("\n----------------------\n");

	for (i = 0; i < 10; i++){

		read_classroom_by_row(classroom_table+i, i+40);
		printf("%d\t", classroom_table[i].id);
		printf("%d\t", classroom_table[i].type);
		printf("%s\t", classroom_table[i].wholename);
		printf("\n");
		for (j = 0; j < 7; j++)
		{
			for (k = 0; k < 13; k++)
			{
				printf("%d ", classroom_table[i].usage[j][k]);
			}
		}
		
		printf("\n");

	}

	printf("\n----------------------\n");

	int id = 30211;
	printf("Search ID %d:\n", id);
	if( read_classroom_by_id(&classroom, id) ){
		printf("%d\t", classroom.id);
		printf("%d\t", classroom.type);
		printf("%s\t", classroom.wholename);
		printf("\n");
		for (j = 0; j < 7; j++)
		{
			for (k = 0; k < 13; k++)
			{
				// if(classroom.usage[j][k]) printf("1 ");
				// else                      printf("0 ");
				printf("%d ", classroom.usage[j][k]);
			}
		}
	}

	printf("\n----------------------\n");

	int x = 5, y = 7, v = 1;
	printf("Modify the %d usage data which %d class in the %d day to %d.\n", 
			classroom.id, y, x, v);

	classroom.usage[x-1][y-1] = v;
	update_classroom_usage(&classroom);

	printf("\n----------------------\n");

	bool search_usage[7*13] = {0};
	int length_ava_list;
	struct _Classroom *ava_list;
	search_usage[1*7+2] = 1;
	search_usage[1*7+3] = 1;
	search_usage[4*7+1] = 1;
	length_ava_list = search_classroom(&ava_list, 2, 55, search_usage);
	printf("There are %d avaliable for the usage\n", length_ava_list);
	
	for (i = 0; i < length_ava_list; i++){
		printf("%d\t", ava_list[i].id);
		printf("%s\t", ava_list[i].nickname);
		printf("\n");
	}

	free(ava_list);

	return 0;
}
*/
