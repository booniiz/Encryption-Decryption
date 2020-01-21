// Boon Chantachaimongkon
// bchantac

#include "morsecode.h"
#include "hw2.h"

char* MorseCode[] = {MorseExclamation, MorseDblQoute, MorseHashtag, Morse$, MorsePercent, MorseAmp, MorseSglQoute, MorseOParen, MorseCParen, MorseStar, MorsePlus, MorseComma, MorseDash, MorsePeriod, MorseFSlash, Morse0, Morse1, Morse2, Morse3, Morse4, Morse5, Morse6, Morse7, Morse8, Morse9, MorseColon, MorseSemiColon, MorseLT, MorseEQ, MorseGT, MorseQuestion, MorseAt, MorseA, MorseB, MorseC, MorseD, MorseE, MorseF, MorseG, MorseH, MorseI, MorseJ, MorseK, MorseL, MorseM, MorseN, MorseO, MorseP, MorseQ, MorseR, MorseS, MorseT, MorseU, MorseV, MorseW, MorseX, MorseY, MorseZ};

/* Part 1 Functions */
int toMorse(FILE *instream, char **mcmsg_ptr){
	
	int sizeOfInput=256,i=0,j=0,k=0;
	char *temp,*m,c;
	temp = (char*)malloc(sizeOfInput);

	while((c = fgetc(instream)) != EOF)
	{
		k= (int)c;
		if(k >= 97 && k <= 122)
		{
			k=k-32;
		}
		if(k >= 32 && k <= 90)
		{
			k= k - 33;
			if(k>=0)
			{
				m = *(MorseCode+k);
				while(*(m+j) != '\0')
				{
					*(temp+i) = *(m+j);
					j++;
					i++;//current
					if(i>sizeOfInput)
					{
						sizeOfInput += 100;
						temp = (char*)realloc(temp,sizeOfInput);
					}
       				}		
		*(temp+i) = 'x';
				i++;
				if(i>sizeOfInput)
					{
						sizeOfInput += 100;
						temp = (char*)realloc(temp,sizeOfInput);
					}

				j=0;
			}
			else if(k ==-1)
			{
				if(*(temp+i-2) != 'x')
				{
				*(temp+(i-1)) = 'x';
				*(temp+i) = 'x';
				i++;
				if(i>sizeOfInput)
					{
						sizeOfInput += 100;
						temp = (char*)realloc(temp,sizeOfInput);
					}
				}
			}
		}
	}

	if(i>0)
	{
		if(*(temp+i-2) != 'x')
		{
		*(temp+(i-1)) = 'x';
		*(temp+i) = 'x';
		i++;
		if(i>sizeOfInput)
		{
			sizeOfInput += 100;
			temp = (char*)realloc(temp,sizeOfInput);
		}
		}
	}
	else
	{
			*(temp+i) = 'x';
			i++;
			*(temp+i) = 'x';
			i++;
	}	
	*(temp+i) = '\0';
		
	*mcmsg_ptr = temp;
	//printf("%s",temp);
        return 1;
}
void createKey(char* keyphrase, char* key){
	if(keyphrase == NULL)
	{
		keyphrase =" ";
	}
	char* c = keyphrase;
	char* a ="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i=0,j=0,k=0,l=0,m=0,r=0;
	while(*(c+i) != '\0')
	{
		l=(int)*(c+i);
		if(l >= 97 && l <= 122)
		{
			l=l-32;
		}
		if(l >= 65 && l <= 90)
		{
			if(i != 0)
			{
				for(j=0;j<i;j++)
				{
					m=(int)*(c+j);
					if(m >= 97 && m <= 122)
					{
						m=m-32;
					}

					if(l == m)
					{
						r=1;
						j=i;
					}
				}
				//printf("%d",r);
				if(r!=1)
				{	
					*(key+k) = (char)l;//*(c+i);
					//printf("%c",*(key+k));
					k++;
				}
				i++;//current
				r=0;
			}
			else
			{
				*(key+k) = (char)l;
				//printf("%c",*(key+k));
				k++;
				i++;
			}
	
		}
		else
		{
			i++;
		}
	}
	i=0;
	r=0;
	while(k !=26)
	{
		
		if(k != 0)
			{
				for(j=0;j<k;j++)
				{
					if(*(key+j) == *(a+i))
					{
						r=1;
						j=k;
					}
				}
				if(r!=1)
				{
					*(key+k) = *(a+i);
					//printf("%c",*(key+k));
					k++;
				}
				i++;//current
				r=0;
			}
			else
			{
				*(key+k) = *(a+i);
				//printf("%c",*(key+k));
				k++;
				i++;
			}
	}
}		

char morseToKey(char* mcmsg, char* key){
    	char* FMCarray = ".....-..x.-..--.-x.x..x-.xx-..-.--.x--.-----x-x.-x--xxx..x.-x.xx-.x--x-xxx.xx-";
        int i=0,j=0,k=0;
	char b,c,m=-1,a='.',g='x',d='-';
	//printf("%s\n",mcmsg);
	while(*(FMCarray+k) != '\0' || i == 0 )
	{
		
		b=*(mcmsg);
		c=*(FMCarray+k);
		if(b == c)
		{
			//printf("%c%c",b,c);
			b=*(mcmsg+1);
			c=*(FMCarray+k+1);
			if(b == c)
			{
				//printf(" %c%c",b,c);
				b=*(mcmsg+2);
				c=*(FMCarray+k+2);
				if(b == c)
				{
					//printf(" %c%c\n",b,c);
					m=*(key+j);
					i=1;
				}
				else if(b == '\0')
				{
					i=1;
					return -1;
				}
			}
			else if(b == '\0')
			{
				return -1;
			}
		}
		else if(b == '\0')
		{
			return -1;
		}
		 if(b == a || b == g || b == d)
		{} //lovely
		else
			return -1;
		k += 3;
		j++;
	}		
	i=0;
	j=0;
	k=0;
	return m;
}

int FMCEncrypt(FILE *instream, char* key, FILE *outstream){
        char* mcmsg,m;
	int i=0;

	toMorse(instream,&mcmsg); 
	while(*(mcmsg+i) != '\0')
	{	
		m= morseToKey((mcmsg+i),key);
		i += 3;
		//printf("%c",m);
		if(m != -1)
		{
		fprintf(outstream,"%c",m);
		}	
	}
        return 0;
}

/* Part 2 Functions */
int fromMorse(char *mcmsg, FILE* outstream){
       	int i=0,j=0,k=0,l=0,m=0,n=0,o=0,p=0;
	char* c=(char*)malloc(10);
	char* test,b;
	while(*(mcmsg+i) != '\0')
	{	
		if(*(mcmsg+i+k) != '-' && *(mcmsg+i+k) != '.' && *(mcmsg+i+k) != 'x'){
				return 0;}	
		while(*(mcmsg+i+k) != 'x')
		{
			*(c+k) = *(mcmsg+i+k);
			k++;
			if(*(mcmsg+i+j) == '\0'){
			break;}
		}	
		
		*(c+k) = '\0';
		for(l=0; l<58;l++)
		{	
			m=0;
			n=0;
			p=0;
			test=*(MorseCode+l);
			while(*(test+p) != '\0')
			{
				p++;
			}
			if(p==k)
			{
			
				for(m=0;m<k;m++)
				{
					if(*(c+m) != *(test+m))
						{
							n=1;
						}
				}
				if(n!=1)
					{
						b=l+33;
						fprintf(outstream,"%c",b);

					}
			}			
		}
		o=0;
		if(*(mcmsg+i+k) == 'x')
		{
			k++;
			if(*(mcmsg+i+k) == 'x')
			{
				k++;
				if(*(mcmsg+i+k) != '\0')
				{
					b=' ';
					fprintf(outstream,"%c",b);
				}
			}
		}
		i+=k;		
		k=0;			
	}
        return 1;
}
int FMCDecrypt(FILE *instream, char* key, FILE *outstream){
	int size = 10,i=0,j=0,k=0,l=0,m=0,n=0;
	char* mcmsg =(char*)malloc(size),c;
	char* message;
	char* FMCarray = ".....-..x.-..--.-x.x..x-.xx-..-.--.x--.-----x-x.-x--xxx..x.-x.xx-.x--x-xxx.xx-";
	while((c = fgetc(instream)) != EOF)
	{
		i=0;
		j=0;
		if(c == '\0')
			break;
		while(c != *(key+i)&& *(key+i) != '\0')
		{
			i++;
		}
		if(c == *(key+i))
		{
			j=i*3;
			n+=j;
			//printf("%d ",j);
			if(n>size)
			{
				size += 100;
				mcmsg = (char*)realloc(mcmsg,size);
			}
			k=0;
			while(k<3)
			{
				*(mcmsg+l+k) = *(FMCarray+j+k);
				k++;
			}
		l+=k;
		}	
	}
	*(mcmsg+l)='\0';
	message = mcmsg;
	fromMorse(message,outstream);
        return 0;
}

