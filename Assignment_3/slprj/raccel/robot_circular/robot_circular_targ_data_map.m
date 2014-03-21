  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 0;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtP)
    ;%
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 2;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtB)
    ;%
      section.nData     = 96;
      section.data(96)  = dumData; %prealloc
      
	  ;% rtB.nonm5g4o4k
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.mnknpq2c4s
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtB.ptf05qfh23
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtB.pi4pgrzjdg
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtB.axilp3tz0a
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtB.kvwcbei2yp
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 10;
	
	  ;% rtB.bdqwapvmep
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 11;
	
	  ;% rtB.cp0i2hcsha
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 12;
	
	  ;% rtB.fywryl4tfe
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 13;
	
	  ;% rtB.c15poiyb0k
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 14;
	
	  ;% rtB.iccfft1fyi
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 26;
	
	  ;% rtB.oodqxyey5l
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 42;
	
	  ;% rtB.bh3kreoxfr
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 58;
	
	  ;% rtB.cgc5dx5go3
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 59;
	
	  ;% rtB.mtf5exy1d5
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 62;
	
	  ;% rtB.olcy3pu40b
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 65;
	
	  ;% rtB.c0j5gjznxd
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 71;
	
	  ;% rtB.l2ybfmwenl
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 74;
	
	  ;% rtB.itpoecacsw
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 77;
	
	  ;% rtB.pxwhdnbs3a
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 80;
	
	  ;% rtB.fapc3wzhgp
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 86;
	
	  ;% rtB.c54mpsjpxe
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 89;
	
	  ;% rtB.izceacj0o4
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 92;
	
	  ;% rtB.ncii3n04xe
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 95;
	
	  ;% rtB.lns4a50jfv
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 101;
	
	  ;% rtB.kds4a0jgsi
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 104;
	
	  ;% rtB.pswhok3m0h
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 107;
	
	  ;% rtB.nxcjgubfup
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 110;
	
	  ;% rtB.bg0w5wujyw
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 113;
	
	  ;% rtB.plwhzf40d5
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 116;
	
	  ;% rtB.i2h1htfzsc
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 122;
	
	  ;% rtB.d24dsjjt3o
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 128;
	
	  ;% rtB.jeci4qlpkk
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 164;
	
	  ;% rtB.hlkmo5q05f
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 170;
	
	  ;% rtB.fq3r53l3l1
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 176;
	
	  ;% rtB.d2p52y2le0
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 182;
	
	  ;% rtB.bawsajx3qj
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 183;
	
	  ;% rtB.bqksmtmspn
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 184;
	
	  ;% rtB.icbou04qgh
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 188;
	
	  ;% rtB.oq001gqp2p
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 204;
	
	  ;% rtB.mvjjykwlqc
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 205;
	
	  ;% rtB.pbi3or4c0k
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 206;
	
	  ;% rtB.goeguqncgp
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 207;
	
	  ;% rtB.m214sy2azr
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 208;
	
	  ;% rtB.p50j15qoex
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 209;
	
	  ;% rtB.f1rqrj0gds
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 210;
	
	  ;% rtB.lo2unisv3r
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 226;
	
	  ;% rtB.gelfrxwjrs
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 242;
	
	  ;% rtB.k5iuwdqmdv
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 258;
	
	  ;% rtB.kcmz2bstxf
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 259;
	
	  ;% rtB.melahpcxwo
	  section.data(51).logicalSrcIdx = 50;
	  section.data(51).dtTransOffset = 260;
	
	  ;% rtB.gio2vjw2fw
	  section.data(52).logicalSrcIdx = 51;
	  section.data(52).dtTransOffset = 261;
	
	  ;% rtB.hw4qs5maxi
	  section.data(53).logicalSrcIdx = 52;
	  section.data(53).dtTransOffset = 262;
	
	  ;% rtB.jqxwm2tpmb
	  section.data(54).logicalSrcIdx = 53;
	  section.data(54).dtTransOffset = 263;
	
	  ;% rtB.euoqqrdkql
	  section.data(55).logicalSrcIdx = 54;
	  section.data(55).dtTransOffset = 264;
	
	  ;% rtB.cgye2zz4fs
	  section.data(56).logicalSrcIdx = 55;
	  section.data(56).dtTransOffset = 265;
	
	  ;% rtB.bkktt4qysn
	  section.data(57).logicalSrcIdx = 56;
	  section.data(57).dtTransOffset = 266;
	
	  ;% rtB.i1y4akvdkd
	  section.data(58).logicalSrcIdx = 57;
	  section.data(58).dtTransOffset = 267;
	
	  ;% rtB.nz5gddymwa
	  section.data(59).logicalSrcIdx = 58;
	  section.data(59).dtTransOffset = 268;
	
	  ;% rtB.ilrbulvgek
	  section.data(60).logicalSrcIdx = 59;
	  section.data(60).dtTransOffset = 269;
	
	  ;% rtB.e0q3brqdgq
	  section.data(61).logicalSrcIdx = 60;
	  section.data(61).dtTransOffset = 270;
	
	  ;% rtB.buky4qjekz
	  section.data(62).logicalSrcIdx = 61;
	  section.data(62).dtTransOffset = 271;
	
	  ;% rtB.figg1nrpod
	  section.data(63).logicalSrcIdx = 62;
	  section.data(63).dtTransOffset = 272;
	
	  ;% rtB.kua0xnsh0o
	  section.data(64).logicalSrcIdx = 63;
	  section.data(64).dtTransOffset = 273;
	
	  ;% rtB.mdd1nwwlps
	  section.data(65).logicalSrcIdx = 64;
	  section.data(65).dtTransOffset = 274;
	
	  ;% rtB.itobk2hvgd
	  section.data(66).logicalSrcIdx = 65;
	  section.data(66).dtTransOffset = 275;
	
	  ;% rtB.iguaipqyek
	  section.data(67).logicalSrcIdx = 66;
	  section.data(67).dtTransOffset = 276;
	
	  ;% rtB.ecxpi3bkcd
	  section.data(68).logicalSrcIdx = 67;
	  section.data(68).dtTransOffset = 277;
	
	  ;% rtB.fng0duekef
	  section.data(69).logicalSrcIdx = 68;
	  section.data(69).dtTransOffset = 278;
	
	  ;% rtB.b402h2idnm
	  section.data(70).logicalSrcIdx = 69;
	  section.data(70).dtTransOffset = 279;
	
	  ;% rtB.dz4xjznsqf
	  section.data(71).logicalSrcIdx = 70;
	  section.data(71).dtTransOffset = 282;
	
	  ;% rtB.amgmrxskq1
	  section.data(72).logicalSrcIdx = 71;
	  section.data(72).dtTransOffset = 288;
	
	  ;% rtB.pv0zwy4ism
	  section.data(73).logicalSrcIdx = 72;
	  section.data(73).dtTransOffset = 324;
	
	  ;% rtB.nwvxmcftuf
	  section.data(74).logicalSrcIdx = 73;
	  section.data(74).dtTransOffset = 354;
	
	  ;% rtB.j2wxn3cjv4
	  section.data(75).logicalSrcIdx = 74;
	  section.data(75).dtTransOffset = 378;
	
	  ;% rtB.fxrx2jteos
	  section.data(76).logicalSrcIdx = 75;
	  section.data(76).dtTransOffset = 396;
	
	  ;% rtB.hyyj3phdcl
	  section.data(77).logicalSrcIdx = 76;
	  section.data(77).dtTransOffset = 408;
	
	  ;% rtB.nu3lqck3bd
	  section.data(78).logicalSrcIdx = 77;
	  section.data(78).dtTransOffset = 414;
	
	  ;% rtB.jyrzcculwp
	  section.data(79).logicalSrcIdx = 78;
	  section.data(79).dtTransOffset = 415;
	
	  ;% rtB.jzztlkosp1
	  section.data(80).logicalSrcIdx = 79;
	  section.data(80).dtTransOffset = 419;
	
	  ;% rtB.fr13pf2yrk
	  section.data(81).logicalSrcIdx = 80;
	  section.data(81).dtTransOffset = 435;
	
	  ;% rtB.ddxq2ghec0
	  section.data(82).logicalSrcIdx = 81;
	  section.data(82).dtTransOffset = 451;
	
	  ;% rtB.kjnhuvsnqx
	  section.data(83).logicalSrcIdx = 82;
	  section.data(83).dtTransOffset = 452;
	
	  ;% rtB.pje1rdxv2r
	  section.data(84).logicalSrcIdx = 83;
	  section.data(84).dtTransOffset = 453;
	
	  ;% rtB.oogxhdfgdu
	  section.data(85).logicalSrcIdx = 84;
	  section.data(85).dtTransOffset = 454;
	
	  ;% rtB.dv0esmlgu1
	  section.data(86).logicalSrcIdx = 85;
	  section.data(86).dtTransOffset = 455;
	
	  ;% rtB.jweiksj5ax
	  section.data(87).logicalSrcIdx = 86;
	  section.data(87).dtTransOffset = 456;
	
	  ;% rtB.izlcklrx3a
	  section.data(88).logicalSrcIdx = 87;
	  section.data(88).dtTransOffset = 457;
	
	  ;% rtB.ltq0doaugx
	  section.data(89).logicalSrcIdx = 88;
	  section.data(89).dtTransOffset = 473;
	
	  ;% rtB.kx1y0wb3wk
	  section.data(90).logicalSrcIdx = 89;
	  section.data(90).dtTransOffset = 489;
	
	  ;% rtB.ap0z031w0t
	  section.data(91).logicalSrcIdx = 90;
	  section.data(91).dtTransOffset = 505;
	
	  ;% rtB.ptpimknh2x
	  section.data(92).logicalSrcIdx = 91;
	  section.data(92).dtTransOffset = 506;
	
	  ;% rtB.gdlwb53cjz
	  section.data(93).logicalSrcIdx = 92;
	  section.data(93).dtTransOffset = 507;
	
	  ;% rtB.f3y1rdetlc
	  section.data(94).logicalSrcIdx = 93;
	  section.data(94).dtTransOffset = 509;
	
	  ;% rtB.lfg0s2opgm
	  section.data(95).logicalSrcIdx = 94;
	  section.data(95).dtTransOffset = 510;
	
	  ;% rtB.ln4kdqr0me
	  section.data(96).logicalSrcIdx = 95;
	  section.data(96).dtTransOffset = 511;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% rtB.kbqerzvazr
	  section.data(1).logicalSrcIdx = 96;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.ozqlu4h43q
	  section.data(2).logicalSrcIdx = 97;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 4;
    sectIdxOffset = 2;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtDW)
    ;%
      section.nData     = 9;
      section.data(9)  = dumData; %prealloc
      
	  ;% rtDW.eeux2ti3uv
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.g5wnsipe0f
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.aj0tywjzak
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 7;
	
	  ;% rtDW.ak2swym2hr
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 16;
	
	  ;% rtDW.bvnna42qnw
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 52;
	
	  ;% rtDW.asjef53ye4
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 88;
	
	  ;% rtDW.dhfl3cl5td
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 124;
	
	  ;% rtDW.p3s2khgxd4
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 125;
	
	  ;% rtDW.mwz1nxvmic
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 141;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% rtDW.ltrljuz1h5.LoggedData
	  section.data(1).logicalSrcIdx = 9;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.dyrjcbme1i.LoggedData
	  section.data(2).logicalSrcIdx = 10;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.hq2ynfxh5b
	  section.data(1).logicalSrcIdx = 11;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% rtDW.cteqqy32ya
	  section.data(1).logicalSrcIdx = 12;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.luwwjirqvw
	  section.data(2).logicalSrcIdx = 13;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.j2qrq44urz
	  section.data(3).logicalSrcIdx = 14;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.coupmxhajs
	  section.data(4).logicalSrcIdx = 15;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.ijfh0nhbll
	  section.data(5).logicalSrcIdx = 16;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDW.gvrqqxide3
	  section.data(6).logicalSrcIdx = 17;
	  section.data(6).dtTransOffset = 5;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 2928393357;
  targMap.checksum1 = 2934841979;
  targMap.checksum2 = 1865750830;
  targMap.checksum3 = 3543056207;

