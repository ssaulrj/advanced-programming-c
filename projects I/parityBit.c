#include<stdio.h>
#include<string.h>

int main(){
	int i,count=0,parity;
	char data[20];
	printf("Enter data: ");
	scanf("%s",&data);
	printf("Choose parity \n0:Even\n1:Odd\n");
	scanf("%d",&parity);
	for(i=0;i<strlen(data);i++){
		if(data[i]=='1')
		count++;
	}
	if(parity==0 && count%2==0){
		printf("No Error Detected");
		
	}
	else if(parity==1 && count%2==0)
	printf("No error detected");
	else
	printf("Error detected");
	return 0;
}
