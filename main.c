/********************************************************************************
* main.c: Blinkning av lysdiod ansluten till pin 9 / PORTB1 vid nedtryckning 
*         av tryckknapp ansluten till pin 13 / PORTB5.
*
*         För implementeringen används datariktningsregister DDRB för att sätta
*         datariktningen, där 1 = utport och 0 = input. Lysdiodens pin (PORTB1)
*         sätts därmed till utport genom att ettställa bit 1 i detta register.
*         Det första vi gör är att konfigurera I/O-portarna.
*
*         För att tryckknappens insignal alltid skall bli 1 (hög) eller 0 (låg)
*         aktiveras den interna pullup-resistorn på tryckknappens pin (PORTB5).
*         Detta åstadkommes genom att ettställa bit 5 i register PORTB vid start.
*         (1 << BUTTON) är samma som (1 << 5), vilket är samma som 0010 0000.
*
*         Register PORTB används också för att skriva utsignalen till utportar,
*         där 1 = hög och 0 = låg, vilket genomförs för lysdiodens utsignal via
*         makron LED_ON samt LED_OFF. För att inte påverka övriga bitar används
*         bitvis OR (|, tänk bitvis addition).
*         
*         PORTB |= (1 << LED) innebär ettställning av lysdiodens utsignal 
*         (+1 på biten LED) utan att påverka övriga bitar (+0 på övriga bitar).
*         (1 << LED) = 0000 0010; när detta adderas på PORTB så ettställs
*         bit 1 (lysdiodens bit).
*
*         För att släcka lysdioden nollställs bit 1 i register PORTB, vilket
*         åstadkommes genom att multiplicera denna bit med 0, medan övriga
*         bitar förblir opåverkade genom att multiplicera med 1. För att
*         genomföra detta används bitvis AND (&, tänk bitvis multiplikation) 
*         samt negation (~, bitvis invertering från 0 till 1 och tvärtom).
*
*         PORTB &= ~(1 << LED) innebär nollställning av lysdiodens utsignal
*         (*0 på biten LED) utan att påverka övriga bitar (*1 på övriga bitar).
*         (1 << LED) = 0000 0010, medan ~(1 << LED) = 1111 1101; när detta
*         multipliceras bitvis på PORTB, så nollställs bit 1 (lysdiodens bit).
*
*         För att läsa av tryckknappens insignal så hämtas insignalerna från
*         register PINB. Eftersom vi bara är intresserade av bit 5 så nollas
*         övriga bitar genom bitvis multiplikation med (1 << BUTTON), vilket
*         är samma som 0010 0000. Kvarstående värde är antingen 0000 0000 
*         (om tryckknappens insignal var 0, alltså då tryckknappen inte är
*         nedtryckt) eller 0010 0000 (om tryckknappens insignal var 1, vilket
*         sker då tryckknappen är nedtryckt). Därmed kontrolleras ifall 
*         kvarstående värde ej är lika med 0 via makrot BUTTON_IS_PRESSED.
********************************************************************************/
#define F_CPU 16000000UL /* Definerar klockfrekvensen till 16 MHz, behövs för korrekt fördröjning. */
#include <avr/io.h>      /* Bibliotek innehållande information om mikrodatorns I/O-portar med mera. */
#include <util/delay.h>  /* Bibliotek för generering av fördröjning. */

#define LED 1    /* Lysdiod ansluten till pin 9 / PORTB1. */
#define BUTTON 5 /* Tryckknapp ansluten till pin 13 / PORTB5. */

#define LED_ON PORTB |= (1 << LED)                      /* Tänder lysdioden. */
#define LED_OFF PORTB &= ~(1 << LED)                    /* Släcker lysdioden. */
#define BUTTON_IS_PRESSED ((PINB & (1 << BUTTON)) != 0) /* Indikerar nedtryckning. */

/********************************************************************************
* main: Konfigurerar pin 9 / PORTB1 till utport samt pin 13 / PORTB5 till inport.
*       Vid nedtryckning av tryckknappen blinkar lysdioden var 100:e millisekund,
*       annars är den släckt.
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

