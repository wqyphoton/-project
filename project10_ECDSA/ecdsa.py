from . import ellipticcurve#椭圆曲线上的运算等相关定义
from hashlib import sha256 #签名算法选取SHA-256
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
generator_160r1 = ellipticcurve.PointJacobi(#生成该曲线上的相关参数
    curve_160r1, _Gx, _Gy, 1, _r, generator=True
)
#计算字符串的bit长度
 def bit_length(x):
        return len(bin(x)) - 2
#求amodn的逆
 def inverse_mod(a, m):
        if a == 0: 
            return 0
        lm, hm = 1, 0
        low, high = a % m, m
        while low > 1: 
            r = high // low
            lm, low, hm, high = hm - lm * r, high - low * r, lm, low
        return lm % m
#计算amodp的平方根
def square_root_mod_prime(a, p):
    assert 0 <= a < p
    assert 1 < p

    if a == 0:
        return 0
    if p == 2:
        return a

    jac = jacobi(a, p)
    if jac == -1:
        raise SquareRootError("%d has no square root modulo %d" % (a, p))

    if p % 4 == 3:
        return pow(a, (p + 1) // 4, p)

    if p % 8 == 5:
        d = pow(a, (p - 1) // 4, p)
        if d == 1:
            return pow(a, (p + 3) // 8, p)
        assert d == p - 1
        return (2 * a * pow(4 * a, (p - 5) // 8, p)) % p
    raise RuntimeError("No b found.")
#签名生成和签名验证
class Signature(object):
       def __init__(self, r, s):#初始化签名
        self.r = r
        self.s = s
       def sign(self, hash, random_k):#签名生成(hash是hash（m）)
        G = self.public_key.generator
        n = G.order()
        k = random_k % n
        ks = k + n
        kt = ks + n
        if bit_length(ks) == bit_length(n):
            p1 = kt * G
        else:
            p1 = ks * G
        r = p1.x() % n
        #检查生成参数是否为0
        if r == 0:
            raise RSZeroError("erroe:r=0")
        s = (
            inverse_mod(k, n)
            * (hash + (self.secret_multiplier * r) % n)
        ) % n
         #self.secret_multiplier为私钥
        if s == 0:
            raise RSZeroError("erroe:s=0")
        return Signature(r, s)
        def verifies(self, hash, signature):#验证签名
        G = self.generator
        n = G.order()
        r = signature.r
        s = signature.s
        if r < 1 or r > n - 1:
            return False
        if s < 1 or s > n - 1:
            return False
        c =inverse_mod(s, n)
        u1 = (hash * c) % n
        u2 = (r * c) % n
        if hasattr(G, "mul_add"):
            xy = G.mul_add(u1, self.point, u2)
        else:
            xy = u1 * G + u2 * self.point
        v = xy.x() % n
        return v == r
         

        
#生成签名的公钥
class Public_key(object):
 
    def __init__(self, generator, point, verify=True):
        self.curve = generator.curve()
        self.generator = generator
        self.point = point
        n = generator.order()
        p = self.curve.p()
        #检查参数是否正确
        if not (0 <= point.x() < p) or not (0 <= point.y() < p):
            raise InvalidPointError(
            )
        if verify and not self.curve.contains_point(point.x(), point.y()):
            #检查该点是否在椭圆曲线上
            raise InvalidPointError("error:Point does not lay on the curve")
        if not n:
            #检查点的阶是否满足做生成元
            raise InvalidPointError("error:Generator point must have order.")
               if (
            verify
            and self.curve.cofactor() != 1
            and not n * point == ellipticcurve.INFINITY#无穷远点
        ):
            #检查生成元阶是否满足
            raise InvalidPointError("error:Generator point order is bad.")

    def __eq__(self, other):
        if isinstance(other, Public_key):
            return self.curve == other.curve and self.point == other.point
        return NotImplemented

    def __ne__(self, other):#检查公钥是否相同
        return not self == other

   

class Private_key(object):#私钥生成
    def __init__(self, public_key, secret_multiplier):
        self.public_key = public_key
        self.secret_multiplier = secret_multiplier

    def __eq__(self, other):
        if isinstance(other, Private_key):
            return (
                self.public_key == other.public_key
                and self.secret_multiplier == other.secret_multiplier
            )
        return NotImplemented
    def __ne__(self, other):
        return not self == other
  
