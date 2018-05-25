#include "driver.h"

char putchar (char ch)
{
        SBUF0=ch;
	    while(!TI0);
	    TI0=0;

		return ch;
}

u8  Stringcmp(u8 *str1,u8 *str2)
{
	 u8  i=0; 
	  while(1)//*p1  !='\0'
	  {
		 
		 if(str1[i] != str2[i]) return ++i;
		 if(str1[i]=='\0' && str2[i]=='\0')return 0;
		 i++;
	  }
	 return -1;
}

u32   s2n(u8 *s)
{
   u8  i,buf;
   u32 n=0;   

   if(*s<'0'||*s>'9') return  -1; //参数检查

	for(i=0;i<10;i++,s++)
	{
		if(*s>='0'&&*s<='9')
	   {
		 buf=*s-0x30;
		 n *=10;
		 n +=buf;
	   }
	   else	  break;
	   
	 }
	if(i<10)  return  n;
	else  return  -1;

}

//从字符串ptr（是由空格符分开的几个单词构成，结尾必须是‘\0’）中找到第n个单词并
//放入buf中（末尾添‘\0’）返回为该单词长度
u8  getword(u8 *ptr,u8 *buf,u8 n)
{
	u8 i=0,j=1,k;

	u8 length=0;

	if(ptr==NULL ||buf==NULL ||n==0) return 0;//参数检查
	//计算可显示字符长度
	while(i<255) 
	{
	 if(ptr[i]<' '||ptr[i]>'~') break;
	 i++;
	};
	if(i>250) return 0;
	length=i;

	 //跳过开头的若干空格
	 for(i=0;i<length;i++)
	  {
		if(ptr[i]!=' ')		break;
	  }
	  if(i>length-1) return 0;
	//开始收索目标单词
	while(1)
	{ //找到目标单词
	  if(n==j)
	  {
	     for(k=0;ptr[i]>' '&&ptr[i]<'\x7f';k++,i++)
	   	 {  buf[k]=ptr[i];
		 }
		  buf[++k]='\0';
		  return  k;
	   }
	   else
	   {
		 //跳过一个单词
		   for(;i<length;i++)
		  {
			if(ptr[i]==' ')break;
		  }
		  if(i>length-1) return 0;

	   }
	  //跳过单词间的分个的若干空格
	   for(;i<length;i++)
	  {
		if(ptr[i]!=' ')break;
	  }
	  if(i>length-1) return 0;

	  j++;
	}
}




