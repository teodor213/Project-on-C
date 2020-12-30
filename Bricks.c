#include <stdio.h>
#include <stdlib.h>


int main(void){
	int firstLayer[50][50] = {0};
	int secondLayer[50][50] = {0};
	
	printf("%d\n", firstLayer[0][0]);
	
	int x = 0, y = 0;
	int maxY;
	
	int dontMove[50][50] = {0};
	
	int x1 = 0;
	int tempX, tempY;
	
	int horizontal = 0;
	
	char c;
	
	while(1){
		
		c = getc(stdin);
		
		if (c == 'a')
			break;
			
		else if (c == '\n'){
			x++;
			maxY = y;
			y = 0;
		}
		
		else{
			firstLayer[x][y] = c;
			y++;
		}
	}
	

	
	while(x >= x1){
		
		for(int y1 = 0, y2 = 0, x2 = 0; y1 != maxY && x2 != x; y1++){
			
			for(;secondLayer[x1][y2] != 0;){
				//printf("Here:%c\n", secondLayer[x1][y2]);
				y2++;
			}
			
			if(firstLayer[x1][y1] == 0)
				break;
			
			else if(firstLayer[x1][y1] == firstLayer[x1 + 1][y1] && horizontal == 0){
				secondLayer[x1][y1] = firstLayer[x1][y1];
				secondLayer[x1][y1 + 1] = firstLayer[x1 + 1][y1];
				
				printf("Vertical:%c:%c\n", firstLayer[x1][y1], firstLayer[x1 + 1][y1]);
				
				dontMove[x1][y1] = 1;
				dontMove[x1 + 1][y1] = 1;
				
				//dontMove[x1][y1 - 1] = 1;
				//dontMove[x1 + 1][y1 - 1] = 1;
				
				horizontal = 1;
				tempY = y1; 
				y2++;
			}
			
			else if(firstLayer[x1][y1] == firstLayer[x1 + 1][y1] && horizontal == 1){
				secondLayer[x1 + 1][tempY] = firstLayer[x1][y1];
				secondLayer[x1 + 1][tempY + 1] = firstLayer[x1][y1];
				
				dontMove[x1][y1] = 1;
				dontMove[x1 + 1][y1] = 1;
				
				printf("With value 1 Vertical:%c:%c\n", firstLayer[x1][y1], firstLayer[x1 + 1][y1]);
				
				//dontMove[x1][y1 - 1] = 1;
				//dontMove[x1 + 1][y1 - 1] = 1;
				
				//printf("FirstLayer:%c%c\n", firstLayer[x1 + 1][y1], firstLayer[x1][y2]);
				//printf("Horizontal:%c%c\n", secondLayer[x1 + 1][y2], secondLayer[x1][y2]);
				
				horizontal = 0;
				tempY = 0; 
			
				x2 += 2;
			}
			
		}
		
		horizontal = 0;
		
		
		for(int y1 = 0, y2 = 0; y1 != maxY; y1 += 2, y2++){
			
			for(;secondLayer[x1][y2] != 0 || secondLayer[x1][y2 + 1] != 0;){
				printf("Here:%c\n", secondLayer[x1][y2]);
				y2++;
			}
		
			if(firstLayer[x1][y1] == 0)
				break;
			
			else if(dontMove[x1][y2] == 1){
				secondLayer[x1][y2] = firstLayer[x1][y1];
				secondLayer[x1][y2 - 1] = firstLayer[x1][y1 - 1];
				
				printf("Dont move these:%c:%c\n", firstLayer[x1][y1], firstLayer[x1][y1 - 1]);
				//secondLayer[x1][y2 + 1]= firstLayer[x1 + 1][y1];
				
				//secondLayer[x1 - 1][y2]= firstLayer[x1][y1];
				break;
			}
			
			
		}
		
		for(int y1 = 0, y2 = 0; y1 != maxY; y1 += 2, y2++){
			
			for(;secondLayer[x1][y2] != 0 ;){
				printf("Here:%c\n", secondLayer[x1][y2]);
				y2++;
			}
		
			if(firstLayer[x1][y1] == 0)
				break;
			
			for(;firstLayer[x1][y1] == firstLayer[x1][y1 + 1] & firstLayer[x1][y1 + 1] != 0; y1 += 2, y2++){
				
				printf("Horizontal:%c:%c\n", firstLayer[x1][y1], firstLayer[x1][y1 + 1]);
				
				if(x1 % 2 != 0){
					secondLayer[x1 - 1][y2] = firstLayer[x1][y1];
					secondLayer[x1][y2] = firstLayer[x1][y1];
				}
				else{
					secondLayer[x1][y2] = firstLayer[x1][y1];
					secondLayer[x1 + 1][y2] = firstLayer[x1][y1];
				}
					
				printf("\tY2:%d X:%d\n", y2, y1);
			}
			
		}
		
		x1++;
		
	}
	
	
	for(int Xx = 0; Xx != 3; Xx++){
		for(int Yy = 0; Yy != 8; Yy++){
			
			printf("%c ", secondLayer[Xx][Yy]);
			
		}
		printf("\n");
		
	}
	
	
	return 0;
}


