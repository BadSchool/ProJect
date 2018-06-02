#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>	
#include <unistd.h>	
#include <termios.h>

#define TRUE 1
#define FALSE 0
#define NULL '\0'

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
	char inputScript[30] = {NULL};
	int how, nTasu, MTasu, acc, wrong, cnt, cntTasu, i;
	double cTime, eTime;
	short randS;

	struct timeval start, end, errorS, errorE;
	how = nTasu = MTasu = acc = wrong = cntTasu = 0;

	while (how < 5)
	{
		cnt = nTasu = acc = 0;
		srand(time(NULL));
		randS = (rand() % 30);

		for(i = 0; i < 30; i++)
			inputScript[i] = NULL;

		gettimeofday(&start, NULL);
		while (1)
		{
			gettimeofday(&errorS, NULL);
			system("clear");
			printf(">> 영문 타자 연습 프로그램 : 짧은 글 연습 <<\n");
			printf("진행도 : %d%%  현재타수 : %d  최고타수 : %d  정확도 : %d%%\n\n", (how * 100) / 5, nTasu, MTasu, acc);
			puts(sScript[randS]);
			for (i = 0; i < cnt; i++)
				printf("%c", inputScript[i]);
			printf("\n");

			inputScript[cnt] = getch();
			gettimeofday(&errorE, NULL);
			gettimeofday(&end, NULL);
			if (inputScript[cnt] == 8 && cnt > 0)
				cnt--;
			else if (inputScript[cnt] == 27 || inputScript[cnt] == 10)
				break;
			else if(cnt >= 0)
				cnt++;

			
			wrong = 0;
			for(i = 0; i < cnt; i++)
				if(sScript[randS][i] != inputScript[i])
					wrong++;

			cntTasu = cnt - wrong;
			eTime = (errorE.tv_sec + errorE.tv_usec / 1000000.0) - (errorS.tv_sec + errorS.tv_usec / 1000000.0);
			cTime = (end.tv_sec + end.tv_usec / 1000000.0) - (start.tv_sec + start.tv_usec / 1000000.0);
			cTime -= eTime;

			nTasu = (cntTasu / cTime) * 60;

			if(cnt != 0)
				acc = 100 - (100 * wrong / cnt);
			else
				acc = 0;

			if (nTasu > MTasu)
				MTasu = nTasu;
		}

		if (inputScript[cnt] == 27)
			break;
		for (i = 0; i <= cnt; i++)
			inputScript[i] = NULL;

		how++;
	}
	if (inputScript[cnt] != 27)
	{
		printf("짧은 글 연습이 끝났습니다. 아무키나 누르시면 메뉴로 돌아갑니다.");
		getch();
	}
}
