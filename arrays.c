/********************************************************************************
* arrays.c: Repetition av arrayer, lite mer information om str�ngar.
* 
*           Arrayer utg�rs av f�lt av medlemmar av samma datatyp lagrade 
*           konsekutivt i minnet. Elementen ligger d�rmed efter varandra och
*           kan d�rmed liknas vid listor, s�som en int-array d�pt data rymmer
*           fem heltal och tilldelas heltal 10, 20, 30, 40 och 50 nedan:
* 
*           int data[5] = { 10, 20, 30, 40, 50 };
* 
*           Samtliga element i arrayen ligger p� en viss position, �ven kallat
*           index, vilket r�knar fr�n 0. Det f�rsta elementet 10 ligger d�rmed
*           p� index 0 och kan l�sas genom att skriva data[0]. N�sta element
*           20 ligger p� index 1 och kan l�sas gneom att skriva data[1].
* 
*           V�rt att komma ih�g om arrayer �r att det sista elementet alltid
*           ligger p� det index om utg�rs av arrayens storlek - 1. I detta
*           fall, d� arrayen har storleken 10, s� ligger d�rmed det sista 
*           elementet 50 p� index 5 - 1 = 4. N�got som �r mycket f�rdelaktigt
*           �r att vektorn slutar p� index som �r lika med vektorns storlek,
*           i detta fall 5. D�rmed blir iteration genom arrayer mycket enkelt.
* 
*           Som exempel, f�r att iterera genom en int-array d�pt data som 
*           rymmer fem element fr�n b�rjan till slut via index och skriva ut 
*           inneh�llet kan f�ljande for-sats anv�ndas:
* 
*           for (int i = 0; i < 5; ++i)
*           {
*              printf("%d\n", data[i]);
*           }
* 
*           Iterator i b�rjar p� index 0 (f�rsta elementet) och slutar n�r denna
*           har n�tt index 5, vilket �r direkt efter det sista elementet.
* 
*           Eftersom elementen i en vektor ligger p� konsekutiva adresser s� kan
*           iteration ocks� implementeras via pekare, d�r startadress kan uppn�s
*           genom att l�ta en pekariterator i b�rja p� adressen till det f�rsta
*           elementet. Detta �stadkommes genom att tilldela int* i = data, som 
*           tilldelar adressen till det f�rsta elementet (l�ngst fram i arrayen).
*           N�r adresser anv�nds i st�ller f�r index �r det v�rt att komma ih�g
*           att det f�rsta elementet ligger p� adressen data (eller data + 0),
*           det andra elementet ligger p� adressen data + 1 och s� vidare.
*           Arrayen slutar p� adressen data + 5, allts� startadressen + 5,
*           d� vi har fem elemenent.
* 
*           Om en array tilldelas direkt n�r den deklareras s� beh�ver ingen
*           storlek anges. Storleken s�tts d� efter antalet element i arrayen.
*           D�rmed �r det okej att skriva
* 
*           int data[] = { 10, 20, 30, 40, 50 }; // Storleken s�tts till 5.
* 
*           Utan initiering m�ste dock en storlek anges. D�rmed �r det inte
*           okej att skriva
* 
*           int data[]; // Ej okej utan initiering, h�r m�ste en storlek anges.
*  
*           D�rmed �r f�ljande okej:
* 
*           int data[5]; // Oinitierad array, rymmer fem heltal.
* 
*           F�r att ber�kna hur mycket minne en array upptar kan den s� kallade
*           sizeof-operatorn anv�ndas, som returnerar storleken i byte i form av
*           datatypen size_t, en osignerade datatyp (bara naturliga tal). 
*           Som exempel, f�ljande returnerar storleken p� arrayen data:
* 
*           sizeof(data); // 5 element x 4 byte per element = 20 byte.
* 
*           F�r att ta reda p� minnes�tg�ngen per element, i detta fall minnes�tg�ngen
*           f�r en int-variabel, kan sizeof-operatorn anv�ndas enligt nedan:
* 
*           sizeof(int); // Returerar storleken p� en int, allts� 4 byte.
* 
*           Eftersom arrayen rymmer fem heltal, varav varje heltal upptar fyra byte,
*           s� upptar arrayen 20 byte. Ovanst�ende kan beskrivas via f�ljande formel:
* 
*           Arrayens minnes�tg�ng = Antalet element i arrayen * Minnes�tg�ng per element.
* 
*           Ovanst�ende formel kan transformeras till f�ljande f�r att ber�kna antalet
*           element som en array rymmer:
* 
*           Antalet element i arrayen = Arrayens minnes�tg�ng / Minnes�tg�ng per element.
* 
*           F�r arrayen data kan d�rmed f�ljande ekvation skrivas:
*          
*           Antalet element i arrayen = 20 byte / 4 byte = 5 element.
* 
*           I C-kod skrivs det enligt nedan, d�r antalet element lagras i en konstant
*           av den osignerade datatypen size_t d�pt size.
* 
*           const size_t size = sizeof(data) / sizeof(int);
* 
*           Ifall vi vill att konstanten size skall tillh�ra datatypen int s� kan en
*           explicit typomvandling g�ras genom att skriva (int) l�ngst fram i h�gerledet,
*           med resten inkapslad via en parentes:
* 
*           const int size = (int)(sizeof(data) / sizeof(int));
* 
*           Arrayer kan antingen vara statiska eller dynamiska. Storleken p�
*           statiska arrayer kan inte �ndras n�r programmet k�rs, medan dynamiska 
*           arrayer kan v�xa och krympa efter behov n�r programmet k�rs. 
* 
*           En f�rdel med statiska arrayer �r att vi inte beh�ver allokera och 
*           frig�ra minnet sj�lva, vilket kr�vs f�r dynamiska arrayer. N�r 
*           dynamiska arrayer anv�nds s� finns d�rmed risk f�r minnesl�ckor om 
*           vi missar att frig�ra allokerat minne. Dynamisk minnesallokering �r 
*           ocks� relativt tidskr�vande, s� ofta f�redras statiska arrayer, 
*           s�rskilt i inbyggda system och dylikt, d�r resurserna �r begr�nsade.
* 
*           N�r en array passeras till en funktion s� passeras automatiskt
*           en pekare till denna, i praktiken till arrayens b�rjan / det
*           f�rsta elementet. Detta implementerades medvetet av skaparna av C
*           f�r att �ka effektiviteten; i st�llet f�r att kunna skapa en kopia 
*           av en array och sedan passera en kopia till denna p� stacken s� 
*           passeras automatiskt en liten pekare. D�rmed beh�ver man inte
*           anv�nda en adressoperator & n�r en array skall passeras vid ett
*           funktionsanrop. Iteration med indexering eller pekare fungerar
*           likadant, oavsett om vi har tillg�ng till arrayen eller bara
*           en pekare till denna.
* 
*           Str�ngar i C implementeras via arrayer inneh�llande enstaka tecken,
*           allts� element av datatypen char. Str�ngar s�gs d�rf�r utg�r s�
*           kallade char-arrayer. F�r att indikera var ett givet textstycke
*           slutar s� anv�nds nolltecken '\0' f�r str�ngar, vilket �r effektivt,
*           d� man kan lokalisera var str�ngen slutar via nolltecknet i st�llet
*           f�r att beh�va h�lla reda p� antalet tecken manuellt. 
* 
*           Som exempel, anta en given str�ng s tilldelas namnet "Kalle Anka":
*           
*           char s[] = "Kalle Anka";
*           
*           Denna str�ng s inneh�ller i praktiken f�ljande:
* 
*           s = { 'K', 'a', 'l', 'l', 'e', ' ', 'A', 'n', 'k', 'a', '\0' };
*           
*           Notera nolltecknet l�ngst bak, som placeras bakom sista tilldelade
*           tecken. Storleken blir d�rmed 11, varav nio bokst�ver, ett blanksteg
*           mellan f�r- och efternamn samt ett nolltecken.
* 
*           Ifall vi vill iterera genom str�ngen kan detta g�ras fr�n index 0
*           tills ett nolltecken n�s enligt nedan:
* 
*           for (int i = 0; s[i] != '\0'; ++i) { }
* 
*           != '\0' kan slopas, vilket �r normalt. D� kan man utl�sa att 
*           for-satsen k�r s� l�nge det tecken s[i] vi tittar p� �r n�got:
* 
*           for (int i = 0; s[i]; ++i) { }
* 
*           Det �r givetvis m�jligt att iterera genom str�ngen via pekare,
*           fr�n adressen till f�rsta elementet (char* i = s) tills det tecken 
*           vi tittar p� / inneh�llet p� adressen (*i) �r ett nolltecken '\0':
* 
*           for (char* i = s; *i != '\0'; ++i) { }
* 
*           �ven h�r kan != '\0' slopas. Vi kan d� utl�sa s� l�nge det tecken
*           vi tittar p� *i �r n�got, s� exekverar loopen:
* 
*           for (char* i = s; *i; ++i) { }
********************************************************************************/
#include <stdio.h>

/********************************************************************************
* main: Deklarerar en tom int-array som rymmer 30 heltal. Denna str�ng tilldelas
*       heltal 0, 2, 4, 6... 58, vilket sedan skrivs ut i terminalen.
*
*       D�refter deklareras tv� str�ngar s1 och s2, som b�da tilldelas namnet
*       "Kalle Anka", s1 p� f�renklat s�tt, medan s2 tilldelas i enlighet med
*       �vriga arrayer. Vid tilldelning till s1 med det f�renklade s�ttet s�
*       sker i praktiken tilldelning p� samma s�tt som till s2 (samtliga tecken 
*       lagras p� var sin adress och textsnutten avslutas med ett nolltecken). 
*       Som tumregel b�r alltid det f�renklade s�ttet anv�ndas.
*
*       Den f�rsta str�ngens inneh�ll skrivs ut enkelt via anv�ndning av
*       formatspecificerare %s, som l�ser varje tecken tills ett nolltecken
*       n�s, medan den andra str�ngens inneh�ll skrivs ut tecken efter tecken
*       via anv�ndning av formatspecificerare %c samt iteration via index. 
*       B�da utskrifter fungerar samma; den f�rsta anv�nds normalt, medan den 
*       andra visar vad som sker vid en s�dan utskrift. Som tumregel b�r alltid
*       formatspecifierare %s anv�nds f�r utskrift av str�ngar i st�llet f�r
*       iteration genom str�ngen och utskrift av tecken en efter en. Det finns
*       dock tillf�llen n�r detta beh�vs, exempelvis transmission av tecken
*       via seriell �verf�ring, vilket vi kommer implementera f�r mikrodator
*       ATmega328P.
********************************************************************************/
int main(void)
{
   int data[30];
   int num = 0;

   for (int i = 0; i < 30; ++i)
   {
      data[i] = num;
      num += 2;
   }

   for (int i = 0; i < 30; ++i)
   {
      printf("%d\n", data[i]);
   }

   printf("\n\n");

   char s1[] = "Kalle Anka";
   char s2[] = { 'K', 'a', 'l', 'l', 'e', ' ', 'A', 'n', 'k', 'a', '\0' };
   
   printf("%s\n\n", s1);

   for (int i = 0; s2[i] != '\0'; ++i)
   {
      printf("%c", s2[i]);
   }

   return 0;
}