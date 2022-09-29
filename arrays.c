/********************************************************************************
* arrays.c: Repetition av arrayer, lite mer information om strängar.
* 
*           Arrayer utgörs av fält av medlemmar av samma datatyp lagrade 
*           konsekutivt i minnet. Elementen ligger därmed efter varandra och
*           kan därmed liknas vid listor, såsom en int-array döpt data rymmer
*           fem heltal och tilldelas heltal 10, 20, 30, 40 och 50 nedan:
* 
*           int data[5] = { 10, 20, 30, 40, 50 };
* 
*           Samtliga element i arrayen ligger på en viss position, även kallat
*           index, vilket räknar från 0. Det första elementet 10 ligger därmed
*           på index 0 och kan läsas genom att skriva data[0]. Nästa element
*           20 ligger på index 1 och kan läsas gneom att skriva data[1].
* 
*           Värt att komma ihåg om arrayer är att det sista elementet alltid
*           ligger på det index om utgörs av arrayens storlek - 1. I detta
*           fall, då arrayen har storleken 10, så ligger därmed det sista 
*           elementet 50 på index 5 - 1 = 4. Något som är mycket fördelaktigt
*           är att vektorn slutar på index som är lika med vektorns storlek,
*           i detta fall 5. Därmed blir iteration genom arrayer mycket enkelt.
* 
*           Som exempel, för att iterera genom en int-array döpt data som 
*           rymmer fem element från början till slut via index och skriva ut 
*           innehållet kan följande for-sats användas:
* 
*           for (int i = 0; i < 5; ++i)
*           {
*              printf("%d\n", data[i]);
*           }
* 
*           Iterator i börjar på index 0 (första elementet) och slutar när denna
*           har nått index 5, vilket är direkt efter det sista elementet.
* 
*           Eftersom elementen i en vektor ligger på konsekutiva adresser så kan
*           iteration också implementeras via pekare, där startadress kan uppnås
*           genom att låta en pekariterator i börja på adressen till det första
*           elementet. Detta åstadkommes genom att tilldela int* i = data, som 
*           tilldelar adressen till det första elementet (längst fram i arrayen).
*           När adresser används i ställer för index är det värt att komma ihåg
*           att det första elementet ligger på adressen data (eller data + 0),
*           det andra elementet ligger på adressen data + 1 och så vidare.
*           Arrayen slutar på adressen data + 5, alltså startadressen + 5,
*           då vi har fem elemenent.
* 
*           Om en array tilldelas direkt när den deklareras så behöver ingen
*           storlek anges. Storleken sätts då efter antalet element i arrayen.
*           Därmed är det okej att skriva
* 
*           int data[] = { 10, 20, 30, 40, 50 }; // Storleken sätts till 5.
* 
*           Utan initiering måste dock en storlek anges. Därmed är det inte
*           okej att skriva
* 
*           int data[]; // Ej okej utan initiering, här måste en storlek anges.
*  
*           Därmed är följande okej:
* 
*           int data[5]; // Oinitierad array, rymmer fem heltal.
* 
*           För att beräkna hur mycket minne en array upptar kan den så kallade
*           sizeof-operatorn användas, som returnerar storleken i byte i form av
*           datatypen size_t, en osignerade datatyp (bara naturliga tal). 
*           Som exempel, följande returnerar storleken på arrayen data:
* 
*           sizeof(data); // 5 element x 4 byte per element = 20 byte.
* 
*           För att ta reda på minnesåtgången per element, i detta fall minnesåtgången
*           för en int-variabel, kan sizeof-operatorn användas enligt nedan:
* 
*           sizeof(int); // Returerar storleken på en int, alltså 4 byte.
* 
*           Eftersom arrayen rymmer fem heltal, varav varje heltal upptar fyra byte,
*           så upptar arrayen 20 byte. Ovanstående kan beskrivas via följande formel:
* 
*           Arrayens minnesåtgång = Antalet element i arrayen * Minnesåtgång per element.
* 
*           Ovanstående formel kan transformeras till följande för att beräkna antalet
*           element som en array rymmer:
* 
*           Antalet element i arrayen = Arrayens minnesåtgång / Minnesåtgång per element.
* 
*           För arrayen data kan därmed följande ekvation skrivas:
*          
*           Antalet element i arrayen = 20 byte / 4 byte = 5 element.
* 
*           I C-kod skrivs det enligt nedan, där antalet element lagras i en konstant
*           av den osignerade datatypen size_t döpt size.
* 
*           const size_t size = sizeof(data) / sizeof(int);
* 
*           Ifall vi vill att konstanten size skall tillhöra datatypen int så kan en
*           explicit typomvandling göras genom att skriva (int) längst fram i högerledet,
*           med resten inkapslad via en parentes:
* 
*           const int size = (int)(sizeof(data) / sizeof(int));
* 
*           Arrayer kan antingen vara statiska eller dynamiska. Storleken på
*           statiska arrayer kan inte ändras när programmet körs, medan dynamiska 
*           arrayer kan växa och krympa efter behov när programmet körs. 
* 
*           En fördel med statiska arrayer är att vi inte behöver allokera och 
*           frigöra minnet själva, vilket krävs för dynamiska arrayer. När 
*           dynamiska arrayer används så finns därmed risk för minnesläckor om 
*           vi missar att frigöra allokerat minne. Dynamisk minnesallokering är 
*           också relativt tidskrävande, så ofta föredras statiska arrayer, 
*           särskilt i inbyggda system och dylikt, där resurserna är begränsade.
* 
*           När en array passeras till en funktion så passeras automatiskt
*           en pekare till denna, i praktiken till arrayens början / det
*           första elementet. Detta implementerades medvetet av skaparna av C
*           för att öka effektiviteten; i stället för att kunna skapa en kopia 
*           av en array och sedan passera en kopia till denna på stacken så 
*           passeras automatiskt en liten pekare. Därmed behöver man inte
*           använda en adressoperator & när en array skall passeras vid ett
*           funktionsanrop. Iteration med indexering eller pekare fungerar
*           likadant, oavsett om vi har tillgång till arrayen eller bara
*           en pekare till denna.
* 
*           Strängar i C implementeras via arrayer innehållande enstaka tecken,
*           alltså element av datatypen char. Strängar sägs därför utgör så
*           kallade char-arrayer. För att indikera var ett givet textstycke
*           slutar så används nolltecken '\0' för strängar, vilket är effektivt,
*           då man kan lokalisera var strängen slutar via nolltecknet i stället
*           för att behöva hålla reda på antalet tecken manuellt. 
* 
*           Som exempel, anta en given sträng s tilldelas namnet "Kalle Anka":
*           
*           char s[] = "Kalle Anka";
*           
*           Denna sträng s innehåller i praktiken följande:
* 
*           s = { 'K', 'a', 'l', 'l', 'e', ' ', 'A', 'n', 'k', 'a', '\0' };
*           
*           Notera nolltecknet längst bak, som placeras bakom sista tilldelade
*           tecken. Storleken blir därmed 11, varav nio bokstäver, ett blanksteg
*           mellan för- och efternamn samt ett nolltecken.
* 
*           Ifall vi vill iterera genom strängen kan detta göras från index 0
*           tills ett nolltecken nås enligt nedan:
* 
*           for (int i = 0; s[i] != '\0'; ++i) { }
* 
*           != '\0' kan slopas, vilket är normalt. Då kan man utläsa att 
*           for-satsen kör så länge det tecken s[i] vi tittar på är något:
* 
*           for (int i = 0; s[i]; ++i) { }
* 
*           Det är givetvis möjligt att iterera genom strängen via pekare,
*           från adressen till första elementet (char* i = s) tills det tecken 
*           vi tittar på / innehållet på adressen (*i) är ett nolltecken '\0':
* 
*           for (char* i = s; *i != '\0'; ++i) { }
* 
*           Även här kan != '\0' slopas. Vi kan då utläsa så länge det tecken
*           vi tittar på *i är något, så exekverar loopen:
* 
*           for (char* i = s; *i; ++i) { }
********************************************************************************/
#include <stdio.h>

/********************************************************************************
* main: Deklarerar en tom int-array som rymmer 30 heltal. Denna sträng tilldelas
*       heltal 0, 2, 4, 6... 58, vilket sedan skrivs ut i terminalen.
*
*       Därefter deklareras två strängar s1 och s2, som båda tilldelas namnet
*       "Kalle Anka", s1 på förenklat sätt, medan s2 tilldelas i enlighet med
*       övriga arrayer. Vid tilldelning till s1 med det förenklade sättet så
*       sker i praktiken tilldelning på samma sätt som till s2 (samtliga tecken 
*       lagras på var sin adress och textsnutten avslutas med ett nolltecken). 
*       Som tumregel bör alltid det förenklade sättet användas.
*
*       Den första strängens innehåll skrivs ut enkelt via användning av
*       formatspecificerare %s, som läser varje tecken tills ett nolltecken
*       nås, medan den andra strängens innehåll skrivs ut tecken efter tecken
*       via användning av formatspecificerare %c samt iteration via index. 
*       Båda utskrifter fungerar samma; den första används normalt, medan den 
*       andra visar vad som sker vid en sådan utskrift. Som tumregel bör alltid
*       formatspecifierare %s används för utskrift av strängar i stället för
*       iteration genom strängen och utskrift av tecken en efter en. Det finns
*       dock tillfällen när detta behövs, exempelvis transmission av tecken
*       via seriell överföring, vilket vi kommer implementera för mikrodator
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