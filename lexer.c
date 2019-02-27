#include "lexer.h"

FILE *getStream(FILE *fp) {
	//printf("%u %u %u\n", buf, buf1,buf2);
	
	if(buf == buf1)
	{
		int char_read = fread(buf2, sizeof(char), sizeof(buf2), fp);
		if(feof(fp))
	    {
			buf2[char_read] = '$';
		}
		printf("1:%s\n",buf2);
		buf = buf2;
	}
	else 
	{
		int char_read = fread(buf1, sizeof(char), sizeof(buf1), fp);
		if(feof(fp))
	    {
		 	buf1[char_read] = '$';
		}
		printf("2:%s\n",buf1);
		
		buf = buf1;
	}
	//printf("%u %u %u\n", buf, buf1,buf2);
	
	
	return fp;
}

token_info * getNextToken(FILE *fp) {
	token_info * tok = (token_info *) malloc (sizeof(token_info));
	memset(tok->lexeme, '\0', sizeof(tok->lexeme));
	int state=1, lexPtr=0;
	char currChar;
	//printf("%u %u %u\n", buf, buf1,buf2);
	
	for(int i=0;i<600;i++) {
		
	
		if(currPtr==BUFFER_SIZE-1)//511=BufferSize-1
		{	
			//printf("Inside currPtr=511 \n");
			fp=getStream(fp);
			currPtr=0;
		}
		//printf("%d %c|\n",currPtr,buf[currPtr] );
		currChar = buf[currPtr++];
		/*if(currChar=='$')
		{	
		}*/
		//printf("%u %u %u %i %c\n", buf, buf1,buf2,i,currChar);
		int a=4;
		switch(state) {
			case 1:
				switch(currChar) {//state =3 incorporated int the same switch later shd be differented  in a different switch
					case '+':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_PLUS");
						state=3;
						return tok;
					case '-':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_MINUS");
						state=3;
						return tok;
					case '*':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_MUL");
						state=3;
						return tok;
					case '/':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_DIV");
						state=3;
						return tok;
					case '[':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_SQL");
						state=3;
						return tok;
					case ']':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_SQR");
						state=3;
						return tok;
					case '.':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_DOT");
						state=3;
						return tok;
					case ',':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_COMMA");
						state=3;
						return tok;
					case ';':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_SEM");
						state=3;
						return tok;
					case ':':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_COLON");
						state=3;
						return tok;
					case '(':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_OP");
						state=3;
						return tok;
					case ')':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_CL");
						state=3;
						return tok;
					case '~':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_NOT");
						state=3;
						return tok;
					case ' ':case '\t':
						state=1;
						break;
					case '\n':
						state=1;
						line_number++;
						break;
					case '%':
						state=42;
						break;
					case '$':
						tok->lexeme[lexPtr++] = currChar;
						tok->line_number=line_number;
						strcpy(tok->token,"Dollar");
						state=100;
						return tok;	
					case '<':
						tok->lexeme[lexPtr++]=currChar;
						state=36;
						break;

				}
				break;
			case 42:
				switch(currChar)
				{
					case '$':
						currPtr--;//so that in next iteration it goes to state 1 and case '$'
						//fall through
					case '\n':
						
						tok->line_number=line_number;
						strcpy(tok->token,"TK_COMMENT");
						if(currChar=='\n')
							line_number++;
						state=43;
						return tok;
						break;

					default:
						state=42;
						tok->lexeme[lexPtr++]=currChar;
						break;
				}
				break;
			case 43:
				switch(currChar)
				{
					default:
						currPtr--;//retract '$'
						state=1;
						break;
				}
				break;
			case 36:
				switch(currChar)
				{
					case '-':
						tok->lexeme[lexPtr++]=currChar;
						state=38;
						break;
					case '=':
						tok->lexeme[lexPtr++]=currChar;
						state=37;
						break;
					default:
						currPtr--;//retract this character
						state=41;

				}
				break;
			case 38:
				switch(currChar)
				{
					case '-':
						tok->lexeme[lexPtr++]=currChar;
						state=39;
						break;

				}
				break;
			case 39:
				switch(currChar)
				{
					case '-':
						tok->lexeme[lexPtr++]=currChar;
						state=40;
						break;
				}
				break;
			case 40:
				switch(currChar)
				{
					default:
						tok->line_number=line_number;
						strcpy(tok->token,"TK_ASSIGNOP");
						currPtr--;
						return tok;

						break;
						
				}
				break;




		}		
	}
}

int main() {
	//buf = buf1;
	//printf("%u %u %u\n", buf, buf1,buf2);
	FILE *fp = fopen("code.txt", "r");
	//fp = getStream(fp);
	//fflush(stdout);
	//currPtr=511;
	token_info * tok ;	
	while(strcmp(tok->token,"Dollar")!=0)
	{
		tok= getNextToken(fp);
		printf("Next token is %s with line_number=%d\n", tok->token,tok->line_number);
	}
	//tok = getNextToken(fp);
	//printf("First token is %s\n", tok->token);
	
	return 0;

}