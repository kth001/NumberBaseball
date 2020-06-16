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
	printf("���ھ߱��� �����մϴ�\n");
	while (1)
	{
		for (int i = 0; i < 18; i++)		
			digitNumber[i] = 0;		
		balled = 0;
	a:	error = warn(warncnt);
		if (error != 0)
			return error;
		printf("���ϴ� �ڸ����� �Է����ּ���(1�̻� 19�̸�): ");
		scanf("%d", &n);
		if (n > 5 && n < 19)
		{
			printf("���ڰ� �ʹ� Ů�ϴ� �̴�� �Ͻðھ��? y/n ");
		b:	error = warn(warncnt);
			if (error != 0)
				return error;
			scanf("%c%c", &ch, &ch);

			if (ch == 'n')
				goto a;
			else if (ch != 'y')
			{
				printf("\ny��n�� �Է��ϼ��� ");
				warncnt++;
				goto b;
			}
		}
		else if (n > 18)
		{
			printf("�ڸ��� ���� �ʰ�!\n");
			warncnt++;
			goto a;
		}
		else if (n < 1)
		{
			printf("1�̻��� �Է����ּ���\n");
			warncnt++;
			goto a;
		}

		printf("%d�ڸ� ������ �����մϴ�\n",n);
		seed = time(0);
		srand(seed);
		for (int i = 0; i < n; i++)
			digitNumber[n - 1 - i] = rand() % 10;		
		printf("���� ���� �Ϸ�!");

		while (1)
		{
			ball = 0;
			strike = 0;
			balled = 0;
		d:	error = warn(warncnt);
			if (error != 0)
				return error;
			printf("\n%d�ڸ� ���� �Է��� �ּ���: ", n);
			scanf("%lld", &answer);
			if (answer >= pow(10, n))
			{
				printf("%d�ڸ��� �ƴմϴ�!", n);
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
				printf("%d��Ʈ����ũ ", strike);
			if (ball != 0)
				printf("%d��", ball);
			if (ball == 0 && strike == 0)
				printf("�ƿ�!");
			if (strike == n)
			{
				printf("����!\n");
				break;
			}
		}		

		printf("���� ��? y/n ");
	c:	error = warn(warncnt);
		if (error != 0)
			return error;

		scanf("%c%c", &ch, &ch);

		if (ch == 'n')
			return 0;
		else if (ch != 'y')
		{
			printf("\ny��n�� �Է��ϼ��� ");
			warncnt++;
			goto c;
		}
	}
}

int warn(int cnt)
{
	if (cnt == 10)
	{
		printf("�� ����");
		system("sleep 10");
		return 1;
	}
	else if (cnt == 5)
		printf("�϶�´�� ���ֽø� �����ϰڽ��ϴ�\n");
	else if (cnt == 9)
		printf("������ ����\n");
	return 0;
}