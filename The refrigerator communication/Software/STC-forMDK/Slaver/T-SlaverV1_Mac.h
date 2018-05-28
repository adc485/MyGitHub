void IapIdle();
unsigned char IapRead(int addr);
void IapProgram(int addr, char dat); 
void Slaver_Write_Mac(int addr, unsigned char *dat, int num);
void Slaver_Read_Mac(int addr, unsigned char *dat, int num);