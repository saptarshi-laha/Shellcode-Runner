#include<stdio.h>
#include<Windows.h>

#pragma warning(disable:4996)

typedef int shellcodeJump(void);

int main(int argc, char** argv) {

	if (argc == 3) {

		if (strcmp(argv[1], "-hex") == 0) {

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
				unsigned char c = fgetc(stream);
				if (feof(stream)) {
					break;
				}
				buffer[i] = c;
				i++;
			} while (1);

			fclose(stream);

			if (size % 2 == 0) {
				size_t dataSize = size / 2;
				unsigned char* executableBuffer = (char*)calloc(dataSize, 1);
				unsigned char hex[2];
				for (i = 0; i < size; i = i + 2) {
					hex[0] = buffer[i];
					hex[1] = buffer[i + 1];

					executableBuffer[((i + 2) / 2) - 1] = strtol(hex, 0, 16);

				}

				free(buffer);
				
				LPVOID execAddress = VirtualAllocEx(GetCurrentProcess(), NULL, dataSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
				if (execAddress != NULL) {
					size_t* bytesWritten = 0;
					if (WriteProcessMemory(GetCurrentProcess(), execAddress, executableBuffer, dataSize, bytesWritten)) {
						free(executableBuffer);

						while (!IsDebuggerPresent()) {
							PBOOL debuggerPresent = 0;
							CheckRemoteDebuggerPresent(GetCurrentProcess(), debuggerPresent);
							if (*debuggerPresent == TRUE) {
								break;
							}
							Sleep(100);
							printf("Attach Your Debugger Now If You Have Not Attached It!!!\n");
						}

						shellcodeJump* sJ = (shellcodeJump*)execAddress;
						DebugBreak();						
						int i = sJ();

						VirtualFree(execAddress, dataSize, MEM_RELEASE);

					}
					else {
						printf("Error Writing To Process Memory!\n");
						return -1;
					}
				}
				else {
					printf("Error Allocating RWX Memory!\n");
					return -1;
				}
			}
			else {
				printf("Error Parsing Hexadecimal Data - Not A Multiple of 2\n");
				return -1;
			}

		}
		else if (strcmp(argv[1], "-oct") == 0) {

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
				unsigned char c = fgetc(stream);
				if (feof(stream)) {
					break;
				}
				buffer[i] = c;
				i++;
			} while (1);

			fclose(stream);

			if (size % 3 == 0) {
				size_t dataSize = size / 3;
				unsigned char* executableBuffer = (char*)calloc(dataSize, 1);
				unsigned char oct[3];
				for (i = 0; i < size; i = i + 3) {
					oct[0] = buffer[i];
					oct[1] = buffer[i + 1];
					oct[2] = buffer[i + 2];

					executableBuffer[((i + 3) / 3) - 1] = strtol(oct, 0, 8);

				}

				free(buffer);

				LPVOID execAddress = VirtualAllocEx(GetCurrentProcess(), NULL, dataSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
				if (execAddress != NULL) {
					size_t* bytesWritten = 0;
					if (WriteProcessMemory(GetCurrentProcess(), execAddress, executableBuffer, dataSize, bytesWritten)) {
						free(executableBuffer);

						while (!IsDebuggerPresent()) {
							PBOOL debuggerPresent = 0;
							CheckRemoteDebuggerPresent(GetCurrentProcess(), debuggerPresent);
							if (*debuggerPresent == TRUE) {
								break;
							}
							printf("Attach Your Debugger Now If You Have Not Attached It!!!\n");
							Sleep(100);
						}

						shellcodeJump* sJ = (shellcodeJump*)execAddress;
						DebugBreak();
						int i = sJ();

						VirtualFree(execAddress, dataSize, MEM_RELEASE);

					}
					else {
						printf("Error Writing To Process Memory!\n");
						return -1;
					}
				}
				else {
					printf("Error Allocating RWX Memory!\n");
					return -1;
				}

			}
			else {
				printf("Error Parsing Octal Data - Not A Multiple of 3\n");
				return -1;
			}

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
					unsigned char c = fgetc(stream);
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
					unsigned char binary[8];
					for (i = 0; i < size; i = i + 8) {
						binary[0] = buffer[i];
						binary[1] = buffer[i + 1];
						binary[2] = buffer[i + 2];
						binary[3] = buffer[i + 3];
						binary[4] = buffer[i + 4];
						binary[5] = buffer[i + 5];
						binary[6] = buffer[i + 6];
						binary[7] = buffer[i + 7];

						executableBuffer[((i+8)/8)-1] = strtol(binary, 0, 2);

					}

					free(buffer);

					LPVOID execAddress = VirtualAllocEx(GetCurrentProcess(), NULL, dataSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
					if (execAddress != NULL) {
						size_t* bytesWritten = 0;
						if (WriteProcessMemory(GetCurrentProcess(), execAddress, executableBuffer, dataSize, bytesWritten)) {
							free(executableBuffer);

							while (!IsDebuggerPresent()) {
								PBOOL debuggerPresent = 0;
								CheckRemoteDebuggerPresent(GetCurrentProcess(), debuggerPresent);
								if (*debuggerPresent == TRUE) {
									break;
								}
								printf("Attach Your Debugger Now If You Have Not Attached It!!!\n");
								Sleep(100);
							}

							shellcodeJump* sJ = (shellcodeJump*)execAddress;
							DebugBreak();
							int i = sJ();

							VirtualFree(execAddress, dataSize, MEM_RELEASE);

						}
						else {
							printf("Error Writing To Process Memory!\n");
							return -1;
						}
					}
					else {
						printf("Error Allocating RWX Memory!\n");
						return -1;
					}

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
			printf("-hex : Hexadecimal String\n");
			printf("-oct : Octal String\n");
			printf("-bin : Binary String\n");
			return 0;
		}

	}
	else {
		printf("Usage : [executable_filename.exe] -[option] [filename.txt]\n");
		printf("Options - \n");
		printf("-hex : Hexadecimal String\n");
		printf("-oct : Octal String\n");
		printf("-bin : Binary String\n");
		return 0;
	}

}