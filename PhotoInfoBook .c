//IRFAN KAAN ALGAN 2328599//
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define FALSE 0
#define TRUE 1

struct datetime{
	int day;
	int month;
	int year;
	int hour;
	int minute;
};

struct photoNode{
    	int ID;
    	struct datetime *dt;
        char photoName[250];
        char photoDim[250];
        char photosize[250];
        char cityName[250];
        char countryName[250];
        struct photoNode *next;
    };
    
struct photoRecord{
	struct photoNode *head;
	struct photoNode *tail;
	int size;
};
typedef struct photoRecord* photo;

int IsEmptylist(photo p);
photo initialisePhotos(void);
photo addPhoto(char[],char[],char[],char[],char[],photo);
void printPhotos(photo);
void searchPhotos(photo);
photo deletePhoto(photo,int);



int main(){
	
	photo photoList;
	char command;
	int exit = FALSE;
	
	int IDscan;
	char photoscan[250];
	char dimscan[250];
	char sizescan[250];
	char cityscan[250];
	char countryscan[250];
	
	fflush(stdin);
	photoList = initialisePhotos();
	printf("The PhotoInfoBook.txt file has been loaded successfully");
	
	while(!exit){
		printf("\n------MENU------\n\n1. Add a new photo\n2. Print Photos\n3. Search Photos\n4. Delete Photos\n5. Print recently deleted photos\n6. Exit\n\nEnter your option: ");
		scanf("%c", &command);
		fflush(stdin);
		printf("\n");
		switch (command){
			case '1':
				printf("Enter name of the photo: ");
				gets(photoscan);
				fflush(stdin);
				
				printf("Enter dimension of the photo: ");
				gets(dimscan);
				fflush(stdin);
				
				printf("Enter size of the photo:  ");
				gets(sizescan);
				fflush(stdin);
				
				printf("Enter name of the city: ");
				gets(cityscan);
				fflush(stdin);
				
				printf("Enter name of the country: ");
				gets(countryscan);
				fflush(stdin);
				
				photoList=addPhoto(photoscan,dimscan,sizescan,cityscan,countryscan,photoList);
				printf("The photo has been added!!\n");
				break;
			case '2':
				printPhotos(photoList);
				break;
			case '3':
				searchPhotos(photoList);
				break;
			case '4':
				printf("Enter the ID of the Photo you want to delete: ");
				scanf("%d",&IDscan);
				fflush(stdin);
				if(IDscan < 1 || IDscan > photoList->size)
					printf("No photo with ID %d in your list! \n",IDscan);
				else {
					photoList = deletePhoto(photoList,IDscan);
					printf("Photo with ID %d has been deleted from your list AND added to recently deleted list \n",IDscan);
				}	
				break;
			case '6':
				exit = TRUE;
				printf("Goodbye!!\n");	
				break;
			default:
				printf("command is not recognized!\n");
				break;	
		}
		
	}
	system("PAUSE");

	return 0;
}


int IsEmptylist(photo p)
{
	return (p->size==0);
}


photo initialisePhotos(){
	
	FILE *plistpt;
	plistpt = fopen("PhotoInfoBook.txt","r");
	
	if(plistpt == NULL)
	{
		printf("FAILED!\n");
		exit(1);
	}
	
	photo listPhotos;
	listPhotos = (struct photoRecord*)malloc(sizeof(struct photoRecord));
	listPhotos->head = (struct photoNode*)malloc(sizeof(struct photoNode));
	listPhotos->head->dt = (struct datetime*)malloc(sizeof(struct datetime));
	listPhotos->tail = listPhotos->head;
	listPhotos->size = 0;
	
	struct photoNode *temp;
	temp = listPhotos->head;
	temp->next = (struct photoNode*)malloc(sizeof(struct photoNode));
	temp->next->dt = (struct datetime*)malloc(sizeof(struct datetime));
	temp->next->next=NULL;
	temp=temp->next;
	
	while(fscanf(plistpt,"%d ;%[^;];%[^;];%[^;];%[^;];%[^;];%d/%d/%d %d:%d\n",&temp->ID,temp->photoName,temp->photoDim,temp->photosize,temp->cityName,&temp->countryName,&temp->dt->day,&temp->dt->month,&temp->dt->year,&temp->dt->hour,&temp->dt->minute) != EOF){
		
		fflush(stdin);
		listPhotos->size++;
		if(feof(plistpt))	break;
		temp->next=(struct photoNode*)malloc(sizeof(struct photoNode));
		temp->next->dt=(struct datetime*)malloc(sizeof(struct datetime));
		temp->next->next=NULL;
		temp=temp->next;
		listPhotos->tail=temp;
		
	}
	fclose(plistpt);
	return listPhotos;
}


photo addPhoto(char name[],char dim[],char size[],char city[],char country[],photo p){
	
	time_t ti = time(NULL);
	struct tm t = *localtime(&ti);
	
	struct photoNode *newphoto,*temp;
	newphoto = (struct photoNode*)malloc(sizeof(struct photoNode));
	newphoto->dt = (struct datetime*)malloc(sizeof(struct datetime));
	newphoto->next=NULL;
	
	strcpy(newphoto->photoName,name);
	strcpy(newphoto->photoDim,dim);
	strcpy(newphoto->photosize,size);
	strcpy(newphoto->cityName,city);
	strcpy(newphoto->countryName,country);
	newphoto->dt->day = t.tm_mday;
	newphoto->dt->month = t.tm_mon+1;
	newphoto->dt->year= t.tm_mon+1+2019;	
	newphoto->dt->hour = t.tm_hour;
	newphoto->dt->minute = t.tm_min;
	newphoto->ID = p->tail->ID+1;
	
	
	if(IsEmptylist(p))
	{
		p->tail->next=newphoto->next;
		p->tail=newphoto;	
	}
	
	else
	{
		temp=p->head;
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
			newphoto->next=temp->next;
			temp->next=newphoto;
			p->tail=temp->next;
		
	}
	p->size++;
	
	return p;
	
}

void printPhotos(photo list){
	
	struct datetime *dt;
	struct photoNode *p;
	
	p=list->head->next;

	printf("Photos in your database:\n");
	printf("--------------------------\n");
	while(p!=NULL)
	{
		
		printf("ID: %d\n",p->ID);
		printf("Photo name: %s\n",p->photoName);
		printf("Photo dimension: %s\n",p->photoDim);
		printf("Photo size: %s\n",p->photosize);
		printf("City name: %s\n",p->cityName);
		printf("Country name: %s\n",p->countryName);
		printf("Date: %02d/%02d/%04d\n",p->dt->day,p->dt->month,p->dt->year);
		printf("Time: %02d:%02d\n",p->dt->hour,p->dt->minute);
		
		printf("\n");
		p=p->next;
	}
	
	printf("\n");
	
}

void searchPhotos(photo p){
	
	int option,lenght,j;
	char ascountryName[100];
	char ascityName[100];
	
	struct photoNode* searchPhoto;
	searchPhoto = p->head;
	int find = FALSE;
	int i;
	
	printf("---- Searching by ---- \n");
	printf("(1)  Country name  \n(2)  City name \n");
	printf("Enter search by option: ");
	scanf("%d",&option);
	fflush(stdin);
	switch(option){
		case 1:
			printf("Enter country name: ");
			gets(ascountryName);
			fflush(stdin);
			printf("\n");
			for(i=0;i<p->size;i++){
				while(searchPhoto!=NULL){
					if(strcmp(searchPhoto->countryName,ascountryName )==0){
						find = TRUE;
						printf("ID:  %d\n",searchPhoto->ID);
						printf("Photo Name: %s\n",searchPhoto->photoName);
						printf("Photo Dimention: %s\n",searchPhoto->photoDim);
						printf("Photo Size: %s\n",searchPhoto->photosize);
						printf("City Name: %s\n",searchPhoto->cityName);
						printf("Country Name: %s\n",searchPhoto->countryName);
						printf("Date: %02d/%02d/%04d\n",searchPhoto->dt->day,searchPhoto->dt->month,searchPhoto->dt->year);
						printf("Time: %02d:%02d\n",searchPhoto->dt->hour,searchPhoto->dt->minute);
						
						printf("\n");
						
					}
					searchPhoto=searchPhoto->next;
				}
				
			}
			
			if(find == FALSE) printf("Not Found!\n");
			
			break;
			case 2:
			printf("Enter city name: ");
			gets(ascityName);
			fflush(stdin);
			printf("\n");
			for(i=0;i<p->size;i++){
				while(searchPhoto!=NULL){
					if(strcmp(searchPhoto->cityName,ascityName )==0){
						find = TRUE;
						printf("ID:  %d\n",searchPhoto->ID);
						printf("Photo Name: %s\n",searchPhoto->photoName);
						printf("Photo Dimention: %s\n",searchPhoto->photoDim);
						printf("Photo Size: %s\n",searchPhoto->photosize);
						printf("City Name: %s\n",searchPhoto->cityName);
						printf("Country Name: %s\n",searchPhoto->countryName);
						printf("Date: %02d/%02d/%04d\n",searchPhoto->dt->day,searchPhoto->dt->month,searchPhoto->dt->year);
						printf("Time: %02d:%02d\n",searchPhoto->dt->hour,searchPhoto->dt->minute);
						
						printf("\n");
						
					}
					searchPhoto=searchPhoto->next;
				}
				
			}
			
			if(find == FALSE) printf("Not Found!\n");
			
			break;
			default:
			printf("Please enter a valid option!\n");
			break;	
	}
	
}

photo deletePhoto(photo p, int pos){
	
	struct photoNode *del, *temp;
	
	temp = p->head;
	
	if(IsEmptylist(p))
		printf("No photos in your photo list\n");
	else
	{
	
		while((temp->next != NULL) && (temp->next->ID != pos))
			temp=temp->next;
			
		del = temp->next;
		temp->next = temp->next->next;
		free(del);
		
		p->size--;
	}
	
	
	return p;
	
}



