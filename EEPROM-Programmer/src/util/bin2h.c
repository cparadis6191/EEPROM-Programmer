#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#include "bin2h.h"


int main(int argc, char **argv) {
	int byte;
	int byte_n = 0;
	int byte_hml;

	FILE *bin;
	FILE *data_h;
	const char *data_name = "../data.h";


	// Make sure we only have one input file
	if (argc != 3) {
		printf("Please specify a file name and opcode byte (321)\n");
		return 1;
	}

	byte_hml = strtol(argv[2], NULL, 10);
	if (byte_hml == 0L || byte_hml < 1 || byte_hml > 3) {
		printf("Opcode section must be 321 corresponding to hml\n");
		return 1;
	}

	// Open the input file
	bin = fopen(argv[1], "rb");
	if (bin == NULL) {
		perror("Error opening input file");
		return errno;
	}

	// Open the output file
	data_h = fopen(data_name, "w");
	if (data_h == NULL) {
		perror("Error opening output file");
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

	// Get and write bytes until we hit the end of the binary
	// Only write specified opcode byte
	while ((byte = fgetc(bin)) != EOF) {
		if (byte_n%3 == byte_hml - 1) { 
			fprintf(data_h, "\t0x%x,\n", byte);
		}
		byte_n++;
	}

	// Close the header information
	fprintf(data_h, "\t0x0\n");
	fprintf(data_h, "};\n");
	fprintf(data_h, "\n\n");
	fprintf(data_h, "#endif\n");


	fclose(bin);
	fclose(data_h);


	return 0;
}
