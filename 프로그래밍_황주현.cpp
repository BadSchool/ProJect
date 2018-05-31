#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <conio.h>
#include <sys/time.h>	
#include <unistd.h>	
#include <termios.h>

#define TRUE 1
#define FALSE 0

void clearBuffer();	// 버퍼 정리
int menu();		// 메뉴
int getch();
void spacePractice();	// 자리 연습
void wordPractice();	// 단어 연습
void shortScript();	// 짧은글 연습
//void longScript();	// 긴글 연습

int main(void)
{
	while (menu() != FALSE);
	return 0;
}

void clearBuffer()
{
	while (getchar() != '\n');
}

int getch(void)  
{  
  int ch;  
  struct termios buf;  
  struct termios save;  
  
   tcgetattr(0, &save);  
   buf = save;  
   buf.c_lflag &= ~(ICANON|ECHO);  
   buf.c_cc[VMIN] = 1;  
   buf.c_cc[VTIME] = 0;  
   tcsetattr(0, TCSAFLUSH, &buf);  
   ch = getchar();  
   tcsetattr(0, TCSAFLUSH, &save);  
   return ch;  
}  
  
int menu()
{
	
	int input;
	system("clear");

	printf(">> 영문 타자 연습 프로그램 <<\n");
	printf("1) 자리 연습	2) 낱말 연습\n\
3) 짧은 글 연습	4) 긴 글 연습\n\
5) 프로그램 종료\n\n\
번호를 선택하세요: ");
	scanf("%d", &input);
	clearBuffer();
	switch (input)
	{
	case 1:
		spacePractice();
		return TRUE;
	case 2:
		wordPractice();
		return TRUE;
	case 3:
		shortScript();
		return TRUE;
	case 4:
		//longScript();
		return TRUE;
	case 5:
		return FALSE;
	}
}

void spacePractice()
{
	int how, wrong, acc, insert;
	short word;
	char input;
	wrong = how = insert = acc = 0;
	while (how <= 20)
	{
		srand(time(NULL));
		word = (rand() % 58) + 65;
		if (word >= 91 && word <= 96)
			continue;
		while (1)
		{
			input = 0;
			if (insert != 0)
				acc = 100 - (100 * wrong / insert);
			system("clear");
			printf(">> 영문 타자 연습 프로그램 : 자리 연습 <<\n");
			printf("진행도 : %d%%	오타수 : %d		정확도 : %d%%\n\n", (how * 100 / 20), wrong, acc);
			printf("%c\n-\n", word);
			input = getch();
			insert++;
			if ((int)input == word || (int)input == 27)
				break;
			else
				wrong++;
		}
		if (input == 27)
			break;
		how++;
	}
}

void wordPractice()
{
	int how, wrong, acc, insert;
	short myWord;
	char *word[] = { "hello", "hi", "help", "apple", "school", "university", "program", "drink", "do", "like", "mean", "word", "hair", "close", "clear", "Buffer", "note", "book", "speak", "listen"};
	char input[20] = { NULL };

	wrong = how = insert = acc = myWord = 0;

	while (how <= 20)
	{
		srand(time(NULL));
		myWord = (rand() % 20);
		while (1)
		{
			if (insert != 0)
				acc = 100 - (100 * wrong / insert);
			system("clear");
			printf(">> 영문 타자 연습 프로그램 : 낱말 연습 <<\n");
			printf("진행도 : %d%%	오타수 : %d		정확도 : %d%%\n\n", (how * 100 / 20), wrong, acc);
			puts(word[myWord]);
			fgets(input, sizeof(input), stdin);

			if (input[strlen(input) - 1] == '\n')
				input[strlen(input) - 1] = '\0';
			insert++;
			if ((!strcmp(input, word[myWord])) || (!strcmp(input, "###")))
				break;
			else
			{
				wrong++;
				break;
			}
		}
		if (!strcmp(input, "###"))
			break;
		how++;
	}
}

void shortScript()
{
	char sScript[][30] = { "I like A.", "I like B.", "I like C.", "I like D.", "I like E.", "I like F.", "I like G.", "I like H.",\
		"I like I.", "I like J.", "I like K.", "I like L.", "I like M.", "I like N.", "I like O.", "I like P.", "I like Q.",\
		"I like R.", "I like S.", "I like T.", "I like U.", "I like V.", "I like W.", "I like X.", "I like Y.", "I like Z.",\
		"I like a.", "I like b.", "I like c.", "I like d." };
	char inputScript[30] = { NULL };
	int how, nTasu, MTasu, acc, wrong, cnt;
	short randS;

	struct timeval start;
	struct timeval end;
	how = nTasu = MTasu = acc = wrong = 0;

	while (how < 30)
	{
		cnt = 0;
		srand(time(NULL));
		randS = (rand() % 30);
		while (1)
		{
			system("clear");
			printf(">> 영문 타자 연습 프로그램 : 짧은 글 연습 <<\n");
			printf("진행도 : %d%%  현재타수 : %d%%  최고타수 : %d%%  정확도 : %d%%\n\n", (how*100)/30, nTasu, MTasu, acc);

			puts(sScript[randS]);
			for (int i = 0; i < cnt; i++)
				printf("%c", inputScript[i]);
			printf("\n");
			gettimeofday(&start, NULL);
			inputScript[cnt] = getch();
			if (inputScript[cnt] == 8 && cnt > 0)
				cnt--;
			else if (inputScript[cnt] == 27 || inputScript[cnt] == 10)
				break;
			else
				cnt++;
			gettimeofday(&end, NULL);
			nTasu = cnt / ((&end - &start) * 3600);
			if (nTasu > MTasu)
				MTasu = nTasu;

		}
		if (inputScript[cnt] == 27)
			break;
		for (int i = 0; i <= cnt; i++)
			inputScript[i] = NULL;
		how++;
	}
}
