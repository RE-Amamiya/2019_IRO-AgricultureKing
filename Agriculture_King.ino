
// Code Wrote by H.S.H. 2019
// Smart Farm & Automation

// Agriculture King

#include <LiquidCrystal.h>                 //LCD 구동 라이브러리
#include <DHT.h>                            //DHT22 온습도센서 라이브러리
#include <MsTimer2.h>                        //타이머 인터럽트 라이브러리
//#include <Servo.h>                          //서보 모터 라이브러리

DHT DHT0(52, DHT22);                        //Sensor 0 <> Pin 52
DHT DHT1(53, DHT22);                        //Sensor 1 <> Pin 51
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);    //Pin 7,8,9,10,11,12 > LCD


char junk;
String inputString;
String Extinput;
int m1fs, m1bs, m2fs, m2bs, m3bs, m3fs, m4fs, m4bs, m5fs, m5bs, mdfs, mdbs, LEDstate, PUMPstate, extPUMPstate, isConv, isAuto, Stage = 0;
int isComplete[] = {0};
int Conv = 1;
int Manual = 1;


unsigned char Temp[2], Humid[2], AvgTemp, AvgHumid;

void SendState() {
  Temp[0] = DHT0.readTemperature();      //온도 Read
  Temp[1] = DHT1.readTemperature();
  Humid[0] = DHT0.readHumidity();        //습도 Read
  Humid[1] = DHT1.readHumidity();

  AvgTemp = (Temp[0] + Temp[1]) / 2;     //센서 2개 평균
  AvgHumid = (Humid[0] + Humid[1]) / 2;  //센서 2개 평균
  
  
  Serial.print(AvgTemp);
  Serial.print(":");
  Serial.print(AvgHumid);

  lcd.setCursor(6, 1);
  lcd.print(AvgHumid);

  lcd.setCursor(17, 1);
  lcd.print(AvgTemp);
}

void Refresh() {
  Temp[0] = DHT0.readTemperature();  //온도 Read
  Temp[1] = DHT1.readTemperature();
  Humid[0] = DHT0.readHumidity();    //습도 Read
  Humid[1] = DHT1.readHumidity();

  AvgTemp = (Temp[0] + Temp[1]) / 2;     //센서 2개 평균
  AvgHumid = (Humid[0] + Humid[1]) / 2;  //센서 2개 평균
  
  lcd.clear();
  lcd.setCursor(2, 0);               //첫번째 줄
  lcd.print("Agriculture King");

  lcd.setCursor(0, 1);               //두번째 줄
  lcd.print("HUMID:");
  lcd.print(AvgHumid);
  lcd.print("% /");
  lcd.setCursor(12, 1);
  lcd.print("TEMP:");
  lcd.print(AvgTemp);
  lcd.print("C");

  lcd.setCursor(0, 2);               //세번째 줄
  lcd.print("LED:");
  lcd.setCursor(4, 2);
  if (LEDstate == 1) {
    lcd.print("ON");
  } else {
    lcd.print("OFF");
  }
  lcd.setCursor(10, 2);
  lcd.print("/");
  lcd.setCursor(12, 2);
  lcd.print("PUMP:");
  lcd.setCursor(18, 2);
  if (PUMPstate == 1) {
    lcd.print("ON");
  } else {
    lcd.print("OFF");
  }
}

void toggleLED() {
  if (LEDstate == 1) {
    digitalWrite(50, !LEDstate);
    LEDstate = !LEDstate;
    Refresh();
    buzzShort();
  }
  else {
    digitalWrite(50, !LEDstate);
    LEDstate = !LEDstate;
    Refresh();
    buzzShort();
  }
}


void togglePUMP() {
  if (PUMPstate == 1) {
    digitalWrite(23, !PUMPstate);
    PUMPstate = !PUMPstate;
    Refresh();
    buzShort();
  }
  else {
    digitalWrite(23, !PUMPstate);
    PUMPstate = !PUMPstate;
    Refresh();
    buzShort();
  }
}


//모터 전후진 함수 (토글)

void M1forward() {
  if (m1fs == 1) {
    digitalWrite(40, LOW);
    digitalWrite(41, LOW);
    m1fs = 0;
  } else {
    digitalWrite(40, HIGH);
    digitalWrite(41, HIGH);
    m1fs = 1;
  }
}

void M1backward() {
  if (m1bs == 1) {
    digitalWrite(40, LOW);
    digitalWrite(41, LOW);
    m1bs = 0;
  } else {
    digitalWrite(40, LOW);
    digitalWrite(41, HIGH);
    m1bs = 1;
  }
}

void M2forward() {
  if (m2fs == 1) {
    digitalWrite(42, LOW);
    digitalWrite(43, LOW);
    m2fs = 0;
  } else {
    digitalWrite(42, HIGH);
    digitalWrite(43, HIGH);
    m2fs = 1;
  }
}

void M2backward() {
  if (m2bs == 1) {
    digitalWrite(42, LOW);
    digitalWrite(43, LOW);
    m2bs = 0;
  } else {
    digitalWrite(42, LOW);
    digitalWrite(43, HIGH);
    m2bs = 1;
  }
}

void M3forward() {
  if (m3fs == 1) {
    digitalWrite(44, LOW);
    digitalWrite(45, LOW);
    m3fs = 0;
  } else {
    digitalWrite(44, HIGH);
    digitalWrite(45, HIGH);
    m3fs = 1;
  }
}

void M3backward() {
  if (m3bs == 1) {
    digitalWrite(44, LOW);
    digitalWrite(45, LOW);
    m3bs = 0;
  } else {
    digitalWrite(44, LOW);
    digitalWrite(45, HIGH);
    m3bs = 1;
  }
}

void M4forward() {
  if (m4fs == 1) {
    digitalWrite(36, HIGH);
    digitalWrite(37, HIGH);
    m4fs = 0;
  } else {
    digitalWrite(36, HIGH);
    digitalWrite(37, LOW);
    m4fs = 1;
  }
}

void M4backward() {
  if (m4bs == 1) {
    digitalWrite(36, HIGH);
    digitalWrite(37, HIGH);
    m4bs = 0;
  } else {
    digitalWrite(36, LOW);
    digitalWrite(37, HIGH);
    m4bs = 1;
  }
}

void M5forward() {
  if (m5fs == 1) {
    digitalWrite(38, HIGH);
    digitalWrite(39, HIGH);
    m5fs = 0;
  } else {
    digitalWrite(38, HIGH);
    digitalWrite(39, LOW);
    m5fs = 1;
  }
}

void M5backward() {
  if (m5bs == 1) {
    digitalWrite(38, HIGH);
    digitalWrite(39, HIGH);
    m5bs = 0;
  } else {
    digitalWrite(38, LOW);
    digitalWrite(39, HIGH);
    m5bs = 1;
  }
}


//부저 길게 한번
void buzLong() {
  digitalWrite(6, HIGH);
  delay(500);
  digitalWrite(6, LOW);
}

//부저 짧게 한번
void buzShort() {
  digitalWrite(6, HIGH);
  delay(100);
  digitalWrite(6, LOW);
}


//시리얼 데이터가 들어올때까지 대기
void WaitResponse() {
  while (Serial1.available() < 1) __asm__("nop\n\t");
  return Serial1.read();
}


void setup() {
  Serial.begin(9600);    //PC 시리얼
  Serial1.begin(9600);   //서보모터 제어용 Arduino 간 시리얼
  DHT0.begin();
  DHT1.begin();

  pinMode(6, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(50, OUTPUT);

  digitalWrite(50, 1);   //릴레이 모듈이 Active LOW
  digitalWrite(23, 1);
  digitalWrite(22, 1);


  lcd.begin(20, 4);
  Refresh();
  lcd.setCursor(4, 2);
  lcd.print("OFF");
  lcd.setCursor(17, 2);
  lcd.print("OFF");

  MsTimer2::set(1000, sendState);  //인터럽트 1초마다 발생
  MsTimer2::start();               //인터럽트 시작

  Serial1.print("Hand:180to0");   //수확기 서보모터 원위치
  WaitResponse();                  //서보모터 제어용 Arduino에서 완료신호 줄 때 까지 대기

  isComplete = 0;
}

void loop() {
  if (Serial.available() > 0) {

    //PC 제어부분

    while (Serial.available())
    {
      char inChar = (char)Serial.read();    //시리얼 데이터 받아오기 (String)
      inputString += inChar;
    }


    if (inputString == "1") {
      toggleLED();
    }

    else if (inputString == "2") {
      togglePUMP();
    }

    else if (inputString == "3") {
      M1forward();
    }

    else if (inputString == "4") {
      M1backward();
    }

    else if (inputString == "5") {
      M2forward();
    }

    else if (inputString == "6") {
      M2backward();
    }

  }
  else {
    inputString = "";
    SendState();

    //컨트롤러 제어 (PC 사용X)
    //스위치 값 변경 이후 다시 스위치 값이 변하기 전까지 다른 동작 하지 않음 (isComplete 변수 이용)
    //(토글스위치이기 때문에 계속 같은 동작을 하는 것 방지)
    
    //비효율적이지만.. 다른 방법이 없음

    int readsw1 = !digitalRead(24);
    if (readsw1 == 1) {
      if (isComplete[0] == 0) {
        togglelLED();
        isComplete[0] = 1;
        Serial.print("A");  //PC 컨트롤 프로그램에 동작 중 메세지 전달
      }
    } else if (readsw1 == 0) {
      if (isComplete[0] == 1) {
        toggleLED();
        isComplete[0] = 0;
        Serial.print("B");  //PC 컨트롤 프로그램에 동작 완료 메세지 전달
      }
    }


    int readsw2 = !digitalRead(25);
    if (readsw2 == 1) {
      if (isComplete[1] == 0) {
        togglePUMP();
        isComplete[1] = 1;
        Serial.print("A");
      }
    } else if (readsw2 == 0) {
      if (isComplete[1] == 1) {
        togglePUMP();
        isComplete[1] = 0;
        Serial.print("B");
      }
    }


    int readsw3 = !digitalRead(26);
    if (readsw3 == 1) {
      if (isComplete[2] == 0) {
        digitalWrite(48, HIGH);
        isComplete[2] = 1;
        isAuto = 1;
      }
    } else if (readsw3 == 0) {
      if (isComplete[2] == 1) {
        digitalWrite(48, LOW);
        isComplete[2] = 0;
        isAuto = 0;
        Manual = 1;
        lcd.setCursor(0, 3);
        lcd.print("Select Stage-");
        lcd.setCursor(14, 3);
        lcd.print(Manual);
      }
    }


    int readsw4 = !digitalRead(27);
    if (readsw4 == 1) {
      if (isComplete[3] == 0) {
        digitalWrite(49, HIGH);
        isComplete[3] = 1;
        isConv = 1;
        buzShort();

      }
    } else if (readsw4 == 0) {
      if (isComplete[3] == 1) {
        digitalWrite(49, LOW);
        lcd.clear();
        Refresh();
        isComplete[3] = 0;
        isConv = 0;
        Conv = 1;
        lcd.setCursor(0, 3);
        lcd.print("Select Stage-");
        lcd.setCursor(14, 3);
        lcd.print(Conv);
      }
    }

    int readsw5 = !digitalRead(28);
    if (readsw5 == 1) {
      if (isComplete[4] == 0) {
        if (isConv == 1) {
          M1forward();
          M2forward();
        } else {
          if (Conv < 10) {
            Conv = Conv + 1;
            lcd.setCursor(14, 3);
            lcd.print(Conv);
            delay(100);
          }
        }
        isComplete[4] = 1;
      }
    } else if (readsw5 == 0) {
      if (isComplete[4] == 1) {
        if (isConv == 1) {
          M1forward();
          M2forward();
        }
        isComplete[4] = 0;
      }
    }


    int readsw6 = !digitalRead(29);
    if (readsw6 == 1) {
      if (isComplete[5] == 0) {
        if (isConv == 1) {
          M1backward();
          M2backward();
        } else {
          if (Conv > 1) {
            Conv = Conv - 1;
            lcd.setCursor(14, 3);
            lcd.print(Conv);
            delay(100);
          }
        }
        isComplete[5] = 1;
      }
    } else if (readsw6 == 0) {
      if (isComplete[5] == 1) {
        if (isConv == 1) {
          M1backward();
          M2backward();
        }
        isComplete[5] = 0;
      }
    }


    int readsw7 = !digitalRead(30); //우측
    if (readsw7 == 1) {
      if (isComplete[6] == 0) {
        if (isConv == 1) {
          M3forward();
        } else {
          if (Conv == 1) {  //1층 선택시
            M4forward();
            delay(50);
          } else if (Conv == 2) {  //2층 선택시
            M5forward();
            delay(50);
          }
        }
        isComplete[6] = 1;
      }
    } else if (readsw7 == 0) {
      if (isComplete[6] == 1) {
        if (isConv == 1) {
          M3forward();
        } else {
          if (Conv == 1) {
            M4forward();
            delay(50);
          } else if (Conv == 2) {
            M5forward();
            delay(50);
          }
        }
        isComplete[6] = 0;
      }
    }

    int readsw8 = !digitalRead(31); //좌측
    if (readsw8 == 1) {
      if (isComplete[7] == 0) {
        if (isConv == 1) {
          M3backward();
        } else {
          if (Conv == 1) {
            M4backward();
          } else if (Conv == 2) {
            M5backward();
          }
        }
        isComplete[7] = 1;
      }
    } else if (readsw8 == 0) {
      if (isComplete[7] == 1) {
        if (isConv == 1) {
          M3backward();
        } else {
          if (Conv == 1) {
            M4backward();
          } else if (Conv == 2) {
            M5backward();
          }
        }
        isComplete[7] = 0;
      }
    }

    int readsw10 = !digitalRead(35);
    if (readsw10 == 1) {
      if (isComplete[9] == 0) {


        //서보모터 제어용 Arduino 와 통신
        //정상동작함을 확인하기 위해 제어용 Arduino에서 완료신호가 들어올 때 까지 대기
        
        if (Stage == 0) {
          Serial1.print("Arm:180to0");
          WaitResponse();
          Stage = 1;
        }

        else if (Stage == 1) {
          Serial1.print("Hand:0to180");
          WaitResponse();
          Stage = 2;
        }

        else if (Stage == 2) {
          Serial1.print("Cut1:0to180");
          WaitResponse();
          Stage = 3;
        }

        else if (Stage == 3) {
          Serial1.print("Cut1:180to0");
          WaitResponse();
          Stage = 4;
        }

        else if (Stage == 4) {
          Serial1.print("Arm:0to180");
          WaitResponse();
          Stage = 5;
        }

        else if (Stage == 5) {
          Serial1.print("Hand:180to0");
          WaitResponse();

          Stage = 0;
          buzShort();
        }

        isComplete[9] = 1;


      }
    } else if (readsw10 == 0) {
      if (isComplete[9] == 1) {

        isComplete[9] = 0;
      }
    }


    int readsw11 = !digitalRead(32);
    if (readsw11 == 1) {
      if (isComplete[10] == 0) {
        if (isAuto == 0) {
          if (Manual < 10) {
            Manual = Manual + 1;
            lcd.setCursor(14, 3);
            lcd.print(Manual);
            delay(100);
          }
        }
      }
    } else {

    }

    int readsw12 = !digitalRead(33);
    if (readsw12 == 1) {
      if (isComplete[11] == 0) {
        if (isAuto == 0) {
          if (Manual > 1) {
            Manual = Manual - 1;
            lcd.setCursor(14, 3);
            lcd.print(Manual);
            delay(100);
          }
        }
      }
    } else {

    }

    int readsw13 = !digitalRead(A6);
    if (readsw13 == 1) {
      if (isComplete[12] == 0) {
        checkextPUMP();
        isComplete[12] = 1;
        Serial.print("A");
      }
    } else if (readsw13 == 0) {
      if (isComplete[12] == 1) {
        checkextPUMP();
        isComplete[12] = 0;
        Serial.print("B");
      }
    }

  }

  if (Serial1.available() > 0) {

    while (Serial1.available())
    {
      char inChar = (char)Serial1.read();
      Extinput += inChar;
    }

  } else {
    Extinput = "";
  }
}
