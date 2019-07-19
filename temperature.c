/*
 * @Author: Liang Weiwei
 * @Description: 温度传感器阻值定义，查询表法计算温度值
 * @Company: Zhejiang geyao technology co. LTD  Development Team
 * @Date: 2019-03-14 10:23:06
 * @LastEditTime: 2019-07-17 14:30:57
 */

#include "temperature.h"
static const uint32_t  NTC_Res_Table[NTC_Res_Table_Size]= {
    6084641,//-50
    5671964,
    5290975,
    4938935,
    4613368,
    4312035,//-45
    4032908,
    3774147,
    3534084,
    3311201,
    3104119,//-40
    2911581,
    2732443,
    2565660,
    2410277,
    2265423,//-35
    2130300,
    2004177,
    1886386,
    1776311,
    1673390,//-30
    1577103,
    1486975,
    1402567,
    1323476,
    1249329,//-25
    1779783,
    1114521,
    1053250,
    995701,
    941623,//-20
    890783,
    842969,
    797980,
    755632,
    715755,//-15
    678190,
    642788,
    609413,
    577937,
    548242,//-10
    520216,
    493756,
    468767,
    445160,
    422849,//-5
    401758,
    381814,
    362948,
    345096,
    328200,//0
    312203,
    297053,
    282701,
    269102,
    256213,//5
    243992,
    232404,
    221411,
    210981,
    201083,//10
    191687,
    182766,
    174293,
    166244,
    157787,//15
    150574,
    143728,
    137230,
    131059,
    125200,//20
    119633,
    114345,
    109319,
    104542,
    100000,//25
    95681,
    91573,
    87664,
    83944,
    80404,//30
    77033,
    73823,
    70766,
    67853,
    65077,//35
    62431,
    59909,
    57503,
    55209,
    53157,//40
    51059,
    49055,
    47139,
    45308,
    43558,//45
    41884,
    40283,
    38751,
    37285,
    35882,//50
    34538,
    33252,
    32020,
    30839,
    29708,//55
    28624,
    27584,
    26588,
    25632,
    24715,//60
    23835,
    22991,
    22181,
    21403,
    20656,//65
    19939,
    19250,
    18588,
    17952,
    17340,//70
    16752,
    16187,
    15644,
    15121,
    14572,//75
    14092,
    13630,
    13186,
    12759,
    12348,//80
    11953,
    11573,
    11206,
    10854,
    10514,//85
    10187,
    9872,
    9568,
    9276,
    9000,//90
    8729,
    8467,
    8214,
    7970,
    7734,//95
    7507,
    7287,
    7074,
    6869,
    6671,//100
    6479,
    6294,
    6115,
    5941,
    5774,//105
    5612,
    5455,
    5303,
    5157,
    5014,//110
    4877,
    4744,
    4615,
    4490,
    4363,//115
    4247,
    4134,
    4024,
    3918,
    3815,//120
    3716,
    3619,
    3526,
    3435,
    3347,//125
    3262,
    3180,
    3100,
    3022,
    2947,//130
    2873,
    2803,
    2734,
    2667,
    2602,//135
    2539,
    2478,
    2419,
    2361,
    2307,//140
    2253,
    2200,
    2148,
    2098,
    2049,//145
    2002,
    1956,
    1911,
    1868,
    1825,//150
    1784,
    1744,
    1705,
    1667,
    1630,//155
    1594,
    1559,
    1525,
    1491,
    1459,//160
    1427,
    1397,
    1367,
    1337,
    1307,//165
    1280,
    1253,
    1226,
    1201,
    1176,//170
    1152,
    1128,
    1105,
    1083,
    1061,//175
    1039,
    1019,
    998,
    979,
    959,//180
    940,
    922,
    904,
    887,
    870,//185
    853,
    837,
    821,
    805,
    792,//190
    777,
    762,
    748,
    734,
    721,//195
    707,
    694,
    682,
    669,
    657,//200
    645,
    634,
    622,
    611,
    600,//205
    590,
    579,
    569,
    559,
    549,//210
    540,
    530,
    521,
    512,
    503,//215
    495,
    486,
    478,
    470,
    462,//220
    454,
    447,
    439,
    432,
    425,//225
    418,
    411,
    404,
    397,
    391,//230
    384,
    378,
    372,
    366,
    360,//235
    354,
    349,
    343,
    338,
    332,//240
    327,
    322,
    317,
    312,
    307,//245
    302,
    298,
    293,
    289,
    284//250    
};
/**
 * @description: 二分查找算法 ->查温度表,查找数据在表中对应的位置 表中数据从大到小
 * @param {type} a                  表地址
 *               TabLong            表长度
 *               data               要查找的数据
 * @return: 数据在表中的位置
 */
static uint16_t FineTab(uint32_t *a,uint16_t TabLong,uint32_t data)//表中数据从大到小
{
    uint16_t st,ed,m ;
    uint16_t i ;

    st = 0 ;
    ed = TabLong-1 ;
    i = 0  ;

    if(data >= a[st]) return st ;
    else if(data <= a[ed]) return ed ;

    while(st < ed)
    {
        m = (st+ed)/2 ;

        if(data == a[m] ) break ;
        if(data < a[m] && data > a[m+1]) break ;


        if(data > a[m])  ed = m ;
        else st = m ;

        if(i++ > TabLong) break ;
    }

    if(st > ed ) return 0 ;

    return m ;
}
/**
 * @description: 输入电阻阻值，根据返回的表中的位置计算出实际温度值
 * @param {type} res        NTC阻值
 * @return: 实际温度值
 */
int16_t Get_Senor_Temperature(uint32_t res)
{
    int16_t table_num;//数据在表中的标号
    int16_t senor_temp;
    uint16_t senor_temp_point;
    uint32_t difference_value1,difference_value2;
    table_num=FineTab((uint32_t *)NTC_Res_Table,NTC_Res_Table_Size,res);
    if(table_num==0)
    {
        senor_temp=Senor_Temp_Min_Value;
    }
    else if(table_num==(NTC_Res_Table_Size-1))
    {
        senor_temp=Senor_Temp_Max_Value;
    }
    else
    {
        difference_value1=NTC_Res_Table[table_num]-NTC_Res_Table[table_num+1];//计算所在的标号和下一个标号电阻差值

        difference_value2=NTC_Res_Table[table_num]-res;//当前阻值与所在标号阻值的差值
        senor_temp_point=(uint16_t)((difference_value2*10)/difference_value1);//求占比,取一位小数
        senor_temp=(int16_t)((table_num*10)+(Senor_Temp_Min_Value*10)+senor_temp_point);//加上小数位，就是带一位小数位的实际温度值*/
    }
    return senor_temp;
}
