#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "asst2.h"
void tokensorter(struct wordsList list[]){
	int i = 0;
	while(i < 8){
                printf("%s\n", list[i].word);
                i++;
        }
	int j = 0;
	int x = 0;
	while(j < 8){
		while(x < 8){
			if(list[j].word != NULL && list[x].word == list[j].word){
				list[j].freq += list[x].freq;
				list[x].word = NULL;
				printf("%d\n", list[j].freq);
			}
			x++;
		}
		x = 0;
		j++;
	}
	i = 0;
	while( i < 8){
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
	struct wordsList list[8]; 
	while(status != 0){
		status = read(in, &buffer, 1);
		if(buffer == 32){
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
	i = 0;	
	tokensorter(list);

}

int main(int argc, const char* argv[]){
	const char *fpin;
	const char *fpout;
	fpin = argv[1];
	fpout = argv[2];
	tokenmaker(fpin);
	return 0;
}
