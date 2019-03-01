
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

FILE *file;
int c;
char* noiseWordList[153] = {"a", "about", "above", "after",        
                 "again", "against", "all", "am", "an", "and", "any", "are",     
                 "as", "at", "be", "because", "been", "before", "being", "below",
                 "between", "both", "but", "by", "could", "did", "do", "does",   
                 "doing", "down", "during", "each", "few", "for", "from",        
                 "further", "had", "has", "have", "having", "he", "he'd",        
                 "he'll", "he's", "her", "here", "here's", "hers", "herself",    
                 "him", "himself", "his", "how", "how's", "i", "i'd", "i'll",    
                 "i'm", "i've", "if", "in", "into", "is", "it", "it's", "its",   
                 "itself", "let's", "me", "more", "most", "my", "myself", "nor", 
                 "of", "on", "once", "only", "or", "other", "ought", "our",      
                 "ours", "ourselves", "out", "over", "own", "same", "she",       
                 "she'd", "she'll", "she's", "should","so", "some", "such",      
                 "than", "that", "that's", "the", "their", "theirs", "them",     
                 "themselves", "then", "there", "there's", "these", "they",      
                 "they'd", "they'll", "they're", "they've","this", "those",      
                 "through", "to", "too", "under", "until", "up", "very", "was",  
                 "we", "we'd", "we'll", "we're", "we've", "were", "what",        
                 "what's", "when", "when's", "where", "where's","which", "while", 
                 "who", "who's", "whom", "why", "why's", "with", "would", "you", 
                 "you'd", "you'll", "you're", "you've", "your", "yours",         
                 "yourself", "yourselves"};   

bool isInWordList(char* word);
bool isUpperCase(int letter);
int toLowercase(int letter);
void processWord(char* word, int lineNumber);
void displayResults();

struct pair
{
	char word[32];
	int lineOccurence[1000];
}q;

struct pair pairArray[10000];

bool isInWordList(char* word)
{
	for(int i = 0; i < sizeof(noiseWordList)/sizeof(noiseWordList[0]); i++)
	{
		if(strcmp(word, noiseWordList[i]) == 0)
		{
			return true;
		}
	}
	return false;
}

bool isUpperCase(int letter)
{
	if(letter >= 64 & letter <= 90)
	{
		return true;
	}
	return false;
	
}

int toLowercase(int letter)
{
	if(isUpperCase(letter))
	{
		letter = letter + 32;
	}
	return letter;
}


void processWord(char* word, int lineNumber)
{
	int i = 0;
	for(int i = 0; sizeof(pairArray)/sizeof(pairArray[0]); i++)
	{
		if(pairArray[i].word[0] == '\0')
		{
			for(int k = 0; k < sizeof(word)/sizeof(word[0]); k++)
			{
				pairArray[i].word[k] = word[k];
			}
			pairArray[i].lineOccurence[0] = lineNumber;
			break;
		}
		else if(strcmp(pairArray[i].word, word) == 0)
		{
			int k = 1;
			while(pairArray[i].lineOccurence[k] != 0)
			{
				k++;
			}
			pairArray[i].lineOccurence[k] = lineNumber;
			break;
		}
		
	}
}


void displayResults()
{
	int i = 0;
	for(int i = 0; pairArray[i].word[0] != '\0'; i++)
	{
		printf("%s : ", pairArray[i].word);

		for(int k = 0; pairArray[i].lineOccurence[k] != 0; k++)
		{
			printf("%d ", pairArray[i].lineOccurence[k]);
		}
		printf("\n");
	}
}


int main(int argc, char **argv)
{	
	int flag = 1;
	char word[32];
	int pos = 0;
	int lineCounter = 0;

	file = fopen(argv[1], "r+");
	if(file)
	{
		while((c = getc(file)) != EOF)
		{
			if(c != ' ' && c != '\n' && c != '\0')
			{
				flag = 1;
			}
			else if(pos > 0)
			{
				word[pos] = '\0';
				flag = 0;
				pos = 0;
				if(!isInWordList(word))
				{
					//printf("%d : %s\n", lineCounter, word);
					processWord(word, lineCounter);
				}
				memset(word, 0, sizeof word);
			}

			if(flag == 1 && isalpha(c))
			{
				word[pos] = toLowercase(c);
				pos++;
			}

			if(c == '\n')
			{
				lineCounter++;
			}
		}
	}

	displayResults();

	fclose(file);
	
	return 0;
}





























