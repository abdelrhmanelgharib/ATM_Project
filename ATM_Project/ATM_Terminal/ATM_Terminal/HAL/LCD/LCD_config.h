/**
 * @file LCD_config.h
 * @author Elgharib
 * @brief File Configuration
 * @version 0.1
 * @date 2021-07-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_




#define LCD_RS_PIN          PIN1
#define LCD_RS_PORT         PORT_A
#define LCD_E_PIN           PIN3
#define LCD_E_PORT          PORT_A

#define LCD_4BITS_PIN1      PIN4
#define LCD_4BITS_PIN2      PIN5
#define LCD_4BITS_PIN3      PIN6
#define LCD_4BITS_PIN4      PIN7


#define LCD_4BITS_PORT            PORT_A
#define LCD_8BITS_DATA_PORT       PORT_B


#define LCD_8BITS_MODE       0
#define LCD_4BITS_MODE       1

/* LCD_4BITS_MODE - LCD_8BITS_MODE */
#define LCD_CURRENT_MODE     LCD_4BITS_MODE





#endif /* LCD_CONFIG_H_ */
