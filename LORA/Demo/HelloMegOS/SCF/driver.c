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

   if(*s<'0'||*s>'9') return  -1; //�������

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

//���ַ���ptr�����ɿո���ֿ��ļ������ʹ��ɣ���β�����ǡ�\0�������ҵ���n�����ʲ�
//����buf�У�ĩβ��\0��������Ϊ�õ��ʳ���
u8  getword(u8 *ptr,u8 *buf,u8 n)
{
	u8 i=0,j=1,k;

	u8 length=0;

	if(ptr==NULL ||buf==NULL ||n==0) return 0;//�������
	//�������ʾ�ַ�����
	while(i<255) 
	{
	 if(ptr[i]<' '||ptr[i]>'~') break;
	 i++;
	};
	if(i>250) return 0;
	length=i;

	 //������ͷ�����ɿո�
	 for(i=0;i<length;i++)
	  {
		if(ptr[i]!=' ')		break;
	  }
	  if(i>length-1) return 0;
	//��ʼ����Ŀ�굥��
	while(1)
	{ //�ҵ�Ŀ�굥��
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
		 //����һ������
		   for(;i<length;i++)
		  {
			if(ptr[i]==' ')break;
		  }
		  if(i>length-1) return 0;

	   }
	  //�������ʼ�ķָ������ɿո�
	   for(;i<length;i++)
	  {
		if(ptr[i]!=' ')break;
	  }
	  if(i>length-1) return 0;

	  j++;
	}
}




