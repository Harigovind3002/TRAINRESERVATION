#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>//Libraries

typedef struct
{
	char name[50];
	int train_num;
	int num_of_seats;
	long long int phnno;
}pd;
struct login
{
  	char name[30],pass[30];
};
int n;
void reservation(void);	//reservation function						
void viewdetails(void);	//function to view details of train				
void cancel(void);	//cancellation function							
void printticket(char name[],long long int,int,int,float,int);//Generating ticket
void specifictrain(int);//data of each train					
float charge(int,int,int);	//Calculation of charges			
void login(void);//function for login
void reg(void);//function for registration
void mainmenu(void);//main menu

int main()
{
    printf("\n============================");
    printf("\n WELCOME TO CLICK AND BOOK");
    printf("\n============================");
    printf("\n\n1.LOGIN\t\t2.REGISTER");
    printf("\n\n\nENTER YOUR CHOICE: ");
    scanf("%d",&n);
    switch(n)
    {
   	    case 1: 
     	printf("\n\n");
    	login();
        break;
        case 2: 
        printf("\n\n");
        reg();
        default:
        printf("\n\n");
        printf("\nWRONG CHOICE");
        main();
        break;
    }
    return 0;
}

void reg()
{
    FILE *fp;
    struct login l;
    fp=fopen("login.txt","w");//opening login.txt file
    printf("\n========================");
    printf("\n      REGISTRARTION");
    printf("\n========================");
    printf("\n\nUSER ID:  ");
    scanf("%s",l.name);
    fflush(stdin);
    printf("\nPASSWORD:  ");
    scanf("%s",l.pass);
    printf("\n\n<<ENTER TO PROCEED>>");
    getch();
    fwrite(&l,sizeof(l),1,fp);
    fclose(fp);   
    printf("\n\nACCOUNT SUCCESSFULLY CREATED");
    printf("\n\nGO TO LOGIN PAGE\n\n");
    printf(">PRESS 1 FOR YES\n\n> PRESS 2 FOR NO\n\n");
    scanf("%d",&n);
    switch(n)
        {
            case 1: 
            login();
            break;
            case 2:  
            printf("\nTHANK YOU FOR REGISTERING");
            exit(0);
            break;
        }  
}  

void login()
{
    FILE *fp;
    char c,name[30],pass[30];
    fp=fopen("login.txt","r");
    printf("\n================");
    printf("\n     LOGIN");
    printf("\n================");
    struct login l;
    printf("\n\nUSER ID:  ");
    scanf("%s",name);
    fflush(stdin);
    printf("\nPASSWORD: ");
    scanf("%s",pass);
    while(fread(&l,sizeof(l),1,fp))
        {
            if(strcmp(name,l.name)==0 && strcmp(pass,l.pass)==0)
            {   
               mainmenu();
            }
            else if(strcmp(name,l.name)==0&&strcmp(pass,l.pass)!=0)
            {
                printf("\n\nWRONG PASSWORD!!");
                printf("\n\n<<PRESS 'Y' TO RE_LOGIN)");
                if(getch()=='y'||getch()=='Y')
                login();
            }
            else if(strcmp(name,l.name)!=0)
            {
            	printf("\n\nNOT AN EXISTING USER\nPRESS ENTER TO REGISTER\n");
                if(getch()==10)
                printf("\n\n");
                reg();
            }
        }
    fclose(fp);
    getch();
}
void mainmenu()
{
	int menu_choice;
	start:
	printf("\n==============================\n");
	printf("         MAIN MENU");
	printf("\n==============================");
	printf("\n1>> Book Ticket");
	printf("\n------------------------");
	printf("\n2>> View All Available Trains");
	printf("\n------------------------");
	printf("\n3>> Cancel Reservation");
	printf("\n------------------------");
	printf("\n4>> Exit");
	printf("\n------------------------");
	printf("\n\n-->");
	scanf("%d",&menu_choice);
	switch(menu_choice)
	{
		case 1:
			reservation();		
			break;
		case 2:
			viewdetails();
			printf("\n\n<<Press any key to go to Main Menu>>");
			getch();
			break;
		case 3:
			cancel();
			getch();
			break;
		case 4:
			printf("\nTHANK YOU!!");
			exit(0);
		default:
			printf("\nInvalid choice");
	}
	printf("\n\n");
	goto start;
}

void viewdetails(void)
{
	printf("\n\n");
   	printf("---------------------------------------------------------------------------------------------");	
	printf("\nTr.No\tNAME\t\t\tDESTINATIONS\t\t\t CHARGES\t\tTIME\n");
	printf("\t\t\t\t\t\t\t\t(FC/SC/SL.C)\n");
	printf("----------------------------------------------------------------------------------------------");
	printf("\n1001\tDURANTO EXPRESS\t\tHYDERABAD TO CHENNAI\t\tRs.800/600/400\t\t9AM");
	printf("\n1002\tDURANTO EXPRESS\t\tCHENNAI TO HYDERABAD\t\tRs.800/600/400\t\t12PM");
	printf("\n1003\tSHATABDI EXPRESS\tCHENNAI TO TRIVANDRUM\t\tRs.900/700/500\t\t8AM");
	printf("\n1004\tSHATABDI EXPRESS\tTRIVANDRUM TO CHENNAI\t\tRs.900/700/500\t\t11AM");
	printf("\n1005\tHUMSAFAR EXPRESS\tTRIVANDRUM TO BANGLORE\t\tRs.700/500/300\t\t7AM");
	printf("\n1006\tHUMSAFAR EXPRESS\tBANGLORE TO TRIVANDRUM\t\tRs.700/500/300\t\t9.30AM");
    printf("\n1007\tTEJAS EXPRESS\t\tBANGLORE TO MUMBAI\t\tRs.850/650/450\t\t1PM");	
  	printf("\n1008\tTEJAS EXPRESS\t\tMUMBAI TO BANGLORE\t\tRs.850/650/450\t\t4PM");
    printf("\n1009\tRAJADHANI EXPRESS\tMUMBAI TO VIZAG\t\t\tRs.950/750/550\t\t3.35PM");
    printf("\n1010\tRAJADHANI EXPRESS\tVIZAG TO MUMBAI\t\t\tRs.950/750/550\t\t4.15PM");  
    
}

void reservation(void)
{
	char confirm;
	int i=0,seatclass;
	float charges;
	pd passdetails;
	FILE *fp;
	fp=fopen("seats_reserved.txt","a");
	printf("\n\n");
	printf("\nEnter Your Name:> ");
	fflush(stdin);//clear the output buffer of the stream
	gets(passdetails.name);
	printf("\nEnter Number of seats:> ");
	scanf("%d",&passdetails.num_of_seats);
	printf("\nEnter Your Phone Number:> ");
	scanf("%lld",&passdetails.phnno);
	printf("\n\n>>Press Enter To View Available Trains<< ");
	getch();
	printf("\n\n");
	viewdetails();
	start1:
	printf("\n\nEnter train number:> ");
	scanf("%d",&passdetails.train_num);
	printf("\n\nEnter The Seat Class(1.First Class 2.Second Class 3.Sleeper Class):> ");
	scanf("%d",&seatclass);
	if(passdetails.train_num>=1001 && passdetails.train_num<=1010)
	{
		charges=charge(passdetails.train_num,passdetails.num_of_seats,seatclass);//function return charges
		printticket(passdetails.name,passdetails.phnno,passdetails.num_of_seats,passdetails.train_num,charges,seatclass);		
	}
	else
	{
		printf("\nInvalid train Number! Enter again--> ");
		goto start1;
	}
	    fwrite(&passdetails,sizeof(pd),1,fp);
		printf("\n\n==================");
		printf("\n Reservation Done\n");
		printf("==================");
		printf("\nPress any key to go back to Main menu");
		fclose(fp);
		getch();
}


float charge(int train_num,int num_of_seats,int seatclass)
{
	if (train_num==1001)
	{
		if(seatclass==1)
		{
			return(800.0*num_of_seats);
		}
	    else if(seatclass==2)
	    {
	    	return(600.0*num_of_seats);
		}
		else if(seatclass==3)
		{
			return(400.0*num_of_seats);
		}
	}
	if (train_num==1002)
	{
		if(seatclass==1)
		{
			return(800.0*num_of_seats);
		}
	    else if(seatclass==2)
	    {
	    	return(600.0*num_of_seats);
		}
		else if(seatclass==3)
		{
			return(400.0*num_of_seats);
		}
	}
	if (train_num==1003)
	{
		if(seatclass==1)
		{
			return(900.0*num_of_seats);
		}
	    else if(seatclass==2)
	    {
	    	return(700.0*num_of_seats);
		}
		else if(seatclass==3)
		{
			return(500.0*num_of_seats);
		}
		
	}
	if (train_num==1004)
	{
		if(seatclass==1)
		{
			return(900.0*num_of_seats);
		}
	    else if(seatclass==2)
	    {
	    	return(700.0*num_of_seats);
		}
		else if(seatclass==3)
		{
			return(500.0*num_of_seats);
		}
	}
	if (train_num==1005)
	{
		if(seatclass==1)
		{
			return(700.0*num_of_seats);
		}
	    else if(seatclass==2)
	    {
	    	return(500.0*num_of_seats);
		}
		else if(seatclass==3)
		{
			return(300.0*num_of_seats);
		}
	}
	if (train_num==1006)
	{
		if(seatclass==1)
		{
			return(700.0*num_of_seats);
		}
	    else if(seatclass==2)
	    {
	    	return(500.0*num_of_seats);
		}
		else if(seatclass==3)
		{
			return(300.0*num_of_seats);
		}
	}
	if (train_num==1007)
	{
		if(seatclass==1)
		{
			return(850.0*num_of_seats);
		}
	    else if(seatclass==2)
	    {
	    	return(650.0*num_of_seats);
		}
		else if(seatclass==3)
		{
			return(450.0*num_of_seats);
		}
	}
	if (train_num==1008)
	{
		if(seatclass==1)
		{
			return(850.0*num_of_seats);
		}
	    else if(seatclass==2)
	    {
	    	return(650.0*num_of_seats);
		}
		else if(seatclass==3)
		{
			return(450.0*num_of_seats);
		}
	}
	if (train_num==1009)
	{
		if(seatclass==1)
		{
			return(950.0*num_of_seats);
		}
	    else if(seatclass==2)
	    {
	    	return(750.0*num_of_seats);
		}
		else if(seatclass==3)
		{
			return(550.0*num_of_seats);
		}
	}
	if (train_num==1010)
	{
     	if(seatclass==1)
		{
			return(950.0*num_of_seats);
		}
	    else if(seatclass==2)
	    {
	    	return(750.0*num_of_seats);
		}
		else if(seatclass==3)
		{
			return(550.0*num_of_seats);
		}
	}
}
void printticket(char name[],long long int phnno,int num_of_seats,int train_num,float charges,int seatclass)
{
	int amt;
	printf("\n<<PRESS ANY KEY TO PROCEED TO PAYMENT>>\n");
	getch();
	payment:
	printf("\nTOTAL AMOUNT:%.2f\n",charges);
	printf("\nENTER THE AMOUNT TO BE PAID:");
	scanf("%d",&amt);
	if(amt==charges)
	{
		printf("\nPAYMENT SUCCESSFULL!!");
		printf("\n\n");
		printf("-------------------\n");
		printf("\tTICKET\n");
		printf("-------------------\n\n");
		printf("Name:\t\t\t%s",name);
		printf("\nPhone Number:\t\t%lld",phnno);
		printf("\nNumber Of Seats:\t%d",num_of_seats);
		printf("\nTrain Number:\t\t%d",train_num);
		if(seatclass==1)
		printf("\nSeat Class:\t\tFirst Class");
		else if(seatclass==2)
		printf("\nSeat Class:\t\tSecond Class");
		else if(seatclass==3)
		printf("\nSeat Class:\t\tSleeper Class");
		specifictrain(train_num);
		printf("\nCharges:\t\t%.2f",charges);
	}
	else
	{
		printf("\nPAYMENT UNSUCCESSFULL!!\n");
		goto payment;
		
	}
}

void specifictrain(int train_num)
{
	if (train_num==1001)
	{
		printf("\nTrain:\t\t\tDuranto Express");
		printf("\nDestination:\t\tHyderabad to Chennai");
		printf("\nDeparture:\t\t9AM ");
	}
	if (train_num==1002)
	{
		printf("\nTrain:\t\t\tDuranto Express");
		printf("\nDestination:\t\tChennai to Hyderabad");
		printf("\nDeparture:\t\t12PM");
	}
	if (train_num==1003)
	{
		printf("\nTrain:\t\t\tShatabdi Express");
		printf("\nDestination:\t\tChennai to Trivandrum");
		printf("\nDeparture:\t\t8AM");
	}
	if (train_num==1004)
	{
		printf("\nTrain:\t\t\tShatabdi Express");
		printf("\nDestination:\t\tTrivandrum to Chennai");
		printf("\nDeparture:\t\t11AM");
	}
	if (train_num==1005)
	{
		printf("\nTrain:\t\t\tHumsafar Express");
		printf("\nDestination:\t\tTrivandrum to Banglore");
		printf("\nDeparture:\t\t7AM");
	}
	if (train_num==1006)
	{
		printf("\ntrain:\t\t\tHumsafar Express");
		printf("\nDestination:\t\tBanglore to Trivandrum");
		printf("\nDeparture:\t\t9.30AM ");
	}
	if (train_num==1007)
	{
		printf("\ntrain:\t\t\tTejas Express");
		printf("\nDestination:\t\tBanglore to Mumbai");
		printf("\nDeparture:\t\t1PM ");
	}
	if (train_num==1008)
	{
		printf("\ntrain:\t\t\tTejas Express");
		printf("\n Destination:\t\tMumbai to Banglore");
		printf("\nDeparture:\t\t4PM ");		
	}
	if (train_num==1009)
	{
		printf("\ntrain:\t\t\tRajadhani Express");
		printf("\nDestination:\t\tMumbai to Vizag");
		printf("\nDeparture:\t\t3.35PM");
	}
	if (train_num==1010)
	{
		printf("\ntrain:\t\t\tRajadhani Express");
		printf("\nDestination:\t\tVizag to Mumbai");
		printf("\nDeparture:\t\t4.15PM");
	}
	
}

void cancel(void)   
{
   pd passdetails;
   FILE *fp,*fp1;
   long long int phnno,found=0;
   fp=fopen("seats_reserved.txt","r");
   fp1=fopen("temp.txt","w");//creating a temporary file
   printf("\nENTER YOUR PHONE NUMBER:");
   scanf("%lld",&phnno);
   while(fread(&passdetails,sizeof(pd),1,fp))
   {
     	if(passdetails.phnno==phnno)
     	{
   		     found=1;
    	}
    	else
    	{
    		fwrite(&passdetails,sizeof(pd),1,fp1);
		}
   }
   fclose(fp);
   fclose(fp1);
   if(found)
   {
   	    printf("\nTICKET SUCCESSFULLY CANCELLED");
   		printf("\nREFUND INITIATED");
   		fp1=fopen("temp.txt","r");
   		fp=fopen("seats_reserved.txt","w");
   		while(fread(&passdetails,sizeof(pd),1,fp1))
   		{
   		    fwrite(&passdetails,sizeof(pd),1,fp);
 		}
   }
   else if(!found)
   {
   	    printf("\nINVALID NUMBER");
    	printf("\nTICKET NOT FOUND");
   }
   fclose(fp);
   fclose(fp1);
}