///////////////////////////////////////////////////////////////////////////////////////////////////
//  MLBP Instances
///////////////////////////////////////////////////////////////////////////////////////////////////

example of filename: m01_n0010__001.inst 
 m01   -> number of levels (here 1 level)
 n0010 -> number of items  (here 10 items)
 __001 -> instance index 
 
++ format ++
m
n^0 n^1 ... n^m
s^0_1 s^0_2 ... s^0_{n^0}
s^1_1 s^1_2 ... s^1_{n^1}
...
s^m_1 s^m_2 ... s^m_{n^m}
w^1_1 w^1_2 ... w^1_{n^1}
...
w^m_1 w^m_2 ... w^m_{n^m}
c^1_1 c^1_2 ... c^1_{n^1}
...
c^m_1 c^m_2 ... c^m_{n^m}

++ explanation ++
first  line:  number of levels
second line:  number of items (n^0) + number of bins at each level (n^1 ... n^m)
third  line:  size of each item 
next m lines: size of each bin at each level
next m lines: weight of each bin at each level
next m lines: cost of each bin at each level




///////////////////////////////////////////////////////////////////////////////////////////////////
//  MLBPFC Instances
///////////////////////////////////////////////////////////////////////////////////////////////////

example of filename: m01_n0010_p040_q020__001.inst 
 m01   -> number of levels (here 1 level)
 n0010 -> number of items  (here 10 items)
 p040  -> penalty factor (here 40)
 q020  -> maximum number of different groups, as a percentage of the number of items (here 20% of 10 items -> at most 2 different groups)
 __001 -> instance index 
 
++ format ++
m
n^0 n^1 ... n^m
s^0_1 s^0_2 ... s^0_{n^0}
s^1_1 s^1_2 ... s^1_{n^1}
...
s^m_1 s^m_2 ... s^m_{n^m}
w^1_1 w^1_2 ... w^1_{n^1}
...
w^m_1 w^m_2 ... w^m_{n^m}
c^1_1 c^1_2 ... c^1_{n^1}
...
c^m_1 c^m_2 ... c^m_{n^m}
p q
g_1 g_2 ... g_{n^0}


++ explanation ++
first  line:  number of levels
second line:  number of items (n^0) + number of bins at each level (n^1 ... n^m)
third  line:  size of each item 
next m lines: size of each bin at each level
next m lines: weight of each bin at each level
next m lines: cost of each bin at each level
next line:    penalty factor and group percentage
next line:    group of each item
