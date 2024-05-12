#include<stdio.h>

#define SIZE 2000

int maxBul(int array[SIZE*2]){									
	int i;
	int max_number = array[0];
	for(i=1;i<SIZE*2;i++){
		if(array[i] > max_number){
			max_number = array[i];
		}
	}
	
	return max_number;
}

int main(){
	
	int rectangles[SIZE][3] = {0};
	int corner[SIZE*2][3];
	int max[SIZE*2] = {0};
	int output[SIZE][2];
	int a = 0,b,c;
	int i,j,k,index,count;
	int flag,temp;
	int max_number_prev, max_number_next;
	int control;
	
	i = 0;
	while(a != -1){																//köþe nokta bilgilerini kullanýcýdan alýyoruz. Kullanýcý a deðerine -1 verene kadar devam edecek
		scanf_s("%d %d %d",&a,&b,&c);												//örneðin -1 1 1 girerse kullanýcýdan bilgi alma iþlemi biter
		if(a != -1){
			rectangles[i][0] = a;
			rectangles[i][1] = b;
			rectangles[i][2] = c;
			i++;
		}
	}
	
	count = i;
	
	
	j = 0;																		//Aldýðýmýz bilgileri algoritmaya yerleþtirebilmek için binanýn baþladýðý köþe noktasý ve bittiði yerdeki köþe noktasý
	for(i=0 ; i < count*2 ; i = i+2){											//olacak þekilde ayarlýyoruz.
		//start
		corner[i][0] = rectangles[j][2];
		corner[i][1] = rectangles[j][1];
		corner[i][2] = 1; 								
		
		
		//end
		corner[i+1][0] = rectangles[j][2] + rectangles[j][0];
		corner[i+1][1] = rectangles[j][1];
		corner[i+1][2] = 0; 						
		
		j++;
	}
	
	
	flag = 0;																	//Köþe noktalarýný binalarýn x eksenindeki konumlarýna göre küçükten büyüðe sýralýyoruz.
	for(i=0 ; i<(count*2)-1 ; i++){
		for(j = i+1 ; j<count*2 ; j++){
			if(corner[j][0] < corner[i][0]){							
				flag = 1;
			}
			
			//Bu algoritmada özel olarak kontrol edilmesi 3 durum var
			
			else if(corner[j][0] == corner[i][0] && corner[j][2] == 1 && corner[i][2] == 1){		//eðer x eksenindeki noktalarý eþitse ve kontrol ettiðimiz noktalar binanýn baþlangýcý ise			
				if(corner[j][1] > corner[i][1]){													//y eksenine göre büyük olan yukarý yazýlýr		
					flag = 1;
				}
			}
			
			else if(corner[j][0] == corner[i][0] && corner[j][2] == 0 && corner[i][2] == 0){		//eðer x eksenindeki noktalarý eþitse ve kontrol ettiðimiz noktalar binanýn bitiþi ise
				if(corner[j][1] < corner[i][1]){													//y eksenine göre küçük olan yukarý yazýlýr
					flag = 1;
				}
			}
			
			else if(corner[j][0] == corner[i][0] && corner[j][2] == 1 && corner[i][2] == 0){		//eðer x eksenindeki noktalarý eþitse ve kontrol ettiðimiz noktalardan birisi baþlangýç
				if(corner[j][1] > corner[i][1]){													//diðeri bitiþ noktasý ise y eksenine göre büyük olan yukarý yazýlýr
					flag = 1;
				}
			}
			
			
			if(flag == 1){																	//Eðer yukardaki kontrollerden flag 1 gelirse elemanlarýn yerlerini deðiþtiriyoruz.
				temp = corner[j][0];
				corner[j][0] = corner[i][0];
				corner[i][0] = temp;
				
				temp = corner[j][1];
				corner[j][1] = corner[i][1];
				corner[i][1] = temp;
				
				temp = corner[j][2];
				corner[j][2] = corner[i][2];
				corner[i][2] = temp;
				
				flag = 0;
			}
			
		}
	}
	
	
	index = 0;
	k = 0;
	for(i=0 ; i<count*2 ; i++){																//Binalarýn köþe noktalarýný bulan algoritma
		if(corner[i][2] == 1){
			max_number_prev = maxBul(max);
			index++;
			max[index] = corner[i][1];
			max_number_next = maxBul(max);
			
			if(max_number_prev != max_number_next){
				output[k][0] = corner[i][0];
				output[k][1] = corner[i][1];
				k++;
			}
			
			
		}
		else{
			
			j = 0;
			control = 0;
			max_number_prev = maxBul(max);
			while(j < 4001 && control == 0){
				if(max[j] == corner[i][1]){
					max[j] = 0;
					control = 1;
				}
				j++;
			}
			max_number_next = maxBul(max);
			
			if(max_number_prev != max_number_next){
				output[k][0] = corner[i][0];
				output[k][1] = max_number_next;
				k++;
			}			
			
		}
	}

	
	printf("\n\n");
	
	
	printf("%d 0 ",output[0][0]);
	for(i=0;i<k;i++){
		if(i!=k-1){
			printf("%d %d ",output[i][0], output[i][1]);
			printf("%d %d ",output[i+1][0], output[i][1]);	
		}
		else{
			printf("%d %d ",output[i][0], output[i][1]);
		}
		
	}
	
	return 0;
}

