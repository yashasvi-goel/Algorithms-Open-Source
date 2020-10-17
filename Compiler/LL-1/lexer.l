%{

char c[100];
int idx =0 ;
%}

%%

[a-z]+ {c[idx++]='i';}
[0-9]+ {c[idx++]='n';}
[(,),+,-,*,/] {c[idx++]=*yytext;}
    
%%
void yyerror(char *s) {
      fprintf(stderr, "line %d: yytext = %s.  Error msg: %s.\n", yylineno, yytext, s);
}

int yywrap(void) {
   return 1;
}

int main()
{
  yyin = fopen("lexinp.txt","r");
  yylex();
  c[idx++]='\0';
  printf("The modified string is %s",c);
FILE *fptr=fopen("lexout.txt","w");
int res=fputs(c,fptr);
if(res==EOF){
printf("faied\n");
}
fclose(fptr);
}
