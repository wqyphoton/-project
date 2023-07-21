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
