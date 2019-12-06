LONG CDSPrinterLibOCXCtrl::DSPrintAgreement_YiQian(LPCTSTR data) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());


    CString str = data;

    //str=L"梁仲文，广州分公司，2015-10-10，2015-10-10，广州分公司，梁仲文，身份证，440104197809145555，2，1，梁仲文，13902211555，zjl@.com，周五，12131222112，中国建设银行广州大德路支行，6236683325555268599，2，1，人民币五十万元，500000.00，2015-10-10，1，2";	
    CStringArray arr;
    SplitStrToSA(str, arr, L "，", TRUE);

    const double SCALE = 25.4; //convert  mm  to  inch
    //=====Print  Preface=======================================	
    int i = 0;
    DSScaleCharacters(2, 2);
    DSPrintCharsABS(85 / SCALE, (171 + 4 - 6 - 2) / SCALE, arr[i++]); //客户编号
    DSPrintCharsABS(85 / SCALE, (182 + 4 - 6 - 4) / SCALE, arr[i++]); //签署地

    CStringArray arrTmp;
    SplitStrToSA(arr[i++], arrTmp, L "-", TRUE);
    if (arrTmp.GetSize() != 3) //年-月-日,3个元素
    {
      return FALSE;
    }

    CString strDate = arrTmp[0] + L "      " + arrTmp[1] + L "      " + arrTmp[2];
    DSPrintCharsABS(85 / SCALE, (197 - 6 - 4) / SCALE, strDate); //年月日

    /*
    DSPrintCharsABS(85/SCALE,197/SCALE,arrTmp[0]);//年
    DSPrintCharsABS((85+19)/SCALE,197/SCALE,arrTmp[1]);//月
    DSPrintCharsABS((85+19+15)/SCALE,197/SCALE,arrTmp[2]);//日
    */
    DSFeedPage();


    //=====Print  Page  1/17=======================================
    DSScaleCharacters(1, 1); //restore  normal.
    SplitStrToSA(arr[i++], arrTmp, L "-", TRUE);
    if (arrTmp.GetSize() != 3) //年-月-日,3个元素
    {
      return FALSE;
    }

    DSPrintCharsABS(63 / SCALE, (35 - 3 + 2) / SCALE, arrTmp[0]); //年
    DSPrintCharsABS((63 + 13 + 3) / SCALE, (35 - 3 + 2) / SCALE, arrTmp[1]); //月
    DSPrintCharsABS((63 + 13 + 5 + 3) / SCALE, (35 - 3 + 2) / SCALE, arrTmp[2]); //日

    DSPrintCharsABS(120 / SCALE, (35 - 3 + 2) / SCALE, arr[i++]); //地方    x坐标不准
    DSPrintCharsABS(59 / SCALE, (35 + 9 - 3 + 2) / SCALE, arr[i++]); //甲方	
    DSPrintCharsABS(47 / SCALE, (35 + 9 + 9 - 3 + 2) / SCALE, arr[i++]); //证件类型


    CString strIDCardNum = arr[i++]; //440104197809145555
    for (int j = 0; j < strIDCardNum.GetLength(); j++) {
      CString strTemp;
      strTemp = strIDCardNum.GetAt(j);
      DSPrintCharsABS((48 + j * 7) / SCALE, (61 - 3 + 2) / SCALE, strTemp); //证件号
    }
    DSFeedPage();


    //=====Print  Page  2/17=======================================
    DSPrintCharsABS(39 / SCALE, 30 / SCALE, Check2Symbol(arr[i++])); //√
    DSPrintCharsABS(39 / SCALE, 50 / SCALE, Check2Symbol(arr[i++])); //×
    DSFeedPage();


    //=====Print  Page  3/17=======================================
    DSPrintCharsABS(85 / SCALE, 114 / SCALE, arr[i++]); //户名

    DSPrintCharsABS(53 / SCALE, 120 / SCALE, arr[i++]); //联系方式
    DSPrintCharsABS(122 / SCALE, 120 / SCALE, arr[i++]); //email

    DSPrintCharsABS(57 / SCALE, 126 / SCALE, arr[i++]); //urgent  contact
    DSPrintCharsABS(133 / SCALE, 126 / SCALE, arr[i++]); //tel

    CString bank = arr[i++]; //中国建设银行广州大德路支行
    CString bank1; //银行
    CString bank2; //分行
    CString bank3; //支行
    int pos1, pos2, pos3;
    pos1 = pos2 = pos3 = 0;

    pos1 = bank.Find(L "银行");
    if (-1 != pos1) {
      bank1 = bank.Left(pos1);
      pos1 += 2;
    } else {
      pos1 = 0;
      bank1 = L "";
    }

    CString tmp = bank.Mid(pos1); //xxx分行xxx支行
    pos2 = tmp.Find(L "分行");
    if (-1 != pos2) {
      bank2 = tmp.Left(pos2);
      pos2 += 2;
    } else {
      pos2 = 0;
      bank2 = L "";
    }

    tmp = tmp.Mid(pos2)
    加载更多