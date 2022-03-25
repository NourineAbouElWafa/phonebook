#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
/*Sohayla Khaled Abouzeid 6851
  Nada Taher Elwazane 6876
  Nourine Mohamed Abou El Wafa 7152
  Farah Ismail Mohamed 7209
  Salma Mohamed Abd El-Karim 7251
*/
typedef struct
{
    int day;
    int month;
    int year;
} date;

typedef struct
{
    char last_name[100];
    char first_name[100];
    date DOB;
    char street_address[100];
    char phone_number[20];
    char email[100];
} contacts;

contacts c[200];
int maxstorage=200;
int i;
int count=0;
int found=0;
int indexs[50];
int counti;
char fn[50];

void loadfile()
{
    int flag=0;
    printf("Enter .txt file name\n");
    while(flag==0)
    {
        gets(fn);
        FILE *f1;
        strcat(fn,".txt");
        f1=fopen(fn,"r");
        if(f1!=NULL)
        {
            flag=1;
            while(!feof(f1))
            {
                fscanf(f1,"%[^,], %[^,], %d-%d-%d, %[^,],%[^,],%s\n",c[count].last_name, c[count].first_name,&c[count].DOB.day,
                       &c[count].DOB.month,&c[count].DOB.year, c[count].street_address, c[count].phone_number, c[count].email);
                count++;
            }
            fclose(f1);
            printf("Contacts are successfully read.\n\n");
        }
        else
        {
            printf("Error file is not found!\nPlease reenter .txt file name: ");
        }
    }
}
void saveFile()
{
    FILE *f1;
    f1=fopen(fn,"w");

    for(i=0; i<count; i++)
    {
        fprintf(f1,"%s,%s,%d-%d-%d,%s,%s,%s\n",c[i].last_name,c[i].first_name,c[i].DOB.day,c[i].DOB.month,c[i].DOB.year,c[i].street_address, c[i].phone_number, c[i].email);
    }
    fclose(f1);
}

int digitonly(int t)
{
    int z=0;

    for(i=0; i<strlen(c[t].phone_number); i++)
    {
        if(isdigit(c[t].phone_number[i]))
        {
            z++;
        }
    }
    if (z==strlen(c[t].phone_number))
        return 1;
    else
        return 0;



}
void phonevalidation(int t)
{
    if (digitonly(t))
    {
        if (strlen(c[t].phone_number)!=11)

        {
            printf("Invalid phone number\n");
            printf("Please reenter telephone NO.: ");
            scanf("%s",c[t].phone_number);
            phonevalidation(t);

        }
        else if (*c[t].phone_number!='0')
        {
            printf("Invalid phone number\n");
            printf("Please reenter telephone NO.: ");
            scanf("%s",c[t].phone_number);
            phonevalidation(t);
        }
        else if (c[t].phone_number[1]!='1')
        {
            printf("Invalid phone number\n");
            printf("Please reenter telephone NO.: ");
            scanf("%s",c[t].phone_number);
            phonevalidation(t);

        }
    }



    else
    {
        printf("Invalid phone number\n");
        printf("Please reenter telephone NO.: ");
        scanf("%s",c[count].phone_number);
        phonevalidation(t);

    }


}


void international(int t)
{
    if(digitonly(t))
    {
        if (strlen(c[t].phone_number)
                <9)
        {
            printf("Invalid international number\n");
            printf("Please reenter telephone NO.: + ");
            scanf("%s",c[t].phone_number);
            international(t);

        }
        else if (strlen(c[t].phone_number)>16)
        {
            printf("Invalid international number\n");
            printf("Please reenter telephone NO.: + ");
            scanf("%s",c[t].phone_number);
            international(t);


        }
    }
    else
    {


        printf("Invalid phone number\n");
        printf("Please reenter telephone NO.: + ");
        scanf("%s",c[t].phone_number);
        international(t);

    }


}

void landline(int t)
{
    if(digitonly(t))
    {
        if(strlen(c[t].phone_number)<5)
        {
            printf("Invalid landline number\n");
            printf("Please reenter telephone NO.: ");
            scanf("%s",c[t].phone_number);
            landline(t);

        }
        if (*c[t].phone_number!='0')
        {
            printf("Invalid landline number\n");
            printf("Please reenter telephone NO.: ");
            scanf("%s",c[t].phone_number);
            landline(t);
        }
        if(strlen(c[t].phone_number)>9)
        {
            printf("Invalid landline number\n");
            printf("Please reenter telephone NO.: ");
            scanf("%s",c[t].phone_number);
            landline(t);
        }
    }
    else
    {


        printf("Invalid phone number\n");
        printf("Please reenter telephone NO.: ");
        scanf("%s",c[t].phone_number);
        landline(t);


    }
}
void birthvalidation(int t)
{
    while(c[t].DOB.day>31||c[t].DOB.month>12||c[t].DOB.year<1900||c[t].DOB.year>2020)
    {
        printf("Invalid birth date\n");
        printf("Please reenter birthday day-month-year: ");
        scanf("%d-%d-%d",&c[t].DOB.day,&c[t].DOB.month,&c[t].DOB.year);
    }
}
void emailcheck(int t)
{
    int i=0,len;
    int at=-1;
    int dot=-1;
    int difference;
    int atflag=0;
    len=strlen(c[t].email);
    if(isalpha(c[t].email[i]))
    {
        for(i=0; i<len&&atflag<2; i++)
        {
            if(c[t].email[i]=='@')
            {
                at=i;
                atflag++;
            }
            if(c[t].email[i]=='.')
            {
                dot=i;
            }
        }
    }
    difference=dot-at;
    if(atflag>1||difference<2||at==0||dot==len-1||i==0||dot==-1||at==-1)
    {
        printf("Email invalid try again\n reenter Email: ");
        scanf("%s",c[t].email);
        emailcheck(t);
    }
}
void lstname_search()
{
    int i;
    counti=0;
    char querylstnm[100];
    printf("Please enter person's last name\n");
    scanf("%s",querylstnm);
    for(i=0; i<count; i++)
    {
        if(strcasecmp(c[i].last_name,querylstnm)==0)
        {
            printf("%d] First Name: %s\tAddress: %s \nEmail %s\tPhone Number: %s\n\n",counti+1,c[i].first_name,c[i].street_address,c[i].email,c[i].phone_number);
            indexs[counti]=i;
            counti++;
        }
    }
    if(counti==0)
    {
        int again;
        printf("Last name not found would you like to run another search?\n1.Yes\n0.No\n");
        scanf("%d",&again);
        if(again==1)
        {
            lstname_search();
        }
        else
            return;
    }
    else
        printf("%d result(s) was/were found\n",counti);

}

void searchflname()
{
    int i;
    counti=0;
    char querylstnm[100];
    char queryfstnm[100];
    printf("Please enter person's first and last name respectively\n");
    scanf("%s%s",queryfstnm,querylstnm);
    for(i=0; i<count; i++)
    {
        if(strcasecmp(c[i].last_name,querylstnm)==0)
        {
            if(strcasecmp(c[i].first_name,queryfstnm)==0)
            {
                indexs[counti]=i;

                printf("%d]\nFirst Name:%s\t\tLast Name:%s\nAddress: %s \nEmail %s\nPhone Number: %s\nBirthday: %d-%d-%d\n\n",counti+1,c[i].first_name,c[i].last_name,c[i].street_address,c[i].email,c[i].phone_number,c[i].DOB.day,c[i].DOB.month,c[i].DOB.year);
                counti++;
            }
        }
    }
}

void addData()
{
    if(count<=199)
    {

        printf("Enter the number of data you are adding: ");
        int n;
        scanf("%d",&n);
        i=0;
        char temp;
        int b;


        while(i<n)
        {
            printf("Enter last Name : ");
            scanf("%s",c[count].last_name);
            printf("Enter first Name : ");
            scanf("%s",c[count].first_name);
            printf("Do you want to enter:\n 1)local number\n 2)international number\n 3)landline\n");
            printf("Enter your choice:");
            scanf("%d",&b);
            while(b>3||b<1)
            {
                printf("Error please choose one of the given choices ");
                scanf("%d",&b);
            }
            if(b==1)
            {

                printf("Enter Telephone No. : ");

                scanf("%s",c[count].phone_number);
                phonevalidation(count);
            }
            else if(b==2)
            {

                printf("Enter Telephone No. : + ");

                scanf("%s",c[count].phone_number);
                international(count);
            }
            else
            {
                printf("Enter Telephone No. : ");

                scanf("%s",c[count].phone_number);
                landline(count);
            }




            printf("Enter Birthday day-month-year: ");
            scanf("%d-%d-%d",&c[count].DOB.day,&c[count].DOB.month,&c[count].DOB.year);
            birthvalidation(count);

            printf("Enter address: ");
            scanf("%c",&temp); // temp statement to clear buffer
            // fflush(stdin);
            gets(c[count].street_address);
            printf("Enter email : ");
            scanf("%s",c[count].email);
            emailcheck(count);

            i++;
            count++;
        }
    }
    else
    {
        printf("you can't add more data");
    }

}

void deleteData()
{
    int l;
    l=0;
    int m;
    int check;
    printf("which contact you would like to delete:\n");
    searchflname();

    if(counti!=0)
    {
        printf("Are you sure you want to delete this/these contact(s)?\n1.Yes\n0.No\n");
        scanf("%d",&check);
        if(check==1)
        {
            for(l=0; l<counti; l++)
            {
                for(m=indexs[l]-l; m<count-1; m++)
                {
                    strcpy(c[m].last_name,c[m+1].last_name);
                    strcpy(c[m].first_name,c[m+1].first_name);
                    strcpy(c[m].street_address,c[m+1].street_address);
                    strcpy(c[m].email,c[m+1].email);
                    c[m].DOB.day=c[m+1].DOB.day;
                    c[m].DOB.month=c[m+1].DOB.month;
                    c[m].DOB.year=c[m+1].DOB.year;
                    strcpy(c[m].phone_number,c[m+1].phone_number);
                }
                count--;

            }
        }
    }

    else
        printf("Not found");
}
void ModifyContact()
{
    lstname_search();
    int z,r,ch,t;
    if(counti==1)
        z=1;
    else
    {
        printf("Which contact would you like to modify?");
        scanf("%d",&z);
        while(z<0||z>counti)
        {
            printf("Error please choose from shown contacts!");
            scanf("%d",&z);
        }
    }
    r=indexs[z-1];
    printf("Do you want to change the last name?\n1.Yes\n0.No\n");
    scanf("%d",&ch);
    if(ch==1)
    {
        printf("Last Name: ");
        scanf("%s",c[r].last_name);
    }

    printf("Do you want to change the first name?\n1.Yes\n0.No\n");
    scanf("%d",&ch);
    if(ch==1)
    {
        printf("First Name: ");
        scanf("%s",c[r].first_name);
    }

    printf("Do you want to change the date of birth?\n1.Yes\n0.No\n");
    scanf("%d",&ch);

    if(ch==1)
    {
        printf("DOB(dd-mm-yyyy): ");
        scanf("%d-%d-%d",&c[r].DOB.day,&c[r].DOB.month,&c[r].DOB.year);

        birthvalidation(r);
    }

    printf("Do you want to change the address?\n1.Yes\n0.No\n");
    scanf("%d",&ch);
    if(ch==1)
    {
        printf("Street Address: ");
        getchar();
        gets(c[r].street_address);
    }

    printf("Do you want to change the phone number?\n1.Yes\n0.No\n");
    scanf("%d",&ch);
    if(ch==1)
    {
        printf("Do you want to enter:\n 1)local number\n 2)international number\n 3)landline\n");
        printf("Enter your choice:");
        scanf("%d",&t);
        while(t>3||t<1)
        {
            printf("Error please choose one of the given choices ");
            scanf("%d",&t);
        }
        if(t==1)
        {
            printf("Enter Telephone No. : ");
            scanf("%s",c[r].phone_number);
            phonevalidation(r);
        }
        else if(t==2)
        {
            printf("Enter Telephone No. :+ ");
            scanf("%s",c[r].phone_number);
            international(r);
        }
        else
        {
            printf("Enter Telephone No. : ");
            scanf("%s",c[r].phone_number);
            landline(r);
        }
    }

    printf("Do you want to change the email?\n1.Yes\n0.No\n");
    scanf("%d",&ch);
    if(ch==1)
    {
        printf("Email: ");
        scanf("%s",c[r].email);
        emailcheck(r);
    }
}
void sortByLname()
{
    int i,j;
    contacts temp;
    for (i = 1; i < count; i++)
        for (j = 0; j < count - i; j++)
        {
            if (strcmp(c[j].last_name, c[j + 1].last_name ) > 0)
            {
                temp = c[j];
                c[j] = c[j + 1];
                c[j + 1] = temp;
            }
        }
    printf(" Last Name\tFirst Name\tDate of Birth\t\t\tStreet Address      Phone Number\tEmail\n");
    for(i=0; i<count; i++)
    {
        printf("%10s\t%10s\t%d-%d-%d\t%30s\t%16s\t%s\n",c[i].last_name, c[i].first_name, c[i].DOB.day,c[i].DOB.month,c[i].DOB.year, c[i].street_address, c[i].phone_number, c[i].email);
    }
}
void sortbyDOB()
{
    int i;
    int pass;
    int  sorted = 0 ;
    contacts temp;
    for (pass=1; pass<count&&!sorted; pass++)
    {
        sorted = 1 ;
        for (i=0; i<count-pass ; i++ )
        {
            if(c[i+1].DOB.year<c[i].DOB.year)
            {
                temp=c[i];
                c[i]=c[i+1];
                c[i+1]=temp;
                sorted=0;

            }
            else if (c[i+1].DOB.year==c[i].DOB.year&&c[i+1].DOB.month<c[i].DOB.month)
            {
                temp=c[i];
                c[i]=c[i+1];
                c[i+1]=temp;
                sorted=0;

            }
            else if(c[i+1].DOB.year==c[i].DOB.year&&c[i+1].DOB.month==c[i].DOB.month&&c[i+1].DOB.day<c[i].DOB.day)
            {
                temp=c[i];
                c[i]=c[i+1];
                c[i+1]=temp;
                sorted=0;

            }
        }
    }
    printf(" Last Name\tFirst Name\tDate of Birth\t\t\tStreet Address      Phone Number\tEmail\n");
    for(i=0; i<count; i++)
    {
        printf("%10s\t%10s\t%d-%d-%d\t%30s\t%16s\t%s\n",c[i].last_name, c[i].first_name, c[i].DOB.day,c[i].DOB.month,c[i].DOB.year, c[i].street_address, c[i].phone_number, c[i].email);
    }
}


void print()
{
    int x;
    printf("if you want to print the callers sorted by last name please enter 1\nif you want to print the callers sorted by date of birth please enter 0\n");
    scanf("%d",&x);
    while(x>1||x<0)
    {
        printf("Error please choose one of the given choices ");
        scanf("%d",&x);
    }
    if(x==0)
    {
        sortbyDOB();
    }
    else
        sortByLname();
}

void subexit()
{
    int esc;
    printf("EXIT\n");
    printf("1.Save and exit\n");
    printf("2.Exit without saving\n");
    scanf("%d",&esc);
    if (esc==1)
    {
        saveFile();
        exit(1);
    }
    else if (esc==2)
    {
        exit(1);
    }
}

int main()
{
    loadfile();
    int x;
    while(1)
    {
        if(maxstorage-count<=10)
            printf("Warning you only have space for %d more contact(s)\n",maxstorage-count);

        printf("\nTELEPHONE DIRECTORY\n\n");
        printf("what do you want to do:\n");
        printf("1) Search for contact\n");
        printf("2) Add new contact\n");
        printf("3) Delete a contact\n");
        printf("4) Modify a contact\n");
        printf("5) Print contacts sorted \n");
        printf("6) Save\n");
        printf("7) Exit\n");
        printf("Enter your choice : ");
        fflush(stdin);
        scanf("%d",&x);
        if(x==1)
        {
            lstname_search();
        }
        else if(x==2)
        {
            addData();
        }
        else if(x==3)
        {
            deleteData();
        }
        else if(x==4)
        {
            ModifyContact();
        }
        else if(x==5)
        {
            print();
        }
        else if (x==6)
        {
            saveFile();
        }
        else if (x==7)
        {
            subexit();
            return 0;
        }
        else
            printf("Error!Please choose command from 1 to 7");
    }
    return 0;
}
