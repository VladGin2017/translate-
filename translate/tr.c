#include <stdio.h>
#include <stdlib.h>


int main(){

	FILE *in=fopen("text_rus.txt","r+"),*out=fopen("text_eng.txt","w+"),*dict=fopen("dictionary.txt","r");
	int i,j,f=0,down=0;
	int dict_size=0;
	char h[30];
	while(!feof(dict)){
		++dict_size;
		fscanf(dict,"%s - %s\n",h,h);
	}
	char **from = malloc( sizeof(char *) * (dict_size)),**to = malloc( sizeof(char *) * (dict_size));
	rewind(dict);
	for(i=0; i<dict_size; ++i){
		from[i] = malloc( sizeof(char) * 30);
		to[i] = malloc( sizeof(char) * 30);
		fscanf(dict,"%s - %s\n",from[i],to[i]);
	}
	fclose(dict);

	int in_size=-1;
	while(!feof(in)){
		++in_size;
		getc(in);
	}
	char *rus = malloc( sizeof(char) * in_size);
	rewind(in);

	for(i=0; i<in_size; ++i){
		rus[i]=getc(in);
	}	
	rus[in_size]='\0';
	fclose(in);
	char * word = malloc( sizeof(char) * 30);
	int b=0,m=0;	
	for(i=0; i<=in_size; ++i){
		if((rus[i]>='à'&&rus[i]<='ÿ')||(rus[i]>='À'&&rus[i]<='ß')){
			word[b++]=rus[i];
		}
		else{
			if(b){
				f=0;
				down=0;
				word[b]='\0';
				if (word[0]>='à'&&word[0]<='ÿ'){
					word[0]-=32;
					down=1;
				}
				for(m=0; m<dict_size; ++m){
					if(!strcmp(word,from[m])){
						if (down){
							to[m][0]+=32;
							fprintf(out,"%s",to[m]);
							to[m][0]-=32;
						}
						else{
							fprintf(out,"%s",to[m]);
						}
						f=1;
						break;
					}
				}
				if(!f){
					if (down){
						word[0]+=32;
					}
					fprintf(out,"%s",word);
				}
				b=0;
			}
			fprintf(out,"%c",rus[i]);
		}
	}

}
