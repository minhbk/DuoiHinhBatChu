#include <stdio.h>
#include <string.h>
#include <stdlib.h>



// char* decode(char* str) {
//    int i = 0;
 
//    while (str[i] != '\0') {
//       str[i] = str[i] + 30;  // Subtract 30 From Charcter
//       i++;
//    }
//    return (str);
// }


int check_username(char s1[80])
{
	char s[80];
	char username1[80];
	char *p; 
	FILE *f1;
	char password[30];
	if((f1=fopen("password.txt","r+"))==NULL)
    {
      g_print("File server error!!\n");
      return 0;
    }
	while(fgets(s,80,f1)!=NULL)
	{
		p=strtok(s,"\t"); //user va pass phan cach boi dau tab
		strcpy(username1,p);
		if(strcmp(s1,username1)==0)
		{
			p=strtok(NULL,"\n");
			//strcpy(password,decode(p));
			return 1;
		}
	}
	fclose(f1);
	return 0;
}