/********************************************************************************
* main.c: Blinkning av lysdiod ansluten till pin 9 / PORTB1 vid nedtryckning 
*         av tryckknapp ansluten till pin 13 / PORTB5.
*
*         F�r implementeringen anv�nds datariktningsregister DDRB f�r att s�tta
*         datariktningen, d�r 1 = utport och 0 = input. Lysdiodens pin (PORTB1)
*         s�tts d�rmed till utport genom att ettst�lla bit 1 i detta register.
*         Det f�rsta vi g�r �r att konfigurera I/O-portarna.
*
*         F�r att tryckknappens insignal alltid skall bli 1 (h�g) eller 0 (l�g)
*         aktiveras den interna pullup-resistorn p� tryckknappens pin (PORTB5).
*         Detta �stadkommes genom att ettst�lla bit 5 i register PORTB vid start.
*         (1 << BUTTON) �r samma som (1 << 5), vilket �r samma som 0010 0000.
*
*         Register PORTB anv�nds ocks� f�r att skriva utsignalen till utportar,
*         d�r 1 = h�g och 0 = l�g, vilket genomf�rs f�r lysdiodens utsignal via
*         makron LED_ON samt LED_OFF. F�r att inte p�verka �vriga bitar anv�nds
*         bitvis OR (|, t�nk bitvis addition).
*         
*         PORTB |= (1 << LED) inneb�r ettst�llning av lysdiodens utsignal 
*         (+1 p� biten LED) utan att p�verka �vriga bitar (+0 p� �vriga bitar).
*         (1 << LED) = 0000 0010; n�r detta adderas p� PORTB s� ettst�lls
*         bit 1 (lysdiodens bit).
*
*         F�r att sl�cka lysdioden nollst�lls bit 1 i register PORTB, vilket
*         �stadkommes genom att multiplicera denna bit med 0, medan �vriga
*         bitar f�rblir op�verkade genom att multiplicera med 1. F�r att
*         genomf�ra detta anv�nds bitvis AND (&, t�nk bitvis multiplikation) 
*         samt negation (~, bitvis invertering fr�n 0 till 1 och tv�rtom).
*
*         PORTB &= ~(1 << LED) inneb�r nollst�llning av lysdiodens utsignal
*         (*0 p� biten LED) utan att p�verka �vriga bitar (*1 p� �vriga bitar).
*         (1 << LED) = 0000 0010, medan ~(1 << LED) = 1111 1101; n�r detta
*         multipliceras bitvis p� PORTB, s� nollst�lls bit 1 (lysdiodens bit).
*
*         F�r att l�sa av tryckknappens insignal s� h�mtas insignalerna fr�n
*         register PINB. Eftersom vi bara �r intresserade av bit 5 s� nollas
*         �vriga bitar genom bitvis multiplikation med (1 << BUTTON), vilket
*         �r samma som 0010 0000. Kvarst�ende v�rde �r antingen 0000 0000 
*         (om tryckknappens insignal var 0, allts� d� tryckknappen inte �r
*         nedtryckt) eller 0010 0000 (om tryckknappens insignal var 1, vilket
*         sker d� tryckknappen �r nedtryckt). D�rmed kontrolleras ifall 
*         kvarst�ende v�rde ej �r lika med 0 via makrot BUTTON_IS_PRESSED.
********************************************************************************/
#define F_CPU 16000000UL /* Definerar klockfrekvensen till 16 MHz, beh�vs f�r korrekt f�rdr�jning. */
#include <avr/io.h>      /* Bibliotek inneh�llande information om mikrodatorns I/O-portar med mera. */
#include <util/delay.h>  /* Bibliotek f�r generering av f�rdr�jning. */

#define LED 1    /* Lysdiod ansluten till pin 9 / PORTB1. */
#define BUTTON 5 /* Tryckknapp ansluten till pin 13 / PORTB5. */

#define LED_ON PORTB |= (1 << LED)                      /* T�nder lysdioden. */
#define LED_OFF PORTB &= ~(1 << LED)                    /* Sl�cker lysdioden. */
#define BUTTON_IS_PRESSED ((PINB & (1 << BUTTON)) != 0) /* Indikerar nedtryckning. */

/********************************************************************************
* main: Konfigurerar pin 9 / PORTB1 till utport samt pin 13 / PORTB5 till inport.
*       Vid nedtryckning av tryckknappen blinkar lysdioden var 100:e millisekund,
*       annars �r den sl�ckt.
********************************************************************************/
int main(void)
{
   DDRB = (1 << LED);     
   PORTB = (1 << BUTTON); 
   
   while (1)
   {
      if (BUTTON_IS_PRESSED)
      {
         LED_ON;
         _delay_ms(100); 
         LED_OFF;
         _delay_ms(100); 
      }
      else
      {
         LED_OFF;
      }
   }

   return 0;
}

