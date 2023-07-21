#project 1，2，3，4，11，19
该project中实现了project1，2，3，4，11，19

Project1：implement the naïve birthday attack of reduced SM3

生日攻击的目的是找到一个给定hash值的弱碰撞，其原理来自概率论中的生日悖论：产生hash值碰撞所需的样本数量远小于所有可能hash值的数量。长为n位的hash值共有种可能，产生
一次碰撞平均需要次尝试。SM3输出长度256bit，取值空间，计算可知拥有hash值个数达到生日攻击成功的概率接近1

这里我尝试对SM3生成hash值的前16bit进行生日攻击。（种可能，需要尝试次）攻击分为离线、在线两个阶段。离线阶段用SM3算法计算hash值（前16bit）生成查找表（个hash值）。在线阶段随机生成一个hash值查表。如果寻找更长bit的碰撞，查表时间也会变长。

本次实现使用Python的SM3模块生成hash值

Project2  implement the Rho method of reduced SM3

ρ攻击的目的也是找一个hash值的弱碰撞，寻找的方式是通过ρ递推表达式来进行多次尝试。这里我尝试对SM3生成hash值的前16bit进行ρ攻击，和生日攻击相同，如果寻找更长bit的碰撞，寻找时间也会变长。本实验选取的ρ函数是计算上一个hash值的hash值作为新的hash值。

Project3  SM3,SHA-256长度扩展攻击

SM3、SHA-256都是MD结构，MD结构易进行长度扩展攻击。长度扩展攻击的原理是找到一个hash值的弱碰撞，在此基础上对消息长度进行扩展。MD结构每轮输入只与本轮消息分组和上一轮杂凑结果有关，所以在此基础上进行消息扩展得到的hash值仍然会碰撞。实现中先用ρ攻击找到前16bit的碰撞，再将消息进行长度扩展。

![image](https://github.com/wqyphoton/-project/assets/139944271/54637e75-5295-45f4-8ec2-91d99ecdfd89)

project4  优化SM3
一、SM3算法简介
SM3杂凑算法可将长度小于bit的消息 经过填充、反复的消息扩展和压缩，生成长度为256bit的杂凑值。在SＭ3算法中，字表示长度为32的比特串。
1.消息填充

![image](https://github.com/wqyphoton/-project/assets/139944271/be8a2f87-1977-4d24-bcac-d406c91ca914)

2.布尔函数

![image](https://github.com/wqyphoton/-project/assets/139944271/12182cd9-b4c6-4234-a807-a1e915a53d4a)

3.置换函数

![image](https://github.com/wqyphoton/-project/assets/139944271/cac24495-cc4c-46fd-a25f-8c9185cf2e24)

4.消息扩展

![image](https://github.com/wqyphoton/-project/assets/139944271/6776db22-b93c-4f56-bfc4-ab395a5a3522)

5.压缩函数

将256bit中间变量分为8个消息块，初始IV也分为8个消息块，每块32bit

![image](https://github.com/wqyphoton/-project/assets/139944271/b473d7cb-d485-4f42-9bdc-90a771e06de9)

二、SM3优化

1.消息扩展的优化

消息扩展是利用512bit的消息分组 扩展得到68个字，…，和64个字，…，。此步骤可以放在压缩函数里执行，具体实现为：

①在执行6４轮压缩函数前只计算初始的４个字 ，…，

②执行压缩函数时，在压缩函数的第i轮生成， ＝⊕。这样的优化减少了存储，提高了消息扩展的速度。 

2.压缩函数的优化 

①将压缩函数每轮输入的中间变量进行调整：

压缩函数每一轮的最末会执行循环右移： Ａ||Ｂ||Ｃ||Ｄ ← （Ａ||Ｂ||Ｃ||Ｄ） ＞ ＞ ＞32， Ｅ||Ｆ||Ｇ||Ｈ ← （Ｅ||F||Ｇ||Ｈ） ＞ ＞ ＞32。为了减少循环移位产生的赋值运算，可以将字的循环右移改为每轮字块赋值顺序的改变，且这个顺序变动在４轮后还 原，每轮输入如下（以下用F()表示一轮压缩）： 

F（ｉ+０，Ａ，Ｂ，Ｃ，Ｄ，Ｅ，Ｆ，Ｇ，Ｈ，Ｗ） 

F（ｉ+１，Ｄ，Ａ，Ｂ，Ｃ，Ｈ，Ｅ，Ｆ，Ｇ，Ｗ） 

F（ｉ+２，Ｃ，Ｄ，Ａ，Ｂ，Ｇ，Ｈ，Ｅ，Ｆ，Ｗ） 

F（ｉ+３，Ｂ，Ｃ，Ｄ，Ａ，Ｆ，Ｇ，Ｈ，Ｅ，Ｗ） 

②预计算并存储轮常数  ＝ ＜ ＜ ＜ ｉ。减少计算，减少存储空间占用。

Project11使用RFC6979实现SM2

SM2是基于椭圆曲线上的离散对数问题的非对称加密算法。

1.椭圆曲线密码算法描述：

zp上的椭圆曲线E：

![image](https://github.com/wqyphoton/-project/assets/139944271/ee30583b-280a-4aa6-b7d9-a44cb77611ee)


①密钥生成：明文空间：P=E  密文空间：C=E×E。设椭圆曲线中有n个点,生成元为α。随机选取x∈。计算y=xα。私钥：x 公钥y

②加密：明文m=(x,y), 随机选取k∈。计算=kα,=ky+m

③解密：m=-x

SM2算法选取参数：

![image](https://github.com/wqyphoton/-project/assets/139944271/1ced4577-4121-4351-83e1-9f75a04a6201)


Project19  forge a signature

数字签名伪造攻击的攻击手段：

①对消息hash值进行碰撞攻击

若没有hash函数或碰撞攻击能成功则签名伪造能够成功

②尝试获取签名私钥

若能够获取k则可计算私钥（k泄露）

若能获取两个使用同一密钥的签名，使用同一k生成，则可计算出签名私钥（k重用）

若能获取两个使用不同密钥生成的签名，使用同一k生成，则可计算出两个签名私钥



