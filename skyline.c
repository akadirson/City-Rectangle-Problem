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
	while(a != -1){																//k��e nokta bilgilerini kullan�c�dan al�yoruz. Kullan�c� a de�erine -1 verene kadar devam edecek
		scanf_s("%d %d %d",&a,&b,&c);												//�rne�in -1 1 1 girerse kullan�c�dan bilgi alma i�lemi biter
		if(a != -1){
			rectangles[i][0] = a;
			rectangles[i][1] = b;
			rectangles[i][2] = c;
			i++;
		}
	}
	
	count = i;
	
	
	j = 0;																		//Ald���m�z bilgileri algoritmaya yerle�tirebilmek i�in binan�n ba�lad��� k��e noktas� ve bitti�i yerdeki k��e noktas�
	for(i=0 ; i < count*2 ; i = i+2){											//olacak �ekilde ayarl�yoruz.
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
	
	
	flag = 0;																	//K��e noktalar�n� binalar�n x eksenindeki konumlar�na g�re k���kten b�y��e s�ral�yoruz.
	for(i=0 ; i<(count*2)-1 ; i++){
		for(j = i+1 ; j<count*2 ; j++){
			if(corner[j][0] < corner[i][0]){							
				flag = 1;
			}
			
			//Bu algoritmada �zel olarak kontrol edilmesi 3 durum var
			
			else if(corner[j][0] == corner[i][0] && corner[j][2] == 1 && corner[i][2] == 1){		//e�er x eksenindeki noktalar� e�itse ve kontrol etti�imiz noktalar binan�n ba�lang�c� ise			
				if(corner[j][1] > corner[i][1]){													//y eksenine g�re b�y�k olan yukar� yaz�l�r		
					flag = 1;
				}
			}
			
			else if(corner[j][0] == corner[i][0] && corner[j][2] == 0 && corner[i][2] == 0){		//e�er x eksenindeki noktalar� e�itse ve kontrol etti�imiz noktalar binan�n biti�i ise
				if(corner[j][1] < corner[i][1]){													//y eksenine g�re k���k olan yukar� yaz�l�r
					flag = 1;
				}
			}
			
			else if(corner[j][0] == corner[i][0] && corner[j][2] == 1 && corner[i][2] == 0){		//e�er x eksenindeki noktalar� e�itse ve kontrol etti�imiz noktalardan birisi ba�lang��
				if(corner[j][1] > corner[i][1]){													//di�eri biti� noktas� ise y eksenine g�re b�y�k olan yukar� yaz�l�r
					flag = 1;
				}
			}
			
			
			if(flag == 1){																	//E�er yukardaki kontrollerden flag 1 gelirse elemanlar�n yerlerini de�i�tiriyoruz.
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
	for(i=0 ; i<count*2 ; i++){																//Binalar�n k��e noktalar�n� bulan algoritma
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

