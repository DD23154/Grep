#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


bool isOutputFile(char* s) {
    bool b=false;
    if (strstr(s, ".out") != NULL) {
        b = !b;
    }
    return b;
}

bool isInputFile(char* s) {
    bool b=false;
    if (strstr(s, ".in") != NULL) {
        b = !b;
    }
    return b;
}

char* lowString(char* s) {
    int size = strlen(s);
    char* lowString = malloc(size * sizeof(char));

    int i=0;
    for (i = 0; i < size; i++) {
        lowString[i] = tolower(s[i]);
    }
    return lowString;
    free(lowString);
}

int main(int argc, char* argv[])
{
    char* keyword = NULL;
    char* outputFileName = "";
    FILE* outputFile;
    FILE* inputFile;
    int arg = 1;
    bool i = false;
    bool o = false;

    int opt_val;

    if (argc == 1) {
        fprintf(stderr,"ERROR %s. Not enough arguments. Please enter at least a keyword. \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    while ((opt_val = getopt(argc, argv, "o:i")) != -1) {
        switch (opt_val) {
        case 'i': i = true;
            arg++;
            keyword = argv[arg];
            keyword = lowString(keyword);
            break;
        case 'o':
            if (isOutputFile(optarg)) {
                o = true;
                outputFileName = optarg;
                arg = arg + 2;
                keyword = argv[arg];
            }
            else {
                fprintf(stderr,"ERROR %s. No output file name", argv[0]);
		exit(EXIT_FAILURE);
            }
            break;
        case '?': printf("Sans options");
            break;
        }
    }
    if (keyword == NULL && arg + 1 == argc) { /* if no arguments but a keyword */
        keyword = argv[argc - 1];
    }


    int max;
    max=1000;
    char* InputString = malloc(max * sizeof(char));
    if (arg == argc - 1) { //without input file take the string from stdin
        fgets(InputString, max, stdin);
    }
    char* originalInputString = InputString;
    if(i==true){
	InputString=lowString(InputString);
    }

    if (strstr(InputString, keyword) != NULL) { /*if the keyword is in the input string*/
        if (o == false) { //without output file
            fprintf(stdout, "%s", originalInputString);
        }
        else {
            outputFile = fopen(outputFileName, "w");
            fprintf(outputFile, "%s", originalInputString);
        }
    }

    //free(InputString);


    size_t size = 2000;
    if (argc > arg + 1) { //input file
	int j=0;
        for (j = arg + 1; j < argc; j++) { /*for each input file argument*/
            if(isInputFile(argv[j])) {
                inputFile = fopen(argv[j], "r");
		if(inputFile==NULL){
		    fprintf(stderr,"ERROR %s. fopen", argv[0]);
		    exit(EXIT_FAILURE);
		}

                char* line = NULL;
		while(getline(&line, &size, inputFile)!=-1){
		    if(i==true){
	                line=lowString(line);
    		    }
                    if (strstr(line, keyword) != NULL) {
                        if (o == false) { /*without output file argument*/
                            fprintf(stdout, "%s", line);
                        }
                        else {
                            outputFile = fopen(outputFileName, "w");
                            fprintf(outputFile, "%s", line);
                        }
		    }
                }
                free(line);
		fclose(inputFile);
            }
        }
    }
return 0;
}