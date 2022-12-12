#include"define.h"
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

int inf = 1061109567;
int boolCnt, clauseCnt, sumOfAns, branchRule;//��Ԫ���� �Ӿ�����  ѡ�����
char fileName[200];  //cnf�ļ��ļ���
int *ans=NULL; //�������
sud S; //��������
clause* CNF=NULL; //SAT����
int main()
{
    
    int op = 1, op1 = 1, op2 = 1, flag_cnf, difficulty;
    clock_t start, finish;
    double time;
    bool res;
    while (op)
    {
        system("cls");
        printf("                               �˵�                                  \n");
        printf("------------------------------------------------------------------------\n");
        printf("                     1.DPLL     2.˫����    0.�˳�                       \n");
        printf("------------------------------------------------------------------------\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            flag_cnf = 1, op1 = 1;
            while (op1)
            {
                system("cls");
                printf("-------------------------------------------------------------------------\n");
                printf("1.���ļ�  2.��ӡ�ļ�  3.DPLL  4.�����������   0.����\n");
                printf("-------------------------------------------------------------------------\n");
                scanf("%d", &op1);
                switch (op1)
                {
                case 1:
                    printf("����������ļ���:");
                    scanf("%s", fileName);
                    if (ReadCNF(CNF, SAT) == OK)
                        flag_cnf = 0, printf("cnf�ļ���ȡ��ϣ�\n");
                    else
                        printf("cnf�ļ���ȡʧ��!\n");
                    getchar(), getchar();
                    break;
                case 2:
                    if (flag_cnf)
                        printf("��δδ��ȡcnf�ļ�!\n ");
                    else
                    {
                        printf("�ļ����������Ӿ䣺\n");
                        printf("___________________________\n");
                        for (clause* lp = CNF; lp; lp = lp->next)
                        {
                            for (node* tp = lp->head; tp; tp = tp->next)
                                printf("%d ", tp->value);
                            printf("\n");
                        }
                    }
                    getchar(), getchar();
                    break;
                case 3:
                    if (flag_cnf)
                        printf("��δδ��ȡcnf�ļ�!\n ");
                    else
                    {   branchRule = 1;
                        ans = (int*)malloc(sizeof(int) * (boolCnt + 1));
                        for (int i = 0; i <= boolCnt; i++)
                            ans[i] = 1;
                        start = clock();
                        res = DPLL(CNF, ans, SAT);
                        finish = clock();
                        if (!res)
                            printf("�������㣡\n");
                        else
                        {
                            printf("�����㣡\n");
                        }
                        time = (double)(finish - start);
                        printf("DPLL�����Ż�����ʱ%lfms\n", time );
                        destroyClause(CNF);
                        ReadCNF(CNF, SAT);
                        branchRule = 4; 
                        for (int i = 0; i <= boolCnt; i++)
                            ans[i] = 1;
                        start = clock();
                        res = DPLL(CNF, ans, SAT);
                        finish = clock();
                        time = (double)(finish - start);
                        printf("DPLL�����Ż�ǰ��ʱ%lfms\n", time );
                    }
                    getchar(), getchar();
                    break;
                case 4:
                    for (int i = 1; i <= boolCnt; i++)
                    {
                        if (ans[i])
                            printf("%d ", i);
                        else
                            printf("%d ", -i);
                    }
                case 5:
                    if (flag_cnf)
                        printf("��δδ��ȡcnf�ļ�!\n ");
                    else
                    {
                        if (printCNF(res, ans, time))
                            printf("����ѱ���\n");
                        else
                            printf("�������ʧ��!\n");
                    }
                    getchar(), getchar();
                    break;
                case 0:
                    break;
                }
            }
            break;
        case 2:
             op2 = 1;
            while (op2)
            {
                system("cls");
                printf("------------------------------------------------------------------------\n");
                printf("                   1.������Ϸ   0.����                            \n");
                printf("------------------------------------------------------------------------\n");
                scanf("%d", &op2);
                switch (op2)
                {
                case 1:
                    SudPlay();
                    getchar();
                    break;
                default:
                    break;
                }
            }
            break;
        case 0:
            break;
        }
    }
    return 0;
}