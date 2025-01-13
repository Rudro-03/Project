#include<stdio.h>
#include<string.h>

typedef struct
{
    char name[50];
    int acc_num;
    float balance;
}Account;

void account();
void deposit();
void withdraw();
void check();
int main()
{
    for(;;)
    {
        int x;
        printf("\n\n*** Bank Management System ***");
        printf("\n1. Create Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Check Balance");
        printf("\n5. Exit");
        printf("\nEnter Your Choice: ");
        scanf("%d",&x);
        getchar();

        switch(x)
        {
            case 1:
            account();

            break;
        case 2:
            deposit();

            break;
        case 3:
            withdraw();

            break;
        case 4:
            check();

            break;
        case 5:
           {
              printf("\nService Closed\n");
              return 0;
            break;
           }


        default:
            printf("Invalid choice.\n");

            break;
        }


    }

}
void account()
{
    Account x;
    FILE *file=fopen("acc.dat","ab+");
    if(file==NULL)
    {
        printf("Account creation unsuccessful!!");
        return;
    }
    printf("\nEnter Your name: ");
    fgets(x.name,sizeof(x.name),stdin);
    int id = strcspn(x.name, "\n");
    if (x.name[id] == '\n')
    {
        x.name[id] = '\0';
    }
    printf("\nEnter Account Number: ");
    scanf("%d",&x.acc_num);
    x.balance=0.00;

    fwrite(&x,sizeof(x),1,file);
    fclose(file);
    printf("\nCongratulation!! Account creation successful.");
}
void deposit()
{
    FILE *file=fopen("acc.dat","rb+");
    if(file==NULL)
    {
        printf("Account creation unsuccessful!!");
        return;
    }
    int numb;
    float cash_in;
    Account in;
    printf("\nEnter Account Number: ");
    scanf("%d",&numb);
    printf("Enter the amount of deposit money: ");
    scanf("%f",&cash_in);

    while(fread(&in, sizeof(in),1,file))
    {
        if(in.acc_num==numb)
        {
            in.balance+=cash_in;
            fseek(file,-sizeof(in),SEEK_CUR);
            fwrite(&in,sizeof(in),1,file);
            fclose(file);
            printf("Successfully deposited %.2f tk in your account",cash_in);
            return;

        }
    }
    fclose(file);
    printf("Account does not exit.");



}
void withdraw()
{
    FILE *file=fopen("acc.dat","rb+");
    if(file==NULL)
    {
        printf("Account creation unsuccessful!!");
        return;
    }
    int numb;
    float cash_out;
    Account out;
    printf("Enter your account number: ");
    scanf("%d",&numb);
    printf("Enter the amount to withdraw money: ");
    scanf("%f",&cash_out);

    while(fread(&out,sizeof(out),1,file))
    {
        if(out.acc_num==numb)
        {
            if(out.balance>=cash_out)
            {
                out.balance-=cash_out;
                fseek(file,-sizeof(out),SEEK_CUR);
                fwrite(&out,sizeof(out),1,file);
                printf("Successfully withdrawn %.2f tk",cash_out);
            }
            else
            {
                printf("Insufficient Balance!");
            }
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("Withdrawal unsuccessful");
}
void check()
{

    FILE *file=fopen("acc.dat","rb");
    if(file==NULL)
    {
        printf("Account creation unsuccessful!!");
        return;
    }
    int numb;
    Account read;
    printf("\nEnter Account Number: ");
    scanf("%d",&numb);

    while(fread(&read,sizeof(read),1,file))
    {
        if(read.acc_num==numb)
        {
            printf("\nYour current balance is %.2ftk",read.balance);
            fclose(file);
            return;
        }
    }
    printf("Your account does not exist.");



}
