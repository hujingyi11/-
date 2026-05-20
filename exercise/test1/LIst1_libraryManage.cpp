#include<iostream>
#include<iomanip>
using namespace std;

#define OK 1
#define ERROR 0
#define overflow -2
typedef int Status;
#define MAXSIZE 100

struct Book{
    string name; 
    string id;
    double price;
};

typedef struct{
    Book *elem;
    int length;
}Sqlist;

Status InitSqlist(Sqlist &L){
    L.elem = new Book[MAXSIZE];
    if(!L.elem) exit(overflow);
    L.length = 0;
    return OK;
}

void output(Sqlist L){
    cout<<L.length<<endl;
    for(int i=0;i<L.length;++i){
        cout<<fixed<<setprecision(2)<<L.elem[i].id<<" "<<L.elem[i].name<<" "<<L.elem[i].price<<endl;
    }
}

Status create_library(Sqlist &L){
    InitSqlist(L);
    int index = 0;
    while(1){
        string elem1,elem2;
        double elem3;
        cin>>elem1>>elem2>>elem3;
        if(elem1 == "0"&&elem2 == "0"&&elem3 == 0){
            return OK;
        }
        L.elem[index].id = elem1;
        L.elem[index].name = elem2;
        L.elem[index].price = elem3;
        ++L.length;
        ++index;
    }
    if(L.length>MAXSIZE) return overflow;
    return OK;
}

void sort_price(Sqlist &L){
    Book t;
    for(int i=0;i<L.length;++i){
        for(int j = i;j<L.length;++j){
            if(L.elem[i].price<L.elem[j].price){
                t=L.elem[j];                
                L.elem[j] = L.elem[i];
                L.elem[i] = t;
            }
        }
    }
}

void control_price(Sqlist &L){
    double averPrice=0;
    for(int i=0;i<L.length;++i){
        averPrice+=L.elem[i].price;
    }
    averPrice/=L.length;
    for(int i=0;i<L.length;++i){
        if(L.elem[i].price<averPrice) L.elem[i].price*=1.2;
        else L.elem[i].price*=1.1;
    }
    output(L);
}

Status reversed_save(Sqlist &L){
    Book p;
    for(int i= 0;i<L.length/2;++i){
        p = L.elem[i];
        L.elem[i] = L.elem[L.length -1-i];
        L.elem[L.length-1-i] = p;
    }
    return OK;
}

void most_expensive(Sqlist L){
    sort_price(L);
    int i=0;
    cout<<L.elem[i].id<<" "<<L.elem[i].name<<" "<<L.elem[i].price<<endl;
    while(L.elem[i].price == L.elem[i+1].price){
        cout<<L.elem[i+1].id<<" "<<L.elem[i+1].name<<" "<<L.elem[i+1].price<<endl;
        ++i;
    }
}

void Insert(Sqlist &L){
    int n;
    Book newbook;
    cin>>n>>newbook.id>>newbook.name>>newbook.price;
    ++L.length;
    for(int i=L.length;i>=n;--i){
        L.elem[i] = L.elem[i-1];
    }
    L.elem[n-1] = newbook;
} 

void delete_book(Sqlist &L,int n){
    for(int i=n-1;i<L.length;++i){
        L.elem[i] = L.elem[i+1];
    }
    --L.length;
}

void remove_duplication(Sqlist &L){
    int i=0;
    while(i<L.length-1){
            int j = i + 1;
            while(j<L.length){
                if(L.elem[i].id == L.elem[j].id){
                    delete_book(L,j+1);                              
                }else j++;
            }       
        ++i;
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
    Sqlist L;
    int n;
    cin>>n;
    switch(n){
        case 1:
            create_library(L);
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
            create_library(L);
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
}


