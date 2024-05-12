#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    int running = 1;
    long choice;
    while(running)
    {
        choice = menu(choice);
        switch(choice)
        {
            case 1:
                addFriend();
                break;
                
            case 2:
                removeFriend();
                break;
                
            case 3:
                showFriendlist();
                break;
                
            case 4:
                running = 0;
                break;
                
            default:
                printf("Please try again.\n");
                break;
        }
    }
    return 0;
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}
 
int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
 
    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}

long lireLong()
{
    char nombreTexte[100] = {0};

    if (lire(nombreTexte, 100))
    {
        return strtol(nombreTexte, NULL, 10);
    }
    else
    {
        return 0;
    }
}

long menu(long choice)
{
    printf("1 - Add friend\n2 - Remove Friend\n3 - Show Friendlist\n4 - exit\n\nEnter choice: ");
    choice = lireLong();
    return choice;
    
}

void addFriend()
{
    FILE* file = NULL;
    file = fopen("friend.list","a");
    if (file != NULL)
    {
        char friend[20];
        printf("Enter friend's name: ");
        fgets(friend,20, stdin);
        fseek(file, SEEK_END, SEEK_CUR);
        fputs(friend, file);
    }
    else
    {
        printf("Fichier est nul ou jsp bref ca marche pas\n");
    }
    fclose(file);
}

void removeFriend()
{
    showFriendlist();
    printf("Select friend you want to remove: ");
    long choice = 0;
    choice = lireLong();
    FILE* file = NULL;
    file = fopen("friend.list","r");
    FILE* file2 = NULL;
    file2 = fopen("replica.list", "w");
    char ch;
    int temp = 1;
    ch = getc(file);
    while (ch != EOF)
        {
            ch = getc(file);
            if (ch == '\n')
                temp++;
            if (temp != choice)
                {
                    putc(ch, file2);
                }
        }
    fclose(file);
    fclose(file2);
    remove("friend.list");
    rename("replica.list", "friend.list");
}

void showFriendlist()
{
    FILE* file = NULL;
    file = fopen("friend.list","r");
    if (file != NULL)
    {
        char string[20] = "";
        int i = 1;
        printf("Friendlist: \n");
        while(fgets(string, 20, file) != NULL)
        {
            printf("%d - %s",i ,string);
            i++;
        }
        printf("\n");
    }
    else
    {
        printf("Fichier est nul ou jsp bref ca marche pas\n");
    }
    fclose(file);
}
