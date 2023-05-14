//code to push and pop into stack and print in the files
#include<stdio.h>
#include<stdlib.h>
int top=-1;
int arr[100];
int random_arr[100];
FILE *fptr,*fptr1,*fptr5,*fptr3,*fptr4;
void push(FILE *fptr4)
{char str[4]="push";
char t='-';
if(top>100)
{
    printf("stack overflow"); //if stack is full then overflow condition is printed
}
int a;
fscanf(fptr4,"%d",&a);
fptr=fopen("file_stack.txt","w+");
 //opening the file to print the operations
fptr3=fopen("file_pop.txt","a");
fprintf(fptr3,"%c",t);
fptr5=fopen("file_print.txt","a");
fprintf(fptr5,"%s\n",str);

top=top+1; //updating the pointer
arr[top]=a;
fptr1=fopen("file_push.txt","a");
fprintf(fptr1,"%d",arr[top]); //printing the pushed elements
for(int i=0;i<=top;i++)
{
    fprintf(fptr,"%d ",arr[i]);  //printing the elements present in the stack
}
fclose(fptr1);

fclose(fptr5);
fclose(fptr);
}
int pop()
{
int a;
char str[4]="pop";
a=arr[top];
if(top<0)
{
    printf("stack underflow");  //if stack is empty then underflow message is printed
}
fptr3=fopen("file_pop.txt","a");
fprintf(fptr3,"%d",a);  //printimg the poped elements
fptr5=fopen("file_print.txt","a");
fprintf(fptr5,"%s\n",str);
fptr1=fopen("file_push.txt","a");
fprintf(fptr1,"%c",'-');


top=top-1;
fptr=fopen("file_stack.txt","w+");
for(int i=0;i<=top;i++)
{
    fprintf(fptr,"%d ",arr[i]);   //printing the elements in the stack
}
fclose(fptr5);
fclose(fptr3);
fclose(fptr);

}
void random(int a,int b,int n)  //generating the random numbers in given range
{int s,count=0;

fptr4=fopen("file_random.txt","w");

    for(int i=0;count<n;i++)
    {
        s=rand()%10;
        if(s>=a&&s<=b)
        {count++;
        printf("l");
           fprintf(fptr4,"%d ",s);

        }
    }
    fclose(fptr4);

}

int main()
{int a,b,n,j;
printf("enter the range");
scanf("%d",&a);
scanf("%d",&b);
printf("enter the number of elements");
scanf("%d",&n);
random(a,b,n);

fptr4=fopen("file_random.txt","r");
while(1)
{printf("enter 1:push 2:pop");
scanf("%d",&j);
if(j==1)
{
  push(fptr4);
}
else if(j==2)
{
    pop();
}

}

fclose(fptr4);
}
