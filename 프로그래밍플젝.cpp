#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define TRUE 1
#define FALSE 0

void spacePractice();
//void wordPractice();
//void shortScript();
//void longScript();
int menu();

int main(void)
{
	while (menu() != FALSE);
	return 0;
}

int menu()
{
	int input;
	printf(">> ���� Ÿ�� ���� ���α׷� <<\n");
	printf("1) �ڸ� ����	2) ���� ����\n\
3) ª�� �� ����	4) �� �� ����\n\
5) ���α׷� ����\n\n\
��ȣ�� �����ϼ���: ");
	scanf("%d", &input);
	fflush(stdin);

	switch (input)
	{
		case 1:
			spacePractice();
			return TRUE;
		case 2:
			//wordPractice();
			return TRUE;
		case 3:
			//shortScript();
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
			if(insert != 0)
			acc = 100 - (100 * wrong / insert);
			//system("clear");
			printf(">> ���� Ÿ�� ���� ���α׷� : �ڸ� ���� <<\n");
			printf("���൵ : %d%%	��Ÿ�� : %d		��Ȯ�� : %d%%\n\n", (how*100/20), wrong, acc);
			printf("%c\n-\n", word);
			fflush(stdin);
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