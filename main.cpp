#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<math.h>
const int width=20,height=20,upscale=20,bias=200;
double learning_reate=1.0;
double ulaz[width][height],tezine[width][height]; // def 0 global 

void random_weights()
{
	for(int i=0;i<height;i++)
	for(int j=0;j<width;j++)
	{
		tezine[i][j]=rand()%10/10;
	}
}

double sigmoid(double x)
{
	return exp(x)/(exp(x)+1);
	//return sin(x);
}

void draw(void)
{
	int i,j,k;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(tezine[i][j]>0)
			{
				setcolor(RED);
				setfillstyle(SOLID_FILL,RED);
				rectangle((i)*upscale,j*upscale,(i)*upscale+10,(j)*upscale+10);
				floodfill(i*upscale+1,j*upscale+1,RED);
			}
				if(tezine[i][j]<=0)
			{
				setcolor(BLUE);
				setfillstyle(SOLID_FILL,BLUE);
				rectangle(i*upscale,j*upscale,(0+i)*upscale+10,(0+j)*upscale+10);
				floodfill(i*upscale+1,j*upscale+1,BLUE);
			}
			
		}
	}
}

float  perceptron_calc_out(void)
{
	double sum=0.0f;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			sum+=ulaz[i][j]*tezine[i][j];
		}
		
	}
	return sigmoid(sum);
}
void perceptron_calc_update(int is)
	{
		if(is==1)
		{
			for(int i=0;i<height;i++)
			for(int j=0;j<width;j++)
			{
				tezine[i][j]+=ulaz[i][j];
			}
		}
		if(is==0)
		{
			for(int i=0;i<height;i++)
			for(int j=0;j<width;j++)
			{
				tezine[i][j]-=ulaz[i][j];
			}
			
		}
	}
void limit(unsigned int *cord)
{
	if(cord[0]>=width)
		cord[0]=width-1;
	if(cord[1]>=height)
		cord[1]=height-1;
	if(cord[2]<10)
		cord[2]=10;
	
}
void generate_full(int what)
{
	clearviewport();
	if(what==0)   //rectangle
	{
				setcolor(RED);
				setfillstyle(SOLID_FILL,RED);
				rectangle(100,100,200,200);
				floodfill(101,101,RED);
		
		//float pom=sigmoid(perceptron_calc_out());
		double pom=perceptron_calc_out();
		for(int i=0;i<20;i++)
		{
				for(int j=0;j<20;j++)
			{
				if(j>width-1||i>height-1)
					break;
					learning_reate=sigmoid(perceptron_calc_out());
					tezine[i][j]=tezine[i][j]+learning_reate-0.2;
					ulaz[i][j]=1.0;	
	
			}
		}
	}
	
		if(what==1)   //circle isto ko kvadrat 
	{
				//float pom=sigmoid(perceptron_calc_out());
				double pom=perceptron_calc_out();
		
				setcolor(RED);
				setfillstyle(SOLID_FILL,RED);
				circle(200,200,100);
				floodfill(201,201,RED);
		//cor
		for(int i=0;i<20;i++)
		{
				for(int j=0;j<20;j++)
			{
				if(j>width-1||i>height-1)
					break;
				if(100<((i)*(i)+(j)*(j)))
					{
						learning_reate=sigmoid(perceptron_calc_out());
							tezine[i][j]=tezine[i][j]-learning_reate;
							ulaz[i][j]=1.0;	
					}
			}
		}
	}
}



void generate(int what)
{
	
	unsigned int cord[3];  //x=cord[0],y=cord[1],za krug r=cord[3
	cord[0]=abs(rand()%20);
	cord[1]=abs(rand()%20);
	cord[2]=abs(rand()%10);
	limit(cord);
	//printf("x=%d y=%d", cord[0],cord[1]);
	clearviewport();
	if(what==0)   //rectangle
	{
				setcolor(RED);
				setfillstyle(SOLID_FILL,RED);
				rectangle(cord[0]*upscale,cord[1]*upscale,cord[0]*upscale+100,cord[1]*upscale+100);
				floodfill(cord[0]*upscale+1,cord[1]*upscale+1,RED);
		
		//float pom=sigmoid(perceptron_calc_out());
		double pom=perceptron_calc_out();
		for(int i=0;i<cord[1];i++)
		{
				for(int j=0;j<cord[0];j++)
			{
				if(j+cord[0]>width-1||i+cord[1]>height-1)
					break;
					//learning_reate=sigmoid(perceptron_calc_out());
					tezine[i+cord[1]][j+cord[0]]=tezine[i+cord[1]][j+cord[0]]+learning_reate;
					ulaz[i+cord[1]][j+cord[0]]=1.0;	
	
			}
		}
	}
	if(what==1)   //circle isto ko kvadrat 
	{
			
				double pom=perceptron_calc_out();
				setcolor(RED);
				setfillstyle(SOLID_FILL,RED);
				circle(cord[0]*upscale,cord[1]*upscale,50);
				floodfill(cord[0]*upscale+1,cord[1]*upscale+1,RED);
		
		for(int i=0;i<cord[1];i++)
		{
				for(int j=0;j<cord[0];j++)
			{
				if(j+cord[0]>width-1||i+cord[1]>height-1)
					break;
				if(cord[2]*cord[2]<((i+cord[1])*(i+cord[1])+(j+cord[0])*(j+cord[0])))
					{
							//learning_reate=sigmoid(perceptron_calc_out());
							tezine[i+cord[1]][j+cord[0]]=tezine[i+cord[1]][j+cord[0]]-learning_reate;
							ulaz[i+cord[1]][j+cord[0]]=1.0;
					}
			}
		}
	}
	
}
void clean_input(void)
{
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
			ulaz[i][j]=0;
}

int main(void)
{
	int i=0,training=100;
	double out,percentage_guees=0.0,what;
	srand(time(NULL));
	int window1=initwindow(width*upscale,height*upscale,"TEZINE");
	int window2=initwindow(width*upscale,height*upscale,"OBLIK") ;
	//random_weights();

	while(1)
	{
		//what=abs(rand()%2);
		what=i%2;
		clean_input();
		i++;
		setcurrentwindow(window2);
		generate(what);
		//generate_full(what);
		setcurrentwindow(window1);
		draw();
		if(i>training)
		{
		system("pause");
		out=perceptron_calc_out();
		if(out>=0&&out<=0.5)		
			{
				if(what==1)
					percentage_guees+=1;
				printf("KVADRAT (RECTANGLE)\n\n");	
			}
		else
			{
				if(what==0)
					percentage_guees+=1;
			
				printf("KRUG (CIRCLE)\n\n");
			
			}
		printf("percantage of a corect answers: %f  \n\n\n\n",(percentage_guees/float((i-training))*100));
		printf("out %f  \n\n\n\n",out);
		}
	}
	printf("nesto");
}
