#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>

int fatal(const char* message){
	write(2, message, strlen(message));
	write(2, "\x0a", 1);
	return -1;
}

void tell(char* msg, char* var){
	if (!var) { printf("af2h: %s\n", msg) ; return; }
	printf("af2h: %s %s\n", msg, var);
}

unsigned char* hexify(unsigned char* byte){
	static unsigned char hexcode[3];
	memset(hexcode, 0x00, 3);
	sprintf(hexcode, "%02x", *byte);
	return hexcode;
}

int main(int argc, char** argv){
	int fd, hfd;
	struct stat dll_stat;

	char opt;
	char *input, *output;
	
	const char*  headers       = "#include <stddef.h>\n";
	const char*  array_start   = "char *dll = \"" ;
	const char*  array_end     = "\";";

	const size_t array_st_size = strlen(array_start);
	const size_t array_ed_size = strlen(array_end);


	const char*  array_size_start = "size_t dll_size = "; 
	const char*  array_size_end   = ";";

	char dll_size[16];
	bzero(dll_size, 16);
	
	if (argc < 4){
		return fatal("Usage: af2h -f inputFile -o outputFile.h");
	}

	while ((opt = getopt(argc, argv, "f:o:")) != -1){
		switch(opt){
			case 'o':
				output = optarg;
				break;
			case 'f':
				input  = optarg;
				break;
			default:
				return fatal("Usage: af2h -f example.dll -o example.h");
		}
	}
	

	if ( (fd = open(input, O_RDONLY)) == -1){
		return fatal("FATAL: Error While Opening Input File, Do You Have Enough Permissions? ");
	};
	
	tell("Calling fstat(fd, &dll_stat)  [...]", NULL);

	fstat(fd, &dll_stat);

	sprintf(dll_size, "%li", dll_stat.st_size);

	unsigned char* dll = (unsigned char*) malloc(dll_stat.st_size);

	if (dll == NULL){
		return fatal("Error Allocating Required Memory");
	}

	tell("Loading Selected File To Heap [...]", NULL);
	if (read(fd, dll, dll_stat.st_size) == -1)
		return fatal("Error Reading Input File, Do You Have Enough Permissions?");

	tell("Generating Header File Data   [...]", NULL);

	hfd=open(output, O_CREAT | O_RDWR, S_IREAD | S_IWRITE);

	if (hfd == -1) return fatal("Error While Creating A Header File, Do You Have Enough Permissions? ");

	tell("Adding Required Header Files  [...]" ,NULL);

	write(hfd, headers, strlen(headers));

	tell("Converting And Writing Data   [...]", NULL);
	
	write(hfd, array_start, array_st_size);
	for (int i=0; i < dll_stat.st_size; i++){
		write(hfd, "\\x", 2);
		write(hfd, hexify(dll+i), 2);
	}
	write(hfd, array_end, array_ed_size);

	tell("Writing Converted File Size   [...]", NULL);

	write(hfd, array_size_start, strlen(array_size_start));
	write(hfd, dll_size, strlen(dll_size));
	write(hfd, array_size_end, 1);
	
	tell("Freeing Allocated Resources   [...]", NULL);

	close(fd);
	close(hfd);
	free(dll);

	tell("Success, Returning From Main  [...]", NULL);
	
	return 0;
}
