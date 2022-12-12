#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define OK 1
#define ERROR 0
#define SUDOKU 1
#define SAT 0

typedef struct node           //��������
{
    int value;                //��������С��0��ʾ���ھ����еĴ��з�
    node* next;               //��һ����
} node;
typedef struct clause           //�����Ӿ�
{
    int num;                    //����Ӿ������ֵĸ���
    node* head;                 //ָ����һ������
    clause* next;              //ָ����һ������
} clause;
typedef struct sudproblem {     //��������
    int original[3][10][10];       //��¼ԭʼ��ֵ
    int pattern[3][10][10];        //0��ʾ�ڳ��Ķ����������ͬori
    int num;                    //��0����
}sud;
typedef int status;

int ABS(int a);                                                   //�������㺯��
int read();                                                       //���
status ReadCNF(clause*& cnf, int satORsudoku);                    //��ȡcnf�ļ�
void destroyClause(clause*& cnf);                                 //ɾ��SAT����
void removeClause(clause*& cnf, clause*& cl);                     //ɾ���Ӿ�
void removeNode(clause* cl, node*& nd);                           //ɾ������
status addClause(clause* cl, clause*& cnf);                       //���뵥�Ӿ�
bool isUnitClause(clause* cl);                                    //�Ӿ��ж��Ƿ�Ϊ���Ӿ�
void delelteSingleClause(clause* s, clause*& cnf);                //���Ӿ����
bool emptyClause(clause* cnf);                                    //�Ӿ��п�
void getForgery(clause*& forgery, clause* cnf);                   //��ȡ����
int getMaxBool(clause* cnf);                                      //ѡȡ���ִ������ı�Ԫ
int getMaxBool_2(clause* cnf);                   //ѡȡ�ܳ��ִ������ı�Ԫ
int getMaxBool_Sudoku(clause* cnf);              //���������ѡ����ִ������ı�Ԫ���㷨
int getNextBool_3(clause* cnf);                  //ѡȡ�ڶ��Ӿ��ܳ��ִ������ı�Ԫ
int getNextBool_4(clause* cnf);                  //ѡȡ�ڶ��Ӿ���ִ������ı�Ԫ
bool DPLL(clause*& cnf, int* v, int satORsudoku);                 //DPLL�㷨
status printCNF(int s, int* v, double t);                         //����res�ļ�

int VarTrans(int f, int i, int j, int n);      //����ת�����������������ת��Ϊ��Ȼ˳����룬
                                                       //���������i��j����������n
void SudPlay();                                        //��������
void Sudcreate();                                      //����һ�������������
status Candig( int x, int y, int z);                   //�ж��Ƿ�Ϊ�����ڶ�
void hint();                                           //������ʾ
void CreateCnf();                                      //����cnf�ļ�
