#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string.h>
#include<math.h>

using namespace std ;

struct spam
{
	char sp[200];
	int count;
};

struct good
{
	char go[200];
	int count;
};

struct test
{
	char txt[200];
	float prob;
};

void convert1(char c[],int i)
{
	int r,k;
	int ct=0;
	char d[10];
	while(i!=0)
	{
		r=i%10;
		ct++;
		d[ct]=48+r;
		i=i/10;
	}
	for(k=0;k<ct;k++)
	{
	c[k+1]=d[ct-k];
	}
	c[k+2]='\0';
}

void convert2(char z[],int i)
{
	int r,k;
	int ct=0;
	char d[10];
	while(i!=0)
	{
		r=i%10;
		ct++;
		d[ct]=48+r;
		i=i/10;
	}
	for(k=0;k<ct;k++)
	{
	z[k+1]=d[ct-k];
	}
	z[k+2]='\0';
}


void swap(struct test t[],int i)
{
	struct test temp;
	temp=t[i];
	{
		t[i].prob=t[i+1].prob;
		strcpy(t[i].txt,t[i+1].txt);		// swapping t[i] to t[i+1]
	}
	{
		t[i+1].prob=temp.prob;			// copying temp to t[i]
		strcpy(t[i+1].txt,temp.txt);
	}
}


float min(float a,float b)
{
	if(a<b)
	return a;
	else
	return b;
}

float max(float a,float b)
{
	if(a>b)
	return a;
	else
	return b;
}



int main()
{
	struct spam s[1000];
	struct good g[1000];
	struct test t[1000];
	int ngood=0, nbad=0 , k, i;
	int p=0,q=0;
	
	char c[10];		/*names of spam emails s0-s9*/
	c[0]='s';
	c[1]='0' ;
	c[2]='\0';

	char z[10];		/*names of good emails g0-g9*/
	z[0]='g';
	z[1]='0' ;
	z[2]='\0';

	
	ifstream fin;
	for(i=0;i<10;i++) 		/* reading 10 spam emails*/  
	{
		
//		cout << "Inside spam loop \n" ;				
		fin.open(c);
		char temp[200];
		while ( 1 )
		{
			fin>>temp;
//			cout << "Reading words \n" ;
			if(fin.eof()!=0)
			{
				goto l1;
			}
			for(k=0;k<nbad;k++)
			{
				p=0;
				if(strcmp(temp,s[k].sp)==0)
				{
					s[k].count++;
					p=1;
					goto l2;
				}
			}
			
			l2: if(p==0)
			{
				strcpy(s[k].sp,temp);
				s[k].count=1;
				nbad ++ ;
			}
		
		}
		l1: fin.close();
		convert1(c,i);
	}

	
	fin.close();
	
	for(int i=0;i<10;i++) 		/* reading 10 good emails*/  
	{
		char temp1[200];
		fin.open(z) ; 
		while(1)
		{
			fin>>temp1;
			
			if(fin.eof() != 0)
			{	
				goto l3;
			}
				
			for(k=0;k<ngood;k++) 
			{
				q=0;
				if(strcmp(temp1,g[k].go)==0)
				{
					g[k].count++;
					q=1;
					goto l4;
				}
			}
				
			l4: if(q==0)
			{
				strcpy(g[k].go,temp1);
				g[k].count=1;
				ngood ++ ;
			}
		
		}
		l3: 
		fin.close();		
		convert2(z,i);		
	}



	/* to calculate probability*/

	 char temp2[200];
	int ntest=0,b=0,a=0;		//b-> stores count of word in spam mail, a-> stores count of word in good mail
	float f1=1,f2=1,x,y,sum,pp,final;
	fin.open("t0");
	while(1)
	{
	//	cout<<"inside while"<<endl;
		l5:fin>>temp2;
		

		if(fin.eof()!=0)
		{
			goto l6;
		}

		for(i=0;i<ntest;i++)
		{
	//		cout<<"inside for1"<<endl;	
			if(strcmp(temp2,t[i].txt)==0)
			{
				goto l5;
			}
			
		}

		for(k=0;k<nbad;k++)
		{
	//		cout<<"inside for2"<<endl;
			if(strcmp(temp2,s[k].sp)==0)
			{
				b=s[k].count;
			break;
			}
		}
		
		for(k=0;k<ngood;k++)
		{
	//		cout<<"inside for3"<<endl;
			if(strcmp(temp2,g[k].go)==0)
			{
				a=g[k].count;
				a=a*2;
			break;
			}
		}

		if((a+b)>5)
		{
			x=(float)b/10.0;
			
			y=(float)a/10.0;
			
		//	cout<<x<<"\t"<<y<<"\t"<<a<<"\t"<<b<<endl;
			sum=(float)x/(x+y);
			pp=max(0.1,min(0.9,sum)); 		// probability lies between 0.1 and 0.9
			t[i].prob=pp;
			strcpy(t[i].txt,temp2);
			ntest++;
		}
	}
		

	
	
	
	l6: fin.close();
	
	for(i=1;i<ntest;i++)
	{
		for(int j=0;j<ntest-i;j++)
		{
			if(t[j].prob<t[j+1].prob)
			{
				swap(t,j);
			}
		}
	}




	
		
	int mm=15;
	if(ntest<15)
		mm=ntest;			
	
	for(i=0;i<mm;i++)
	{
		f1=f1*t[i].prob;
		f2=f2*(1-t[i].prob);
	}
	
	final=f1/(f1+f2);
	cout<<final<<endl;
	if(final>0.9)
	{
		cout<<"Mail is Spam"<<endl;
	}
		else
	{
		cout<<"mail is good"<<endl;
	}	



	return 0;
}
