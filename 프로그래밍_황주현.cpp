#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define TRUE 1
#define FALSE 0

void clearBuffer();	// 버퍼 정리
int menu();		// 메뉴

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

int menu()
{
	int input;
	//system("clear");	// 리눅스 clear	
	system("cls");

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
	int word, how, wrong, acc, insert;
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
			//system("clear");	// 리눅스 clear	
			system("cls");
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
	int how, wrong, acc, insert, myWord;
	char *word[] = { "hello", "hi", "help" };
	char input[20] = { NULL };

	wrong = how = insert = acc = myWord = 0;

	while (how <= 20)
	{
		srand(time(NULL));
		myWord = (rand() % 3);
		while (1)
		{
			if (insert != 0)
				acc = 100 - (100 * wrong / insert);
			//system("clear");	// 리눅스 clear	
			system("cls");
			printf(">> 영문 타자 연습 프로그램 : 낱말 연습 <<\n");
			printf("진행도 : %d%%	오타수 : %d		정확도 : %d%%\n\n", (how * 100 / 20), wrong, acc);
			puts(word[myWord]); // 개행 수정
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
	char sScript[][30] = { "I like A.", "I like B.", "I like C.", "I like D.", "I like E.", "I like F.", "I like G.", "I like H.", "I like I.", "I like J.", "I like K.", "I like L.", "I like M.", "I like N.", "I like O.", "I like P.", "I like Q.", "I like R.", "I like S.", "I like T.", "I like U.", "I like V.", "I like W.", "I like X.", "I like Y.", "I like Z.", "I like a.", "I like b.", "I like c.", "I like d." };
	char inputScript[30];
	int cnt1, cnt2, pgs, acc, wl, n, x, q;
	unsigned ct = 0, ht = 0, gap = 0;
	clock_t start, end;
	cnt1 = cnt2 = pgs = acc = wl = ct = ht = gap = 0;
	//system("clear");	// 리눅스 clear	
	system("cls");

	srand(time(NULL));
	while (pgs != 100)
	{
		x = rand() % 29;
		for (int i = 0; i < 30; i++)
			inputScript[i] = NULL;

		while (1)
		{
			start = clock();
			cnt1 = 0;
			printf(">> 영문 타자 연습 프로그램 : 짧은 글 연습 <<\n");
			printf("진행도 : %d%%, 현재타수 : %u, 최고타수 : %u, 정확도 : %d%%  ([Esc] 키를 통해 메뉴로)\n", pgs, ct, ht, acc);

			for (int i = 0; sScript[x][i] != NULL; i++, cnt1++)
				printf("%c", sScript[x][i]);

			printf("\n");

			for (int i = 0; i < cnt2; i++)
				printf("%c", inputScript[i]);
			inputScript[cnt2] = getch();
			end = clock();
			if (inputScript[cnt2] == 27 || inputScript[cnt2] == '\n')
				break;
			else if (inputScript[cnt2] == 127)
				cnt2 = cnt2 - 2;
			wl = 0;
			for (int i = 0; i <= cnt2; i++)
				if (inputScript != sScript[x][i])
					wl++;

			if (cnt2 >= 0 && cnt2 < cnt1)
				acc = (double)(cnt2 + 1 - wl) / (cnt2 + 1) * 100;
			else if (cnt2 < 0)
			{
				acc = 0;
				cnt2 = -1;
			}
			gap = (double)end - start;
			if (wl != cnt2 + 1)
				ct = (double)(cnt2 + 1 - wl) / gap * 60;
			if (ct > ht)
				ht = ct;
			cnt2++;
			system("cls");
			//system("clear");
		}
		if (inputScript[cnt2] == 27)
			break;
		pgs += 20;
		if (pgs != 100)
		{
			acc = 0;
			cnt2 = 0;
		}
	}
}
