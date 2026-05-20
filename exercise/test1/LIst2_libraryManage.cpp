#include<iostream>
#include<iomanip>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;

struct Book{
    string name;
    string id;
    double price; 
};

typedef struct Lnode{
    Book data;
    struct Lnode* next;
    int length = 0;
}Lnode,*Linklist;

Status InitList(Linklist &L){
    L = new Lnode;
    L->next = NULL;
    return OK;
}

void output(Linklist L){
    Lnode *p;
    p=L->next;
    while(p){
        cout<<fixed<<setprecision(2)<<p->data.id<<' '<<p->data.name<<' '<<p->data.price<<endl;
        p=p->next;
    }
}

Status create_library(Linklist &L){
    InitList(L);
    Lnode *p,*q;
    q = L;
    while(1){
        p=new Lnode;
        cin>>p->data.id>>p->data.name>>p->data.price;
        if(p->data.id == "0"&&p->data.name=="0"&&p->data.price == 0){
            break;
        }
        ++L->length;
        p->next = NULL;
        q->next = p;
        q = p;
    }
    return OK;
}

void sort_price(Linklist &L){//前插法将每次循环最小值插入
    Lnode *p,*q;
    Book t;
    q = L->next;

    while(q){    
        p = q->next;
        while(p){
            if(p->data.price>q->data.price){
                t = p->data;
                p->data = q->data;
                q->data = t;
            }
            p = p->next;
        }
        q = q->next;
    }
}

void control_price(Linklist &L){
    double averPrice=0;
    Lnode *p;
    p = L->next;
    while(p){
        averPrice += p->data.price;
        p=p->next;
    }
    averPrice/=L->length;
    p=L->next;
    while(p){
        if(p->data.price<averPrice)
            p->data.price*=1.2;
        else 
            p->data.price*=1.1;
        p = p->next;
    }
    output(L);
}

Status reversed_save(Linklist &L){
    InitList(L);
    Lnode *p;
    while(1){
        p = new Lnode;
        cin>>p->data.id>>p->data.name>>p->data.price;
        if(p->data.id == "0"&& p->data.name == "0" && p->data.price == 0){
            return OK;
        }
        p->next = L->next;
        L->next = p;
    }
    output(L);
    return OK;
}

void most_expensive(Linklist L){
    Lnode *p;
    p=L->next;
    double max;
    max = 0;
    while(p){
        if(p->data.price > max)
            max = p->data.price;
        p = p->next;
    }
    p = L->next;
    while(p){
        if(p->data.price == max)
            cout<<fixed<<setprecision(2)<<p->data.id<<" "<<p->data.name<<" "<<p->data.price<<endl;
        p = p->next;
    }
}

void Insert(Linklist &L){
    int n;
    cin>>n;
    Lnode *s,*p;
    s = new Lnode;
    cin>>s->data.id>>s->data.name>>s->data.price;
    p=L->next;
    for(int i = 1;i<n-1;++i){
        p=p->next;
    }
    s->next = p->next;
    p->next = s;
}

void delete_book(Linklist &L,int n){
    Lnode *p;
    p=L;
    for(int i = 0;i<n-1;++i){
        p=p->next;
    }
    Lnode *temp = p->next;
    p->next = temp->next;
    delete temp;
    L->length--;
}

void remove_duplication(Linklist &L){
    string nn;
    int qn = 2,pn;
    Lnode *p,*q;
    q=L->next;
    while(q){
        pn = qn;
        p = q;
        nn = p->data.id;
        while(p->next){
            if(p->next->data.id == nn)
                delete_book(L,pn);
            else {
                ++pn;
                p=p->next;
            }
        }
        q = q->next;
        ++qn;    
    }
}

int main(){
    cout<<"1：图书信息表的创建和输出"<<endl;
    cout<<"2：图书信息表的排序（价格降序）"<<endl;
    cout<<"3：图书信息表的修改（根据平均价格调整）"<<endl;
    cout<<"4：图书信息表的逆序存储"<<endl;
    cout<<"5：查找最贵的图书"<<endl;
    cout<<"6：新图书入库（插入操作）"<<endl;
    cout<<"7：旧图书出库（删除操作）"<<endl;
    cout<<"8：图书去重（保留首次出现的书号）"<<endl;
    Linklist L;
    int n;
    cin>>n;
    switch(n){
        case 1:
            create_library(L);
            cout<<L->length<<endl;
            output(L);
            break;
        case 2:
            create_library(L);
            sort_price(L);
            output(L);
            break;
        case 3:
            create_library(L);
            control_price(L);
            break;
        case 4:
            reversed_save(L);
            output(L);
            break;
        case 5:
            create_library(L);
            most_expensive(L);
            break;
        case 6:
            create_library(L);
            Insert(L);
            output(L);
            break;
        case 7:
            create_library(L);
            int m;
            cin>>m;
            delete_book(L,m);
            output(L);
            break;
        case 8:
            create_library(L);
            remove_duplication(L);
            output(L);
            break;
    }
    return 0;
}