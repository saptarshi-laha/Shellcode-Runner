#include<stdio.h>
#include<Windows.h>

#pragma warning(disable:4996)

int main(int argc, char** argv) {

	if (argc == 3) {

		if (strcmp(argv[1], "-b64") == 0) {
			    
			FILE* stream = fopen(argv[2], "r");

			if (!stream) {
				printf("Error Reading File - %s \n", argv[2]);
				return -1;
			}

			fseek(stream, 0, SEEK_END);
			size_t size = ftell(stream);
			unsigned char* buffer = (char*)calloc(size, 1);
			fseek(stream, 0, SEEK_SET);

			int i = 0;

			do {
				char c = fgetc(stream);
				if (feof(stream)) {
					break;
				}
				buffer[i] = c;
				i++;
			} while (1);

			fclose(stream);

		}
		else if (strcmp(argv[1], "-hex") == 0) {

			FILE* stream = fopen(argv[2], "r");

			if (!stream) {
				printf("Error Reading File - %s \n", argv[2]);
				return -1;
			}

			fseek(stream, 0, SEEK_END);
			size_t size = ftell(stream);
			unsigned char* buffer = (char*)calloc(size, 1);
			fseek(stream, 0, SEEK_SET);

			int i = 0;

			do {
				char c = fgetc(stream);
				if (feof(stream)) {
					break;
				}
				buffer[i] = c;
				i++;
			} while (1);

			fclose(stream);

		}
		else if (strcmp(argv[1], "-bin") == 0) {

			FILE* stream = fopen(argv[2], "r");

			if (!stream) {
				printf("Error Reading File - %s \n", argv[2]);
				return -1;
			}

			fseek(stream, 0, SEEK_END);
			size_t size = ftell(stream);

			if (size > 0) {

				unsigned char* buffer = (char*)calloc(size, 1);
				fseek(stream, 0, SEEK_SET);

				int i = 0;

				do {
					char c = fgetc(stream);
					if (feof(stream)) {
						break;
					}
					buffer[i] = c;
					i++;
				} while (1);

				fclose(stream);

				if (size % 8 == 0) {
					size_t dataSize = size / 8;
					unsigned char* executableBuffer = (char*)calloc(dataSize, 1);
					char binary[8];
					for (i = 0; i < size; i = i + 8) {
						binary[0] = buffer[i];
						binary[1] = buffer[i + 1];
						binary[2] = buffer[i + 2];
						binary[3] = buffer[i + 3];
						binary[4] = buffer[i + 4];
						binary[5] = buffer[i + 5];
						binary[6] = buffer[i + 6];
						buffer[7] = buffer[i + 7];

						executableBuffer[(i+8)/8] = strtol(binary, 0, 2);

					}

					free(buffer);

					//Common Windows functions.
					DebugBreak();
					//Use this before jump.

				}
				else {
					printf("Error Parsing Binary Data - Not A Multiple of 8\n");
					return -1;
				}

			}
			else {
				printf("Error - Empty File\n");
				return -1;
			}

		}
		else {
			printf("Operation Not Supported : %s\n", argv[1]);
			printf("Usage : shelldebugger.exe -[option] [filename.txt]\n");
			printf("Options - \n");
			printf("-b64 : Base64 Encoded String\n");
			printf("-hex : Hexadecimal String\n");
			printf("-bin : Binary String\n");
			return 0;
		}

	}
	else {
		printf("Usage : [executable_filename.exe] -[option] [filename.txt]\n");
		printf("Options - \n");
		printf("-b64 : Base64 Encoded String\n");
		printf("-hex : Hexadecimal String\n");
		printf("-bin : Binary String\n");
		return 0;
	}

}