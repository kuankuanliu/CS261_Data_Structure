/* CS261- Assignment 1A - Question 3
   Name: Kuan-Ting Liu, Parthiveshwar Sharma Pagidimarri
   Date: 2022/10/01
   Solution description:
    Follow the coding description, first we transfer all non alphabets word to '_', and transfer all alphabets to lowercase words. Then we can do the CamelCase function
*/

#include <stdio.h>
#include <stdlib.h>

char toUpperCase(char ch)
{
  // Convert ch to upper case, assuming it is in lower case currently
    ch=ch-'a'+'A';
    return ch;
}

char toLowerCase(char ch)
{
  // Convert ch to lower case, assuming it is in upper case currently
    ch=ch-'A'+'a';
    return ch;
}

int stringLength(char s[])
{
   // Return the length of the string
    int i=0;
    while (s[i]!='\0'){
    i++;
    }
    return i;
}


/*suuport function for remove underscores in CamelCase*/
void removeUnderscore(char* word, int location){
    int length=stringLength(word);
    for(int i=location; i<length; i++){
    word[i]=word[i+1];
    }
    word[length-1]='\0';
}

void camelCase(char* word)
{
    // Convert to camelCase
    int length=stringLength(word);
    for (int i=1; i<length; i++){
    if (word[i-1]=='_' && word[i]!='_'){
        word[i]=toUpperCase(word[i]);
    }
    }
    int j=0;
    while (word[j]!='\0'){
    if (word[j]=='_'){
        removeUnderscore(word, j);
        j--;
    }
    j++;
    }
    
}

int main()
{
    char word[100];
    // Read the string from the keyboard
    printf("%s\n", "Please enter a string:\n");
    fgets(word, 100, stdin);
    int length=stringLength(word);
    /*Transfer all the non alphebet word to '_' and 'lower case letters'*/
    for (int i=0; i<length; i++){
    if (word[i]<'A' || (word[i]>'Z'&& word[i]<'a') || word[i]>'z'){
        word[i]='_';
    }
    else if (word[i]>='A' && word[i]<='Z'){
        word[i]=toLowerCase(word[i]);
    }
    }
    /*Remove all '_' in the beginning of the word*/
    int j=0;
    while (word[0]=='_'){
    removeUnderscore(word, 0);
    j++;
    }
    length=length-j;
    /*Remove all '_' at the end of the word*/
    while (word[length-1]=='_'){
    word[length-1]='\0';
    length--;
    /* Remove duplicate '_'*/
    }
    for (int i = 0; i <= length; i++)
    {
        while ((word[i] == '_'&& word[i + 1] == '_' &&word[i]!='\0'))
        {
            for (j = i; j <= length; j++)
            {
                if (j == length)
                    word[j] = '\0';
                else
                    word[j] = word[j + 1];
            }
        }
    }
    printf("after 1st convert = ");

    for(int i = 0; i<length; i++){
        printf("%c", word[i]);
    }
    printf("\n");
 
    
    /*Validate if the input string consists of at least two groups of
     *lowercase alphabetic characters*/
    
    
    
    int underscoreCount=0;
    for (int k=0; k<length; k++){
    if (word[k]=='_'){
        underscoreCount++;
    }
    }

    // Call camelCase
    /*If the input string is valid*/
    if (underscoreCount>0){
    /*Call camelCase*/
    camelCase(word);
    // Print the new string
    
    printf("Final result = ");
    for(int i = 0; i<length; i++){
        printf("%c", word[i]);
    }
    printf("\n");
    }

    /*If the input string is invalid*/
    else{
    printf("%s\n", "invalid input string!");
    }
    
    return 0;
}



