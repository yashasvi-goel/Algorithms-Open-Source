%{

char c[100];
int idx =0 ;
%}

%%

[a-z]+ {c[idx++]='i';}
[0-9]+ {c[idx++]='n';}
"(" {c[idx++]='(';}
")" {c[idx++]=')';}
"+" {c[idx++]='+';}
"-" {c[idx++]='-';}
"*" {c[idx++]='*';}
"/" {c[idx++]='/';}
    
%%

int main()
{
  yyin = fopen("lexinp.txt","r");
  yylex();
  c[idx++]='\0';
  printf("The modified string is %s",c);
FILE *fptr=fopen("file2.txt","w");
int res=fputs(c,fptr);
if(res==EOF){
printf("faied\n");
}
fclose(fptr);
}
