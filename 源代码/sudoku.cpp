#include"define.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6031)

extern int boolCnt, clauseCnt, sumOfAns, branchRule;
extern int * ans ;
extern char fileName[100];
extern clause* CNF ;
extern sud S;
int VarTrans(int f, int i, int j, int n) {
	return (f - 1) * 729 + (i - 1) * 81 + (j - 1) * 9 + n;
}

status Candig( int x, int y, int z) //�޸Ķ���original�Ļ�����
{
	if (S.original[x][y][z] == 0) return ERROR;
	for (int i = 1; i <= 9; i++) //�����ԭ������֮���8�����֣�������������˵�������ڶ�
	{
		if (i == S.pattern[x][y][z]) continue;//��ԭ������ͬ����Ƚ���һ������
		S.original[x][y][z] = i;//���ո�����һ�����֣�������Ƿ��н�
		CreateCnf();
		ReadCNF(CNF, SUDOKU);
		ans = (int*)malloc(sizeof(int) * (boolCnt + 1));
		for (int i = 0; i <= boolCnt; i++)
			ans[i] = 1;
		int res=DPLL(CNF, ans, SUDOKU);
		if (!res) continue;
		else
		{//�������㣬˵�������ڶ����������ָ���ֵ
			S.original[x][y][z] = S.pattern[x][y][z];
			return ERROR;
		}
	}
	S.original[x][y][z] = 0;//�����ڶ�
	S.num--;
	return OK;
}
void hint() {
	int x, y, z, flag;
	flag = 1;
	srand(time(NULL));
	while (flag) {
		x = rand() % 2 + 1;
		y = rand() % 9 + 1;
		z = rand() % 9 + 1;
		if (!S.original[x][y][z]) {
			S.original[x][y][z] = S.pattern[x][y][z];
			flag = 0;
		}
	}
}
void CreateCnf()
{
	FILE* fp = fopen("sud.cnf", "w");
	int d[9][2] = { {0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2} };
	fprintf(fp, "p cnf %d %d\n", 1458, 24138 + S.num * 9);//˫���� fijn==2*9*9*9=1458   ����Ҫ�� 162������*��1+36��  ��Լ�� 18��*��9+36*9�� ��Լ��ͬ��  ����Լ�� 18������*��9+36*9���ȼ�Լ�� 18*9=162
	int x, y, z, n;
	int f, i, j, count;
	{//��������Ϸ������ʾ����Ӧ�ĵ��Ӿ伯¼��cnf�ļ�
		for (f = 1; f <= 2; f++)
		{
			for (i = 1; i <= 9; i++) {

				for (j = 1; j <= 9; j++)
				{
					if (S.original[f][i][j]) {
						fprintf(fp, "%d 0\n", VarTrans(f, i, j, S.original[f][i][j]));
						for (x = 1; x <= 9; x++)
						{
							if (x == S.original[f][i][j]) continue;
							fprintf(fp, "%d 0\n", -VarTrans(f, i, j, x));
						}
					}
				}
			}

		}

	}
	{//����������¼��cnf�ļ�
		for (f = 1; f <= 2; f++) {
			for (i = 1; i <= 9; i++)//����9�У�ÿһ����(9*C92+9)���Ӿ�
			{
				for (n = 1; n <= 9; n++)//111��121��131����nΪ��������֣�9��ѭ����ÿѭ��һ������һ������
				{
					for (j = 1; j <= 9; j++)//jΪ�кţ�
						fprintf(fp, "%d ", VarTrans(f, i, j, n));
					fprintf(fp, "0\n");
				}
				for (n = 1; n <= 9; n++)//nΪ��������֣�9��ѭ��
					for (count = 1; count <= 9; count++)//����ѭ�������111���121���ȣ���C92������
						for (j = count + 1; j <= 9; j++)
							fprintf(fp, "%d %d 0\n", -VarTrans(f, i, count, n), -VarTrans(f, i, j, n));
			}
		}

		for (f = 1; f <= 2; f++)
		{
			for (j = 1; j <= 9; j++)//����9�У�ÿһ����(9*C92+9)���Ӿ�
			{
				for (n = 1; n <= 9; n++)//111��211��311����nΪ��������֣�9��ѭ����ÿѭ��һ������һ������
				{
					for (i = 1; i <= 9; i++)//iΪ�к�
						fprintf(fp, "%d ", VarTrans(f, i, j, n));
					fprintf(fp, "0\n");
				}
				for (n = 1; n <= 9; n++)//nΪ��������֣�9��ѭ��
					for (count = 1; count <= 9; count++)//����ѭ�������111���211���ȣ���C92������
						for (i = count + 1; i <= 9; i++)
							fprintf(fp, "%d %d 0\n", -VarTrans(f, count, j, n), -VarTrans(f, i, j, n));
			}
		}
		for (f = 1; f <= 2; f++) {
			for (count = 0; count < 9; count++)//����9���Ź���ÿ��������(9*C92+9)���Ӿ�
			{
				x = 1 + d[count][0] * 3;
				y = 1 + d[count][1] * 3;//ÿ���������ϽǸ��ӵ�λ��
				for (n = 1; n <= 9; n++)//nΪ���������
				{
					for (int m = 0; m < 9; m++)
						fprintf(fp, "%d ", VarTrans(f, x + d[m][0], y + d[m][1], n));
					fprintf(fp, "0\n");
				}


				for (n = 1; n <= 9; n++)//nΪ��������֣�9��ѭ��
					for (int m1 = 0; m1 < 9; m1++)//���Ƹ����е�9��λ�ã���C92������
						for (int m2 = m1 + 1; m2 < 9; m2++)
							fprintf(fp, "%d %d 0\n", -VarTrans(f, x + d[m1][0], y + d[m1][1], n), -VarTrans(f, x + d[m2][0], y + d[m2][1], n));
			}
		}
		for (f = 1; f <= 2; f++)
		{
			for (i = 1; i <= 9; i++) {
				for (j = 1; j <= 9; j++)//����81�����ӣ�ÿ��������(C92+1)������
				{
					for (n = 1; n <= 9; n++)//nΪ���������
						fprintf(fp, "%d ", VarTrans(f, i, j, n));
					fprintf(fp, "0\n");
					for (n = 1; n <= 9; n++)
						for (count = n + 1; count <= 9; count++)
							fprintf(fp, "%d %d 0\n", -VarTrans(f, i, j, n), -VarTrans(f, i, j, count));
				}
			}
		}

		for (n = 1; n <= 9; n++)
		{
			for (i = 7; i <= 9; i++)
			{
				for (j = 7; j <= 9; j++)
				{
					fprintf(fp, "%d %d 0\n", -VarTrans(1, i, j, n), VarTrans(2, i - 6, j - 6, n));
					fprintf(fp, "%d %d 0\n", VarTrans(1, i, j, n), -VarTrans(2, i - 6, j - 6, n));
				}
			}
		}
	}

	//������¼��cnf�ļ�
	fclose(fp);
}
void Sudcreate() {
	int x, y, z, v;
	int f, i, j, n;
	srand(time(NULL));
	x = rand() % 2 + 1;
	y = rand() % 9 + 1;//���ȷ������һ��λ�õ���ֵ
	z = rand() % 9 + 1;
	v = rand() % 9 + 1;
	for (int f = 0; f <= 2; f++)
		for (int i = 0; i <= 9; i++)
			for (int j = 0; j <= 9; j++)
				S.original[f][i][j] = S.pattern[f][i][j] = 0;

	S.num = 0;//��ʼ������
	S.original[x][y][z] = v;
	S.num = 1;
	CreateCnf();//����cnf�ļ�
	ReadCNF(CNF, SUDOKU);
	ans = (int*)malloc(sizeof(int) * (boolCnt + 1));
	for (int i = 0; i <= boolCnt; i++)
		ans[i] = 1;
	DPLL(CNF, ans, SUDOKU);//���˫����
	for (f = 1; f <= 2; f++)
		for (i = 1; i <= 9; i++)
			for (j = 1; j <= 9; j++)
				for (n = 1; n <= 9; n++)
					if (ans[VarTrans(f, i, j, n)]) S.pattern[f][i][j] = n;
	S.num = 162;
}
void SudPlay()
{
	int choice = 1, diff, op;
	int x, y, z, v;
	while (choice) {
		system("cls");
		printf("��ѡ���Ѷȣ�\n");
		printf("   1.��     2.�е�     3.���� \n");
		scanf("%d", &diff);
		printf("�����������������Եȡ���");
		Sudcreate();//����γ�һ������
		for (int f = 1; f <= 2; f++)
			for (int i = 1; i <= 9; i++)
				for (int j = 1; j <= 9; j++)
					S.original[f][i][j] = S.pattern[f][i][j];
		int dignum = 0,xx,yy,zz;//�������ڶ�
		do
		{
			xx = rand() % 2 + 1;
			yy = rand() % 9 + 1;//���ȷ������һ��λ�õ���ֵ
			zz = rand() % 9 + 1;
			Candig(xx, yy, zz); 
			dignum++;
		} while (dignum < diff * 40);
		op = 1;
		while (op)
		{
			system("cls");
			printf("------------sudoku------------\n\n");
			for (int i = 1; i <= 6; i++)
			{
				for (int j = 1; j <= 9; j++)
					printf("%3d", S.original[1][i][j]);
				printf("\n");
			}
			for (int i = 7; i <= 9; i++)
			{
				for (int j = 1; j <= 9; j++)
					printf("%3d", S.original[1][i][j]);
				for (int j = 4; j <= 9; j++)
					printf("%3d", S.original[2][i - 6][j]);
				printf("\n");
			}
			for (int i = 4; i <= 9; i++)
			{
				printf("                  ");
				for (int j = 1; j <= 9; j++)
					printf("%3d", S.original[2][i][j]);
				printf("\n");
			}
			printf("------------------------------\n");
			printf("\n1.��д        2.������ʾ\n0.��ʾ��/�˳�\n");
			scanf("%d", &op);
			if (op == 2) hint();
			if (op == 1)
			{
				printf("\n������д�����������ֵ:");
				scanf("%d%d%d%d", &x, &y, &z, &v);
				if (!S.original[x][y][z] && v == S.pattern[x][y][z])
				{
					printf("\n��д��ȷ!\n");
					S.original[x][y][z] = S.pattern[x][y][z];
					getchar(); getchar();
				}
				else {
					printf("\n�𰸴���\n");
					getchar(); getchar();
				}
			}
		}
		for (int i = 1; i <= 6; i++)
		{
			for (int j = 1; j <= 9; j++)
				printf("%3d", S.pattern[1][i][j]);
			printf("\n");
		}
		for (int i = 7; i <= 9; i++)
		{
			for (int j = 1; j <= 9; j++)
				printf("%3d", S.pattern[1][i][j]);
			for (int j = 4; j <= 9; j++)
				printf("%3d", S.pattern[2][i - 6][j]);
			printf("\n");
		}
		for (int i = 4; i <= 9; i++)
		{
			printf("                  ");
			for (int j = 1; j <= 9; j++)
				printf("%3d", S.pattern[2][i][j]);
			printf("\n");
		}
		printf("1.����һ��       0.�˳�\n");
		scanf("%d", &choice);
	}
}