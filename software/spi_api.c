#include "uart_api.h"
#include "spi_api.h"

void SPI_Enable(void)
{
    SPI->SPI_CONTROL = ((1 << 6));
    SPI->SPI_EXTENSION = 0x03;
}

uint8_t PS2_Raw_Data[8];
void Get_PS2_Data(PS2 *PS2_data, bool verbose)
{
    SPI->SPI_CONTROL = ((1 << 5) | (1 << 6)); // enable CS
    // delay_us(20);
    // 每次处理4个 fifo大小是4 处理两轮 最后一个不要了
    uint8_t cmd_require2[9] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    SPI->SPI_DATA = cmd_require2[0];
    SPI->SPI_DATA = cmd_require2[1];
    SPI->SPI_DATA = cmd_require2[2];
    SPI->SPI_DATA = cmd_require2[3];
    SPI->SPI_DATA = cmd_require2[4];
    SPI->SPI_DATA = cmd_require2[5];
    SPI->SPI_DATA = cmd_require2[6];
    SPI->SPI_DATA = cmd_require2[7];
    // 等待读fifo满
    while (!(SPI->SPI_STATE & 0x02))
        ;
    // delay_ms(100);
    PS2_Raw_Data[0] = SPI->SPI_DATA;
    PS2_Raw_Data[1] = SPI->SPI_DATA;
    PS2_Raw_Data[2] = SPI->SPI_DATA;
    PS2_Raw_Data[3] = SPI->SPI_DATA;
    PS2_Raw_Data[4] = SPI->SPI_DATA;
    PS2_Raw_Data[5] = SPI->SPI_DATA;
    PS2_Raw_Data[6] = SPI->SPI_DATA;
    PS2_Raw_Data[7] = SPI->SPI_DATA;
    // print("\n");
    SPI->SPI_CONTROL = (1 << 6); // disable CS
    // 处理对应位置按键
    PS2_data->L1 = !(PS2_Raw_Data[4] & PS2_OFFSET_L1);
    PS2_data->L2 = !(PS2_Raw_Data[4] & PS2_OFFSET_L2);
    PS2_data->R1 = !(PS2_Raw_Data[4] & PS2_OFFSET_R1);
    PS2_data->R2 = !(PS2_Raw_Data[4] & PS2_OFFSET_R2);
    PS2_data->La = !(PS2_Raw_Data[3] & PS2_OFFSET_a);
    PS2_data->Lb = !(PS2_Raw_Data[3] & PS2_OFFSET_b);
    PS2_data->Lc = !(PS2_Raw_Data[3] & PS2_OFFSET_c);
    PS2_data->Ld = !(PS2_Raw_Data[3] & PS2_OFFSET_d);
    PS2_data->Ra = !(PS2_Raw_Data[4] & PS2_OFFSET_a);
    PS2_data->Rb = !(PS2_Raw_Data[4] & PS2_OFFSET_b);
    PS2_data->Rc = !(PS2_Raw_Data[4] & PS2_OFFSET_c);
    PS2_data->Rd = !(PS2_Raw_Data[4] & PS2_OFFSET_d);
    if (verbose)
    {
        for (int i = 0; i < 8; i++)
        {
            printf("%x ", PS2_Raw_Data[i]);
        }
        printf("\n");
        if (PS2_data->L1)
            printf("L1 Pressed!\n");
        if (PS2_data->L2)
            printf("L2 Pressed!\n");
        if (PS2_data->R1)
            printf("R1 Pressed!\n");
        if (PS2_data->R2)
            printf("R2 Pressed!\n");
        if (PS2_data->La)
            printf("La Pressed!\n");
        if (PS2_data->Lb)
            printf("Lb Pressed!\n");
        if (PS2_data->Lc)
            printf("Lc Pressed!\n");
        if (PS2_data->Ld)
            printf("Ld Pressed!\n");
        if (PS2_data->Ra)
            printf("Ra Pressed!\n");
        if (PS2_data->Rb)
            printf("Rb Pressed!\n");
        if (PS2_data->Rc)
            printf("Rc Pressed!\n");
        if (PS2_data->Rd)
            printf("Rd Pressed!\n");
    }

    // PS2.La = PS2_Raw_Data[3]&
}
