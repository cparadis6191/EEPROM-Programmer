#include <stdio.h>
#include <errno.h>
#include <stdint.h>

#include "bin2h.h"


int main(int argc, char **argv) {
	int byte;

	FILE *bin;
	FILE *data_h;
	const char *data_h_name = "../data.h";


	// Make sure we only have one input file
	if (argc != 2) {
		perror("Please specify a file name...\n");
	}

	bin = fopen(argv[1], "r");
	if (bin == NULL) {
		perror("Error opening input file...\n");
		return errno;
	}

	data_h = fopen(data_h_name, "w");
	if (data_h == NULL) {
		perror("Error opening output file...\n");
		return errno;
	}


	// Printf off the header information
	fprintf(data_h, "#ifndef __DATA_H_\n");
	fprintf(data_h, "#define __DATA_H_\n");
	fprintf(data_h, "\n");
	fprintf(data_h, "#include <avr/pgmspace.h>\n");
	fprintf(data_h, "#include <stdint.h>\n");
	fprintf(data_h, "\n\n");
	fprintf(data_h, "// http://www.nongnu.org/avr-libc/user-manual/pgmspace.html\n");
	fprintf(data_h, "// Reference for writing data to program space flash\n");
	fprintf(data_h, "const uint8_t data[] PROGMEM = {\n");


// http://www.nongnu.org/avr-libc/user-manual/pgmspace.html
// Reference for writing data to program space flash


	while ((byte = fgetc(bin)) != EOF) {
		fprintf(data_h, "\t0x%x,\n", byte);
	}

	// Close the header information
	fprintf(data_h, "};\n");
	fprintf(data_h, "\n\n");
	fprintf(data_h, "#endif\n");


	fclose(bin);
	fclose(data_h);


	return 0;
}
