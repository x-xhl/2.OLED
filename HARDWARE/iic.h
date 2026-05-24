#ifndef __I2C_H
#define __I2C_H

void iic_init(void);
void iic_SDA_out(void);
void iic_SDA_in(void);
void iic_start(void);
void iic_stop(void);
void iic_send_ark(char ark);
unsigned char iic_receive_ark(void);
void iic_write_byte(unsigned char Byte);


#endif
