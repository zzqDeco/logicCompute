#include <cstdio>
#include <stack>
#include <iostream>
#include <string>

using namespace std;

string str1,str2;

struct subPair
{
  int s,l;
}num[100010];

int size=0;

bool gitbit(int n,int i)
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
          char nowNum1=numberStack.top().first;
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
            char nowNum2=numberStack.top().first;
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
          char nowNum1=numberStack.top().first;
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
            char nowNum2=numberStack.top().first;
            pair<int,int> nowNum2Place=numberStack.top().second;
            numberStack.pop();
            numberStack.emplace('a',make_pair(nowNum2Place.first,nowNum1Place.second));
            num[++size].s=nowNum2Place.first;
            num[size].l=nowNum1Place.second;
          }
        }
        pair<int,int> nowCPlace=signalStack.top().second;
        num[++size].s=nowCPlace.first;
        num[size].l=j;
        signalStack.pop();
      }
    }
  }
  while(!signalStack.empty())
  {
    char nowSignal=signalStack.top().first;
    pair<int,int> nowSignalPlace=signalStack.top().second;
    signalStack.pop();
    char nowNum1=numberStack.top().first;
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
      char nowNum2=numberStack.top().first;
      pair<int,int> nowNum2Place=numberStack.top().second;
      numberStack.pop();
      numberStack.emplace('a',make_pair(nowNum2Place.first,nowNum1Place.second));
      num[++size].s=nowNum2Place.first;
      num[size].l=nowNum1Place.second;
    }
  }
  num[++size].s=0;
  num[size].l=(int)a.size()-1;
}

bool calc(int i,string a)
{
  stack<char> signalStack;
  stack<int> numberStack;
  for(int j=0;j<a.size();j++)
  {
    if(a[j]>='a'&&a[j]<='z')
    {
      numberStack.push(gitbit(a[j]-'a',i));
    }
    else
    {
      if(fst(a[j]))
      {
        while(!signalStack.empty()&&fst(signalStack.top())<fst(a[j])&&fst(signalStack.top()))
        {
          char nowSignal=signalStack.top();
          signalStack.pop();
          int nowNum1=numberStack.top();
          numberStack.pop();
          if(nowSignal=='!')
          {
            numberStack.push(!nowNum1);
          }
          if(nowSignal=='&')
          {
            int nowNum2=numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1&nowNum2);
          }
          if(nowSignal=='|')
          {
            int nowNum2=numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1|nowNum2);
          }
          if(nowSignal=='^')
          {
            int nowNum2=numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1^nowNum2);
          }
          if(nowSignal=='>')
          {
            int nowNum2=numberStack.top();
            numberStack.pop();
            numberStack.push((!nowNum2)|nowNum1);
          }
          if(nowSignal=='=')
          {
            int nowNum2=numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1==nowNum2);
          }
        }
        signalStack.push(a[j]);
      }
      else
      {
        if(a[j]=='(')
        {
          signalStack.push('(');
          continue;
        }
        while(!signalStack.empty()&&fst(signalStack.top()))
        {
          char nowSignal=signalStack.top();
          signalStack.pop();
          int nowNum1=numberStack.top();
          numberStack.pop();
          if(nowSignal=='!')
          {
            numberStack.push(!nowNum1);
          }
          if(nowSignal=='&')
          {
            int nowNum2=numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1&nowNum2);
          }
          if(nowSignal=='|')
          {
            int nowNum2=numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1|nowNum2);
          }
          if(nowSignal=='^')
          {
            int nowNum2=numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1^nowNum2);
          }
          if(nowSignal=='>')
          {
            int nowNum2=numberStack.top();
            numberStack.pop();
            numberStack.push((!nowNum2)|nowNum1);
          }
          if(nowSignal=='=')
          {
            int nowNum2=numberStack.top();
            numberStack.pop();
            numberStack.push(nowNum1==nowNum2);
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
    }
    if(nowSignal=='&')
    {
      int nowNum2=numberStack.top();
      numberStack.pop();
      numberStack.push(nowNum1&nowNum2);
    }
    if(nowSignal=='|')
    {
      int nowNum2=numberStack.top();
      numberStack.pop();
      numberStack.push(nowNum1|nowNum2);
    }
    if(nowSignal=='^')
    {
      int nowNum2=numberStack.top();
      numberStack.pop();
      numberStack.push(nowNum1^nowNum2);
    }
    if(nowSignal=='>')
    {
      int nowNum2=numberStack.top();
      numberStack.pop();
      numberStack.push((!nowNum2)|nowNum1);
    }
    if(nowSignal=='=')
    {
      int nowNum2=numberStack.top();
      numberStack.pop();
      numberStack.push(nowNum1==nowNum2);
    }
  }
  return numberStack.top();
}

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
  for(int i=0;i<n;i++) printf("%c ",'a'+i);
  size=0;
  init(str1);
  for(int i=1;i<=size;i++)
  {
    cout<<str1.substr(num[i].s,num[i].l-num[i].s+1);
  }
  size=0;
  init(str2);
  for(int i=1;i<=size;i++)
  {
    cout<<str2.substr(num[i].s,num[i].l-num[i].s+1);
  }
  for(int i=0;i<(1<<n);i++)
  {
    if(calc(i,str1)!=calc(i,str2))
    {
      printf("Not equal!");
      return 0;
    }
  }
  printf("Equal!");
}