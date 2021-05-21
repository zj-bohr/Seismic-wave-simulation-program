/*（一）正演模拟程序*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.1415926
#define FM 20.0
#define R 3
#define e 2.71828
int main(int argc, char *argv[])
{
	/************声明变量****************/
	FILE *fp;
	int  i, j, k, m, n, p, Xn=300,Zn=300,Tn=400;
	double temp, tem, mid,dt=0.001,dh=5.0;
	double *w, **v,**u0, **u1, **u2, **u3, **u4; 
    tem=280;//波前快照时间
  	p=10;//检波面位置
	/************数组开辟（略）****************/
	w=(double*)calloc(Tn,sizeof(double));
	v = (double**)calloc(Zn,sizeof(double*));
	for (i = 0; i < Zn; i++)
	{
		v[i] = (double*)calloc(Xn,sizeof(double));
	}
	u0 = (double**)calloc(Xn,sizeof(double*));
	for (i = 0; i < Xn; i++)
	{
		u0[i] = (double*)calloc(Zn,sizeof(double));
	}

	u1 = (double**)calloc(Xn,sizeof(double*));
	for (i = 0; i < Xn; i++)
	{
		u1[i] = (double*)calloc(Zn,sizeof(double));
	}

	u2 = (double**)calloc(Xn,sizeof(double*));
	for (i = 0; i < Xn; i++)
	{
		u2[i] = (double*)calloc(Zn,sizeof(double));
	}

	u3 = (double**)calloc(Xn,sizeof(double*));
	for (i = 0; i < Xn; i++)
	{
		u3[i] = (double*)calloc(Zn,sizeof(double));
	}

	u4 = (double**)calloc(Xn,sizeof(double*));
	for (i = 0; i < Xn; i++)
	{
		u4[i] = (double*)calloc(Tn,sizeof(double));
	}
	/************子波和速度数组赋值****************/
	for(k=0;k<Tn;k++)
	w[k] = pow(e, (-pow(2 * PI*FM / R, 2)*pow((k - 40)*dt, 2)))*cos(2 * PI*FM*(k - 40)*dt);//雷克子波采样 
	/*均匀介质*/ 
	for (i = 0; i < Xn; i++)
	{
		for (j = 0; j < Zn; j++)
		{
			v[i][j] = 2500.0;
		}
	}
	/************波场计算****************/
	for(k=1;k<Tn-1;k++)	
	{
	  for (i = 2; i < Xn - 2; i++)
		{
			for (j = 2; j < Zn - 2; j++)
			{
				if (i == 150 && j ==150)//震源点
					temp = 1;
				else temp = 0;
				u2[i][j] = 2 * u1[i][j] - u0[i][j]+ pow(v[i][j],2 )* pow(dt,2 ) / pow(dh,2 )*\
							(-1 / 12 * (u1[i - 2][j] + u1[i + 2][j]) + 4 / 3 * (u1[i + 1][j] +\
							 u1[i - 1][j]) - 5 / 2 * u1[i][j])+ pow(v[i][j],2 )* pow(dt,2 ) / pow(dh,2 )*\
							 (-1 / 12 * (u1[i][j - 2] + u1[i][j + 2]) + 4 / 3 * (u1[i][j + 1] + \
							 u1[i][j - 1]) - 5 / 2 * u1[i][j])+ 10 * w[k] * temp;
	  		}
		}
	  for (m = 0; m < Xn; m++)
		for (n = 0; n < Zn; n++)
		{
			u0[m][n] = u1[m][n];
			u1[m][n] = u2[m][n];
		}
		for (i = 0; i < Xn; i++)
		{
			u4[i][k + 1] = u2[i][p];
		}
		if (k == tem)
		{
			for (i = 0; i < Xn; i++)
				for (j = 0; j < Zn; j++)
					u3[i][j] = u2[i][j];
		}
	}
	//三个二维数组表示出一个三维数组的波场运算

	/************写文件****************/
	FILE* fp;
	errno_t error;
	error = fopen_s(&fp, "wavefront.dat", "w+");
	if (error != 0)
	{
		printf("打开失败");
	}
	else 
	{
		for (int i = 0; i < Xn; i++)
		{
			for (int j = 0; j < Zn; j++)
			{
				fprintf(fp, "%lf\n ", u3[i][j]);
			}
		}
	}
	fclose(fp);
	
	/*内存释放*/ 
	free(w);
	for(i=0;i<Xn;i++)
		free(v[i]);
	free(v);
	for(i=0;i<Xn;i++)
		free(u0[i]);
	free(u0);
	for(i=0;i<Xn;i++)
		free(u1[i]);
	free(u1);
	for(i=0;i<Xn;i++)
		free(u2[i]);
	free(u2);
	for(i=0;i<Xn;i++)
		free(u3[i]);
	free(u3);
	for(i=0;i<Xn;i++)
		free(u4[i]);
	free(u4);
	return 0;
}
