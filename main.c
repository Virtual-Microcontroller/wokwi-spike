void uart_init(void);
void uart_puts(const char *s);
void led_init(void);
void led_set(int on);
void button_init(void);
int  button_pressed(void);

/* Busy waiting rather than a timer, because the point of this project is the
   pins and the serial line. A timer-driven version is a later exercise. */
static void delay(volatile unsigned long n)
{
    while (n--) { }
}

int main(void)
{
    uart_init();
    led_init();
    button_init();

    /* AI-HINT: 文字列リテラルの終わりの " はどこにありますか。21 行目と 22 行目に分かれていますが、これは C では許可されていません */
    uart_puts("Hello from Blue Pill!
");

    int was_pressed = 0;

    for (;;) {
        int is_pressed = button_pressed();

        /* Report the edge, not the level. Reporting the level would print on
           every pass of the loop for as long as a finger rests on the button. */
        if (is_pressed && !was_pressed) {
            uart_puts("Button pressed\n");
        }
        was_pressed = is_pressed;

        led_set(1);
        delay(100000);
        led_set(0);
        delay(100000);
    }
}
