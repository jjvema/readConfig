#include <stdio.h>
#include <string.h>

#define MAXLEN 80
#define CONFIG_FILE "/home/bbox/etc/bbox.conf"

char value[MAXLEN];

/*
 * trim: get rid of trailing and leading whitespace...
 *       ...including the annoying "\n" from fgets()
 */

char *trim (char * s){
  /* Initialize start, end pointers */
  char *s1 = s, *s2 = &s[strlen (s) - 1];

  /* Trim and delimit right side */
  while ( (isspace (*s2)) && (s2 >= s1) )
    s2--;
  *(s2+1) = '\0';

  /* Trim left side */
  while ( (isspace (*s1)) && (s1 < s2) )
    s1++;

  /* Copy finished string */
  strcpy (s, s1);
  return s;
}

/*
 * Get value from config file
 */
 
char *getValue(char *name){
    char *s, buff[256];
    
    FILE *fp = fopen (CONFIG_FILE, "r"); 
    
    if (fp == NULL){
        return;
    }

    while ((s = fgets (buff, sizeof buff, fp)) != NULL){
        if (buff[0] == '\n' || buff[0] == '#')
        continue;

        s = strtok (buff, "=");
        
        if (s==NULL){
            continue;
        }else{
            if(!strcmp(name, s )){
                s = strtok (NULL, "=");
                if (s==NULL)
                    continue;
                else{
                    strncpy (value, s, MAXLEN);
                    trim (value);
                    fclose(fp);
                    return(value);
                }
            }else{
                continue;
            }   
        }
    }
    fclose(fp);
    return(0);   
}
int main(void){
    
   char *value;
   
   value = getValue("INCREMENT");
   
   printf("El valor es: %s\n", value);
        
    return 0;
}
