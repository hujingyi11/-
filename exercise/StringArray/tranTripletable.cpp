#include <stdio.h>
#include <stdlib.h>
#define M 100
struct node{
    int i,j,v;
};

struct tripletable
{
    struct node S[M];
    int m,n,t;
};

struct tripletable * create()
{    int i;
    struct tripletable *head=(struct tripletable *)malloc(sizeof(struct tripletable));
    scanf("%d%d%d",&(head->m),&(head->n),&(head->t));
    for(i=0;i<head->t;i++)
        scanf("%d%d%d",&(head->S[i].i),&(head->S[i].j),&(head->S[i].v));
    return head;
}

void print(struct tripletable * head)
{
    int i;
    for(i=0;i<head->t;i++)
    printf("%d %d %d\n",(head->S[i].i),(head->S[i].j),(head->S[i].v));
}

struct tripletable * trans(struct tripletable *t1);
int main()
{ 
    struct tripletable * head,*t2;
    head=create();
    t2=trans(head);
    print(t2);
    return 0;
}

/* 璇峰湪杩欓噷濉啓绛旀 */
struct tripletable * trans(struct tripletable *t1){
    //鐭╅樀琛屾暟m銆佸垪鏁皀鍙婇潪闆跺厓绱犱釜鏁皌
    //闈為浂鍏冪礌鐨勮鏍囥€佸垪鏍囧拰鍊?//i,j,v
    struct node t2;
    int t;
    for(int i=0; i<t1->t; ++i){
        t=t1->S[i].i;
        t1->S[i].i = t1->S[i].j;
        t1->S[i].j = t;
    }
    for(int i=0; i<t1->t; ++i) {
        for(int j = i; j < t1->t; ++j){
            if(t1->S[i].i>t1->S[j].i) {
                t2 = t1->S[i];
                t1->S[i] = t1->S[j];
                t1->S[j] = t2;
            }
        }
    }
    for(int i=0; i<t1->t; ++i) {
        for(int j = i; j < t1->t; ++j){
            if(t1->S[i].j>t1->S[j].j&&t1->S[i].i == t1->S[j].i) {
                t2 = t1->S[i];
                t1->S[i] = t1->S[j];
                t1->S[j] = t2;
            }
        }
    }
    return t1;
}