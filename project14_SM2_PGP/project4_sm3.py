from functools import reduce
import struct
def str2bytes(msg: str, encoding='utf-8'):
    #字符串转换成byte数组
    msg_bytearray = msg.encode(encoding) if isinstance(msg, str) else msg
    return list(msg_bytearray)
#布尔函数
def FF(x,y,z,j):
    if j>=0 and j<=15:
        return x^y^z
    if j>=16 and j<=63:
        return (x & y)|(x & z)|(y & z)
def GG(x,y,z,j):
    if j>=0 and j<=15:
        return x^y^z
    if j>=16 and j<=63:
        return (x & y)|(~x & z)
#置换函数
def p1(x):
    return x^(x<<<9)^(x<<<17)
def p2(x):
    return x^(x<<<15)^(x<<<23)
#生成轮常数
T_j = [0x79cc4519] * 16 + [0x7a879d8a] * 48
T_j_rotate_left = [rotate_left(Tj, j) for j, Tj in enumerate(T_j)]
#只存储j-1...j-16 16个消息扩展字
Wi[16]
#最终的hash值
sm3_hash
#初始向量IV
IV = [1937774191, 1226093241, 388252375, 3666478592, 2842636476, 372324522, 3817729613, 2969243214]
A=IV[0:2]
B=IV[2:4]
C=IV[4:6]
D=IV[6:8]
E=IV[8:10]
F=IV[10:12]
G=IV[12:14]
H=IV[14:16]
#消息填充
def pad(msg):
    pad=[512]
    msg.append(b"1")#填充1bit1
    length=list(bin(len(msg)))#消息长度的二进制表示
    length_0=64-len(length)
    list_0=[0]*length_0
    length.extend(list_0)#64bit的长度
    length_d=((512-64)-1-len(msg))%512
    d=[0]*length_d
    pad=msg+d+length
    return pad
#压缩函数
def F( A, B, C, D, E, F, G, H,j,sm3_hash, msg_1):
     W_j = [W[j] ^ W[j + 4]#在压缩函数中计算消息字
    if j in range(0, 15)
        if j>=4:
            wi[j]= msg_1[j:j+2]#在压缩函数中计算消息字
        high_A12, low_A12 = divmod(A, BIT_EACH_32[20])
        r_l_12 = high_A12 + low_A12 * BIT_EACH_32[12]
        high, low = divmod((r_l_12 + E + T_j_rotate_left[j]) & 0xFFFFFFFF, BIT_EACH_32[25])
        SS1 = high + low * BIT_EACH_32[7]
        SS2 = SS1 ^ r_l_12
        TT1 = ((A ^ B ^ C) + D + SS2 + W_j[j]) & 0xFFFFFFFF
        TT2 = ((E ^ F ^ G) + H + SS1 + W[j]) & 0xFFFFFFFF
        high_B9, low_B9 = divmod(B, BIT_EACH_32[23])
        high_F19, low_F19 = divmod(F, BIT_EACH_32[13])
        high, low = divmod(TT2, BIT_EACH_32[23])
        r_l_9 = high + low * BIT_EACH_32[9]
        high, low = divmod(TT2, BIT_EACH_32[15])
        r_l_17 = high + low * BIT_EACH_32[17]
        A, B, C, D, E, F, G, H = TT1, A, high_B9 + low_B9 * BIT_EACH_32[9] & 0xffffffff, C, (
                TT2 ^ r_l_9 ^ r_l_17) & 0xffffffff, E, high_F19 + low_F19 * BIT_EACH_32[19] & 0xffffffff, G
      if j in range(16, 64):
            w[j%16]=p1(w[j-16]^w[j-9]^(w[j-3]<<<15))^(w[j-1]<<<7)^w[j-6]
        high_A12, low_A12 = divmod(A, BIT_EACH_32[20])
        r_l_12 = high_A12 + low_A12 * BIT_EACH_32[12]
        high, low = divmod((r_l_12 + E + T_j_rotate_left[j]) & 0xFFFFFFFF, BIT_EACH_32[25])
        SS1 = high + low * BIT_EACH_32[7]
        SS2 = SS1 ^ r_l_12
        TT1 = (((A & B) | (A & C) | (B & C)) + D + SS2 + W_j[j]) & 0xFFFFFFFF
        TT2 = (((E & F) | ((~ E) & G)) + H + SS1 + W[j]) & 0xFFFFFFFF
        high_B9, low_B9 = divmod(B, BIT_EACH_32[23])
        high_F19, low_F19 = divmod(F, BIT_EACH_32[13])
        high, low = divmod(TT2, BIT_EACH_32[23])
        r_l_9 = high + low * BIT_EACH_32[9]
        high, low = divmod(TT2, BIT_EACH_32[15])
        r_l_17 = high + low * BIT_EACH_32[17]
        A, B, C, D, E, F, G, H = TT1, A, high_B9 + low_B9 * BIT_EACH_32[9] & 0xffffffff, C, (
                TT2 ^ r_l_9 ^ r_l_17) & 0xffffffff, E, high_F19 + low_F19 * BIT_EACH_32[19] & 0xffffffff, G
   sm3_hash=[A ^ V_i[0], B ^ V_i[1], C ^ V_i[2],
            D ^ V_i[3], E ^ V_i[4], F ^ V_i[5], G ^ V_i[6], H ^ V_i[7]]

def CF(A,B,C,D,E,F,G,H,msg_1,sm3_hash)
    #优化每轮输入顺序
    for j in range(0,63):
        if j%4==0:
           F(A,B,C,D,E,F,G,H,j)
        if j%4==1:
           F(D,A,B,C,H,E,F,G,j)
        if j%4==2:
           F(C,D,A,B,G,H,E,F,j)
        if j%4==3:
           F(B,C,D,A,F,G,H,E,j)
        A=sm3_hash[0:2]
        B=sm3_hash[2:4]
        C=sm3_hash[4:6]
        D=sm3_hash[6:8]
        E=sm3_hash[8:10]
        F=sm3_hash[10:12]
        G=sm3_hash[12:14]
        H=sm3_hash[14:16]
def digest(msg, state=(IV, 0)):
    msg = str2bytes(msg)
    msg=pad(msg)
    i=0
    while(i<=msg/32)：#msg/32为消息分组个数
            msg_1=msg[i:i+32]#一个消息分组的长度
            i=i+32
            while (j<=6):
                wi[j]=msg_1[j,j+2]#一个消息字16bit,2byte
                j=j+2
            CF(A,B,C,D,E,F,G,H,msg_1)
    return sm3_hash


