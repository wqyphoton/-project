#include <iostream>
#include <string.h>
using namespace std;

//明文分组长度选择128
#define N_plaintext 128
//明文4列
#define Nb 4
//密钥长度128bit
#define N_key 128
//密钥4列
#define Nk 4
//生成状态128bit
void ProduceState(char* plaintext, unsigned char state[4][4])
{
	int temp, index = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp = 0;
			for (int k = 128; k >= 1; k /= 2)
			{
				temp += k * (plaintext[index++] - '0');
			}
			state[j][i] = (unsigned char)temp;
		}
	}
}

//字节代换
void SubByte(unsigned char a)//对应te表，只变换一个字节 
{
	//S盒
	const unsigned char S_Table[16][16] =
	{
	0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
	0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
	0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
	0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
	0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
	0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
	0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
	0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
	0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
	0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
	0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
	0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
	0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
	0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
	0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
	0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
	};

			a= S_Table[(int)(a>> 4)][(int)(a& 0x0f)];
}

//行移位
void  RowShift(unsigned char state[4][4])
{
	//第1行左移一位
	unsigned char temp = state[1][0];
	for (int i = 1; i <= 3; i++)
		state[1][i - 1] = state[1][i];
	state[1][3] = temp;

	//第2行左移两位
	temp = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = temp;
	temp = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = temp;

	//第3行左移三位
	temp = state[3][3];
	for (int i = 3; i >= 1; i--)
		state[3][i] = state[3][i - 1];
	state[3][0] = temp;
}
//te表
void te0(unsigned char a )
{
	SubByte(a);
	unsigned char vector;
	vector[0]=0x02*a;
	vector[1]=0x01*a;
	vector[2]=0x01*a;
	vector[3]=0x03*a;
	return vector;
 } 
 
void te1(unsigned char a )
{
	SubByte(vector);
	unsigned char vector;
	vector[0]=0x03*a;
	vector[1]=0x02*a;
	vector[2]=0x01*a;
	vector[3]=0x01*a;
	return vector;
 } 
 void te2(unsigned char a )
{
	SubByte(vector);
	unsigned char vector;
	vector[0]=0x01*a;
	vector[1]=0x03*a;
	vector[2]=0x02*a;
	vector[3]=0x01*a;
	return vector;
 } 
 void te3(unsigned char a )
{
	SubByte(vector);
	unsigned char vector;
	vector[0]=0x01*a;
	vector[1]=0x01*a;
	vector[2]=0x03*a;
	vector[3]=0x02*a;
	return vector;
 } 
 void te4(unsigned char a )
{
	SubByte(vector);
	unsigned char vector;
	vector[0]=0x01*a;
	vector[1]=0x01*a;
	vector[2]=0x01*a;
	vector[3]=0x01*a;
	return vector;
 } 
 void te4_key(unsigned char a )
{
	SubByte_Key(vector);
	unsigned char vector;
	vector[0]=0x01*a;
	vector[1]=0x01*a;
	vector[2]=0x01*a;
	vector[3]=0x01*a;
	return vector;
 } 
//轮密钥加
void AddRoundKey(unsigned char state[4][4], unsigned char roundKey[11][4][4], int n)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			state[i][j] ^= roundKey[n][i][j];
}

//轮函数
void Round(unsigned char state[4][4], unsigned char roundKey[11][4][4], int n)
{
	RowShift(state);
	unsigned char v_state[4][4];//存储中间值 
	for(int i=0;i<4;i++)//s盒和列混淆合并为查找te表 
	{
		for(int j=0;j<4;j++)//state的每一列分别计算 
		{
			a=state[j][i];
		if(j==0)v_state[0]=te0(a);
		if(j==1)v_state[1]=te1(a);
		if(j==2)v_state[2]=te2(a);
		if(j==3)v_state[3]=te3(a);
		}
	
			for(int j=0;j<4;j++)
		{
			state[j]=v_state[0]^v_state[1]^v_state[2]^v_state[3];//每一列的异或值 
		}
	}
	AddRoundKey(state, roundKey, n);
}

//最后轮函数
void FinalRound(unsigned char state[4][4], unsigned char roundKey[11][4][4])
{
	RowShift(state);
	unsigned char v_state[4][4];//存储中间值 
	for(int i=0;i<4;i++)//s盒和列混淆合并为查找te表 
	{
		for(int j=0;j<4;j++)//state的每一列分别计算 
		{
			a=state[j][i];
		v_state[0]=te4(a);//最后一轮没有列混淆，只调用te4表即可 
		v_state[1]=te4(a);
	    v_state[2]=te4(a);
		v_state[3]=te4(a);
		}
	
			for(int j=0;j<4;j++)
		{
			state[j]=v_state[0]^v_state[1]^v_state[2]^v_state[3];//每一列的异或值 
		}
	}
	AddRoundKey(state, roundKey, 10);
}
//密钥扩展SubByte
void SubByte_Key(unsigned char a)
{
	//S盒
	const unsigned char S_Table[16][16] =
	{
	0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
	0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
	0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
	0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
	0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
	0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
	0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
	0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
	0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
	0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
	0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
	0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
	0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
	0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
	0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
	0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
	};
		a= S_Table[(int)(a >> 4)][(int)(a& 0x0f)];
}
//密钥扩展
void KeyExpansion(char key[], unsigned char roundKey[11][4][4])
{
	ProduceState(key, roundKey[0]);
	//用于密钥扩展的轮常数 
	const unsigned char Rcon[11] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36 };
	unsigned char vector[4]={0x00,0x00,0x00,0x00};//存储中间值 
	for(int i=1;i<11;i++)
	{
		for(int j=0;j<4;j++) 
		{
        a=roundkey[i][j][4];
    	vector[j]=te4(a);
        }
        roundKey[i][][0]=roundKey[i-1][][0]^vector^Rcon;
        roundKey[i][][1]=roundKey[i-1][][1]^roundKey[i][][0];
        roundKey[i][][2]=roundKey[i-1][][2]^roundKey[i][][1];
        roundKey[i][][3]=roundKey[i-1][][3]^roundKey[i][][2];
    }
}

//加密
void Rijndael(unsigned char state[4][4], char key[N_key])
{
	unsigned char roundkey[11][4][4];
	KeyExpansion(key, roundkey);

	//输出密钥
	cout << "\n密钥为：\n";
	Print(roundkey[0]);

	AddRoundKey(state, roundkey, 0);
	for (int i = 1; i < 10; i++)
		Round(state, roundkey, i);
	FinalRound(state, roundkey);
}

//解密
void InvRijndael(unsigned char state[4][4], char key[N_key])
{
	unsigned char roundkey[11][4][4];
	KeyExpansion(key, roundkey);
	//逆密钥
	for (int i = 1; i <= 9; i++)
		InvMixColumn(roundkey[i]);

	AddRoundKey(state, roundkey, 10);
	for (int i = 9; i >= 1; i--)
		InvRound(state, roundkey, i);
	InvFinalRound(state, roundkey);
}
void invte0(unsigned char a )
{
	InvSubByte(a);
	unsigned char vector;
	vector[0]=0x02*a;
	vector[1]=0x01*a;
	vector[2]=0x01*a;
	vector[3]=0x03*a;
	return vector;
 } 
 
void invte1(unsigned char a )
{
	InvSubByte(vector);
	unsigned char vector;
	vector[0]=0x03*a;
	vector[1]=0x02*a;
	vector[2]=0x01*a;
	vector[3]=0x01*a;
	return vector;
 } 
 void invte2(unsigned char a )
{
	InvSubByte(vector);
	unsigned char vector;
	vector[0]=0x01*a;
	vector[1]=0x03*a;
	vector[2]=0x02*a;
	vector[3]=0x01*a;
	return vector;
 } 
 void invte3(unsigned char a )
{
	InvSubByte(vector);
	unsigned char vector;
	vector[0]=0x01*a;
	vector[1]=0x01*a;
	vector[2]=0x03*a;
	vector[3]=0x02*a;
	return vector;
 } 
 void invte4(unsigned char a )
{
	InvSubByte(vector);
	unsigned char vector;
	vector[0]=0x01*a;
	vector[1]=0x01*a;
	vector[2]=0x01*a;
	vector[3]=0x01*a;
	return vector;
 } 

//逆字节代换
void InvSubByte(unsigned char a)
{
	//逆S盒
	const unsigned char ReS_Table[16][16] =
	{
	0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
	0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
	0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
	0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
	0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
	0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
	0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
	0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
	0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
	0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
	0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
	0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
	0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
	0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
	0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
	};

	//逆字节代换
		a= S_Table[(int)(a>> 4)][(int)(a& 0x0f)];
}

//逆行移位
void InvRowShift(unsigned char state[4][4])
{
	//第1行
	unsigned char temp = state[1][3];
	for (int i = 3; i >= 1; i--)
		state[1][i] = state[1][i - 1];
	state[1][0] = temp;

	//第2行
	temp = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = temp;
	temp = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = temp;

	//第3行
	temp = state[3][0];
	for (int i = 1; i <= 3; i++)
		state[3][i - 1] = state[3][i];
	state[3][3] = temp;

}
//逆轮函数
void InvRound(unsigned char state[4][4], unsigned char roundKey[11][4][4], int n)
{
	InvRowShift(state);
	unsigned char v_state[4][4];//存储中间值 
	for(int i=0;i<4;i++)//s盒和列混淆合并为查找te表 
	{
		for(int j=0;j<4;j++)//state的每一列分别计算 
		{
			a=state[j][i];
		if(j==0)v_state[0]=te0(a);
		if(j==1)v_state[1]=te1(a);
		if(j==2)v_state[2]=te2(a);
		if(j==3)v_state[3]=te3(a);
		}
	
			for(int j=0;j<4;j++)
		{
			state[j]=v_state[0]^v_state[1]^v_state[2]^v_state[3];//每一列的异或值 
		}
	}
	AddRoundKey(state, roundKey, n);
}

//逆最后轮函数
void InvFinalRound(unsigned char state[4][4], unsigned char roundKey[11][4][4])
{
	InvRowShift(state);
		unsigned char v_state[4][4];//存储中间值 
	for(int i=0;i<4;i++)//s盒和列混淆合并为查找te表 
	{
		for(int j=0;j<4;j++)//state的每一列分别计算 
		{
			a=state[j][i];
		v_state[0]=te4(a);//最后一轮没有列混淆，只调用te4表即可 
		v_state[1]=te4(a);
	    v_state[2]=te4(a);
		v_state[3]=te4(a);
		}
	
			for(int j=0;j<4;j++)
		{
			state[j]=v_state[0]^v_state[1]^v_state[2]^v_state[3];//每一列的异或值 
		}
	}
	AddRoundKey(state, roundKey, 0);
}
int main()
{
	//一组明文
	char plaintext[N_plaintext + 1];
	//一组密钥
	char key[N_key + 1];
		cout << "请输入128bit明文：\n";
		cin.getline(plaintext, 129);
		cout << "请输入128bit密钥：\n";
		cin.getline(key, 129);
	system("cls");

	//状态
	unsigned char plainState[4][Nb];

	//明文生成状态
	ProduceState(plaintext, plainState);

	//输出明文和密钥
	cout << "明文为：\n";
	Print(plainState);

	//加密
	Rijndael(plainState, key);
	cout << "\n加密后密文为：\n";
	Print(plainState);

	//解密
	InvRijndael(plainState, key);
	cout << "\n再对密文解密后明文为：\n";
	Print(plainState);

	system("pause");
	return 0;
}

