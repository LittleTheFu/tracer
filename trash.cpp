  static int totalReflectCnt = 0;
    static int totalTransmitCnt = 0;

    if(totalReflectCnt % 100 == 0)
    {
        std::cout << "totalReflectCnt: " << totalReflectCnt << std::endl;
        std::cout << "totalTransmitCnt: " << totalTransmitCnt << std::endl;
    }


    //for debug
    if(totalReflect)
    {
        totalReflectCnt++;
        return Color::COLOR_WHITE;
    }
    else
    {
        totalTransmitCnt++;
        // return Color::COLOR_WHITE;
    }
    // static int moreThanOneCnt = 0;
    // static int lessThanOneCnt = 0;

    // if(etaI > etaT)
    // {
    //     moreThanOneCnt++;
    // }
    // else
    // {
    //     lessThanOneCnt++;
    // }

    // if(moreThanOneCnt % 10 == 0)
    // {
    //     std::cout << "moreThanOneCnt: " << moreThanOneCnt << std::endl;
    //     std::cout << "lessThanOneCnt: " << lessThanOneCnt << std::endl;
    // }