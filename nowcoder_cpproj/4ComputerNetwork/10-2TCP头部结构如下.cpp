/*TCP头定义，共20个字节*/
typedef struct _TCP_HEADER
{
    short m_sSourPort;               // 源端口号16bit
    short m_sDestPort;               // 目的端口号16bit
    unsigned int m_uiSequNum;        // 序列号32bit
    unsigned int m_uiAcknowledgeNum; // 确认号32bit
    short m_sHeaderLenAndFlag;       // 前4位：TCP头长度；中6位：保留；后6位：标志位
    short m_sWindowSize;             // 窗口大小16bit
    short m_sCheckSum;               // 检验和16bit
    short m_surgentPointer;          // 紧急数据偏移量16bit
} __attribute__((packed)) TCP_HEADER, *PTCP_HEADER;

/* TCP头中的选项定义
kind(8bit)+Length(8bit，整个选项的长度，包含前两部分)+内容(如果有的话)
KIND = 1表示 无操作NOP，无后面的部分
2表示 maximum segment   后面的LENGTH就是maximum segment选项的长度（以byte为单位，1+1+内容部分长度）
3表示 windows scale     后面的LENGTH就是 windows scale选项的长度（以byte为单位，1+1+内容部分长度）
4表示 SACK permitted    LENGTH为2，没有内容部分
5表示这是一个SACK包     LENGTH为2，没有内容部分  8表示时间戳，LENGTH为10，含8个字节的时间戳 */

typedef struct _TCP_OPTIONS
{
    char m_ckind;
    char m_cLength;
    char m_cContext[32];
} __attribute__((packed)) TCP_OPTIONS, *PTCP_OPTIONS;

//```  UDP头部结构如下： ```cpp /*UDP头定义，共8个字节*/
typedef struct _UDP_HEADER
{
    unsigned short m_usSourPort;                    // 源端口号16bit
    unsigned short m_usDestPort;                    // 目的端口号16bit
    unsigned short m_usLength;                      // 数据包长度16bit
    unsigned short m_usCheckSum;                    // 校验和16bit
} __attribute__((packed)) UDP_HEADER, *PUDP_HEADER; //```