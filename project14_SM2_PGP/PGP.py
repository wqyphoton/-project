from . import project11_sm2 as sm2
from . import signature_SM2 as sigsm2
from . import sm4
#相关参数（本次实现使用secp160曲线，也可以使用其他安全椭圆曲线参数）
_p =0xFFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF 7FFFFFFF
S =0x1053CDE4 2C14D696 E6768756 1517533B F3F83345
_a = -3
_b =0x1C97BEFC 54BD7A8B 65ACF89F 81D4D4AD C565FA45
_Gx = 0x4A96B568 8EF57328 46646989 68C38BB9 13CBFC82
_Gy = 0x23A62855 3168947D 59DCC912 04235137 7AC5FB32
_r = 0x01 00000000 00000000 0001F4C8 F927AED3 CA752257
_h = 1
curve_160r1 = ellipticcurve.CurveFp(_p, -3, _b, _h)
generator_160r1 = ellipticcurve.PointJacobi(
    curve_160r1, _Gx, _Gy, 1, _r, generator=True)
main_key[16]=[0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef]

def PGP(m):
    turple=sigsm2.Signature.sign(,m,)#SM2签名
    rk=sm4.key_extend(main_key)#对称加密sm4密钥生成
    msg_1=sm4.encode(turple,rk)#加密签名
    msg_2=sm2.sm2_encrypt(rk)#加密对称密钥
    return msg_1+msg_2
    
    
