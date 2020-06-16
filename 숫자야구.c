#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int warn(int cnt);

int main(void)
{
	int n, strike, ball, balled;//balled: bitmaskfrom left to right, first bit(from left) balled answer,second bit ballplus
	unsigned long long answer;
	char ch;
	int warncnt = 0, error, digitNumber[18] = { 0 }, digitAnswer = 0;
	time_t seed;
	printf("숫자야구를 시작합니다\n");
	while (1)
	{
		for (int i = 0; i < 18; i++)		
			digitNumber[i] = 0;		
		balled = 0;
	a:	error = warn(warncnt);
		if (error != 0)
			return error;
		printf("원하는 자릿수를 입력해주세요(1이상 19미만): ");
		scanf("%d", &n);
		if (n > 5 && n < 19)
		{
			printf("숫자가 너무 큽니다 이대로 하시겠어요? y/n ");
		b:	error = warn(warncnt);
			if (error != 0)
				return error;
			scanf("%c%c", &ch, &ch);

			if (ch == 'n')
				goto a;
			else if (ch != 'y')
			{
				printf("\ny나n을 입력하세요 ");
				warncnt++;
				goto b;
			}
		}
		else if (n > 18)
		{
			printf("자릿수 범위 초과!\n");
			warncnt++;
			goto a;
		}
		else if (n < 1)
		{
			printf("1이상을 입력해주세요\n");
			warncnt++;
			goto a;
		}

		printf("%d자리 난수를 생성합니다\n",n);
		seed = time(0);
		srand(seed);
		for (int i = 0; i < n; i++)
			digitNumber[n - 1 - i] = rand() % 10;		
		printf("난수 생성 완료!");

		while (1)
		{
			ball = 0;
			strike = 0;
			balled = 0;
		d:	error = warn(warncnt);
			if (error != 0)
				return error;
			printf("\n%d자리 답을 입력해 주세요: ", n);
			scanf("%lld", &answer);
			if (answer >= pow(10, n))
			{
				printf("%d자리가 아닙니다!", n);
				goto d;
				warncnt++;
			}
			for (int i = 0; i < n; i++)
			{
				digitAnswer = (answer % 10);
				for (int j = 0; j < n; j++)
				{
					if (digitAnswer == digitNumber[j])
					{
						if (i == j)
						{
							strike++;
							if ((balled >> (31 - j)) & 1)
								ball--;
							balled |= 1 << (31 - j);
							
							break;
						}
						else if (!((balled >> (31 - j)) & 1) && !(balled & 1))
						{
							balled |= 1 << (31 - j);
							balled |= 1;
							balled |= 2;
						}
					}
				}
				ball += (balled & 2) >> 1;
				balled &= 0xfffffffc;
				answer /= 10;
			}
			if (strike != 0)
				printf("%d스트라이크 ", strike);
			if (ball != 0)
				printf("%d볼", ball);
			if (ball == 0 && strike == 0)
				printf("아웃!");
			if (strike == n)
			{
				printf("정답!\n");
				break;
			}
		}		

		printf("한판 더? y/n ");
	c:	error = warn(warncnt);
		if (error != 0)
			return error;

		scanf("%c%c", &ch, &ch);

		if (ch == 'n')
			return 0;
		else if (ch != 'y')
		{
			printf("\ny나n을 입력하세요 ");
			warncnt++;
			goto c;
		}
	}
}

int warn(int cnt)
{
	if (cnt == 10)
	{
		printf("나 안해");
		system("sleep 10");
		return 1;
	}
	else if (cnt == 5)
		printf("하라는대로 해주시면 감사하겠습니다\n");
	else if (cnt == 9)
		printf("마지막 경고다\n");
	return 0;
}