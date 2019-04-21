//Projekt na Arduino
//Zegar fotograficzny
//Ndzoruje czas wywolywania i naswietlania zdjecia
//Steruje dzialaniem dwoch lamp
//Wyswietla czasy na wuswietlaczu 7-segmentowym sterowanym metoda multipleksacji
//Czasy sutawaine sa prz pomocy encodera
//Do wyzwalania, zatrzymaywania, zerowania i wznawiania czasow sluza cztery przyciski
//Piaty przycisk sluzy do zmianiania wyswietlanych informacji


#define SI 2
#define RCK 3
#define SCK 4
#define przycisk1 5
#define przycisk2 6
#define przycisk3 7
#define przycisk4 8
#define przyciskencodera 9
#define outA 0
#define outB 1
#define przekaznik 10
#define buzz 11

boolean buzzpierwszezerowanie = 0;


boolean rejestr[16];

void setup() {
  
  pinMode(SI, OUTPUT);
  pinMode(RCK, OUTPUT);
  pinMode(SCK, OUTPUT);
  pinMode(przekaznik, OUTPUT);
  pinMode(przycisk1, INPUT_PULLUP);
  pinMode(przycisk2, INPUT_PULLUP);
  pinMode(przycisk3, INPUT_PULLUP);
  pinMode(przycisk4, INPUT_PULLUP);
  pinMode(przyciskencodera, INPUT_PULLUP);
  pinMode(outA, INPUT_PULLUP);
  pinMode(outB, INPUT_PULLUP);
  pinMode(buzz, OUTPUT);


  frejestr();

  Serial.begin(9600);
}




void cyfra(int c)
{
  //c -> cyfra, która ma być wyświetlona

  switch(c)
  {
    case 0:
      //rejestr[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};


        rejestr[0] = HIGH;
        rejestr[1] = HIGH;
        rejestr[2] = HIGH;
        rejestr[3] = HIGH;
        rejestr[4] = HIGH;
        rejestr[5] = HIGH;
        rejestr[6] = LOW;
        
        
      
        frejestr();
      
    break;

    case 1:
      //rejestr[] = {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW};

        rejestr[0] = LOW;
        rejestr[1] = HIGH;
        rejestr[2] = HIGH;
        rejestr[3] = LOW;
        rejestr[4] = LOW;
        rejestr[5] = LOW;
        rejestr[6] = LOW;
        
      
        frejestr();
      
    break;

    case 2:
      //rejestr[] = {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW};

        rejestr[0] = HIGH;
        rejestr[1] = HIGH;
        rejestr[2] = LOW;
        rejestr[3] = HIGH;
        rejestr[4] = HIGH;
        rejestr[5] = LOW;
        rejestr[6] = HIGH;
       
       
        
        frejestr();
      
    break;

    case 3:
      //rejestr[] = {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH, LOW};

        rejestr[0] = HIGH;
        rejestr[1] = HIGH;
        rejestr[2] = HIGH;
        rejestr[3] = HIGH;
        rejestr[4] = LOW;
        rejestr[5] = LOW;
        rejestr[6] = HIGH;
        
       

        frejestr();
      
    break;
    
    case 4:
      //rejestr[] = {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW};

        rejestr[0] = LOW;
        rejestr[1] = HIGH;
        rejestr[2] = HIGH;
        rejestr[3] = LOW;
        rejestr[4] = LOW;
        rejestr[5] = HIGH;
        rejestr[6] = HIGH;
        
      

        frejestr();
      
    break;
    
    case 5:
      //rejestr[] = {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW};

        rejestr[0] = HIGH;
        rejestr[1] = LOW;
        rejestr[2] = HIGH;
        rejestr[3] = HIGH;
        rejestr[4] = LOW;
        rejestr[5] = HIGH;
        rejestr[6] = HIGH;
        
       
        
        frejestr();
      
    break;
    
    case 6:
      //rejestr[] = {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};

        rejestr[0] = HIGH;
        rejestr[1] = LOW;
        rejestr[2] = HIGH;
        rejestr[3] = HIGH;
        rejestr[4] = HIGH;
        rejestr[5] = HIGH;
        rejestr[6] = HIGH;
        
    

        frejestr();
      
    break;
    
    case 7:
      //rejestr[] = {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW};

        rejestr[0] = HIGH;
        rejestr[1] = HIGH;
        rejestr[2] = HIGH;
        rejestr[3] = LOW;
        rejestr[4] = LOW;
        rejestr[5] = LOW;
        rejestr[6] = LOW;
        
        

        frejestr();
      
    break;
    
    case 8:
      //rejestr[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
        rejestr[0] = HIGH;
        rejestr[1] = HIGH;
        rejestr[2] = HIGH;
        rejestr[3] = HIGH;
        rejestr[4] = HIGH;
        rejestr[5] = HIGH;
        rejestr[6] = HIGH;
        
       

        frejestr();

      
    break;
    
    case 9:
      //rejestr[] = {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, LOW};

        rejestr[0] = HIGH;
        rejestr[1] = HIGH;
        rejestr[2] = HIGH;
        rejestr[3] = HIGH;
        rejestr[4] = LOW;
        rejestr[5] = HIGH;
        rejestr[6] = HIGH;
        
     

        frejestr();

      
    break;
    
    case 10:

        //wyświetla "-"
    
      //rejestr[] = {LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW};
        rejestr[0] = LOW;
        rejestr[1] = LOW;
        rejestr[2] = LOW;
        rejestr[3] = LOW;
        rejestr[4] = LOW;
        rejestr[5] = LOW;
        rejestr[6] = HIGH;
        
      
        frejestr();


      
    break;

    case 11:

        //zgaszony ekran
    
      //rejestr[] = {LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW};
        rejestr[0] = LOW;
        rejestr[1] = LOW;
        rejestr[2] = LOW;
        rejestr[3] = LOW;
        rejestr[4] = LOW;
        rejestr[5] = LOW;
        rejestr[6] = LOW;
        
      

        frejestr();


      
    break;
  }

  
}



void frejestr()
{

  // sprawdzic czy RCK i SCK nie są zamienione
  
  digitalWrite(RCK, LOW);
  
  for(int i = 16; i>=0; i--)
  {
    digitalWrite(SCK, LOW);

    digitalWrite(SI, rejestr[i]);

    digitalWrite(SCK, HIGH);  
  }

  digitalWrite(RCK, HIGH);
}

int a, b, c, d;
int czasodswiezaniaekranu = 1;

void wyswietl(int liczba, int wyswietlanyczas)
{
  a = liczba/1000;
  b = (liczba%1000)/100;
  c = (liczba%100)/10;
  d = liczba%10;

  
  //a -> pierwszy ekran, b -> drugi ekran, c -> trzeci ekran, d -> czwarty ekran

  /*digitalWrite(pierwszacyfra, HIGH);
  digitalWrite(drugacyfra, LOW);
  digitalWrite(trzeciacyfra, LOW);
  digitalWrite(czwartacyfra, LOW);*/
  
  
  rejestr[8] = HIGH;
  rejestr[9] = LOW;
  rejestr[10] = LOW;
  rejestr[11] = LOW;

  if(liczba == 9999)
  {
    cyfra(10);
  }
  else if(a == 0) //żeby nie wyświttlało tej cyfry niepotrzebnie
  {
    cyfra(11); 
  }
  else
  {
    cyfra(a);
  }

  
  
  

  delay(czasodswiezaniaekranu);

  /*digitalWrite(pierwszacyfra, LOW);
  digitalWrite(drugacyfra, HIGH);
  digitalWrite(trzeciacyfra, LOW);
  digitalWrite(czwartacyfra, LOW);*/
  rejestr[8] = LOW;
  rejestr[9] = HIGH;
  rejestr[10] = LOW;
  rejestr[11] = LOW;
  
  if(liczba == 9999)
  {
    cyfra(10);
  }
  else if((b == 0 && a > 0) || b > 0) //żeby nie wyświttlało tej cyfry niepotrzebnie
  {
    cyfra(b);
  }
  else
  {
    cyfra(11);
  }

  

  delay(czasodswiezaniaekranu);

  /*digitalWrite(pierwszacyfra, LOW);
  digitalWrite(drugacyfra, LOW);
  digitalWrite(trzeciacyfra, HIGH);
  digitalWrite(czwartacyfra, LOW);*/
  rejestr[8] = LOW;
  rejestr[9] = LOW;
  rejestr[10] = HIGH;
  rejestr[11] = LOW;

   if(wyswietlanyczas == 0 && liczba != 9999)
    {
      rejestr[7] = HIGH;
    }
    else
    {
      rejestr[7] = LOW;
    }
    
    if(liczba == 9999)
    {
      cyfra(10);
    }
    else
    {
      cyfra(c);
    }
  

   rejestr[7] = LOW;

   

  delay(czasodswiezaniaekranu);

  /*digitalWrite(pierwszacyfra, LOW);
  digitalWrite(drugacyfra, LOW);
  digitalWrite(trzeciacyfra, LOW);
  digitalWrite(czwartacyfra, HIGH);*/
  rejestr[8] = LOW;
  rejestr[9] = LOW;
  rejestr[10] = LOW;
  rejestr[11] = HIGH;

   if(liczba == 9999)
  {
    cyfra(10);
  }
  else
  {
    cyfra(d);
  }

  

 

  delay(czasodswiezaniaekranu);


}

long czaswyw = millis();
long czasre = millis();

int q=0;

int czaswywolywania = 600;


boolean czaswywolywaniadzialaj = 0;
boolean czaswywolywaniazeruj = 0;
boolean czasresztydzialaj = 0;
boolean czasresztyzeruj = 0;

int czas[4] = {60, 4, 7, 5};
int czaszapamietany[4] = {60, 4, 7, 5};

//czas[0] = 600; //czas wywolywania
//czas[1] = 45; //czas reszty 1
//czas[2] = 30; //czas reszty 2

int wyswietlanyczas = 0;

int obrot = 0;
int nowyA, staryA = 0;

int freq = 3000, buzzile = 0;
long long czasbuzz = 0;
boolean buzzdziala = 1;


int buzzer(int freq, int buzzile)
{ 
  
  if((millis() - czasbuzz) > 80)
{
  buzzdziala = !buzzdziala;
  

  
  if(buzzile < 4)
  {
    if(buzzdziala == 1)
    {
      tone(buzz, freq);
      
      buzzile++;
    }
    else
    {
      noTone(buzz);
    }
  }
  else
  {
    noTone(buzz);
    buzzdziala = 1;
  }

  czasbuzz = millis();
}

return buzzile;

}





boolean fprzycisk1(boolean wlprzekaznik, int czas)
{
  if(digitalRead(przycisk1) == LOW)
  {
    delay(20);

    czaswywolywaniadzialaj = !czaswywolywaniadzialaj;

    if(czaswywolywaniadzialaj == 1)
    {
      czaswywolywaniazeruj = 0;
      
    }
    if(czas <=0)
    {
       wlprzekaznik = 1;      
    }
    else
    {
      wlprzekaznik = !wlprzekaznik;
    }
    
     
      
    while(digitalRead(przycisk1) == LOW);

    delay(20);
  }

  return wlprzekaznik;  
}




void fprzycisk3()
{
  if(digitalRead(przycisk3) == LOW)
  {
    delay(20);

    czasresztydzialaj = !czasresztydzialaj;

    if(czasresztydzialaj == 1)
    {
      czasresztyzeruj = 0;
    }

    while(digitalRead(przycisk3) == LOW);

    delay(20);
  }
  
}

boolean czyresztastartowa = 0;

int fprzycisk4(int wyswietlanyczas, boolean czyresztastartowa)
{
  if(digitalRead(przycisk4) == LOW)
  {
    delay(20);

    

    if(czyresztastartowa == 1)
    {
      wyswietlanyczas++;

      if(wyswietlanyczas > 3)
      {
        wyswietlanyczas = 0;
      }
    }
    else
    {
      czasresztyzeruj = !czasresztyzeruj;

      if(czasresztyzeruj == 1)
      {
        czasresztydzialaj = 0;
      }
    }
    

    while(digitalRead(przycisk4) == LOW);

    delay(20);
  }
  return wyswietlanyczas;
  
}

boolean skala = 0;



int fprzyciskencodera(boolean skala)
{
  if(digitalRead(przyciskencodera) == LOW)
  {
    delay(20);

    skala = !skala;

    while(digitalRead(przyciskencodera) == LOW);

    delay(20);
  }

  return skala;
  
}

void diody(int ktoryczas)
{
  if(ktoryczas == 0)
    {
      rejestr[12] = HIGH;
      rejestr[13] = LOW;
      rejestr[14] = LOW;

    }
    
    if(ktoryczas == 1)
    {
      rejestr[12] = HIGH;
      rejestr[13] = HIGH;
      rejestr[14] = LOW;

    }
    
    if(ktoryczas == 2)
    {
      rejestr[12] = HIGH;
      rejestr[13] = HIGH;
      rejestr[14] = HIGH;

    }

    if(ktoryczas == 4)
    {
      rejestr[12] = LOW;
      rejestr[13] = LOW;
      rejestr[14] = LOW;

    }
}

int ktoryczas = 0; //ktory czas z reszty czasow (bez tego dokladnego)

boolean wylbuzz = 0, wlprzekaznik = 0, wlprzekazniknastale = 0;


void loop() {

wlprzekaznik = fprzycisk1(wlprzekaznik, czas[0]);
//wlprzekaznik = fprzycisk2(wlprzekaznik);
fprzycisk3();
wyswietlanyczas = fprzycisk4(wyswietlanyczas, czyresztastartowa);
skala = fprzyciskencodera(skala);
//czas = encoder(wyswietlanyczas, czaswywolywaniadzialaj, czasresztydzialaj, skala);


diody(ktoryczas);
  
  if((millis() - czaswyw) > 100)
{
    
  if(czas[0] > 0 && czaswywolywaniadzialaj == 1)
  {
    czas[0]--;
  }


  czaswyw = millis();
}

if((millis() - czasre) > 1000)
{
    
  if(czas[1] > 0 && czasresztydzialaj == 1)
  {
    czas[1]--;
    
  }

  if(czas[1] == 0 && czasresztydzialaj == 1 && czas[2] > 0)
  {
    czas[2]--;

  }
  
  if(czas[1] == 0 && czas[2] == 0 && czasresztydzialaj == 1 && czas[3] > 0)
  {
    czas[3]--;

  }

  czasre = millis();
}

if(digitalRead(przycisk2) == LOW)
  {
    delay(20);

    czaswywolywaniazeruj = !czaswywolywaniazeruj;

    if(czaswywolywaniazeruj == 1)
    {
      czaswywolywaniadzialaj = 0;      
      
    }

    if(czas[0] == czaszapamietany[0])
    {
       wlprzekazniknastale = !wlprzekazniknastale;

       wlprzekaznik = !wlprzekaznik;
    }
    else
    {
      wlprzekaznik = 0;
    }
    
    

    while(digitalRead(przycisk2) == LOW);

    delay(20);
  }

if(wlprzekazniknastale == 0)
{
  wyswietl(czas[wyswietlanyczas], wyswietlanyczas);
}
else
{
  wyswietl(9999, wyswietlanyczas);
}


        
        

        if(czaswywolywaniazeruj == 1)
        {
          czas[0] = czaszapamietany[0];
        }

        if(czasresztyzeruj == 1)
        {
          czas[1] = czaszapamietany[1];
          czas[2] = czaszapamietany[2];
          czas[3] = czaszapamietany[3];

          wylbuzz = 0;
          buzzile = 0;
        }

        if(czas[0] <= 0)
        {
          czas[0] = czaszapamietany[0];
          czaswywolywaniadzialaj = 0;

          wlprzekaznik = 0;                    
        }
        
        if(wlprzekaznik == 1)
        {
          digitalWrite(przekaznik, HIGH);
          
        } 
        else
        {
          digitalWrite(przekaznik, LOW);
           
        }

        if(czas[1] <= 0)
        {                   
          buzzile = buzzer(freq, buzzile);                  
        }
      

        if(czas[1] <= 0 && czas[2] <= 0 && wylbuzz == 0 && buzzpierwszezerowanie == 0)
        {
          
            buzzile = 0; 

            buzzpierwszezerowanie = 1;           
           
           wylbuzz = 0;
           
          
        }

         if(czas[1] <= 0 && czas[2] <= 0 && wylbuzz == 0)
        {
             

          buzzile = buzzer(freq, buzzile); 

             if(buzzile >3)
             {
                wylbuzz == 1;
             }
           
        }
        
        

        

        if(czas[1] <= 0 && czas[2] <= 0 && czas[3] <= 0)
        {

          buzzile = 0;

          while(buzzile < 3)
          {
            buzzile = buzzer(freq, buzzile);

            
          }        
                  
         noTone(buzz);
                   
        }

        if(czas[1] <= czaszapamietany[1] && czas[1] > 0 && czas[2] == czaszapamietany[2] && czas[3] == czaszapamietany[3])
        {
          ktoryczas = 0;
        }
        else if(czas[1] <= 0 && czas[2] <= czaszapamietany[2] && czas[2] > 0 && czas[3] == czaszapamietany[3])
        {
          ktoryczas = 1;
        }
        else
        {
          ktoryczas = 2;
        }

        if(czas[1] == czaszapamietany[1] && czas[2] == czaszapamietany[2] && czas[3] == czaszapamietany[3])
        {
          ktoryczas = 4;
        }
        

        if(czas[1] == czaszapamietany[1] && czas[2] == czaszapamietany[2] && czas[3] == czaszapamietany[3])
        {
          czyresztastartowa = 1;
        }
        else
        {
          czyresztastartowa = 0;
        }

        
 


nowyA = digitalRead(outA);

  
  if(staryA != nowyA && wyswietlanyczas == 0 && czaswywolywaniadzialaj == 0)
  {
    if(nowyA == digitalRead(outB))
    {
      
      if(skala == 0)
      {
        czas[wyswietlanyczas]--;
      }
      else
      {
        czas[wyswietlanyczas] -= 10;
      }

      if(czas[wyswietlanyczas] <= 0)
      {
        czas[wyswietlanyczas] = 0;
      }
           
      
      
      czaszapamietany[wyswietlanyczas] = czas[wyswietlanyczas];
    }
    else
    {
      if(skala == 0)
      {
        czas[wyswietlanyczas]++;
      }
      else
      {
        czas[wyswietlanyczas] += 10;
      }

      if(czas[wyswietlanyczas] <= 0)
      {
        czas[wyswietlanyczas] = 0;
      }

        
     
      czaszapamietany[wyswietlanyczas] = czas[wyswietlanyczas];
    }

  }

  if(staryA != nowyA && (wyswietlanyczas == 1 || wyswietlanyczas == 2 || wyswietlanyczas == 3) && czasresztydzialaj == 0)
  {
    if(nowyA == digitalRead(outB))
    {
      czas[wyswietlanyczas]--;
      
      if(czas[wyswietlanyczas] <= 0)
      {
        czas[wyswietlanyczas] = 0;
      }
      
      czaszapamietany[wyswietlanyczas] = czas[wyswietlanyczas];
    }
    else
    {
      czas[wyswietlanyczas]++;

      if(czas[wyswietlanyczas] <= 0)
      {
        czas[wyswietlanyczas] = 0;
      }
      
      czaszapamietany[wyswietlanyczas] = czas[wyswietlanyczas];
    }
    
  }
  
  staryA = nowyA;



  if(czas[1] <= 0 && czas[2] <= 0 && czas[3] <= 0)
        {
          czas[1] = czaszapamietany[1];
          czas[2] = czaszapamietany[2];
          czas[3] = czaszapamietany[3];
          czasresztydzialaj = 0; 
          
        }

        

        

}
