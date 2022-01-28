/* This is a restaurant billing software. It can generate invoices for the customer and show the breakup of the amount to be paid 
by the customer. */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items{
    char item[30];
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[50];
    int numofitems;
    struct items itm[50];
};

//functions to generate the bills
void generatebillheader(char name[50], char date[50])
{
    printf("\n\n");
    printf("\t      CSBS Restaurant");
    printf("\n\t   -------------------");
    printf("\nDate: %s", date);
    printf("\nInvoice to: %s", name);
    printf("\n");
    printf("\n");
    printf("Items: \t\t");
    printf("Qty:\t\t");
    printf("Total: \t\t");
    printf("\n---------------------------------------");
    printf("\n\n");
}

void generatebillbody(char item[30],int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty*price);
    printf("\n");

}

void generatebillfooter(float total)
{
    printf("\n");
    float dis= 0.1*total;
    float nettotal= total-dis;
    float cgst=0.009*nettotal,grandtotal=nettotal+2*cgst;
    printf("-------------------------------------\n");
    printf("Sub total\t\t\t%.2f", total);
    printf("'\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t--------");
    printf("\nNet Total\t\t\t%.2f", nettotal);
    printf("\nCGST @9%s\t\t\t%.2f","%", cgst);
    printf("\nSGST @9%s\t\t\t\t%.2f","%", cgst);
    printf("\n------------------------------------\n");
    printf("\nGrand Total\t\t\t%.2f", grandtotal);
    printf("\n-------------------------------------\n");
    printf("\n\nTHANK YOU, WE LOOK FORWARD TO SEEING YOU AGAIN!\n\n");
}

int main() 
{
    float total;
    int opt,n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y', contFlag = 'y';
    char name[50];
FILE *fp;
         //dashboard
while(contFlag == 'y' )
    {
        system("cls");
        float total = 0;
        int invoicefound = 0;
        printf("\t============CSBS RESTAURANT============");                          
        printf("\n\nPlease select your preferred operation");
        printf("\n\n1. Generate Invoice");
        printf("\n2. Show all Invoices");
        printf("\n3. Search Invoice");
        printf("\n4. Exit");

        printf("\n\nYour choice: \t");
        scanf("%d",&opt);
        fgetc(stdin);
        switch(opt)
            {                                                                                                             
                case 1:                                                                                                                  
                        system("cls");
                        printf("\nPlease enter the name of the customer :\t");
                        fgets(ord.customer,50,stdin);
                        ord.customer[strlen(ord.customer)-1] = 0;
                        strcpy(ord.date,__DATE__);
                        printf("\nPlease enter the number of items : \t");
                        scanf("%d",&n);
                        ord.numofitems = n;
                        for(int i=0; i<n; i++) 
                        {                                                                                                
                            fgetc(stdin);                                                                                                      
                            printf("\n\n");                    
                            printf("Please enter the item %d:\t",i+1);
                            fgets(ord.itm[i].item,20,stdin);
                            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
                            printf("Please enter the quantity : \t");
                            scanf("%d",&ord.itm[i].qty);
                            printf("Please enter the unit price: \t");
                            scanf("%f",&ord.itm[i].price);
                            total += ord.itm[i].qty * ord.itm[i].price;                                                             
                        }      

                        generatebillheader(ord.customer,ord.date);                                                         
                        for(int i=0;i<ord.numofitems;i++)
                            {     
                                generatebillbody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
                            }
                        generatebillfooter(total);
                        printf("\nDo you want to save the invoice [y/n] :\t");
                        scanf("%s",&saveBill);

                        if(saveBill == 'y')
                            {
                                fp =  fopen("RestaurantBill.dat","a+");
                                fwrite(&ord,sizeof(struct orders),1,fp);
                                if(fwrite != 0)
                                    printf("\nSuccessfully saved");
                                else
                                    printf("\nError saving");
                                fclose(fp);
                            }
                        break;

                case 2:
                    system("cls");
                    fp = fopen("RestaurantBill.dat","r");
                    printf("\n   **Your Previous Invoices**\n");
                    while(fread(&order,sizeof(struct orders),1,fp))
                        {
                            float tot = 0;
                            generatebillheader(order.customer,order.date);
                            for(int i=0;i<order.numofitems;i++)
                                {
                                    generatebillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                                    tot+=order.itm[i].qty * order.itm[i].price;
                                }
                        generatebillfooter(tot);
                        }
                    fclose(fp);
                    break;

                    case 3:
                        printf("\n Enter the name of the customer:\t");
                        fgetc(stdin);
                        fgets(name ,50,stdin);
                        name[strlen(name)-1] = 0;
                        system("cls");
                        fp = fopen("RestaurantBill.dat","r");
                        printf("\n   **Invoice of %s**\n",name);
                        while(fread(&order,sizeof(struct orders),1,fp))
                            {
                                float tot = 0;
                                if(!strcmp(order.customer,name))
                                    {
                                        generatebillheader(order.customer,order.date);
                                        for(int i=0;i<order.numofitems;i++)
                                            {
                                                generatebillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                                                tot+=order.itm[i].qty * order.itm[i].price;
                                            }
                                        generatebillfooter(tot);
                                        invoicefound = 1;
                                    }
                            }
                            if(!invoicefound)
                                {
                                    printf("Sorry the invoice for %s does not exists", name);
                                }
                                fclose(fp);
                                break;

                    case 4:
                        printf("\n\t\t Bye Bye :)\n\n");
                        exit(0);
                        break;
                        default:
                        printf("Sorry invalid option"); 
                        break;
            } 
            printf("\nDo you want to perform another operation?");
            scanf("%s", &contFlag);
        } 
    printf("\n\n");
    return 0;
}