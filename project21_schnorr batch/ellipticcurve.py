class PointJacobi(AbstractPoint):
    def __init__(self, curve, x, y, z, order=None, generator=False):
        super(PointJacobi, self).__init__()
        self.__curve = curve
        if GMPY:  # pragma: no branch
            self.__coords = (mpz(x), mpz(y), mpz(z))
            self.__order = order and mpz(order)
        else:  # pragma: no branch
            self.__coords = (x, y, z)
            self.__order = order
        self.__generator = generator
        self.__precompute = []
    @classmethod
    def add(cls, P, Q):#椭圆曲线上的加法运算（两点横坐标不等时）
        if cls.is_inf(P):
            return Q
        if cls.is_inf(Q):
            return P
        xp, yp = P
        xq, yq = Q
        if xp == xq:
            if (yp + yq) % cls.q == 0:
                return cls.gen_inf()  # infi
            else:
                return cls.double(P)
        else: 
            lamb = ((yq - yp) * inverse((xq - xp) % cls.q, cls.q)) % cls.q
            xs = (lamb ** 2 - xp - xq) % cls.q
            ys = (lamb * (xp - xs) - yp) % cls.q
            return xs, ys

    @classmethod
    def double(cls, P):#椭圆曲线上的加法运算（两点横坐标相等时）
        assert cls.is_include(P)
        if cls.is_inf(P):
            return cls.gen_inf()
        x, y = P
        lamb = ((3 * (x ** 2)) + cls.a) * inverse((2 * y) % cls.q, cls.q) % cls.q
        xr = (lamb ** 2 - 2 * x) % cls.q
        yr = (lamb * (x - xr) - y) & cls.q
        return xr, yr

    @classmethod
    def smul(cls, n: int, P) -> int:
        mask = 1 << 255 
        A = cls.gen_inf()
        for i in range(255):
            if n & mask != 0:
                A = cls.add(A, P)
            A = cls.double(A)
            mask >>= 1
        if n & mask:
            A = cls.add(A, P)
        return A
class Point(AbstractPoint):
    def __init__(self, curve, x, y, order=None):
        super(Point, self).__init__()
        self.__curve = curve
        if GMPY:
            self.__x = x and mpz(x)
            self.__y = y and mpz(y)
            self.__order = order and mpz(order)
        else:
            self.__x = x
            self.__y = y
            self.__order = order
        # 确定该点是否为无穷远点
        if self.__curve:
            assert self.__curve.contains_point(x, y)
        if curve and curve.cofactor() != 1 and order:
            assert self * order == INFINITY
#无穷远点
INFINITY = Point(None, None, None)
