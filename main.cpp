#include <cstdio>
#include <stack>
#include <iostream>
#include <string>

using namespace std;

string str1,str2;

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
  for(int i=0;i<(1<<n);i++)
  {
    if(!(calc(i,str1)==calc(i,str2)))
    {
      printf("Not equal!");
      return 0;
    }
  }
  printf("Equal!");
}