#include "drivers/terminal.h"
#include "cpu/ports.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buff = (uint16_t*) 0xB8000;

void terminal_initialize(void){
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

    for(size_t y=0; y<VGA_HEIGHT; y++){
        for(size_t x=0; x<VGA_WIDTH; x++){
            const size_t idx = y*VGA_WIDTH+x;
            terminal_buff[idx] = vga_entry(' ', terminal_color);
        }
    }
    terminal_update_cursor();
}

void terminal_putchar(char c){
    if(c == '\b'){
        if(terminal_column > 0) terminal_column--;
        else if(terminal_row > 0){
            terminal_row--;
            terminal_column = VGA_WIDTH-1;
        }
        const size_t idx = terminal_row * VGA_WIDTH + terminal_column;
        terminal_buff[idx] = vga_entry(' ', terminal_color);

        terminal_update_cursor();
        return;
    }
    if(c == '\n'){
        terminal_column = 0;
        if(++terminal_row == VGA_HEIGHT){
            terminal_row =0;
        }
        terminal_update_cursor();
        return;
    }
    const size_t idx = terminal_row*VGA_WIDTH + terminal_column;
    terminal_buff[idx] = vga_entry(c, terminal_color);
    if(++terminal_column==VGA_WIDTH){
        terminal_column = 0;
        if(++terminal_row==VGA_HEIGHT){
            terminal_row=0;
        }
    }
    terminal_update_cursor();
}

void terminal_writestring(const char* data){
    for(size_t i=0; data[i]!='\0'; i++){
        terminal_putchar(data[i]);
    }
}

void terminal_update_cursor(void){
    uint16_t pos = terminal_row * VGA_WIDTH + terminal_column;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos>>8) & 0xFF));

}


