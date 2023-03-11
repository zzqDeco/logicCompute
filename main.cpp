#include <cstdio>
#include <stack>
#include <iostream>

using namespace std;

string str1,str2;

string ans1[100010],ans2[100010];

struct subPair
{
  int s,l;
}num[100010];

int size=0,size1=0,size2=0;

bool getBit(int n, int i)
{
  return (i>>n)%2;
}

int fst(char i)
{
  if(i=='!') return 1;
  if(i=='&') return 2;
  if(i=='^') return 3;
  if(i=='|') return 4;
  if(i=='>') return 5;
  if(i=='=') return 6;
  return 0;
}

void init(string a)
{
  stack<pair<char,pair<int,int>>> signalStack;
  stack<pair<char,pair<int,int>>> numberStack;
  for(int j=0;j<a.size();j++)
  {
    if(a[j]>='a'&&a[j]<='z')
    {
      numberStack.emplace('a',make_pair(j,j));
    }
    else
    {
      if(fst(a[j]))
      {
        while(!signalStack.empty()&&fst(signalStack.top().first)<fst(a[j])&&fst(signalStack.top().first))
        {
          char nowSignal=signalStack.top().first;
          pair<int,int> nowSignalPlace=signalStack.top().second;
          signalStack.pop();
          pair<int,int> nowNum1Place=numberStack.top().second;
          numberStack.pop();
          if(nowSignal=='!')
          {
            numberStack.emplace('a',make_pair(nowSignalPlace.first,nowNum1Place.second));
            num[++size].s=nowSignalPlace.first;
            num[size].l=nowNum1Place.second;
          }
          if(nowSignal=='&'||nowSignal=='|'||nowSignal=='^'||nowSignal=='>'||nowSignal=='=')
          {
            pair<int,int> nowNum2Place=numberStack.top().second;
            numberStack.pop();
            numberStack.emplace('a',make_pair(nowNum2Place.first,nowNum1Place.second));
            num[++size].s=nowNum2Place.first;
            num[size].l=nowNum1Place.second;
          }
        }
        signalStack.emplace(a[j],make_pair(j,j));
      }
      else
      {
        if(a[j]=='(')
        {
          signalStack.emplace('(',make_pair(j,j));
          continue;
        }
        while(!signalStack.empty()&&fst(signalStack.top().first))
        {
          char nowSignal=signalStack.top().first;
          pair<int,int> nowSignalPlace=signalStack.top().second;
          signalStack.pop();
          pair<int,int> nowNum1Place=numberStack.top().second;
          numberStack.pop();
          if(nowSignal=='!')
          {
            numberStack.emplace('a',make_pair(nowSignalPlace.first,nowNum1Place.second));
            num[++size].s=nowSignalPlace.first;
            num[size].l=nowNum1Place.second;
          }
          if(nowSignal=='&'||nowSignal=='|'||nowSignal=='^'||nowSignal=='>'||nowSignal=='=')
          {
            pair<int,int> nowNum2Place=numberStack.top().second;
            numberStack.pop();
            numberStack.emplace('a',make_pair(nowNum2Place.first,nowNum1Place.second));
            num[++size].s=nowNum2Place.first;
            num[size].l=nowNum1Place.second;
          }
        }
        pair<char,pair<int,int>> now=numberStack.top();
        numberStack.pop();
        numberStack.emplace('a',make_pair(signalStack.top().second.first,now.second.second));
        signalStack.pop();
      }
    }
  }
  while(!signalStack.empty())
  {
    char nowSignal=signalStack.top().first;
    pair<int,int> nowSignalPlace=signalStack.top().second;
    signalStack.pop();
    pair<int,int> nowNum1Place=numberStack.top().second;
    numberStack.pop();
    if(nowSignal=='!')
    {
      numberStack.emplace('a',make_pair(nowSignalPlace.first,nowNum1Place.second));
      num[++size].s=nowSignalPlace.first;
      num[size].l=nowNum1Place.second;
    }
    if(nowSignal=='&'||nowSignal=='|'||nowSignal=='^'||nowSignal=='>'||nowSignal=='=')
    {
      pair<int,int> nowNum2Place=numberStack.top().second;
      numberStack.pop();
      numberStack.emplace('a',make_pair(nowNum2Place.first,nowNum1Place.second));
      num[++size].s=nowNum2Place.first;
      num[size].l=nowNum1Place.second;
    }
  }
}

bool calc(int i,const string& a)
{
  stack<char> signalStack;
  stack<int> numberStack;
  for(char j:a)
  {
    if(j>='a'&&j<='z')
    {
      numberStack.push(getBit(j - 'a', i));
    }
    else
    {
      if(fst(j))
      {
        while(!signalStack.empty()&&fst(signalStack.top())<fst(j)&&fst(signalStack.top()))
        {
          char nowSignal=signalStack.top();
          signalStack.pop();
          int nowNum1=numberStack.top();
          numberStack.pop();
          if(nowSignal=='!')
          {
            numberStack.push(!nowNum1);
            printf("%d\t\t",!nowNum1);
          }
          if(nowSignal=='&')
          {
            int nowNum2=numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1&nowNum2);
            printf("%d\t\t",nowNum1&nowNum2);
          }
          if(nowSignal=='|')
          {
            int nowNum2=numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1|nowNum2);
            printf("%d\t\t",nowNum1|nowNum2);
          }
          if(nowSignal=='^')
          {
            int nowNum2=numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1^nowNum2);
            printf("%d\t\t",nowNum1^nowNum2);
          }
          if(nowSignal=='>')
          {
            int nowNum2=numberStack.top();
            numberStack.pop();
            numberStack.push((!nowNum2)|nowNum1);
            printf("%d\t\t",(!nowNum2)|nowNum1);
          }
          if(nowSignal=='=')
          {
            int nowNum2=numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1==nowNum2);
            printf("%d\t\t",nowNum2==nowNum1);
          }
        }
        signalStack.push(j);
      }
      else
      {
        if(j=='(')
        {
          signalStack.push('(');
          continue;
        }
        while(!signalStack.empty()&&fst(signalStack.top()))
        {
          char nowSignal = signalStack.top();
          signalStack.pop();
          int nowNum1 = numberStack.top();
          numberStack.pop();
          if (nowSignal == '!')
          {
            numberStack.push(!nowNum1);
            printf("%d\t\t", !nowNum1);
          }
          if (nowSignal == '&')
          {
            int nowNum2 = numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1 & nowNum2);
            printf("%d\t\t", nowNum1 & nowNum2);
          }
          if (nowSignal == '|')
          {
            int nowNum2 = numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1 | nowNum2);
            printf("%d\t\t", nowNum1 | nowNum2);
          }
          if (nowSignal == '^')
          {
            int nowNum2 = numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1 ^ nowNum2);
            printf("%d\t\t", nowNum1 ^ nowNum2);
          }
          if (nowSignal == '>')
          {
            int nowNum2 = numberStack.top();
            numberStack.pop();
            numberStack.push((!nowNum2) | nowNum1);
            printf("%d\t\t", (!nowNum2) | nowNum1);
          }
          if (nowSignal == '=')
          {
            int nowNum2 = numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1 == nowNum2);
            printf("%d\t\t", nowNum2 == nowNum1);
          }
        }
        signalStack.pop();
      }
    }
  }
  while(!signalStack.empty())
  {
    char nowSignal=signalStack.top();
    signalStack.pop();
    int nowNum1=numberStack.top();
    numberStack.pop();
    if(nowSignal=='!')
    {
      numberStack.push(!nowNum1);
      printf("%d\t\t",!nowNum1);
    }
    if(nowSignal=='&')
    {
      int nowNum2=numberStack.top();
      numberStack.pop();
      numberStack.push(nowNum1&nowNum2);
      printf("%d\t\t",nowNum1&nowNum2);
    }
    if(nowSignal=='|')
    {
      int nowNum2=numberStack.top();
      numberStack.pop();
      numberStack.push(nowNum1|nowNum2);
      printf("%d\t\t",nowNum1|nowNum2);
    }
    if(nowSignal=='^')
    {
      int nowNum2=numberStack.top();
      numberStack.pop();
      numberStack.push(nowNum1^nowNum2);
      printf("%d\t\t",nowNum1^nowNum2);
    }
    if(nowSignal=='>')
    {
      int nowNum2=numberStack.top();
      numberStack.pop();
      numberStack.push((!nowNum2)|nowNum1);
      printf("%d\t\t",(!nowNum2)|nowNum1);
    }
    if(nowSignal=='=')
    {
      int nowNum2=numberStack.top();
      numberStack.pop();
      numberStack.push(nowNum1==nowNum2);
      printf("%d\t\t",nowNum2==nowNum1);
    }
  }
  return numberStack.top();
}

/*
 * 主函数一大堆花里胡哨的格式化输入输出
 */

int main()
{
  int n;
  cout<<"Please enter the number of propositional variables (the propositional variables appearing in the formula are numbered from 'a'):";
  cin>>n;
  cout<<"\"not a\" denoted by \"!a\"\n"
        "\"a and b\" denoted by \"a&b\"\n"
        "\"a or b\" denoted by \"a|b\"\n"
        "\"a xor b\" denoted by \"a^b\"\n"
        "\"if a then b\" denoted by \"a>b\"\n"
        "\"a iif b\" denoted by \"a=b\"\n"
        "You can use \"()\" to render the precedence in the formula"<<endl;
  cout<<"Please enter the first formula:";
  cin>>str1;
  cout<<"Please enter the second formula:";
  cin>>str2;
  for(int i=0;i<n;i++) printf("%c\t\t",'a'+i);
  size=0;
  init(str1);
  for(int i=1;i<=size;i++)
  {
    ans1[++size1]=str1.substr(num[i].s,num[i].l-num[i].s+1);
    cout<<"f1("<<i<<")\t";
  }
  size=0;
  init(str2);
  for(int i=1;i<=size;i++)
  {
    ans2[++size2]=str2.substr(num[i].s,num[i].l-num[i].s+1);
    cout<<"f2("<<i<<")\t";
  }
  printf("\n");
  bool flag=false;
  for(int i=0;i<(1<<n);i++)
  {
    for(int j=1;j<=n;j++)
    {
      printf("%d\t\t", getBit(j - 1, i));
    }
    if(calc(i,str1)!=calc(i,str2))
    {
      flag=true;
    }
    printf("\n");
  }
  if(flag) printf("Not equal!\n");
  else printf("Equal!\n");
  while(true)
  {
    int id,ip;
    printf(R"(Please choose the formula that you wanna see:(press "i j" to get fi(j) or press "0 0" to exit))");
    scanf("%d%d",&id,&ip);
    if(id==0&&ip==0) exit(0);
    if(id==1)
    {
      if(ip>size1)
      {
        printf("Error!");
        continue;
      }
      printf("f1(%d)=",ip);
      cout<<ans1[ip]<<endl;
    }
    else if(id==2)
    {
      if(ip>size2)
      {
        printf("Error!");
        continue;
      }
      printf("f2(%d)=",ip);
      cout<<ans2[ip]<<endl;
    }
    else
    {
      printf("Error!");
      continue;
    }
  }
}