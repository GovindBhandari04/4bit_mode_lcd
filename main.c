#include <stm32f4xx.h>

#define GPIOAEN (1U<<0)
#define GPIOBEN (1U<<1)
#define lcd_rs  (1U<<0)
#define lcd_rw  (1U<<1)
#define lcd_en  (1U<<2)

void lcd_data(unsigned char data) {
    GPIOB -> ODR = (data & 0xf0);
    GPIOA -> ODR |= lcd_rs;
    GPIOA -> ODR &= ~lcd_rw;
    GPIOA -> ODR |= lcd_en;
    for(int i=0; i<2000; i++) {}  // Reduced the delay for illustration purposes
    GPIOA -> ODR &= ~lcd_en;

    GPIOB -> ODR = (data << 4) & 0xf0;
    GPIOA -> ODR |= lcd_rs;
    GPIOA -> ODR &= ~lcd_rw;
    GPIOA -> ODR |= lcd_en;
    for(int i=0; i<2000; i++) {}  // Reduced the delay for illustration purposes
    GPIOA -> ODR &= ~lcd_en;
}

void lcd_command(unsigned char cmd) {
    GPIOB -> ODR = (cmd & 0xf0);
    GPIOA -> ODR &= ~lcd_rs;
    GPIOA -> ODR &= ~lcd_rw;
    GPIOA -> ODR |= lcd_en;
    for(int i=0; i<2000; i++) {}  // Reduced the delay for illustration purposes
    GPIOA -> ODR &= ~lcd_en;

    GPIOB -> ODR = (cmd << 4) & 0xf0;
    GPIOA -> ODR &= ~lcd_rs;
    GPIOA -> ODR &= ~lcd_rw;
    GPIOA -> ODR |= lcd_en;
    for(int i=0; i<2000; i++) {}  // Reduced the delay for illustration purposes
    GPIOA -> ODR &= ~lcd_en;
}

void lcd_string(const char *str) {
    while(*str != '\0')
    {
    	lcd_data(*str);
    	str++;
    }
}

void lcd_initialize() {
    lcd_command(0x02);
    lcd_command(0x28);
    lcd_command(0x0C);
    lcd_command(0x01);
    lcd_command(0x06);
}

int main() {
    RCC -> AHB1ENR |= GPIOAEN | GPIOBEN;
    GPIOA -> MODER |= (1U<<0) | (1U<<2) | (1U<<4);
    GPIOB -> MODER |= (1U<<8) | (1U<<10) | (1U<<12) | (1U<<14);

    lcd_initialize();

    while(1) {
        lcd_command(0x80);
        lcd_string("Hello Govind");

        lcd_command(0xC7);
        lcd_string("Bhandari");
    }
}
