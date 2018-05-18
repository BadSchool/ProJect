#include <stdio.h>
#include <termio.h>
#include <stdlib.h>
#include <time.h>
int getch(void) { //getch 함수
	int ch;
	struct termios buf;
	struct termios save;
	tcgetattr(0, &save);
	buf = save;
	buf.c_lflag &= ~(ICANON | ECHO );
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &buf);
	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);
	return ch;
}

void main(){
	char a[][30] = {"I like A.", "I like B.", "I like C.", "I like D.", "I like E.", "I like F.", "I like G.", "I like H.", "I like I.", "I like J.", "I like K.", "I like L.", "I like M.", "I like N.", "I like O.", "I like P.", "I like Q.", "I like R.", "I like S.", "I like T.", "I like U.", "I like V.", "I like W.", "I like X.", "I like Y.", "I like Z.", "I like a.", "I like b.", "I like c.", "I like d."};
	char b[30]; // a는 원래 문장 배열, b는 입력받는 문장 배열
	int cnt = 0, cnt2 = 0, pgs = 0, acc = 0, wl = 0, n, x, q;
	unsigned ct = 0, ht = 0, gap = 0; 
	time_t start, end; // 시작시간, 종료시간, gap = 종료시간 - 시작시간
	// pgs = 진행도, ct = 현재타수, ht = 최고타수, acc = 정확도, wl = 오타
	
	srand(time(NULL)); // 킬 때마다 랜덤 바뀌게 하기
	while(pgs != 100){ 
		x = rand() % 29; // 랜덤 배정
		for (int i = 0; i <= 30; i++) // b 배열 초기화
			b[i] = '\0';
		//start = clock(); 
		time(&start); // 시작할때 시간 start에 저장
		while(1){
			cnt = 0; //cnt 초기화
			printf(">> 영문 타자 연습 프로그램 : 짧은 글 연습 <<\n"); 
			printf("진행도 : %d%%, 현재타수 : %u, 최고타수 : %u, 정확도 : %d%%\n", 
					pgs, ct, ht, acc);
			for (int i = 0; a[x][i] != '\0'; i++){ // a 배열 출력
				printf("%c", a[x][i]);
				cnt++;
			}
			printf("\n"); //개행
			for (int i = 0; i < cnt2; i++)
				printf("%c", b[i]); // b 배열 출력
			b[cnt2] = getch(); // getch 함수를 통해 b 배열에 저장
			//end = clock(); 
			time(&end); //타자 치고 나서 시간 end에 저장
			if (b[cnt2] == '\n') // 개행 입력시 반복문 나감
				break;
			if (b[cnt2] == 127) // 백스페이스 구현
				cnt2 = cnt2 - 2;
			wl = 0; // 오타 개수 초기화
			for (int i = 0; i <= cnt2; i++)
				if (b[i] != a[x][i]) // a 배열과 b 배열 비교를 통해 오타 개수 체크
					wl++;	
			if (cnt2 >= 0 && cnt2 < cnt) 
				acc = (double) (cnt2 + 1 - wl) / (cnt2 + 1) * 100; // 정확도 구현
			else if (cnt2 < 0){
				acc = 0; // 입력한 개수가 0이면 정확도는 0
				cnt2 = -1; // cnt2 값 음수 안되게 설정
			}
			gap = end - start; // end - start를 gap에 저장
			if (wl != cnt2 + 1) // 오타 = 총 타자수 일 때는 계산 x
				ct = (double) (cnt2 + 1 - wl) / gap * 60; // 현재타수 계산
			if (ct > ht) // 현재타수 > 최고타수 일 때 최고타수 갱신
				ht = ct;
			cnt2++;
			system("clear"); // 화면 지우기
		}
		pgs += 20; // 진행도 증가
		if (pgs != 100){
			acc = 0; // 정확도 초기화
			cnt2 = 0; // b 배열 카운트 초기화
		}
		system("clear"); // 화면 지우기
	}
	while (1){ // 진행도 100일 때 프로그램 종료 준비
		printf(">> 영문 타자 연습 프로그램 : 짧은 글 연습 <<\n"); 
		printf("진행도 : %d%%, 현재타수 : %u, 최고타수 : %u, 정확도 : %d%%\n", 
				pgs, ct, ht, acc);
		printf("짧은 글 연습이 종료되었습니다. [Enter] 키를 통해 메뉴로 돌아가세요.");
		if (getch() == '\n') // Enter 입력시 프로그램 종료
			break;
		system("clear");
	}
	
}
