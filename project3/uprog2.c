main() {
  interrupt(0x21, 0, "I'm Back!\r\n\0", 0, 0);
  interrupt(0x05, 0, 0, 0, 0); 
}
