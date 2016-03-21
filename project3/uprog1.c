main() {
  interrupt(0x21,0,"WooHoo! I'm a user program!\r\n\0",0,0);
  while(1);

  //makeInterrupt21();
  //interrupt(0x21, 0x04, "uprog1\0", 0x2000, 0);
  //interrupt(0x21, 0x00, "Done!\n\r\0", 0, 0);
  while(1);
}
