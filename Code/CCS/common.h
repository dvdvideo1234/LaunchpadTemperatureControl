#ifndef COMMON_H_
    #define COMMON_H_
    void waitCount(u16 uiCount)
    {
      while(uiCount--);
    }
    
    void waitCountTimes(u16 uiCount, u16 uiTimes)
    {
      while(uiCount--)
      {
        while(uiTimes--)
      }
    }
#endif

