#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "asst2.h"
//Got it to stop seg faulting. Problem is it cuts off the last word of the file for some reason
void tokensorter(struct wordsList list[]){
	int i = 0;

	while(i < wordcount){
		char* str = list[i].word;
		int j = i + 1;
		while(j < wordcount){
			char* str2  = list[j].word;
			if((list[i].word != NULL && list[j].word != NULL) && strcmp(str, str2) == 0){
				list[i].freq +=  list[j].freq;
				list[j].word = NULL;
				list[j].freq = NULL;
				j++;
			}
			else{
				j++;
			}
		}
		j = 0;
		i++;
	}
	i = 0;
	while( i < wordcount){
		if(list[i].word != NULL){
			printf("%s\n", list[i].word);
			printf("%d\n", list[i].freq);
		}
		i++;
	}
}

void tokenmaker(const char *fpin){
	int *in = open(fpin, O_RDONLY);
	int status = -1;
	int buffer = '\0';
	char temp[100];
	int lettercount = 0;
	int i = 0;
	struct wordsList list[wordcount + 2];
	while(status != 0){
		status = read(in, &buffer, 1);
		if(buffer == 32 || buffer == 9){
			list[i].word = malloc(lettercount);
			memcpy(list[i].word, temp, lettercount);
			list[i].freq = 1;
			lettercount = 0;
			i++;
		}
		if(buffer != 32){
			temp[lettercount] = buffer;
			lettercount++;
		}
	}
	close(in);
	tokensorter(list);

}

void wordcounter(const char *fpin){
	int *in = open (fpin, O_RDONLY);
	int status = -1;
	int buffer = '\0';
	while(status != 0){
		status = read( in, & buffer, 1);
			if(buffer == 32 || buffer == 9){
				wordcount++;
			}
	}
	close(in);
	printf("%d\n", wordcount);
}

int main(int argc, const char* argv[]){
	const char *fpin;
	const char *fpout;
	fpin = argv[1];
	fpout = argv[2];
	wordcounter(fpin);
	tokenmaker(fpin);
	return 0;
}
