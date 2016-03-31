//---------------------------------------------------------------------------


#pragma hdrstop

#include "Unit2.h"
 #include <fstream.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)

struct Cases{
string ans;
string Comb;
};     //Структура для комбинации ответов и результата этой комбинации

class Test
{
public:
string Question[MAX];
Cases Results[MAX];
ifstream in; //входящий поток данных
int num;
int var;
string fullres;
int curr;
int colv;
int alc;
int currkol;
public:
int answers[200];
Test(char*);
void Next() ; //Следующий вопрос теста
void Result() ; //Считывание комбинаций ответов
void Check() ;  //Сравнение ответов с комбинациями
};
Test::Test(char* Path)
{
in.open(Path);
in>>num;
in>>var;
colv=var;
curr=0;
currkol=0;
alc=0;
}  ;

void Test::Next()
{
curr++;
if(curr<num+1){
string ques;
int Nq;
string ques1;
for(int i=0;i<150;i++){
in>>ques1;
ques=ques+' '+ques1;
if(ques1.at(ques1.size()-1)=='?') break;
}
Nq=std::atoi( ques.substr(1,4).c_str());
currkol=std::atoi(ques.substr(5,3).c_str());
ques=ques.substr(8,ques.size());
Question[0]=ques;
for(int i=0;i<currkol;i++){
string currs;
string currs1;
for(int i=0;i<150;i++){
in>>currs1;
currs=currs+' '+currs1;
if(currs1.at(currs1.size()-1)=='.') break;
}
Question[i+1]=currs;
}
}else{
this->Result();
}
};

void Test::Result(){
for(int i=0;i<var;i++){
string currs;
string temp;
string currs1;
string currs2;
for(int s=0;s<150;s++){
in>>currs1;
currs=currs+' '+currs1;
if(currs1.at(currs1.size()-1)=='.'){

for(int j=0;j<150;j++){
in>>temp;
currs2=currs2+' '+temp;
if(currs2.at(currs2.size()-1)=='.')break;}
break;
} ;
}
Results[i].Comb=currs;
Results[i].ans=currs2.c_str();
}
this->Check();
};

void Test::Check(){
int otv=0;
int sp[MAX];
for(int i=0;i<MAX;i++)
sp[i]=0;

for(int i=0;i<var;i++){
sp[otv]=i;
bool a =false;
for(int j=0;j<Results[i].Comb.size();j++){
if(!a){
switch(Results[i].Comb.at(j)){
case '=':
  i=1;
  break;
case '<':
 i=2;
  break;
case '>':
  i=3;
  break;
}
a=!a;
}else{
switch(i){
case 1:
 if(!Results[i].Comb.at(j)==answers[(int)(j+1)/2]) sp[otv]=0;
  break;
case 2:
if(Results[i].Comb.at(j)<answers[(int)(j+1)/2]) sp[otv]=0;
  break;
case 3:
if(Results[i].Comb.at(j)>answers[(int)(j+1)/2]) sp[otv]=0;
  break;
}
}
}
otv++;
}

for(int i=0;i<otv;i++){
if(sp[i]>alc) {alc=sp[i];
fullres=Results[sp[i]].ans;
}}
};
